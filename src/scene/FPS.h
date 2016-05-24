/*
 * FPS.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef POLA_FPS_H_
#define POLA_FPS_H_

#include "utils/Times.h"

class FPS {
public:
	FPS();

	double fps();

private:
	int mTotalCount;
	int mFrameCount;
	long mFrameCountingStart;
	double mFps;
};

inline FPS::FPS() : mTotalCount(0), mFrameCount(0), mFrameCountingStart(0), mFps(0) {
}

inline double FPS::fps() {
	long now = uptimeMillis();
	++mFrameCount;
	if (mFrameCountingStart == 0) {
		mFrameCountingStart = now;
	} else if ((now - mFrameCountingStart) > 1000) {
		mFps = (double) mFrameCount
				* 1000 / (now - mFrameCountingStart);
		printf("FPS:%f\n", mFps);
		mFrameCountingStart = now;
		mFrameCount = 0;
	}
	++mTotalCount;
	return mFps;
}

#endif /* POLA_FPS_H_ */
