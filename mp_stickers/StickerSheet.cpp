#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	index_ = 0;
    base = new Image(picture);
	images = new Image *[max_];
	x_coordinate = new unsigned[max_];
	y_coordinate = new unsigned[max_];
}

StickerSheet::~StickerSheet() {
	clear_();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		clear_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	Image ** temp_images = new Image * [index_];
	unsigned * temp_xc = new unsigned [index_];
	unsigned * temp_yc = new unsigned [index_];

	for (unsigned i = 0; i < index_; i++) {
		temp_images[i] = images[i];
		temp_xc[i] = x_coordinate[i];
		temp_yc[i] = y_coordinate[i];
	}

	delete[] images;
	delete[] x_coordinate;
	delete[] y_coordinate;
	images = new Image * [max];
	x_coordinate = new unsigned[max];
	y_coordinate = new unsigned[max];

    if (max < index_) {
		index_ = max;
    }
	for (unsigned i = 0; i < index_; i++) {
		images[i] = temp_images[i];
		x_coordinate[i] = temp_xc[i];
		y_coordinate[i] = temp_yc[i];
	}

	max_ = max;
	delete[] temp_images;
	delete[] temp_xc;
	delete[] temp_yc;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (index_ >= max_) {
        return -1;
    } else {
        images[index_] = new Image(sticker);
        x_coordinate[index_] = x;
        y_coordinate[index_] = y;
        int i = index_++;
        return i;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < index_) {
		x_coordinate[index] = x;
		y_coordinate[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index_ > max_) {
        return;
    }

	delete images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		images[i] = images[i + 1];
		x_coordinate[i] = x_coordinate[i + 1];
		y_coordinate[i] = y_coordinate[i + 1];
	}
	index_--;
}

Image * StickerSheet::getSticker(unsigned index) {
	if (index >= index_) {return NULL;}
	return images[index];
}

Image StickerSheet::render() const {
	Image output(*base);
    int output_x = output.width();
    int output_y = output.height();

	for (unsigned i = 0; i < index_; i++) {
		unsigned image_x = images[i]->width();
		unsigned image_y = images[i]->height();
        output_x = std::max((int)image_x + (int)x_coordinate[i], output_x);
        output_y = std::max((int)image_y + (int)y_coordinate[i], output_y);
        output.resize(output_x, output_y);

		for (unsigned x = 0; x < image_x; x++) {
			for (unsigned y = 0; y < image_y; y++) {
				cs225::HSLAPixel & output_pixel = output.getPixel(x + x_coordinate[i], y + y_coordinate[i]);
				cs225::HSLAPixel & image_pixel = images[i]->getPixel(x, y);
				if (image_pixel.a != 0) {
					output_pixel = image_pixel;
				}
			}
		}
	}
	return output;
}

void StickerSheet::copy_(const StickerSheet & other) {
    if (this != &other) {
        max_ = other.max_;
        index_ = other.index_;
	    base = new Image(*other.base);
	    images = new Image *[max_];
	    x_coordinate = new unsigned[max_];
	    y_coordinate = new unsigned[max_];
	    for (unsigned i = 0; i < index_; i++) {
		    images[i] = new Image();
		    *images[i] = *other.images[i];
		    x_coordinate[i] = other.x_coordinate[i];
		    y_coordinate[i] = other.y_coordinate[i];
	    }
    }
}

void StickerSheet::clear_() {
    delete base;
	delete[] x_coordinate;
	delete[] y_coordinate;
	for (unsigned i = 0; i < index_; i++) {
		delete images[i];
		images[i] = NULL;
	}
}