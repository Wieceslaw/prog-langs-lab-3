//
// Created by wieceslaw on 06.11.22.
//

#include "transform_rotate.h"

struct image rotate( struct image const source ) {
    struct image img = image_initialize(source.height, source.width);
    for (uint64_t y = 0; y < source.height; y++) {
        for (uint64_t x = 0; x < source.width; x++) {
            image_set(img, img.width - y - 1, x, image_get(source, x, y));
        }
    }
    return img;
}
