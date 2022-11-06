file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} src/image_bmp.c src/image.c include/image_bmp.h include/transform_rotate.h src/transform_rotate.c include/file.h src/file.c include/main.h)
target_include_directories(image-transformer PRIVATE src include)
