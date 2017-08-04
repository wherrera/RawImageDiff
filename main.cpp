/*
	Author: william herrera
	github: https://github.com/wherrera
*/

#include <cstdio>
#include <iostream>
#include <fstream>

#include "Image.h"

using namespace std;

int main(int count, char *args[])
{
	printf("RawImageDiff");

	printf("\ncount: %d", count);

	for (int i = 0; i < count; i++) {
		printf("\narg: %s", args[i]);
	}

	if (count < 3) {
		printf("\nRawImageDiff.exe <file1.raw> <file2.raw>");
		printf("\nSupported Formats:");
		printf("\n1. raw interleaved RGB 8 bits per channel.");
		return -1;
	}

	Image *img1 = new Image();

	img1->load(args[1]);

	Image *img2 = new Image();

	img2->load(args[2]);

	Image *save = Image::generate(img1->size());	

	for (int i = 0; i < img1->size(); i += 3)
	{
		int pixel1 = img1->get(i);
		int pixel2 = img2->get(i);

		save->set(i, pixel2-pixel1 );

		if (pixel2 - pixel1 != 0)
		{
			printf("\npixel: %d,%d -> %d", pixel1, pixel2, pixel2 - pixel1);
		}
	}

	save->save("result.raw");

	printf("\ndone.");

	return 0;
}