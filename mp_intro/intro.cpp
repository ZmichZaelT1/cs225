#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG *input = new cs225::PNG();
  input->readFromFile(inputFile);
  cs225::PNG *output = new cs225::PNG(input->width(), input->height());

  for (unsigned x = 0; x < input->width(); x++) {
    for (unsigned y = 0; y < input->height(); y++) {
      cs225::HSLAPixel & input_pixel = input->getPixel(x, y);
      cs225::HSLAPixel & output_pixel = output->getPixel(input->width() - 1 - x, input->height() - 1 -y);

      output_pixel = input_pixel;
    }
  }

  output->writeToFile (outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel &pixel = png.getPixel(x, y);
      pixel.h = 360 * (double(x) / double(width) + double(y) / double(height));
      pixel.s = 0.7;
      pixel.l = 0.4;

      if (x >= std::floor(width * 0.25) && x <= std::floor(width * 0.75)) {
        if ((y >= std::floor(height * 0.25) && y <= std::floor(height * 0.375)) ||
            (y >= std::floor(height * 0.75) && y <= std::floor(height * 0.875))) {
          pixel.h = 11 * (1.2 + double(x) / double(width) + double(y) / double (height));
          pixel.l = 0.5;
          pixel.s = double(x) / double(width) + 0.2;
        }
      }

      if ((x >= std::floor(width * 0.375) && x <= std::floor(width * 0.625)) && 
          (y >= std::floor(height * 0.375) && y <= std::floor(height * 0.875))){
          pixel.h = 11 * (1.2 + double(x) / double(width) + double(y) / double (height));
          pixel.l = 0.5;
          pixel.s = double(x) / double(width) + 0.2;
      }
    }
  }
  return png;
}
