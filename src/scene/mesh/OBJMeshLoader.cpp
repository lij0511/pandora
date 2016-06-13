/*
 * OBJMeshLoader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "log/Log.h"
#include "scene/mesh/OBJMeshLoader.h"
#include "io/BufferedReader.h"
#include "io/InputStreamReader.h"
#include <regex.h>

namespace pola {
namespace scene {

static bool regexMatch(const char* pattern, const char* string, utils::String*& matchResult, int32_t& matchCount) {
	int error;
	regex_t reg;
	static const size_t nmatch = 20;
	static regmatch_t pm[nmatch];
	error = regcomp(&reg, pattern, REG_EXTENDED);
	matchCount = 0;
	if (error != 0) {
		char ebuf[128];
		regerror(error, &reg, ebuf, sizeof(ebuf));
		LOGE("regcomp (%s) error, %s\n", pattern, ebuf);
		return false;
	}
	error = regexec(&reg, string, nmatch, pm, 0);
	if (error != 0) {
		char ebuf[128];
		regerror(error, &reg, ebuf, sizeof(ebuf));
		LOGE("regexec (%s) error, %s\n", string, ebuf);
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
//	BasicMesh* mesh = new BasicMesh(graphic::VertexType::TYPE_VERTEX3_TEXTURE_NORMAL);

	io::InputStreamReader isReader(is);
	io::BufferedReader reader(&isReader);

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
				if (regexMatch("^f\\s+(-?[0-9]+)\\s+(-?[0-9]+)\\s+(-?[0-9]+)(\\s+-?[0-9]+)?$", line.characters(), matchResult, matchCount)) {
					if (matchCount == 4) {

					} else if (matchCount == 5) {

					}
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
	return nullptr;
}

} /* namespace scene */
} /* namespace pola */
