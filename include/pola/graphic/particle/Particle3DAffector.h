/*
 * Particle3DAffector.h
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3DAFFECTOR_H_
#define POLA_PARTICLE3DAFFECTOR_H_

namespace pola {
namespace graphic {

class Particle3DSystem;

/*
 *
 */
class Particle3DAffector {
public:
	/** Enables or disables the emitter.
	 */
	void setEnabled (bool enabled) { _isEnabled = enabled; }

	bool isEnabled(void) const { return _isEnabled; }

protected:
	Particle3DAffector();
	virtual ~Particle3DAffector();

protected:
	Particle3DSystem* _particleSystem;
	bool _isEnabled;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3DAFFECTOR_H_ */
