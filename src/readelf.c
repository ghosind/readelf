#include <stdio.h>
#include <stdlib.h>

#include "elf.h"
#include "file.h"
#include "readelf.h"

void print_usage(void) {
  fprintf(stdout, "Usage: readelf <option(s)> elf-file\n");
  fprintf(stdout, " Display information about the contents of ELF format files\n");
  fprintf(stdout, " Options are:\n");
  fprintf(stdout, "  -a                     Equivalent to: -h\n");
  fprintf(stdout, "  -h                     Display the ELF file header\n");
}

int parse_options_flags(int argc, char *argv[]) {
  int flags = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      continue;
    }

    if (argv[i][2] != '\0') {
      fprintf(stderr, "readelf: invalid option %s\n", argv[i]);
      print_usage();
      exit(1);
    }

    switch (argv[i][1]) {
    case 'a':
      flags |= FLAG_ELF_HEADER;
      break;
    case 'h':
      flags |= FLAG_ELF_HEADER;
      break;
    default:
      fprintf(stderr, "readelf: invalid option %s\n", argv[i]);
      print_usage();
      exit(1);
    }
  }

  return flags;
}

void read_elf_data(const char *path, int flags) {
  unsigned char *buf = (unsigned char *) read_file(path);

  if (flags & FLAG_ELF_HEADER) {
    display_file_header(buf);
  }

  free(buf);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  int flags = parse_options_flags(argc, argv);

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    read_elf_data(argv[i], flags);
  }

  return 0;
}
