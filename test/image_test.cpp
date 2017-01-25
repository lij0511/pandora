/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "pola/utils/Times.h"
#include "pola/utils/String.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../include/pola/graphic/ImageFactory.h"

using namespace pola;

int main(int argc, char *argv[]) {

	graphic::Image* b = graphic::ImageFactory::decodeFile("/home/lijing/work/cyclone/src/screensaver/screensaver1.jpg");
//	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("/home/lijing/work/workspace/irrlicht-1.8.3/media/007shot.jpg");
//	printf("%p\n", b);
//	return 1;
	printf("curentTime=%lu\n", uptimeMillis());

	/*utils::String dir("/home/lijing/work/workspace/irrlicht-1.8.3/media/");
	DIR* dp = opendir(dir.characters());
	if (!dp) {
		LOGE("opendir failed, dir=%s\n", dir.characters());
		return 1;
	}
	dirent* dirent;
	while ((dirent = ::readdir(dp)) != NULL) {
		utils::String str(dir);
		if (!str.endsWith("/") && !str.endsWith("\\"))
			str += "/";
		str += dirent->d_name;
		struct stat s;
		if (0 == stat(str.characters(), &s)) {
			if (s.st_mode & S_IFDIR) {
				utils::String f(dirent->d_name);
				if (!f.startsWith(".")) {
					load_directory_fonts(str);
				} else {
					LOGD("dir(%s) file(%s) start with '.', ignore.\n", dir.c_str(), f.c_str());
				}
			} else if (!(s.st_mode & S_IFDIR)) {
				utils::String f(dirent->d_name);
				if (!f.startsWith(".") && f.lower().endsWith(".jpg")) {
					LOGD("dir=%s, file=%s\n", dir.characters(), dirent->d_name);
					b = graphic::BitmapFactory::decodeFile(str.characters());
					printf("%p, file(%s)\n", b, f.characters());
				}
			}
		}
	}
	closedir(dp);*/
	graphic::Image* c = nullptr;
	if (b->scale(c, 1.f, 0.5f)) {
		printf("bw=%u, bh=%u\n", b->getWidth(), b->getHeight());
		printf("cw=%u, ch=%u\n", c->getWidth(), c->getHeight());
	}


	printf("curentTime=%lu\n", uptimeMillis());
}


