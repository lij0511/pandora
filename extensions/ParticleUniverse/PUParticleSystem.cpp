/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PUParticleSystem.h"
#include "PUScriptCompiler.h"
#include "PUTranslateManager.h"

#include <algorithm>

namespace pola {
namespace graphic {

void convertToUnixStylePath( std::string &path )
{
#ifdef WIN32
    for (auto &iter : path){
        if (iter == '\\') iter = '/';
    }
#endif
}

PUParticleSystem::PUParticleSystem() {
}

PUParticleSystem::~PUParticleSystem() {
}

PUParticleSystem* PUParticleSystem::create() {
	return new PUParticleSystem;
}

PUParticleSystem* PUParticleSystem::create(const std::string& file) {
	return nullptr;
}

bool PUParticleSystem::initSystem(const std::string &filePath) {
	bool isFirstCompile = true;
	auto list = PUScriptCompiler::Instance()->compile(filePath, isFirstCompile);
	if (list == nullptr || list->empty()) return false;
	PUTranslateManager::Instance()->translateParticleSystem(this, list);
	//std::string  data = FileUtils::getInstance()->getStringFromFile(filePath);
	return true;
}

bool PUParticleSystem::initWithFilePath( const std::string &filePath )
{
    std::string fullPath = filePath;//FileUtils::getInstance()->fullPathForFilename(filePath);
    convertToUnixStylePath(fullPath);
    std::string::size_type pos = fullPath.find_last_of("/");
    std::string materialFolder = "materials";
    if (pos != std::string::npos){
        std::string temp = fullPath.substr(0, pos);
        pos = temp.find_last_of("/");
        if (pos != std::string::npos){
            materialFolder = temp.substr(0, pos + 1) + materialFolder;
        }
    }
    static std::vector<std::string> loadedFolder;
    if (std::find(loadedFolder.begin(), loadedFolder.end(), materialFolder) == loadedFolder.end())
    {
//        PUMaterialCache::Instance()->loadMaterialsFromSearchPaths(materialFolder);
        loadedFolder.push_back(materialFolder);
    }

    if (!initSystem(fullPath)){
        return false;
    }
    return true;
}

} /* namespace graphic */
} /* namespace pola */
