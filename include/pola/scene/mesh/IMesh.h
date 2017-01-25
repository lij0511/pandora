/*
 * Mesh.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_IMESH_H_
#define POLA_IMESH_H_

#include "pola/utils/RefBase.h"
#include "pola/graphic/Geometry.h"
#include "pola/graphic/math/Frustum.h"

namespace pola {
namespace scene {

class IMesh : public utils::RefBase {
public:
	struct Group {
		uint32_t start;
		uint32_t end;
		uint16_t materialId;
	};

	IMesh();
	virtual ~IMesh();

	virtual graphic::Geometry* geometry() = 0;

	void addGroup(uint32_t start, uint32_t end, uint16_t materialId);
	void addGroup(const Group& group);

	uint8_t groupCount() const;
	Group group(uint8_t index) const;

	void setMaterialId(uint16_t mId);
	uint16_t materialId() const;

	virtual bool intersectsBox(const graphic::Frustum& frustum, const graphic::mat4& transform);

protected:
	std::vector<Group> mGroups;
	uint16_t mMaterialId;
};

}
}

#endif /* POLA_IMESH_H_ */
