/*
 * Particle3DEmitter.h
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3DEMITTER_H_
#define POLA_PARTICLE3DEMITTER_H_

namespace pola {
namespace graphic {

/*
 *
 */
class Particle3DEmitter {
public:
	Particle3DEmitter();
	virtual ~Particle3DEmitter();

	virtual void emit(int count) = 0;

	void setEnable(bool enable);
	bool isEnable() const;
private:
	bool mEnable;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3DEMITTER_H_ */
