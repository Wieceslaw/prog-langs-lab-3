//
// Created by wieceslaw on 06.11.22.
//

#ifndef IMAGE_TRANSFORMER_FILE_H
#define IMAGE_TRANSFORMER_FILE_H

#include <bits/types/FILE.h>
#include <errno.h>
#include <stdio.h>

enum file_open_status {
    FL_OPEN_OK = 0,
    FL_OPEN_ERR = 1,
    FL_OPEN_NOT_FOUND
    /* other status codes */
};

enum file_open_status file_open(FILE** file, char* file_name, char* mode);

enum file_close_status {
    FL_CLOSE_OK,
    FL_CLOSE_ERR
    /* other status codes */
};

enum file_close_status file_close(FILE* file);

#endif //IMAGE_TRANSFORMER_FILE_H
