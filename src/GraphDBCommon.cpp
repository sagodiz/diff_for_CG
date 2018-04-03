#include "../inc/GraphDBCommon.h"
#include "../inc/common.h"
#include "../inc/Labels.h"
#include <fstream>
#include <stdio.h>

using namespace std;

void GraphDBCommon::writeUnifiedGraphToGraphml(string filename, const vector<Record>& records, const set<pair<int, int>>& connections) {
	//ofstream graphml(Labels::PROJECT_NAME + "_" + tool + ".graphml");
	ofstream graphml(filename);
	if (!graphml.is_open())
		throw Labels::COULD_NOT_WRITE_GRAPHML;


	auto encode = [](const std::string& data) {
		std::string buffer;
		buffer.reserve(data.size());
		for (size_t pos = 0; pos != data.size(); ++pos) {
			switch (data[pos]) {
			case '&':  buffer.append("&amp;");       break;
			case '\"': buffer.append("&quot;");      break;
			case '\'': buffer.append("&apos;");      break;
			case '<':  buffer.append("&lt;");        break;
			case '>':  buffer.append("&gt;");        break;
			default:   buffer.append(&data[pos], 1); break;
			}
		}
		return buffer;
	};

	graphml << "<?xml version='1.0' encoding='utf-8'?>\n<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n<key attr.name=\"label\" attr.type=\"string\" for=\"node\" id=\"d0\"/>\n";
	graphml << "<graph edgedefault=\"directed\">\n";


	for (unsigned i = 0; i < records.size(); ++i) {
		graphml << "<node id=\"" << i << "\">" << std::endl;
		graphml << "	<data key=\"d0\">" << encode(common::getMethodById(i)) << "</data>" << std::endl;
		graphml << "</node>" << std::endl;
	}

	for (const auto edge : connections) {
		graphml << "<edge source=\"" << edge.first << "\"  target=\"" << edge.second << "\"/>" << std::endl;
	}


	graphml << "</graph></graphml>";
	graphml.close();
}


bool GraphDBCommon::convertGraphmlToJson(const std::string& in_filename, const std::string& o_filename) {
	std::string command("python convert-graph-formats.py -i graphml -o json "+ in_filename + " " + o_filename);
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe) {
		std::cerr << "Failed to popen";
		return false;
	}
	char buffer[128];
	std::string result;
	while (fgets(buffer, 128, pipe) != NULL) {
		std::cout << "Reading..." << std::endl;
		result.append(buffer);
	}
	auto returnCode = _pclose(pipe);

	std::cout << result << std::endl;
	std::cout << returnCode << std::endl;

	return true;
}