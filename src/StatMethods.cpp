#include <iostream>
#include <fstream>
#include <algorithm> 
#include <iterator>
#include <map>

#include "../inc/StatMethods.h"

using namespace std;

void makeGraphDBStat(const vector<string>& graph_ids) {
  if (graph_ids.size() == 0) {
    cerr << "No graph ids!" << endl;
  }
  else {
    for (unsigned i = 0; i < graph_ids.size() - 1; i++) {
      for (unsigned j = i + 1; j < graph_ids.size(); j++) {
        GraphDBCommon::compareInGraphDB(graph_ids[i], graph_ids[j]);
      }
    }
  }
}

void writeConnTSV(set<pair<int, int>> connections, string name) {

  ofstream TSV(common::produceFileNamePrefix() + name + "connections.tsv");

  if (!TSV.is_open())
    throw Labels::COULD_NOT_WRITE_TSV;

  TSV << "caller->callee" << "\t" << name << endl;

  for (pair<int, int> it : connections) {

    TSV << "(" << it.first << ")" << common::getMethodById(it.first) << "->(" << it.second << ")" << common::getMethodById(it.second) << "\t" << name << endl;
    //TSV << it.first << "->" << it.second << "\t" << name << endl;
  }
}

void writeTSV(vector<Record> records, string name, string tool) {

  ofstream TSV(common::produceFileNamePrefix() + tool + "loadedMethods.tsv");

  if (!TSV.is_open())
    throw Labels::COULD_NOT_WRITE_TSV;

  TSV << "name" << "\t" << "transformed-rep." << "\t" << "tool.rep" << endl;

  for (unsigned i = 0; i < records.size(); i++) {

    TSV << name << "\t";// << records[i] << "\t"; it was the transformed rep, but from this point we use IDs since non equal transformed reps could be equal.
    //get the id.
    unsigned id = -1;
    
    for ( unsigned j = 0; j < common::storedIds.size(); j++ ) {
    
      if ( common::storedIds[j] == records[i] ) {
        
        id = j;
        break;
      }
    }
    TSV << id << "\t";
    
    TSV << records[i].getSameMethods().at(0).first + records[i].getSecondaryRepresentation() << endl; 
  }
}

std::pair<std::set<int>, std::set<int>> getInOutEdges(int id, const set<pair<int, int>>& compareSet, std::map<int, std::pair<std::set<int>, std::set<int>>>& allInOuts) {
	auto it = allInOuts.find(id);
	if (it != allInOuts.end()) {
		return it->second;
	}
	std::set<int> outs, ins;
	for (auto edge : compareSet) {
		if (edge.first == id) {
			outs.insert(edge.second);
		}
		if (edge.second == id) {
			ins.insert(id);
		}
	}
	auto result = std::make_pair(ins, outs);
	
	allInOuts[id] = result;

	return result;
}


void transformInputGraph(const std::set<std::pair<int, int>>& compareSet, Named * loader, const std::vector<Record>& r) {
	ofstream transformed(common::produceFileNamePrefix() + loader->getName() + ".transformed");
	ofstream cheatsheet(common::produceFileNamePrefix() + loader->getName() + ".transformed_cheatsheet");
	transformed << r.size() << endl;
	cheatsheet << r.size() << endl;
	std::map<int, int> idMapper;
	for (int i = 0; i < r.size(); ++i) {
		transformed << "1" << endl;
		int id = common::getIdForMethod(r[i]);
		idMapper[id] = i;
		try {
			cheatsheet << id << " " << (common::storedIds[id].getOriginalNames().at(loader->getName())) << endl;
		}
		catch (...) {
			std::cout << "bdfh" << std::endl;
		}
	}
	for (auto edge : compareSet) {
		transformed << idMapper[edge.first] << " " << idMapper[edge.second] << std::endl;
	}

	transformed.close();
	cheatsheet.close();
}



double jaccardForNodes(int id1, int id2, const set<pair<int, int>>& compareSet1, const set<pair<int, int>>& compareSet2, std::map<int, std::pair<std::set<int>, std::set<int>>>& allInOuts1, std::map<int, std::pair<std::set<int>, std::set<int>>>& allInOuts2) {
	std::pair<std::set<int>, std::set<int>> inOuts1 = getInOutEdges(id1, compareSet1, allInOuts1);
	std::pair<std::set<int>, std::set<int>> inOuts2 = getInOutEdges(id2, compareSet2, allInOuts2);

	auto jaccardForSets = [](std::set<int>& s1, std::set<int>& s2) -> double {
		std::vector<int> intersection;
		std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(intersection));
		if (s1.size() == 0 && s2.size() == 0) {
			return 1.0;
		}
		double divider = (double)s1.size() + (double)s2.size() - (double)intersection.size();
		if (divider == 0) { //should not be possible
			return 1.0;
		}
		return (double)intersection.size() / divider;
	};


	//std::set_union(inOuts1.first.begin(), inOuts1.first.end(), inOuts1.second.begin(), inOuts1.second.end(), std::back_inserter(s1));
	//std::set_union(inOuts2.first.begin(), inOuts2.first.end(), inOuts2.second.begin(), inOuts2.second.end(), std::back_inserter(s2));
	double inJaccard = jaccardForSets(inOuts1.first, inOuts2.first);
	double outJaccard = jaccardForSets(inOuts1.second, inOuts2.second);

	return (inJaccard + outJaccard)/2;
}

