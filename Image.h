
/*	
	Author: william herrera
	github: https://github.com/wherrera
*/

enum IMAGE_TYPE {
	RAW8_RGB = 1
};

class Image {
private:
	IMAGE_TYPE _type = IMAGE_TYPE::RAW8_RGB;
	int _size;
	char *_data;

public:
	static Image* generate(int size);
	IMAGE_TYPE type();
	bool load(char *path);
	bool save(char *path);
	int channels();
	int get(int index);
	void set(int index, int color);
	int size();
};
