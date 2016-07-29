/*
 * ImageDecoder.h
 *
 *  Created on: 2015年12月12日
 *      Author: lijing
 */

#ifndef POLA_IMAGEDECODER_H_
#define POLA_IMAGEDECODER_H_

#include "pola/graphic/Bitmap.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace graphic {

class ImageDecoder {
public:
	ImageDecoder();
	virtual ~ImageDecoder();

	virtual bool decode(io::InputStream* is, Bitmap*& bitmap, Bitmap::Format format = Bitmap::Format::UNKONWN) = 0;

	static ImageDecoder* Factory(io::InputStream* is);

	class Peeker {
	public:
		virtual ~Peeker() {};

		/** Return true to continue decoding, or false to indicate an error, which
			will cause the decoder to not return the image.
		*/
		virtual bool peek(const char tag[], const void* data, size_t length) = 0;
	};

	Peeker* getPeeker() const { return mPeeker; }
	Peeker* setPeeker(Peeker*);

	void disablePreMultipyAlpha() {
		mPreMultiplyAlpha = false;
	}

protected:
	Peeker* mPeeker;
	bool mPreMultiplyAlpha;
};

}
}

#endif /* POLA_IMAGEDECODER_H_ */
