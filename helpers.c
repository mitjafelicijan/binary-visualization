#include <ctype.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
