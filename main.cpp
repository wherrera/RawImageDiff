/*
	Author: william herrera
	github: https://github.com/wherrera
*/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>

#include "Image.h"

using namespace std;

#define NUM_WORKERS 4
#define USE_THREADS true

void run(int start, int end, Image *img1, Image *img2, Image *output)
{
	printf("\nStarting chunk: (%d,%d)",start,end);

	for (int i = start; i < end; i += 3)
	{
		int pixel1 = img1->get(i);
		int pixel2 = img2->get(i);

		output->set(i, pixel2 - pixel1);

		if (pixel2 - pixel1 != 0)
		{
			//printf("\npixel: %d,%d -> %d", pixel1, pixel2, pixel2 - pixel1);
		}
	}
}


int main(int count, char *args[])
{
	printf("RawImageDiff v1.0");

	printf("\nNUM_WORKERS: %d", NUM_WORKERS);

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

	if (img1->size() != img2->size()) {
		printf("\nerror: images must be of equal size.");
		return -1;
	}

	Image *output = Image::generate(img1->size());

	int num_pixels = img1->size() / img1->channels();
	int chunk_size = num_pixels / NUM_WORKERS;
	int remainder = num_pixels % NUM_WORKERS;

	std::thread *workers = new std::thread[NUM_WORKERS];

	clock_t start_tm = clock();

	for (int i = 0; i < NUM_WORKERS; i++)
	{
		int start_pixel = i * chunk_size;
		int end_pixel = start_pixel + chunk_size;

		if (i == NUM_WORKERS - 1) {
			end_pixel += remainder;
		}

		if (USE_THREADS) {
			workers[i] = std::thread(run, start_pixel * img1->channels(), end_pixel * img1->channels(), img1, img2, output);
		}
		else {
			run(start_pixel * img1->channels(), end_pixel * img1->channels(), img1, img2, output);
		}
	}

	if (USE_THREADS) {
		for (int i = 0; i < NUM_WORKERS; i++)
		{
			workers[i].join();
		}
	}

	output->save("result.raw");

	clock_t tm = clock() - start_tm;

	printf("\ncompleted in: %f seconds", ((float)tm)/CLOCKS_PER_SEC );

	return 0;
}