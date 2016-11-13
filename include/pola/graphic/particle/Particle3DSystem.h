/*
 * Particle3DSystem.h
 *
 *  Created on: 2016年7月26日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3DSYSTEM_H_
#define POLA_PARTICLE3DSYSTEM_H_

#include "pola/graphic/particle/Particle3D.h"
#include "pola/graphic/particle/Particle3DEmitter.h"
#include "pola/graphic/particle/Particle3DAffector.h"
#include "pola/graphic/particle/Particle3DRender.h"

#include <list>

namespace pola {
namespace graphic {

template<typename T>
class DataPool
{
public:
    typedef typename std::list<T*> PoolList;
    typedef typename std::list<T*>::iterator PoolIterator;

    DataPool(){};
    ~DataPool(){};

    T* createData(){
        if (_locked.empty()) return nullptr;
        T* p = _locked.front();
        //_released.push_back(p);
        //_locked.erase(_locked.begin());
        _released.splice(_released.end(), _locked, _locked.begin());
        return p;
    };

    void lockLatestData(){
        _locked.push_back(*_releasedIter);
        _releasedIter = _released.erase(_releasedIter);
        if (_releasedIter != _released.begin() && _releasedIter != _released.end())
        {
            --_releasedIter;
        }
    };

    void lockData(T *data){
        PoolIterator tempIter = _releasedIter;
        T *ptr = getFirst();
        while (ptr)
        {
            if (ptr == data) break;
            ptr = getNext();
        }
        if (ptr)
            lockLatestData();
        _releasedIter = tempIter;
    }

    void lockAllDatas(){
        _locked.splice(_locked.end(), _released);
        //_locked.insert(_locked.end(), _released.begin(), _released.end());
        //_released.clear();
        _releasedIter = _released.begin();
    };

    T* getFirst(){
        _releasedIter = _released.begin();
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    T* getNext(){
        if (_releasedIter == _released.end()) return nullptr;
        ++_releasedIter;
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    const PoolList& getActiveDataList() const { return _released; };
    const PoolList& getUnActiveDataList() const { return _locked; };

    void addData(T* data){
        _locked.push_back(data);
    };

    bool empty() const { return _released.empty(); };

    void removeAllDatas(){
        lockAllDatas();
        for (auto iter : _locked){
            delete iter;
        }
        _locked.clear();
    };

private:

    PoolIterator _releasedIter;
    PoolList _released;
    PoolList _locked;
};

typedef DataPool<Particle3D> ParticlePool;

/*
 *
 */
class Particle3DSystem {
public:
	enum class State {
		STOP,
		RUNNING,
		PAUSE,
	};

	Particle3DSystem();
	virtual ~Particle3DSystem();

	/**
	 * override function
	 */
	virtual void setBlendFunc(const BlendFunc &blendFunc) override;

	/**
	 * override function
	 */
	virtual const BlendFunc &getBlendFunc() const override;

	/**
	 * set emitter for particle system, can set your own particle emitter
	 */
	void setEmitter(Particle3DEmitter* emitter);
	/**
	 * set particle render, can set your own particle render
	 */
	void setRender(Particle3DRender* render);
	/**
	* return particle render
	*/
	Particle3DRender* getRender(){ return _render; }
	/**
	 * add particle affector
	 */
	void addAffector(Particle3DAffector* affector);

	/**
	 * remove affector by index
	 */
	void removeAffector(int index);

	/**
	 * remove all particle affector
	 */
	void removeAllAffector();

	/**
	 * get particle quota
	 */
	unsigned int getParticleQuota() const;
	/**
	 * set particle quota
	 */
	void setParticleQuota(unsigned int quota);

	/**
	 * get particle affector by index
	 */
	Particle3DAffector* getAffector(int index);

	/**
	 * get particle pool
	 */
	const ParticlePool& getParticlePool()
	{
		return  _particlePool;
	}

	/**
	 * get alive particles count
	 */
	virtual int getAliveParticleCount() const
	{
		return 0;
	}

	/**
	 * get particle playing state
	 */
	State getState() const { return _state; }

	bool isKeepLocal(void) const { return _keepLocal; }
	void setKeepLocal(bool keepLocal);

	 /**
	  *Enables or disables the system.
	  */
	void setEnabled (bool enabled);

	/**
	 * is enabled
	 */
	bool isEnabled(void) const { return _isEnabled; }

protected:
	State                            _state;
	Particle3DEmitter*               _emitter;
	std::vector<Particle3DAffector*> _affectors;
	Particle3DRender*                _render;

	//particles
	ParticlePool                     _particlePool;
	int                              _aliveParticlesCnt;
	unsigned int                     _particleQuota;

	BlendFunc                        _blend;

	bool _keepLocal;
	bool _isEnabled;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3DSYSTEM_H_ */
