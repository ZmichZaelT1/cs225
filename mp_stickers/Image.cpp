#include "Image.h"


void Image::lighten() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
           if (pixel.l > 0.9) {
               pixel.l = 1;
           } else {
               pixel.l += 0.1;
           }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l > (1.0 - amount)) {
                pixel.l = 1;
            } else {
                pixel.l += amount;
            }
        }
    }
}

void Image::darken() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l < 0.1) {
                pixel.l = 0;
            } else {
                pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l < amount) {
                pixel.l = 0;
            } else {
                pixel.l -= amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s > 0.9) {
                pixel.s = 1;
            } else {
                pixel.s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s > (1.0 - amount)) {
                pixel.s = 1;
            } else {
                pixel.s += amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s < 0.1) {
                pixel.s = 0;
            } else {
                pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s < amount) {
                pixel.s = 0;
            } else {
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            if ((pixel.h + degrees) > 360) {
                pixel.h = int (pixel.h + degrees) % 360;
            } else {
                pixel.h += degrees;
            }
        }
    }
}

void Image::illinify() {
    const double kOrangeHue = 11;
    const double kBlueHue = 216;

    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);

            if (pixel.h > 113.5 && pixel.h < 293.5) {
                pixel.h = kBlueHue;
            } else {
                pixel.h = kOrangeHue;
            }
        }
    }
}

void Image::scale(double factor) {

}

void Image::scale(unsigned w, unsigned h) {}
