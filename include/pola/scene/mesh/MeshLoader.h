/*
 * MeshLoader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_MESHLOADER_H_
#define POLA_MESHLOADER_H_

#include "pola/io/InputStream.h"
#include "pola/graphic/Color.h"
#include "pola/scene/mesh/Mesh.h"
#include "pola/utils/String.h"

#include <vector>
#include <string>

namespace pola {
namespace scene {

struct MaterialDescription {
	graphic::FColor4 ambient;
	graphic::FColor4 diffuse;
	graphic::FColor4 specular;
	graphic::FColor4 emissive;
	float shininess;
	std::string texture;
};

class MeshLoader {
public:
	virtual ~MeshLoader() {};

	static bool loadMesh(const char* meshFile, Mesh*& meshes, std::vector<MaterialDescription>& materials);
	static bool loadMesh(io::InputStream* is, const utils::String& type, Mesh*& meshes, std::vector<MaterialDescription>& materials);

	virtual bool available(io::InputStream* is) = 0;
protected:
	virtual bool doLoadMesh(io::InputStream* is, Mesh*& meshes, std::vector<MaterialDescription>& materials) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHLOADER_H_ */
