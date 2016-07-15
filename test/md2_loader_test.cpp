/*
 * test.cpp
 *
 *  Created on: 2016年1月14日
 *      Author: lijing
 */

#include "pola/scene/mesh/MeshLoader.h"
#include "pola/io/FileInputStream.h"

int main(int argc, char *argv[]) {

	pola::scene::MeshLoader::loadMesh("/home/lijing/work/workspace/irrlicht-1.8.3/media/faerie.md2");
}
