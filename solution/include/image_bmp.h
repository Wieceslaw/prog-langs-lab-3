//
// Created by wieceslaw on 06.11.22.
//

#ifndef IMAGE_TRANSFORMER_IMAGE_BMP_H
#define IMAGE_TRANSFORMER_IMAGE_BMP_H

#include "image.h"
#include <bits/types/FILE.h>
#include <malloc.h>
#include <stdio.h>

/*  header  */
struct __attribute__((packed)) bmp_header
{
    uint16_t bfType; // BM 0x4D42
    uint32_t bfileSize; // header + n_pixels * sizeof(struct pixel)
    uint32_t bfReserved; // 0
    uint32_t bOffBits; // 54
    uint32_t biSize; // 40
    uint32_t biWidth; // w
    uint32_t biHeight; // h
    uint16_t biPlanes; // 1
    uint16_t biBitCount; // 24
    uint32_t biCompression; // 0
    uint32_t biSizeImage; // n_pixels * sizeof(struct pixel)
    uint32_t biXPelsPerMeter; // 0
    uint32_t biYPelsPerMeter; // 0
    uint32_t biClrUsed; // 0
    uint32_t biClrImportant; // 0
};

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* other error codes  */
};

enum read_status from_bmp(FILE* in, struct image* img);

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* other error codes  */
};

enum write_status to_bmp(FILE* out, struct image const* img);


#endif //IMAGE_TRANSFORMER_IMAGE_BMP_H
