/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "utils/String.h"

using namespace pola;

int main(int argc, char *argv[]) {

	utils::String s;
	s += utils::String("hehe") + "oooo";
	s += utils::String("hehe111") + "341" + "jjj";
	s += "huhu";

	s.print();

	utils::String s1 = "heihei";
	s1.print();

	s1 = s;
	s1.print();
	return 1;
}


