#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "termset.h"

int main(int argc, char *argv[])
{
  int flag = 1;
  char solicitud;
  int fd;

  fd = open(argv[2], O_RDWR | O_NOCTTY | O_NDELAY);

  if(fd == -1){
    fprintf(stderr, "ERROR: no se pudo abrir el dispositivo\n");
    return -1; 
  }
  if(termset(fd, 9600, &ttyold, &ttynew) == -1){
    fprintf(stderr, "ERROR: no se pudo configurar el TTY\n");
    return -1;
  }

  tcflush(fd, TCIOFLUSH); // DABA ERROR SI NO SE INCLUIA

	write(fd, argv[1], 1);
  tcdrain(fd);
	sleep(1);

  
	close(fd);

  return EXIT_SUCCESS;
}
