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
#include "pola/scene/mesh/IMesh.h"
#include "pola/utils/String.h"
#include "pola/utils/RefBase.h"

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

	class MeshInfo : public pola::utils::RefBase {
	public:
		pola::utils::sp<IMesh> mesh;
		std::vector<MaterialDescription> materials;
		std::vector<pola::utils::sp<MeshInfo>> children;
	};

	virtual ~MeshLoader() {};

	static pola::utils::sp<MeshInfo> loadMesh(const char* meshFile);
	static pola::utils::sp<MeshInfo> loadMesh(io::InputStream* is, const utils::String& type);

	virtual bool available(io::InputStream* is) = 0;
protected:
	virtual pola::utils::sp<MeshInfo> doLoadMesh(io::InputStream* is) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHLOADER_H_ */
