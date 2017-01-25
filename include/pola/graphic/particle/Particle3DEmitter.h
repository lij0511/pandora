/*
 * Particle3DEmitter.h
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3DEMITTER_H_
#define POLA_PARTICLE3DEMITTER_H_

#include "pola/utils/RefBase.h"
#include "pola/graphic/particle/Particle3D.h"

namespace pola {
namespace graphic {

class Particle3DSystem;

/*
 *
 */
class Particle3DEmitter : public pola::utils::RefBase {
	friend class Particle3DSystem;
public:
	Particle3DEmitter();
	virtual ~Particle3DEmitter();

	virtual void updateEmitter(Particle3D* particle, float deltaTime);

	virtual void emit(int count) = 0;

	void setEnable(bool enable);
	bool isEnable() const;
protected:
	Particle3DSystem* _particleSystem;

	bool mEnable;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3DEMITTER_H_ */
