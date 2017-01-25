/*
 * Particle3DAffector.h
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3DAFFECTOR_H_
#define POLA_PARTICLE3DAFFECTOR_H_

#include "pola/utils/RefBase.h"
#include "pola/graphic/particle/Particle3D.h"

namespace pola {
namespace graphic {

class Particle3DSystem;

/*
 *
 */
class Particle3DAffector : public pola::utils::RefBase {
public:
	virtual void updateAffector(Particle3D* particle, float deltaTime);

	/** Enables or disables the emitter.
	 */
	void setEnabled (bool enabled) { _isEnabled = enabled; }

	bool isEnabled(void) const { return _isEnabled; }

public:
	Particle3DAffector();
	virtual ~Particle3DAffector();

protected:
	friend class Particle3DSystem;
	Particle3DSystem* _particleSystem;
	bool _isEnabled;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3DAFFECTOR_H_ */
