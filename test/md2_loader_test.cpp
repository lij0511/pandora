/*
 * test.cpp
 *
 *  Created on: 2016年1月14日
 *      Author: lijing
 */

#include "scene/mesh/MD2MeshLoader.h"
#include "io/FileInputStream.h"

int main(int argc, char *argv[]) {

	pola::scene::MD2MeshLoader loader;
	pola::io::FileInputStream is("/home/lijing/work/workspace/irrlicht-1.8.3/media/faerie.md2");

	loader.loadMesh(&is);
}