void produceJaccard(const set<pair<int, int>>& compareSet1, const set<pair<int, int>>& compareSet2, Named * l1, Named * l2, const vector<Record>& r1, const vector<Record>& r2) {
	ofstream statOut(common::produceFileNamePrefix() + l1->getName() + "-" + l2->getName() + "-jaccard.csv");
	ofstream outstanding(common::produceFileNamePrefix() + l1->getName() + "-" + l2->getName() + "-outstanding-jaccard.csv");
	ofstream lowstanding(common::produceFileNamePrefix() + l1->getName() + "-" + l2->getName() + "-verylow-jaccard.csv");
	std::pair<int,int> outstanding_counter, lowstanding_counter;
	outstanding_counter.first = outstanding_counter.second = lowstanding_counter.first = lowstanding_counter.second = 0;

	std::map<int, std::pair<std::set<int>, std::set<int>>> allInOuts1, allInOuts2;

	for (int j = 0; j < r2.size(); ++j) {
		statOut << ";" << common::getMethodById(common::getIdForMethod(r2[j]));
	}

	for (int i = 0; i < r1.size(); ++i) {
		int id1 = common::getIdForMethod(r1[i]);
		statOut << std::endl << common::getMethodById(id1);
		for (int j = 0; j < r2.size(); ++j) {
			int id2 = common::getIdForMethod(r2[j]);

			double jaccard = jaccardForNodes(id1, id2, compareSet1, compareSet2, allInOuts1, allInOuts2);

			if (jaccard >= 0.7) {
				if (r1[i] == r2[j]) {
					outstanding_counter.first++;
				}
				else {
					outstanding << common::getMethodById(id1) << "(" << id1 << ")" << " " << common::getMethodById(id2)<<"("<<id2 <<")" << ":" << jaccard  << std::endl;
					outstanding_counter.second++;
				}
			}

			if (jaccard < 0.7) {
				if (r1[i] == r2[j]) {
					lowstanding << common::getMethodById(id1) << "(" << id1 << ")" << " " << common::getMethodById(id2) << "(" << id2 << ")" << ":" << jaccard << std::endl;
					lowstanding_counter.first++;
					}
				else {
					lowstanding_counter.second++;
				}
				
			}
			
			statOut << ";" << jaccard;
		}
	}
	statOut.close();
	outstanding << "High value (>0.7) and r1 == r2: " << outstanding_counter.first << std::endl;
	outstanding << "High value (>0.7) and r1 != r2: " << outstanding_counter.second << std::endl;
	outstanding.close();
	lowstanding << "Low value (<0.7) and r1 != r2: "<<lowstanding_counter.second << std::endl;
	lowstanding << "Low value (<0.7) and r1 == r2: " << lowstanding_counter.first << std::endl;
	lowstanding.close();
}

