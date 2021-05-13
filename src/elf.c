#include "elf.h"
#include "elf_ident.h"

int check_elf_magic_num(const unsigned char *buf) {
  return buf[EI_MAG0] != ELFMAG0 ||
    buf[EI_MAG1] != ELFMAG1 ||
    buf[EI_MAG2] != ELFMAG2 ||
    buf[EI_MAG3] != ELFMAG3;
}
