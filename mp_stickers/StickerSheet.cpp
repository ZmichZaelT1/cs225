#include "StickerSheet.h"

//     StickerSheet::StickerSheet (const Image &picture, unsigned max) {
//         image_array = new Image[max - 1];
//         image_array[0] = picture;

//     }

//  	StickerSheet::~StickerSheet () {
//         if (image_array != NULL) {
//             delete[] image_array;
//         }
//     }

//  	StickerSheet::StickerSheet (const StickerSheet &other) {
//         copy(other);
//     }

//     const StickerSheet & operator= (const StickerSheet &other) {
//         if (this != other) {
//             clear();
//             copy(other);
//         }
//         return *this;
//     }

//     void StickerSheet::changeMaxStickers (unsigned max) {
//         Image *copy_img_array = new Image[max];
//         for (int = 0; i < max; i++) {
//             copy_img_array[i] = image_array[i];
//         }
//         clear();
//         image_array = copy_img_array;
//     }

//     int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
//         image_array[]
//     }

//     bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {

//     }

//     void StickerSheet::removeSticker (unsigned index) {

//     }

//     Image * StickerSheet::getSticker (unsigned index) {

//     }

//     Image StickerSheet::render () const {

//     }