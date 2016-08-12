/*
 * Mesh.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_MESH_H_
#define POLA_MESH_H_

#include "pola/utils/RefBase.h"
#include "pola/graphic/Geometry.h"

namespace pola {
namespace scene {

class Mesh : public utils::RefBase<Mesh> {
public:
	struct Group {
		uint32_t start;
		uint32_t end;
		uint32_t materialId;
	};

	Mesh();
	virtual ~Mesh();

	virtual graphic::Geometry* geometry() = 0;

	void addGroup(uint32_t start, uint32_t end, uint32_t materialId);
	void addGroup(const Group& group);

	uint8_t groupCount() const;
	Group group(uint8_t index) const;

private:
	std::vector<Group> mGroups;
};

}
}

#endif /* POLA_MESH_H_ */
