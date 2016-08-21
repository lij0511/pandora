/*
 * test.cpp
 *
 *  Created on: 2016年1月14日
 *      Author: lijing
 */

#include "pola/scene/mesh/MeshLoader.h"
#include "pola/io/FileInputStream.h"

int main(int argc, char *argv[]) {

	pola::scene::IMesh* meshs = nullptr;
	std::vector<pola::scene::MaterialDescription> materials;
	pola::scene::MeshLoader::loadMesh("./res/faerie.md2", meshs, materials);
}
