/*
 * OBJMeshLoader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/scene/mesh/OBJMeshLoader.h"
#include "pola/scene/mesh/BasicMesh.h"
#include "pola/io/BufferedReader.h"
#include "pola/io/InputStreamReader.h"
#include <string>
#include <regex>
#include <iostream>
#include <regex.h>

//#define DEBUG_REGEX

namespace pola {
namespace scene {

static bool regexMatch(const char* pattern, const char* string, utils::String*& matchResult, int32_t& matchCount) {
//	std::regex reg(pattern/*, std::regex_constants::ECMAScript|std::regex_constants::optimize*/);
//	std::cmatch result;
//	bool match = std::regex_match(string, result, reg);
//	matchCount = 0;
//	if (match) {
//		matchCount = (int32_t) result.size();
//		if (matchResult) {
//			delete[] matchResult;
//			matchResult = nullptr;
//		}
//		matchResult = new utils::String[matchCount];
//		for (int x = 0; x < matchCount; x ++) {
//			if (result[x].second == result[x].first) {
//				matchResult[x] = utils::String(true);
//			} else {
//				matchResult[x] = utils::String(result[x].first, size_t(result[x].second - result[x].first));
//			}
//		}
//	}
//
//	return match;
	int error;
	regex_t reg;
	static const size_t nmatch = 20;
	static regmatch_t pm[nmatch];
	error = regcomp(&reg, pattern, REG_EXTENDED);
	matchCount = 0;
	if (error != 0) {
#ifdef DEBUG_REGEX
		char ebuf[128];
		regerror(error, &reg, ebuf, sizeof(ebuf));
		LOGE("regcomp (%s) error, %s\n", pattern, ebuf);
#endif
		regfree(&reg);
		return false;
	}
	error = regexec(&reg, string, nmatch, pm, 0);
	if (error != 0) {
#ifdef DEBUG_REGEX
		char ebuf[128];
		regerror(error, &reg, ebuf, sizeof(ebuf));
		LOGE("regexec (%s) error, %s\n", string, ebuf);
#endif
		regfree(&reg);
		return false;
	}
	for (unsigned x = 0; x < nmatch && pm[x].rm_so != -1; x ++) {
		matchCount++;
	}
	if (matchCount > 0) {
		if (matchResult) {
			delete[] matchResult;
			matchResult = nullptr;
		}
		matchResult = new utils::String[matchCount];
		for (int x = 0; x < matchCount; x ++) {
			matchResult[x] = utils::String(string + pm[x].rm_so, size_t(pm[x].rm_eo - pm[x].rm_so));
		}
	}
	regfree(&reg);
	return matchCount > 0;
}

OBJMeshLoader::OBJMeshLoader() {
}

OBJMeshLoader::~OBJMeshLoader() {
}

bool OBJMeshLoader::available(io::InputStream* is) {
	return false;
}

