#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "helpers.c"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAP_SIZE 256

static size_t map[MAP_SIZE][MAP_SIZE][MAP_SIZE] = {0};
static uint32_t pixels[MAP_SIZE][MAP_SIZE] = {0};

int main(int argc, char *argv[]) {
  Arguments arg = parse_arguments(argc, argv);

  Data data;
  if (strcmp(arg.type, "image") == 0) {
    data = read_image_file_into_array(arg.input_file);
  } else if (strcmp(arg.type, "other") == 0) {
    data = read_binary_file_into_array(arg.input_file);
  } else {
    exit(EXIT_FAILURE);
  }

  memset(map, 0, sizeof(map));
  for (size_t i = 0; i < data.count; i++) {
    uint8_t x = data.content[i];
    uint8_t y = data.content[i+1];
    uint8_t z = data.content[i+2];
    map[y][x][z] += 1;
  }

  FILE *file;

  file = fopen(arg.output_file, "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for writing\n");
    return 1;
  }

  for (size_t x = 0; x < MAP_SIZE; x++) {
    for (size_t y = 0; y < MAP_SIZE; y++) {
      for (size_t z = 0; z < MAP_SIZE; z++) {
        if (map[x][y][z] > 0) {
          fprintf(file, "%ld,%ld,%ld,%ld\n", x, y, z, map[x][y][z]);
        }
      }
    }
  }

  fclose(file);

  printf("Visualization for %s file %s written to %s\n", arg.type, arg.input_file, arg.output_file);

  return 0;
}
