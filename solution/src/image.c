//
// Created by wieceslaw on 06.11.22.
//

#include <malloc.h>
#include "image.h"
struct image image_initialize(uint64_t width, uint64_t height) {
    struct image img = {
            .height = height,
            .width = width,
            .data = malloc(width * height * sizeof(struct pixel))
    };
    return img;
}

void image_destroy(struct image img) {
    free(img.data);
}

struct pixel image_get(struct image img, uint64_t x, uint64_t y) {
    return img.data[y * img.width + x];
}

void image_set(struct image img, uint64_t x, uint64_t y, struct pixel px) {
    img.data[y * img.width + x] = px;
}
