#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image a;
  a.readFromFile("a1.png");
  Image b;
  b.readFromFile("b1.png");

  Image base;
  base.readFromFile("base.png");

  StickerSheet my (base, 4);
  my.addSticker(a, 0, 0);
  my.addSticker(b, 10, 0);


  Image output = my.render();
  output.writeToFile("output.png");

  return 0;
}
