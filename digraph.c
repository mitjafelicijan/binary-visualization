#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "helpers.c"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAP_SIZE 256

static size_t map[MAP_SIZE][MAP_SIZE] = {0};
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
	map[y][x] += 1;
  }

  float max = 0;

  for (size_t y = 0; y < MAP_SIZE; ++y) {
	for (size_t x = 0; x < MAP_SIZE; ++x) {
	  float f = 0.0f;
	  if (map[y][x] > 0) f = logf(map[y][x]);
	  if (f > max) max = f;
	}
  }

  for (size_t y = 0; y < MAP_SIZE; ++y) {
	for (size_t x = 0; x < MAP_SIZE; ++x) {
	  float t = logf(map[y][x])/max;
	  uint32_t b = t*255;
	  pixels[y][x] = 0xFF000000 | b | (b<<8) | (b<<16);
	}
  }

  if (!stbi_write_png(arg.output_file, MAP_SIZE, MAP_SIZE, 4, pixels, MAP_SIZE*sizeof(uint32_t))) {
	printf("Error writing image to file");
	return 1;
  }

  printf("Visualization for %s file %s written to %s\n", arg.type, arg.input_file, arg.output_file);

  return 0;
}
