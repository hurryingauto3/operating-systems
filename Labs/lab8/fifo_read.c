#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
  int fd,retval;
  char buffer[256];
  while(1){

    fd = open("/tmp/fifo", O_RDONLY);
    retval = read(fd, buffer, sizeof(buffer));
    fflush(stdin);
    write(1, buffer, sizeof(buffer));
    printf("\n");
    close(fd);

    char buffer[256] = { 0 };

    printf("Enter a message: ");
    fgets(buffer, sizeof(buffer), stdin);
    fflush(stdin);

    retval = mkfifo("/tmp/fifo", 0666);
    fd = open("/tmp/fifo", O_WRONLY);
    write(fd, buffer, sizeof(buffer));
    close(fd);
  }
  
  
}
