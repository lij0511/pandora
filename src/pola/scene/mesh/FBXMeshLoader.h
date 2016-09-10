/*
 * FBXMeshLoader.h
 *
 *  Created on: 2016年8月17日
 *      Author: lijing
 */

#ifndef POLA_FBXMESHLOADER_H_
#define POLA_FBXMESHLOADER_H_

#include "pola/scene/mesh/MeshLoader.h"

namespace pola {
namespace scene {

/*
 *
 */
class FBXMeshLoader: public MeshLoader {
public:
	FBXMeshLoader();
	virtual ~FBXMeshLoader();

	protected:
		virtual bool available(io::InputStream* is);
		virtual pola::utils::sp<MeshLoader::MeshInfo> doLoadMesh(io::InputStream* is);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_FBXMESHLOADER_H_ */
