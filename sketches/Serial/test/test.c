#include <stdio.h> /* Standard input/output definitions */
#include <fcntl.h> /* File control definitions */
#include <unistd.h> /* UNIX standard function definitions */

int main(int argc, char * argv[]) {
	int n, fd;
	char v = 'Y';
	char * ptrV = &v;
	fd = open("/dev/cu.usbmodem14101", O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1) {} /* ERROR */
 	n = write(fd, ptrV, 1);
	close(fd);
	return 0;
}
