/*
 * ImageDecoderFactory.cpp
 *
 *  Created on: 2016年1月4日
 *      Author: lijing
 */

#include "pola/graphic/image/ImageDecoderFactory.h"
#include "pola/graphic/image/BMPImageDecoder.h"
#include "pola/graphic/image/JPEGImageDecoder.h"
#include "pola/graphic/image/PNGImageDecoder.h"

namespace pola {
namespace graphic {

struct ImageFactoryReg {
	image_factory factory;
	ImageFactoryReg* next;
	ImageFactoryReg() : factory(0), next(nullptr) {
	}
};

static ImageFactoryReg* head = nullptr;
static ImageFactoryReg* cur = nullptr;

void image_factory_reg(image_factory f) {
	ImageFactoryReg* r = new ImageFactoryReg;
	r->factory = f;
	if (cur) {
		cur->next = r;
	} else {
		head = r;
	}
	cur = r;
}

ImageDecoder* newDecoder(io::InputStream* is) {
	static bool reg = false;
	if (!reg) {
		BMPImageDecoder::reg();
		JPEGImageDecoder::reg();
		PNGImageDecoder::reg();
		reg = true;
	}

	 const ImageFactoryReg* curr = head;
	 ImageDecoder* decoder;
	 while (curr) {
		 decoder = curr->factory(is);
		 if (!is->rewind()) {
			 if (decoder) {
				 delete decoder;
			 }
			 return nullptr;
		 }
		 if (decoder) {
			 return decoder;
		 }
		 curr = curr->next;
	}
	return nullptr;
}

}
}