commonCounters makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Named * l1, Named * l2, vector<Record> r1, vector<Record> r2) {

  unsigned long long commonCalls = 0;
  unsigned long long commonCallsCheck = 0;
  unsigned long long commonMethods = 0;
  unsigned long long commonMethodsCheck = 0;
  unsigned long long not_paired_first = 0;
  unsigned long long not_paired_second = 0;

  vector<Record> onlyFirst;
  vector<Record> onlySecond;

  vector<pair<int, int>> onlyFirstCall;
  vector<pair<int, int>> onlySecondCall;

  ofstream statOut(common::produceFileNamePrefix() + l1->getName() + "-" + l2->getName() + "-common-calls.txt");

  //check calls
  if (!statOut.is_open())
    throw Labels::COULD_NOT_WRITE_OUTPUT;

  for (auto it1 : compareSet1) {

    if (compareSet2.find(it1) != compareSet2.end()) {
      //found
      ++commonCalls;
    }
    else {

      onlyFirstCall.push_back(it1);
    }
  }

  for (auto it2 : compareSet2) {

    if (compareSet1.find(it2) != compareSet1.end()) {
      //found
      ++commonCallsCheck;
    }
    else {

      onlySecondCall.push_back(it2);
    }
  }

  if (commonCalls != commonCallsCheck) {
    
    cerr << "The search for common calls failed" << endl;
    cerr << l1->getName() << " " << l2->getName() << "Nums: " << commonCalls << " " << commonCallsCheck << endl;
  }

  //check the methods
  ofstream debug(l1->getName() + l2->getName() + ".debug");
  
  if ( !debug.is_open() )
    throw Labels::DEBUG_FILE_COULD_NOT_WRITE + l1->getName() + l2->getName() + ".debug";
    
    
  debug << l1->getName() << " searched in "  << l2->getName() << endl;
  
    
  
  vector<Record> firstInsecond;
  unsigned int sectionNum;
  
  if ( common::enums::methodRes::unio == common::options::resolve ) {
  
    for (unsigned i = 0; i < r1.size(); i++) {
     
      bool check = false;;
      //get every pair for a given method not only one
      for ( auto it = r2.begin(); it != r2.end(); it++ ) {

        if ( *it == r1[i] ) {
          check = true;
          ++commonMethods;
        }
      }
      if ( !check ) {

        onlyFirst.push_back(r1[i]);
        ++not_paired_first;
      }
    }
  }
  else {

    if ( common::enums::methodRes::section == common::options::resolve ) {

      for (unsigned i = 0; i < r1.size(); i++) {

        vector<Record>::iterator ehh = find(r2.begin(), r2.end(), r1[i]);
        if ( ehh != r2.end()) {
          
          ++commonMethods;
          debug << l1->getName() << " " << *ehh << " " << r1[i] << endl;
          //TODO: save the match
          firstInsecond.push_back(r1[i]);
        }
        else {
          //this method is not in the second tool's vector
          onlyFirst.push_back(r1[i]);
          ++not_paired_first;
        }
      }
    }
    else {

      for (unsigned i = 0; i < r1.size(); i++) {
        
        vector<Record>::iterator ehh = find(r2.begin(), r2.end(), r1[i]);
        if ( ehh != r2.end()) {
          
          ++commonMethods;
          debug << l1->getName() << " " << *ehh << " " << r1[i] << endl;
        }
        else {
          //this method is not in the second tool's vector
          onlyFirst.push_back(r1[i]);
          ++not_paired_first;
        }
      }
    }
  }
  
  debug << "next: " << l2->getName() << " searched in " << l1->getName() << endl;
    
  if ( common::enums::methodRes::unio == common::options::resolve ) {

    for (unsigned i = 0; i < r2.size(); i++) {
      
      bool check = false;
      for ( auto it = r1.begin(); it != r1.end(); it++ ) {

        if ( *it == r2[i] ) {
          check = true;
          ++commonMethodsCheck;
        }
      }
      if ( !check ) {

        onlySecond.push_back(r2[i]);
        ++not_paired_second;
      }
    }
  }
  else {

    if ( common::enums::methodRes::section == common::options::resolve ) {
      
      sectionNum = 0;
      
      for (unsigned i = 0; i < r2.size(); i++) {
        //TODO
        vector<Record>::iterator ahh = find(r1.begin(), r1.end(), r2[i]);
        if ( ahh != r1.end()) {

          ++commonMethodsCheck;
          debug << l2->getName() << " " << *ahh << " " << r2[i] << endl;
        }
        else {
          //this method is not in the second tool's vector
          onlySecond.push_back(r2[i]);
          ++not_paired_second;
        }
        
        vector<Record>::iterator ii = find(firstInsecond.begin(), firstInsecond.end(), r2[i]);
        if ( ii != firstInsecond.end()) {

          ++sectionNum;
        }
        
      }
    }
    else {
      
      for (unsigned i = 0; i < r2.size(); i++) {
        
        vector<Record>::iterator ahh = find(r1.begin(), r1.end(), r2[i]);
        if ( ahh != r1.end()) {

          ++commonMethodsCheck;
          debug << l2->getName() << " " << *ahh << " " << r2[i] << endl;
        }
        else {
          //this method is not in the second tool's vector
          onlySecond.push_back(r2[i]);
          ++not_paired_second;
        }
      }
    }
  }

  if ( commonMethodsCheck != commonMethods ) {
    
    cerr << "The search for common methods failed" << endl;
    cerr << l1->getName() << " " << l2->getName() << "Nums: " << commonMethods << " " << commonMethodsCheck << endl;
  }

  statOut << l1->getFilePath() << " has " << compareSet1.size() << " calls" << " and " << r1.size() << " unique methods. " << endl;
  statOut << l2->getFilePath() << " has " << compareSet2.size() << " calls" << " and " << r2.size() << " unique methods. " << endl;
  
  if ( common::enums::methodRes::nothing == common::options::resolve ) {

  statOut << "Calls:" << l1->getName() << " searched in " << l2->getName() << " " << commonCalls << ". " << l2->getName() << " searched in " << l1->getName() << " " << commonCallsCheck << " common calls" << endl;
  statOut << "Methods:" << l1->getName() << " searched in " << l2->getName() << " " << commonMethods << ". " << l2->getName() << " searched in " << l1->getName() << " " << commonMethodsCheck << " common methods." << endl;

  }
  else if ( common::enums::methodRes::unio == common::options::resolve ) {
    
  statOut << "Calls:" << l1->getName() << " and(unio) " << l2->getName() << " " << commonCalls << endl;
  statOut << "Methods:" << l1->getName() << " and(unio) " << l2->getName() << " " << commonMethods << endl;
  }
  else if ( common::enums::methodRes::section == common::options::resolve ) {
    
  statOut << "Calls:" << l1->getName() << " searched in " << l2->getName() << " " << commonCalls << ". " << l2->getName() << " searched in " << l1->getName() << " " << commonCallsCheck << " common calls" << endl;
  statOut << "Methods:" << l1->getName() << " searched in " << l2->getName() << " " << commonMethods << ". " << l2->getName() << " searched in " << l1->getName() << " " << commonMethodsCheck << " common methods." << endl;
    statOut << l1->getName() << " (section) " << l2->getName() << " " << sectionNum << endl;
  }
  //write the differences
  statOut << "Only the " << l1->getName() << " contains this/these method(s):" << endl;

  for (unsigned i = 0; i < onlyFirst.size(); i++) {

    statOut << onlyFirst[i] << endl;
  }

  statOut << "Only the " << l2->getName() << " contains this/these method(s):" << endl;

  for (unsigned i = 0; i < onlySecond.size(); i++) {

    statOut << onlySecond[i] << endl;
  }

  statOut << "Only the " << l1->getName() << " contains this/these call(s):" << endl;

  for (unsigned i = 0; i < onlyFirstCall.size(); i++) {

    statOut << onlyFirstCall[i].first << " [" << common::getMethodById(onlyFirstCall[i].first) << "] " << onlyFirstCall[i].second << " [" << common::getMethodById(onlyFirstCall[i].second) << " ]" << endl;
  }

  statOut << "Only the " << l2->getName() << " contains this/these call(s):" << endl;

  for (unsigned i = 0; i < onlySecondCall.size(); i++) {

    statOut << onlySecondCall[i].first << " [" << common::getMethodById(onlySecondCall[i].first) << "] " << onlySecondCall[i].second << " [" << common::getMethodById(onlySecondCall[i].second) << " ]" << endl;
  }

  statOut.close();

  //----------------------------------Extra info differences only in edges-----------------------------------------------------------
  if ("L_" == l1->getKind() && "L_" == l2->getKind()) {

    ofstream edgeStatOut(common::produceFileNamePrefix() + l1->getName() + "-" + l2->getName() + "edge.diff");

    if (!edgeStatOut.is_open())
      throw Labels::COULD_NOT_WRITE_OUTPUT;

    edgeStatOut << "Calls that are in " + l1->getName() + " could be but are not in " + l2->getName() << endl;

    for (unsigned i = 0; i < onlyFirstCall.size(); i++) {

      string caller, callee;
      caller = common::getMethodById(onlyFirstCall[i].first);
      callee = common::getMethodById(onlyFirstCall[i].second);
      if ((find(r2.begin(), r2.end(), caller) != r2.end()) && (find(r2.begin(), r2.end(), callee) != r2.end())) {

        edgeStatOut << caller << "->" << callee << endl;
      }
    }


    edgeStatOut << endl << "#######################################################################################################################" << endl;

    edgeStatOut << "Calls that are in " + l2->getName() + " could be but are not in " + l1->getName() << endl;

    for (unsigned i = 0; i < onlySecondCall.size(); i++) {

      string caller, callee;
      caller = common::getMethodById(onlySecondCall[i].first);
      callee = common::getMethodById(onlySecondCall[i].second);
      if ((find(r1.begin(), r1.end(), caller) != r1.end()) && (find(r1.begin(), r1.end(), callee) != r1.end())) {

        edgeStatOut << caller << "->" << callee << endl;
      }
    }

    edgeStatOut.close();
  }


  if (common::enums::methodRes::unio == common::options::resolve) {
	  return{ std::make_pair(commonMethods, 0), commonCalls, std::make_pair(not_paired_first, not_paired_second)};
  }
  else if (common::enums::methodRes::section == common::options::resolve) {
	  return{ std::make_pair(sectionNum,0), commonCalls, std::make_pair(not_paired_first, not_paired_second) };
  }
  else {
	  return{ std::make_pair(commonMethods, commonMethodsCheck), commonCalls, std::make_pair(not_paired_first, not_paired_second) };
  }

  
}
