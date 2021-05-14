#include <stdio.h>
#include <stdlib.h>

#include "elf.h"
#include "elf_header.h"
#include "elf_ident.h"

Elf_Internal_Ehdr *get_elf_header(const unsigned char *buf) {
  static Elf_Internal_Ehdr header;

  for (int i = 0; i < EI_NIDENT; i++) {
    header.e_ident[i] = buf[i];
  }

  if (buf[EI_CLASS] == ELFCLASS64) {
    Elf64_Ehdr *elf64 = (Elf64_Ehdr *) buf;

    header.e_type = elf64->e_type;
    header.e_machine = elf64->e_machine;
    header.e_version = elf64->e_version;
    header.e_entry = elf64->e_entry;
    header.e_phoff = elf64->e_phoff;
    header.e_shoff = elf64->e_shoff;
    header.e_flags = elf64->e_flags;
    header.e_ehsize = elf64->e_ehsize;
    header.e_phentsize = elf64->e_phentsize;
    header.e_phnum = elf64->e_phnum;
    header.e_shentsize = elf64->e_shentsize;
    header.e_shnum = elf64->e_shnum;
    header.e_shstrndx = elf64->e_shstrndx;
  } else {
    Elf32_Ehdr *elf32 = (Elf32_Ehdr *) buf;

    header.e_type = elf32->e_type;
    header.e_machine = elf32->e_machine;
    header.e_version = elf32->e_version;
    header.e_entry = elf32->e_entry;
    header.e_phoff = elf32->e_phoff;
    header.e_shoff = elf32->e_shoff;
    header.e_flags = elf32->e_flags;
    header.e_ehsize = elf32->e_ehsize;
    header.e_phentsize = elf32->e_phentsize;
    header.e_phnum = elf32->e_phnum;
    header.e_shentsize = elf32->e_shentsize;
    header.e_shnum = elf32->e_shnum;
    header.e_shstrndx = elf32->e_shstrndx;
  }

  return &header;
}

void print_magic(const unsigned char *e_ident) {
  fprintf(stdout, "  Magic:  ");
  for (int i = 0; i < EI_NIDENT; i++) {
    printf(" %02x", e_ident[i]);
  }
  fprintf(stdout, "\n");
}

char *get_file_class(const unsigned char class) {
  static char buf[32];

  switch (class) {
  case ELFCLASSNONE:
    return "none";
  case ELFCLASS32:
    return "ELF32";
  case ELFCLASS64:
    return "ELF64";
  default:
    snprintf(buf, sizeof(buf), "<unknown: %u>", class);
  }

  return buf;
}

char *get_data_encoding(const unsigned char encoding) {
  static char buf[32];

  switch (encoding) {
  case ELFDATANONE:
    return "none";
  case ELFDATA2LSB:
    return "2's complement, little endian";
  case ELFDATA2MSB:
    return "2's complement, big endian";
  default:
    snprintf(buf, sizeof(buf), "<unknown: %x>", encoding);
  }

  return buf;
}

char *get_elf_version(const unsigned char version) {
  static char buf[32];

  switch (version) {
  case EV_CURRENT:
    return "1 (current)";
  case EV_NONE:
    return "0";
  default:
    snprintf(buf, sizeof(buf), "%x <unknown>", version);
  }

  return buf;
}

char *get_osabi_name(const unsigned char osabi) {
  static char buf[32];

  switch (osabi) {
  case ELFOSABI_NONE:
    return "UNIX - System V";
  case ELFOSABI_HPUX:
    return "UNIX - HP-UX";
  case ELFOSABI_NETBSD:
    return "UNIX - NetBSD";
  case ELFOSABI_GNU:
    return "UNIX - GNU";
  case ELFOSABI_SOLARIS:
    return "UNIX - Solaris";
  case ELFOSABI_AIX:
    return "UNIX - AIX";
  case ELFOSABI_IRIX:
    return "UNIX - IRIX";
  case ELFOSABI_FREEBSD:
    return "UNIX - FreeBSD";
  case ELFOSABI_TRU64:
    return "UNIX - TRU64";
  case ELFOSABI_MODESTO:
    return "Novell - Modesto";
  case ELFOSABI_OPENBSD:
    return "UNIX - OpenBSD";
  case ELFOSABI_OPENVMS:
    return "VMS - OpenVMS";
  case ELFOSABI_NSK:
    return "HP - Non-Stop Kernel";
  case ELFOSABI_AROS:
    return "AROS";
  case ELFOSABI_FENIXOS:
    return "FenixOS";
  case ELFOSABI_CLOUDABI:
    return "Nuxi - CloudABI";
  case ELFOSABI_OPENVOS:
    return "Stratus Technologies OpenVOS";
  default:
    if (osabi >= 64) {
      // TODO: machine dependent osabi
      return "";
    } else {
      snprintf(buf, sizeof(buf), "<unknown: %x>", osabi);
    }
  }

  return buf;
}

char *get_file_type(uint16_t e_type) {
  static char buf[32];

  switch (e_type) {
  case ET_NONE:
    return "NONE (None)";
  case ET_REL:
    return "REL (Relocatable file)";
  case ET_EXEC:
    return "EXEC (Executable file)";
  case ET_DYN:
    return "DYN (Shared object file)";
  case ET_CORE:
    return "CORE (Core file)";
  default:
    if (e_type >= ET_LOOS && e_type <= ET_HIOS) {
      snprintf(buf, sizeof(buf), "OS Specific: (%x)", e_type);
    } else if (e_type >= ET_LOPROC && e_type <= ET_HIPROC) {
      snprintf(buf, sizeof(buf), "Processor Specific: (%x)", e_type);
    } else {
      snprintf(buf, sizeof(buf), "<unknown>: (%x)", e_type);
    }
  }

  return buf;
}

void display_file_header(const unsigned char *buf) {
  Elf_Internal_Ehdr *header = get_elf_header(buf);

  if (check_elf_magic_num(header->e_ident)) {
    fprintf(stderr,
      "readelf: Error: Not an ELF file - it has wrong magic bytes at the starts\n");
    exit(1);
  }

  fprintf(stdout, "ELF Header:\n");
  print_magic(header->e_ident);
  fprintf(stdout,
    "  Class:                             %s\n",
    get_file_class(header->e_ident[EI_CLASS]));
  fprintf(stdout,
    "  Data:                              %s\n",
    get_data_encoding(header->e_ident[EI_DATA]));
  fprintf(stdout,
    "  Version:                           %s\n",
    get_elf_version(header->e_ident[EI_VERSION]));
  fprintf(stdout,
    "  OS/ABI:                            %s\n",
    get_osabi_name(header->e_ident[EI_OSABI]));
  fprintf(stdout,
    "  ABI Version:                       %x\n",
    header->e_ident[EI_ABIVERSION]);
  fprintf(stdout,
    "  Type:                              %s\n",
    get_file_type(header->e_type));
  // fprintf(stdout,
  //   "  Machine:                           %s\n",
  //   get_machine_name(header->e_machine));
  fprintf(stdout,
    "  Version:                           0x%X\n",
    header->e_version);
  fprintf(stdout,
    "  Entry point address:               0x%llX\n",
    header->e_entry);
  fprintf(stdout,
    "  Start of program headers:          %llu (bytes into file)\n",
    header->e_phoff);
  fprintf(stdout,
    "  Start of section headers:          %llu (bytes into file)\n",
    header->e_shoff);
}
