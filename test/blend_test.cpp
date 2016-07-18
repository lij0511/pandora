/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include <string.h>
#include <stdio.h>
#include "pola/graphic/utils/Blend.h"

using namespace pola;

int main(int argc, char *argv[]) {
	uint32_t c = pola::graphic::blend(0xAAAAAA10, 0x11111111, pola::graphic::BlendMode::SrcOver);
	printf("%x\n", c);
	return 1;
}


