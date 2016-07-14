/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "utils/Times.h"
#include "io/FileInputStream.h"
#include "io/BufferedReader.h"
#include "io/InputStreamReader.h"

using namespace pola;

int main(int argc, char *argv[]) {

	io::FileInputStream file("/home/lijing/下载/无法进入数字电视.txt");
	io::InputStreamReader isreader(&file);
	io::BufferedReader reader(&isreader);

	printf("begin %lu\n", uptimeMillis());
	utils::String line;
	while(reader.readLine(line)) {
//		line.print();
	}
	printf("end %lu\n", uptimeMillis());



	return 1;
}


