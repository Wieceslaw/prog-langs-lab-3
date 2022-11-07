#include "main.h"
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
        err(EXIT_FAILURE, "Error occurred when opening input file.");
    }
    open_status = file_open(&out, argv[2], "wb");
    if (open_status != FL_OPEN_OK) {
        err(EXIT_FAILURE, "Error occurred when opening output file.");
    }

    struct image img;
    struct image new_img;
    enum read_status read_status = from_bmp(in, &img);
    if (read_status) {
        err(EXIT_FAILURE, "Error occurred when reading input file");
    }
    new_img = rotate(img);
    enum write_status write_status = to_bmp(out, &new_img);
    if (write_status) {
        err(EXIT_FAILURE, "Error occurred when writing input file");
    }

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
