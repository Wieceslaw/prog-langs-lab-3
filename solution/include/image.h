//
// Created by wieceslaw on 06.11.22.
//

#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H


#include <malloc.h>
#include <stddef.h>
#include <stdint.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image image_initialize(uint64_t width, uint64_t height);
void image_destroy(struct image img);
struct pixel image_get(struct image img, uint64_t x, uint64_t y);
void image_set(struct image img, uint64_t x, uint64_t y, struct pixel px);


#endif //IMAGE_TRANSFORMER_IMAGE_H
