#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include "termset.h"

unsigned char menuLoop(void);
void printBits(unsigned char);

int main(int argc, char * argv[]){
	
	int fd ; /* Descriptor de archivo del puerto */
	struct termios oldtty, newtty;
	
	if(argc != 2){
		printf("Uso: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
 	
	fd = open (argv[1], O_RDWR | O_NOCTTY | O_NDELAY );
 	
	if( fd == -1){
 		printf ("El dispositivo no se ha encontrado. Intentelo nuevamente.\n");
 		exit(EXIT_FAILURE);
 	}
 	
	if(termset(fd, 9600, &oldtty, &newtty) == -1){
 		printf ("Ocurrio un error al inicializar el puerto serie. Intentelo nuevamente.\n");
 		exit(EXIT_FAILURE);
 	}
 	
	tcflush (fd, TCIOFLUSH);
	
	while(1){
		unsigned char config = menuLoop();
 		write(fd, &config, 1);
 		tcdrain(fd);
 		sleep (1);
 	}
}
/*
 * B7 = Alarma 20 seg 
 * B6 = Alarma 10 seg
 * B5 = Alarma 5 seg
 * B4 = Periodo Mensual
 * B3 = Periodo Diario
 * B2 = Modo Comparacion a Uso normal
 * B1 = Modo Comparacion a Periodo anterior
 * B0 = Modo Normal
*/
unsigned char menuLoop(void){
	unsigned char config = 0, choice;
	
	while(1){
		printf("Menu\n");
		printf("1 - Configurar Alarma\n");	
		printf("2 - Configurar Modo\n");	
		printf("3 - Configurar Periodo\n");	
		printf("4 - Confirmar\n");
		printf("5 - Salir\n");
		printf("Su eleccion: ");
		scanf("%hhu", &choice);
		switch(choice){
		
			case 1:
				printf("1 - Alarma a los 5 segundos\n");	
				printf("2 - Alarma a los 10 segundos\n");	
				printf("3 - Alarma a los 20 segundos\n");	
				printf("Su eleccion: ");
				scanf("%hhu", &choice);
				
				if(choice >= 1 && choice <= 3){
					config &= ~(0x7 << 5); //Apaga bits de seccion (Alarma)
					config |= (1 << (5 + (choice - 1)));
				}	
		
				printBits(config);		
				break;
		
			case 2:
				printf("1 - Normal\n");	
				printf("2 - Comparacion al Periodo anterior\n");	
				printf("3 - Comparacion a uso normal\n");	
				printf("Su eleccion: ");
				scanf("%hhu", &choice);
				
				if(choice >= 1 && choice <= 3){
					config &= ~0x7; //Apaga bits de seccion (Modo) 
					config |= (1 << (choice - 1));
				}	
		
				printBits(config);		
				break;
		
			case 3:
				printf("1 - Periodo Diario\n");	
				printf("2 - Periodo Mensual\n");	
				printf("Su eleccion: ");
				scanf("%hhu", &choice);
				
				if(choice >= 1 && choice <= 2){
					config &= ~(0x3 << 3); //Apaga bits de seccion (Periodo)
					config |= (1 << (3 + choice - 1));
				}	
		
				printBits(config);		
				break;
				
			case 4:
				return config;
		
			case 5:
				exit(EXIT_SUCCESS);
		}
	}	
}

void printBits(unsigned char num){
	for(int i = 7; i >= 0; i--)
		printf("%d", num & (1 << i) ? 1 : 0);
	printf("\n");
}

