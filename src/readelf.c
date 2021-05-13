#include <stdlib.h>

#include "elf.h"
#include "file.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    exit(0);
  }

  unsigned char *buf = (unsigned char *) read_file(argv[1]);

  display_file_header(buf);

  free(buf);

  return 0;
}
