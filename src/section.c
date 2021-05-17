#include <stdio.h>
#include <stdlib.h>

#include "elf_header.h"
#include "section.h"

Elf_Internal_Shdr *get_section_header(const unsigned char *buf,
    Elf_Internal_Ehdr *elf_header,
    int index) {
  static Elf_Internal_Shdr header;

  if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
    Elf64_Shdr *shdr =
      (Elf64_Shdr *)(buf + elf_header->e_shoff + sizeof(Elf64_Shdr) * index);

    header.sh_name = shdr->sh_name;
    header.sh_type = shdr->sh_type;
    header.sh_flags = shdr->sh_flags;
    header.sh_addr = shdr->sh_addr;
    header.sh_offset = shdr->sh_offset;
    header.sh_size = shdr->sh_size;
    header.sh_link = shdr->sh_link;
    header.sh_info = shdr->sh_info;
    header.sh_addralign = shdr->sh_addralign;
    header.sh_entsize = shdr->sh_entsize;
  } else {
    Elf32_Shdr *shdr =
      (Elf32_Shdr *)(buf + elf_header->e_shoff + sizeof(Elf32_Shdr) * index);

    header.sh_name = shdr->sh_name;
    header.sh_type = shdr->sh_type;
    header.sh_flags = shdr->sh_flags;
    header.sh_addr = shdr->sh_addr;
    header.sh_offset = shdr->sh_offset;
    header.sh_size = shdr->sh_size;
    header.sh_link = shdr->sh_link;
    header.sh_info = shdr->sh_info;
    header.sh_addralign = shdr->sh_addralign;
    header.sh_entsize = shdr->sh_entsize;
  }

  return &header;
}

char *get_section_type(uint32_t sh_type) {
  static char buf[32];

  switch (sh_type) {
  case SHT_NULL:
    return "NULL";
  case SHT_PROGBITS:
    return "PROGBITS";
  case SHT_SYMTAB:
    return "SYMTAB";
  case SHT_STRTAB:
    return "STRTAB";
  case SHT_RELA:
    return "RELA";
  case SHT_HASH:
    return "HASH";
  case SHT_DYNAMIC:
    return "DYNAMIC";
  case SHT_NOTE:
    return "NOTE";
  case SHT_NOBITS:
    return "NOBITS";
  case SHT_REL:
    return "REL";
  case SHT_SHLIB:
    return "SHLIB";
  case SHT_DYNSYM:
    return "DYNSYM";
  case SHT_INIT_ARRAY:
    return "INIT_ARRAY";
  case SHT_FINI_ARRAY:
    return "FINI_ARRAY";
  case SHT_PREINIT_ARRAY:
    return "PREINIT_ARRAY";
  case SHT_GROUP:
    return "GROUP";
  case SHT_SYMTAB_SHNDX:
    return "STMTAB SECTION INDICES";
  default:
    snprintf(buf, sizeof(buf), "%08x: <unknown>, sh_type");
  }

  return buf;
}

void display_section_header(const unsigned char *buf) {
  Elf_Internal_Ehdr *elf_header = get_elf_header(buf);

  if (check_elf_magic_num(elf_header->e_ident)) {
    fprintf(stderr,
        "readelf: Error: Not an ELF file - it has wrong magic bytes at the starts\n");
    exit(1);
  }

  fprintf(stdout,
      "There are %d section headers, starting at offset 0x%x\n\n",
      elf_header->e_shnum,
      elf_header->e_shoff);
  fprintf(stdout, "Section Headers:\n");
  // Header
  fprintf(stdout,
      "  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");

  for (int i = 0; i < elf_header->e_shnum; i++) {
    Elf_Internal_Shdr *shdr = get_section_header(buf, elf_header, i);

    
    fprintf(stdout,
        "  [%2u] %-17s %-15s %08lx %06lx %06lx %02x\n",
        i,
        "", // TODO: get section name
        get_section_type(shdr->sh_type),
        shdr->sh_addr,
        shdr->sh_offset,
        shdr->sh_size,
        shdr->sh_entsize);
  }

  fprintf(stdout, "Key to Flags:\n");
  fprintf(stdout,
      "  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
  fprintf(stdout,
      "  L (link order), O (extra OS processing required), G (group), T (TLS),\n");
  fprintf(stdout,
      "  C (compressed), x (unknown), o (OS specific), E (exclude),\n");
  fprintf(stdout, "  p (processor specific)\n");
}
