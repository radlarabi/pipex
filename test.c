// #include <stdio.h>
// # include <fcntl.h>
// int main(int argc, char const *argv[])
// {
//     open("abc.txt", O_CREAT | O_RDWR);
//     return 0;
// }
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
   int fd;

   fd = open("filee.txt", O_RDWR | O_CREAT);
   if (fd == -1) {
      return(-1);
   }
   /* Do something with the file */
   close(fd);
   return 0;
}
