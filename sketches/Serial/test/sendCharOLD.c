#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "termset.h"
#define BAUDRATE 9600

int main(int argc, char *argv[]){
	int fd;
	if (argc < 3) {
		printf("USAGE: %s <device> <char>\n", argv[0]);
		return -1;
	}
	struct termios oldtty, newtty;

	// Open Device
	fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < -1) {
		printf("ERROR: opening serial port\n");
		return -1;
	}

	if (termset(fd, BAUDRATE, &ttyold, &ttynew) == -1) {
		printf("ERROR: setting tty\n");
		return -1;
	}
	tcflush(fd, TCIOFLUSH);
	write(fd, argv[2], 1);
	tcdrain(fd);
	close(fd);
	return 0;
}
