#include <iostream>
#include <fstream>

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

  ofstream TSV(Labels::PROJECT_NAME + name + "connections.tsv");

  if (!TSV.is_open())
    throw Labels::COULD_NOT_WRITE_TSV;

  TSV << "caller->callee" << "\t" << name << endl;

  for (pair<int, int> it : connections) {

    TSV << "(" << it.first << ")" << common::getMethodById(it.first) << "->(" << it.second << ")" << common::getMethodById(it.second) << "\t" << name << endl;
  }
}

void writeTSV(vector<Record> records, string name, string tool) {

  ofstream TSV(Labels::PROJECT_NAME + tool + "loadedMethods.tsv");

  if (!TSV.is_open())
    throw Labels::COULD_NOT_WRITE_TSV;

  TSV << "name" << "\t" << "transformed-rep." << "\t" << "tool.rep" << endl;

  for (unsigned i = 0; i < records.size(); i++) {

    TSV << name << "\t" << records[i] << "\t";

    TSV << records[i].getSameMethods().at(0).first + records[i].getSecondaryRepresentation() << endl;
  }
}

pair<unsigned long long, unsigned long long> makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Named * l1, Named * l2, vector<Record> r1, vector<Record> r2) {

  unsigned long long commonCalls = 0;
  unsigned long long commonCallsCheck = 0;
  unsigned long long commonMethods = 0;
  unsigned long long commonMethodsCheck = 0;

  vector<Record> onlyFirst;
  vector<Record> onlySecond;

  vector<pair<int, int>> onlyFirstCall;
  vector<pair<int, int>> onlySecondCall;

  ofstream statOut(Labels::PROJECT_NAME + l1->getName() + "-" + l2->getName() + "-common-calls.txt");

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
  cout << "#####################\n\n";
  for (unsigned i = 0; i < r1.size(); i++) {
    vector<Record>::iterator ehh = find(r2.begin(), r2.end(), r1[i]);
    if ( ehh != r2.end()) {

      ++commonMethods;
      cout << l1->getName() << " " << *ehh << " " << r1[i] << endl;
    }
    else {
      //this method is not in the second tool's vector
      onlyFirst.push_back(r1[i]);
    }
  }
  cout << "??" << endl;
  for (unsigned i = 0; i < r2.size(); i++) {
    vector<Record>::iterator ahh = find(r1.begin(), r1.end(), r2[i]);
    if ( ahh != r1.end()) {

      ++commonMethodsCheck;
      cout << l2->getName() << " " << *ahh << " " << r2[i] << endl;
    }
    else {
      //this method is not in the second tool's vector
      onlySecond.push_back(r2[i]);
    }
  }

  if (commonMethodsCheck != commonMethods) {
    cout << "The search for common methods failed" << endl;
    cout << l1->getName() << " " << l2->getName() << "Nums: " << commonMethods << " " << commonMethodsCheck << endl;
  }

  statOut << l1->getFilePath() << " has " << compareSet1.size() << " calls" << " and " << r1.size() << " unique methods. " << endl;
  statOut << l2->getFilePath() << " has " << compareSet2.size() << " calls" << " and " << r2.size() << " unique methods. " << endl;
  statOut << commonCalls << " common calls and " << commonMethods << " common methods." << endl;

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

    ofstream edgeStatOut(Labels::PROJECT_NAME + l1->getName() + "-" + l2->getName() + "edge.diff");

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

  return std::make_pair(commonMethods, commonCalls);
}
