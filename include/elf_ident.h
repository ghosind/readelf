#ifndef ELF_IDENT_H
#define ELF_IDENT_H

#define EI_MAG0       0
#define EI_MAG1       1
#define EI_MAG2       2
#define EI_MAG3       3
#define EI_CLASS      4
#define EI_DATA       5
#define EI_VERSION    6
#define EI_OSABI      7
#define EI_ABIVERSION 8
#define EI_PAD        9
#define EI_NIDENT     16

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASSNONE  0
#define ELFCLASS32    1
#define ELFCLASS64    2

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define ELFOSABI_NONE     0
#define ELFOSABI_HPUX     1
#define ELFOSABI_NETBSD   2
#define ELFOSABI_GNU      3
#define ELFOSABI_LINUX    3
#define ELFOSABI_SOLARIS  6
#define ELFOSABI_AIX      7
#define ELFOSABI_IRIX     8
#define ELFOSABI_FREEBSD  9
#define ELFOSABI_TRU64    10
#define ELFOSABI_MODESTO  11
#define ELFOSABI_OPENBSD  12
#define ELFOSABI_OPENVMS  13
#define ELFOSABI_NSK      14
#define ELFOSABI_AROS     15
#define ELFOSABI_FENIXOS  16
#define ELFOSABI_CLOUDABI 17
#define ELFOSABI_OPENVOS  18

#endif // ELF_IDENT_H
