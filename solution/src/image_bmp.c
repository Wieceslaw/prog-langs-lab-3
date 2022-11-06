//
// Created by wieceslaw on 06.11.22.
//

#include "image_bmp.h"

#define ZERO 0
#define OFFSET 54
#define SIGNATURE 0x4D42
#define SIZE 40
#define PLANES 1
#define BIT_COUNT 24

struct bmp_header bmp_header_initialize(uint64_t width, uint64_t height) {
    uint64_t img_size = width * height * sizeof(struct pixel);
    uint64_t file_size = img_size + OFFSET;
    return (struct bmp_header) {
            .bfType = SIGNATURE,
            .bfileSize = file_size,
            .bfReserved = ZERO,
            .bOffBits = OFFSET,
            .biSize = SIZE,
            .biWidth = width,
            .biHeight = height,
            .biPlanes = PLANES,
            .biBitCount = BIT_COUNT,
            .biCompression = ZERO,
            .biSizeImage = img_size,
            .biXPelsPerMeter = ZERO,
            .biYPelsPerMeter = ZERO,
            .biClrUsed = ZERO,
            .biClrImportant = ZERO
    };
}

enum write_status to_bmp(FILE* out, struct image const* img) {
    // todo add checks
    struct bmp_header header = bmp_header_initialize(img->width, img->height);
    size_t written;
    written = fwrite(&header, sizeof(struct bmp_header), 1, out);
    if (written != 1) {
        return WRITE_ERROR;
    }
    uint64_t byte_width = img->width * sizeof(struct pixel);
    uint8_t padding = 0;
    if (byte_width % 4 != 0) {
        padding = ((byte_width / 4) * 4) + 4 - byte_width;
    }
    for (uint64_t y = 0; y < img->height; y++) {
        // write real pixels
        written = fwrite(img->data + y * img->width, sizeof(struct pixel), img->width, out);
        if (written != img->width) {
            return WRITE_ERROR;
        }
        // skip padding
        fseek(out, padding, SEEK_CUR);
    }
    return WRITE_OK;
}

enum read_status from_bmp(FILE* in, struct image* img) {
    // todo: add checks
    struct bmp_header header;
    fread(&header, sizeof(struct bmp_header), 1, in);
    uint64_t width = header.biWidth;
    uint64_t height = header.biHeight;
    *img = image_initialize(width, height);
    uint64_t byte_width = width * sizeof(struct pixel);
    uint8_t padding = 0;
    if (byte_width % 4 != 0) {
        padding = ((byte_width / 4) * 4) + 4 - byte_width;
    }
    for (uint64_t y = 0; y < height; y++) {
        fread(img->data + y * width, byte_width, 1, in);
        fseek(in, padding, SEEK_CUR);
    }
    return 0; // todo
}