Mesh* OBJMeshLoader::doLoadMesh(io::InputStream* is) {
	io::InputStreamReader isReader(is);
	io::BufferedReader reader(&isReader);

	graphic::Geometry3D* geometry = new graphic::Geometry3D;
	graphic::Box3 boundingBox;

	utils::Vector<graphic::vec3> vertexBuffer;
	utils::Vector<graphic::vec2> uvBuffer;
	utils::Vector<graphic::vec3> normalBuffer;
	utils::String line;
	utils::String* matchResult = nullptr;
	int32_t matchCount = 0;
	while (reader.readLine(line)) {
		line = line.trim();
		if (line.length() == 0) {
			continue;
		}
		char firstC = line.charAt(0);
		switch (firstC) {
			case '#':
				continue;
				break;
			case 'v':
				if (line.length() > 1) {
					if (line.charAt(1) == 'n') {
						regexMatch("^vn\\s+([0-9\\.\\+-eE]+)\\s+([0-9\\.\\+-eE]+)\\s+([0-9\\.\\+-eE]+)", line.characters(), matchResult, matchCount);
						if (matchCount == 4) {
							normalBuffer.push({(float) atof(matchResult[1].characters()), (float) atof(matchResult[2].characters()), (float) atof(matchResult[3].characters())});
						}
					} else if ((line.charAt(1) == 't')) {
						regexMatch("^vt\\s+([0-9\\.\\+-eE]+)\\s+([0-9\\.\\+-eE]+)", line.characters(), matchResult, matchCount);
						if (matchCount == 3) {
							uvBuffer.push({(float) atof(matchResult[1].characters()), (float) atof(matchResult[2].characters())});
						}
					} else {
						regexMatch("^v\\s+([0-9\\.\\+-eE]+)\\s+([0-9\\.\\+-eE]+)\\s+([0-9\\.\\+-eE]+)", line.characters(), matchResult, matchCount);
						if (matchCount == 4) {
							vertexBuffer.push({(float) atof(matchResult[1].characters()), (float) atof(matchResult[2].characters()), (float) atof(matchResult[3].characters())});
						}
					}
				}
				break;
			case 'f':
				if (regexMatch("^f\\s+(-?[0-9]+)\\s+(-?[0-9]+)\\s+(-?[0-9]+)(\\s+(-?[0-9]+))?$", line.characters(), matchResult, matchCount) && matchCount == 5) {

				} else if (regexMatch("^f\\s+(-?[0-9]+)\\/\\/(-?[0-9]+)\\s+(-?[0-9]+)\\/\\/(-?[0-9]+)\\s+(-?[0-9]+)\\/\\/(-?[0-9]+)(\\s+(-?[0-9]+)\\/\\/(-?[0-9]+))?$", line.characters(), matchResult, matchCount) && matchCount >= 7) {
					int a = atoi(matchResult[1].characters());
					int b = atoi(matchResult[3].characters());
					int c = atoi(matchResult[5].characters());
					a = a > 0 ? a - 1 : a + vertexBuffer.size();
					b = b > 0 ? b - 1 : b + vertexBuffer.size();
					c = c > 0 ? c - 1 : c + vertexBuffer.size();
					geometry->addPosition(vertexBuffer[a]);
					geometry->addPosition(vertexBuffer[b]);
					geometry->addPosition(vertexBuffer[c]);

					boundingBox.expandByPoint(vertexBuffer[a]);
					boundingBox.expandByPoint(vertexBuffer[b]);
					boundingBox.expandByPoint(vertexBuffer[c]);
				} else if (regexMatch("^f\\s+(-?[0-9]+)\\/(-?[0-9]+)\\/(-?[0-9]+)\\s+(-?[0-9]+)\\/(-?[0-9]+)\\/(-?[0-9]+)\\s+(-?[0-9]+)\\/(-?[0-9]+)\\/(-?[0-9]+)(\\s+(-?[0-9]+)\\/(-?[0-9]+)\\/(-?[0-9]+))?$", line.characters(), matchResult, matchCount) && matchCount >= 10) {
					graphic::NormalTextureVertex3 vertex;
					int a = atoi(matchResult[1].characters());
					int b = atoi(matchResult[4].characters());
					int c = atoi(matchResult[7].characters());
					a = a > 0 ? a - 1 : a + vertexBuffer.size();
					b = b > 0 ? b - 1 : b + vertexBuffer.size();
					c = c > 0 ? c - 1 : c + vertexBuffer.size();
					geometry->addPosition(vertexBuffer[a]);
					geometry->addPosition(vertexBuffer[b]);
					geometry->addPosition(vertexBuffer[c]);

					boundingBox.expandByPoint(vertexBuffer[a]);
					boundingBox.expandByPoint(vertexBuffer[b]);
					boundingBox.expandByPoint(vertexBuffer[c]);
				}
				break;
			default:
				continue;
				break;
		}
	}
	if (matchResult) {
		delete[] matchResult;
		matchResult = nullptr;
	}
	geometry->setBoundingBox(boundingBox);
	return new BasicMesh(geometry);
}

} /* namespace scene */
} /* namespace pola */
