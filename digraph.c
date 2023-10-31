#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAP_SIZE 256

static size_t map[MAP_SIZE][MAP_SIZE] = {0};
static uint32_t pixels[MAP_SIZE][MAP_SIZE] = {0};

typedef struct {
  unsigned char *content;
  size_t count;
} Data;

typedef struct {
  char *input_file;
  char *output_file;
  char *type;
} Arguments;

Arguments parse_arguments(int argc, char *argv[]) {
  Arguments arg = (Arguments){0};
  int c;

  while ((c = getopt(argc, argv, "t:i:o:")) != -1) {
	switch (c) {
	case 't':
	  arg.type = optarg;
	  if (strcmp(optarg, "image") != 0 && strcmp(optarg, "other") != 0) {
		fprintf(stderr, "Invalid type. Only 'image' or 'other' is supported.\n");
		exit(EXIT_FAILURE);
	  }
	  break;
	case 'i':
	  arg.input_file = optarg;
	  break;
	case 'o':
	  arg.output_file = optarg;
	  break;
	case '?':
	  if (optopt == 't' || optopt == 'i' || optopt == 'o') {
		fprintf(stderr, "Option -%c requires an argument.\n", optopt);
	  } else if (isprint(optopt)) {
		fprintf(stderr, "Unknown option `-%c'.\n", optopt);
	  } else {
		fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
	  }
	  exit(EXIT_FAILURE);
	default:
	  abort();
	}
  }

  if (arg.type == NULL || arg.input_file == NULL || arg.output_file == NULL) {
	fprintf(stderr, "Usage: %s -t type -i <input file> -o <output file>\n", argv[0]);
	exit(EXIT_FAILURE);
  }

  return arg;
}

Data read_binary_file_into_array(char* input_file) {
  FILE *file;
  size_t i;
  Data data = (Data){0};

  file = fopen(input_file, "rb");
  if (file == NULL) {
	perror("Error opening file");
	exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  data.count = ftell(file);

  data.content = (unsigned char *)malloc(data.count);
  if (data.content == NULL) {
	perror("Error allocating memory");
	fclose(file);
	exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_SET);

  if (fread(data.content, 1, data.count, file) != data.count) {
	perror("Error reading file");
	free(data.content);
	fclose(file);
	exit(EXIT_FAILURE);
  }

  fclose(file);
  return data;
}

Data read_image_file_into_array(char* input_file) {
  int width, height, channels;
  unsigned char *content = stbi_load(input_file, &width, &height, &channels, 0);
  if (content == NULL) {
	fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
	exit(EXIT_FAILURE);
  }

  Data data;
  data.content = content;
  data.count = (size_t)width * height * channels;;

  return data;
}

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
