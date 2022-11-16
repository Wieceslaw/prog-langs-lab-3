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

static struct bmp_header bmp_header_initialize(uint64_t width, uint64_t height) {
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

static uint8_t calc_padding(uint64_t width) {
    uint64_t byte_width = width * sizeof(struct pixel);
    uint8_t padding = 0;
    if (byte_width % 4 != 0) {
        padding = ((byte_width / 4) * 4) + 4 - byte_width;
    }
    return padding;
}

static enum read_status validate_header(struct bmp_header const header) {
    if (header.bfType != 0x4D42) {
        return READ_INVALID_SIGNATURE;
    }
    if (header.biBitCount != 24) {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

enum write_status to_bmp(FILE* const out, struct image const img) {
    size_t written;
    struct bmp_header header = bmp_header_initialize(img.width, img.height);
    written = fwrite(&header, sizeof(struct bmp_header), 1, out);
    if (written != 1) {
        return WRITE_ERROR;
    }
    uint8_t padding = calc_padding(img.width);
    for (uint64_t y = 0; y < img.height; y++) {
        written = fwrite(img.data + y * img.width, sizeof(struct pixel), img.width, out);
        if (written != img.width) {
            return WRITE_ERROR;
        }
        if (fseek(out, padding, SEEK_CUR) == -1) {
            return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}

enum read_status from_bmp(FILE* const in, struct image* const img) {
    struct bmp_header header = {0};
    if (!fread(&header, sizeof(struct bmp_header), 1, in)) {
        return READ_INVALID_BITS;
    }
    enum read_status result = validate_header(header);
    if (result != READ_OK) {
        return result;
    }
    uint64_t width = header.biWidth;
    uint64_t height = header.biHeight;
    *img = image_initialize(width, height);
    uint8_t padding = calc_padding(width);
    for (uint64_t y = 0; y < height; y++) {
        if (!fread(img->data + y * width, width * sizeof(struct pixel), 1, in)) {
            return READ_INVALID_BITS;
        }
        if (fseek(in, padding, SEEK_CUR) == -1) {
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}

