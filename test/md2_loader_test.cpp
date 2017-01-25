/*
 * test.cpp
 *
 *  Created on: 2016年1月14日
 *      Author: lijing
 */

#include "pola/scene/mesh/MeshLoader.h"
#include "pola/io/FileInputStream.h"

int main(int argc, char *argv[]) {

	pola::utils::sp<pola::scene::MeshLoader::MeshInfo> result;
	result = pola::scene::MeshLoader::loadMesh("./res/faerie.md2");
}
