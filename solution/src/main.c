#include <err.h>
#include <stdlib.h>
#include "file.h"
#include "image_bmp.h"
#include "transform_rotate.h"

int main( int argc, char** argv ) {
    if (argc > 3) {
        err(EXIT_FAILURE, "Too many arguments.");
    }
    if (argc < 3) {
        err(EXIT_FAILURE, "Not enough arguments.");
    }

    FILE* in = NULL;
    FILE* out = NULL;
    enum file_open_status open_status;
    open_status = file_open(&in, argv[1], "rb");
    if (open_status != FL_OPEN_OK) {
        err(EXIT_FAILURE, "Source in opening error.");
    }
    open_status = file_open(&out, argv[2], "wb");
    if (open_status != FL_OPEN_OK) {
        err(EXIT_FAILURE, "Source in opening error.");
    }

    struct image img;
    struct image new_img;
    from_bmp(in, &img);
    new_img = rotate(img);
    to_bmp(out, &new_img);

    image_destroy(img);
    image_destroy(new_img);

    enum file_close_status close_status;
    close_status = file_close(in);
    if (close_status) {
        err(EXIT_FAILURE, "Error occurred when closing input file");
    }
    close_status = file_close(out);
    if (close_status) {
        err(EXIT_FAILURE, "Error occurred when closing output file");
    }
    printf("Successfully created file.");
    return 0;
}
