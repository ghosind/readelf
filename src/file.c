#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

off_t get_file_size(int fd) {
  struct stat buf;
  int errno_save = errno;

  if (fstat(fd, &buf) == -1) {
    perror("readelf");
    exit(errno);
  }

  errno = errno_save;
  return buf.st_size;
}

void *read_file(const char *filename) {
  int errno_save = errno;

  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("readelf");
    exit(errno);
  }

  off_t size = get_file_size(fd);
  void *buf = malloc(size + 1);
  if (read(fd, buf, size) != size) {
    perror("readelf");
    exit(errno);
  }

  close(fd);
  errno = errno_save;

  return buf;
}
