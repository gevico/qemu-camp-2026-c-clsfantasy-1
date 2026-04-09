#include "myfile.h"

void print_elf_type(uint16_t e_type) {
    const char *type_str;
    switch (e_type) {
    case ET_NONE:
      type_str = "Unknown (ET_NONE)";
      break;
    case ET_REL:
      type_str = "Relocatable (ET_REL)";
      break;
    case ET_EXEC:
      type_str = "Executable (ET_EXEC)";
      break;
    case ET_DYN:
      type_str = "Shared Object/PIE (ET_DYN)";
      break;
    case ET_CORE:
      type_str = "Core Dump (ET_CORE)";
      break;
    default:
      if (e_type >= ET_LOOS && e_type <= ET_HIOS)
        type_str = "OS-Specific";
      else if (e_type >= ET_LOPROC && e_type <= ET_HIPROC)
        type_str = "Processor-Specific";
      else
        type_str = "Invalid";
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int __cmd_myfile(const char* filename) {
    char filepath[256];
    int fd;
    Elf64_Ehdr ehdr;

    strcpy(filepath, filename);
    fflush(stdout);
    printf("filepath: %s\n", filepath);

    fd = open(filepath, O_RDONLY);
    if (fd < 0) {
      perror(filepath);
      return 1;
    }

    ssize_t bytes_read = read(fd, &ehdr, sizeof(ehdr));
    if (bytes_read != sizeof(ehdr)) {
      perror(filepath);
      close(fd);
      return 1;
    }

    close(fd);

    print_elf_type(ehdr.e_type);
    return 0;
}