#include <stdio.h> /* Standard input / output definitions */
#include <fcntl.h> /* File control definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include "termset.h"

int main ( void )
{
	int fd ; /* Descriptor de archivo del puerto */
	struct termios oldtty, newtty;

 	fd = open ("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY );
 	if( fd == -1)
 	{
 		printf (" ERROR :␣no␣se␣ pudo ␣ abrir ␣el␣ dispositivo .\n");
 		return -1;
 	}
 	if(termset(fd, 9600, &oldtty, &newtty) == -1)
 	{
 		printf (" ERROR :␣no␣se␣ pudo ␣ configurar ␣el␣ TTY \n");
 		return -1;
 	}
	/*
 	tcflush (fd, TCIOFLUSH);
	for (;;)
 	{
 		write (fd , "v", 1);
 		tcdrain ( fd );
 		sleep (1);
 	}
 	*/
 	tcflush (fd, TCIOFLUSH);
 	write (fd , "v", 1);
 	tcdrain ( fd );
 	sleep (1);
 	write (fd , "v", 1);
 	tcdrain ( fd );
 	sleep (1);
	close ( fd );
 	
	return 0;
}
