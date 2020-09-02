#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


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
  // TODO: Part 3

  return png;
}
