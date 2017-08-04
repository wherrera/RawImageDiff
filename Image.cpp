
/*
	Author: william herrera
	github: https://github.com/wherrera
*/

#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

#include "Image.h"

Image* Image::generate(int size) {
	Image* img = new Image();
	img->_size = size;
	img->_data = new char[size];
	return img;
}

int Image::get(int index)
{	
	if (_type == IMAGE_TYPE::RAW8_RGB)
	{
		return	(int)(this->_data[index]&0xff) |
			(int)(this->_data[index + 1]&0xff) << 8 |
			(int)(this->_data[index + 2]&0xff) << 16;
	}
	return 0;
}

void Image::set(int index, int color) {
	if (_type == IMAGE_TYPE::RAW8_RGB)
	{
		this->_data[index+0] = color & 0xff;
		this->_data[index+1] = (color>>8) & 0xff;
		this->_data[index+2] = (color>>16) & 0xff;
	}
}

IMAGE_TYPE Image::type() {
	return this->_type;
}

int Image::size() {
	return this->_size;
}

bool Image::save(char *path) {
	ofstream file;
	file.open(path,ios::binary | ios::out);
	if (!file.is_open())
		return false;
	file.write((char*)this->_data, this->_size);
	file.close();
	return true;
}

bool Image::load(char *path) {
	ifstream infile;
	infile.open(path,ios::binary | ios::in | ios::ate);

	if (!infile.is_open())
		return false;
	
	int size = infile.tellg();
	printf("file size: %d", size);
	char* buffer = new char[size];
	
	infile.seekg(0,ios::beg);
	infile.read(buffer, size);
	infile.close();

	this->_size = size;
	this->_data = buffer;

	return true;
}