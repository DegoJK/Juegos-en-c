#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include <ctype.h>

void Color(int Background, int Text); // Prototipo de función          

enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};


void titulo(char move2[], int record, int pasada);

int juego(int modo);
int modos(int n, int m, int T, int M);
int selec(char move[], int i);

void mostrar_pantalla(char [10][10], int cont, int tesoros);
void mostrar_pantalla2(char [10][15], int cont, int tesoros);
void tdp();

int main()
{
	char move[4];
	int i;
	for(i = 1; i<4; i++)move[i] = 32;
	move[0] = 175;
	selec(move, 0);
}

void titulo(char move2[], int record, int pasada)
{
	Color(BLACK,CYAN);
	printf( "					  _______                                       \n");
	printf( "					 |__   __|                                      \n");
	printf( "					    | | _ __  ___   __ _  ___  _   _  _ __  ___ \n");
	printf( "					    | || '__|/ _ \\ / _\\ |/ __|| | | || '__|/ _ \\\n");
	printf( "					    | || |  |  __/| (_| |\\__ \\| |_| || |  |  __/\n");
	printf( "					    |_||_|  _\\___| \\__,_||___/ \\__,_||_|   \\___|\n");
	Color(BLACK, YELLOW),
	printf( "					           / __ \\                   | |         \n");
	printf( "					          | |  | | _   _   ___  ___ | |_        \n");
	printf( "					          | |  | || | | | / _ \\/ __|| __|       \n");
	printf( "					          | |__| || |_| ||  __/\\__ \\| |_        \n");
	printf( "					           \\___\\_\\ \\__,_| \\___||___/ \\__|       \n");
	printf( "					                                                \n");
	printf( "					                                                \n");
	printf( "					                                                \n");
	Color(BLACK, LGREEN);
	printf( "					                %2c Modo facil                                \n", move2[0]);
	Color(BLACK, YELLOW);
	printf( "					                %2c Modo Normal                                \n", move2[1]);
	Color(BLACK, LRED);
	printf( "					                %2c Modo dificil                                \n", move2[2]);
	Color(BLACK, WHITE);
	printf( "					                                                \n");
	printf( "					                %2c Salir                                \n", move2[3]);
	printf( "					                                                \n");
	printf( "					          | Movimientos ultima partida: %d  |                              \n", pasada);
	Color(BLACK, YELLOW);
	printf( "					          |  Record de movimientos: %d      |                          \n", record);
	Color(BLACK, WHITE);
	printf( "					                                                \n");
	printf( "					            [ W  arriba  //  S  abajo ]                                \n");
	printf( "                                                \n");

}


int selec(char move[], int i)
{
	int record = 0, pasada = 0, respaldo = 0;
	
	do
	{
		system("cls");
		titulo(move, record, pasada);
		
		switch(tolower(_getch()))
		{
			case 'w':
				if(i>0)
				{
					move[i] = 32;
					i = i - 1;
					move[i] = 175;
				}else
				{
					
					move[i] = 32;
					i = 3;
					move[i] = 175;
				}
				break;
			case 's':
				
				if(i<3)
				{
					move[i] = 32;
					i = i + 1;
					move[i] = 175;
				}else
				{
					move[i] = 32;
					i = 0;
					move[i] = 175;
				}
				
				break;
			case 13:
				
				pasada = juego(i);
				if(pasada != 0)
				{
					if(pasada < record)
					{
						record = pasada;
					}	
					record = pasada;
				}
				
				break;
			default:
				break;
		}	
					
	}while(1);
}
int juego(int modo)
{
	int pasos;
	system("cls");
	switch(modo)
	{
		case 0:
			pasos = modos(10, 10, 5, 10);
			return pasos;
			break;
		case 1:
			
			pasos = modos(10, 15, 10, 20);
			return pasos;
			break;
		case 2:
			pasos = modos(10, 15, 20, 50);
			return pasos;
			break;
		default:
			tdp();
			return -1;
			break;
	}
	
}
int modos(int n, int m, int ct, int cm)
{
	
	int mod, i = 0, j = 0, cont = 0;
	
	mod = ct;
	
	srand(time(NULL));
	char nivel[n][m];
	
	
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			nivel[i][j] = 32;
			nivel[0][0] = '#';
		}
	}
	
	do //PONER TESOROS RANDOM
	{
		
		
		i = rand()%n;
		j = rand()%m;
		
		if(nivel[i][j] == 32)
		{
			nivel[i][j] = 'T';
			cont = cont + 1;
		}
	}while(cont != ct);
	
	cont = 0;	
	do //PONER TESOROS RANDOM
	{
		i = rand()%n;
		j = rand()%m;

		if(nivel[i][j] == 32)
		{
			nivel[i][j] = 'M';
			cont = cont + 1;
		}
	}while(cont != ct);
	
	ct=0;
	i = 0;
	j = 0;
	cont = 0;
	do
	{
		
		system("cls");
		
		if(m == 10){
			mostrar_pantalla(nivel, cont, ct);
		}else{
			mostrar_pantalla2(nivel, cont, ct);
		}
		
		if(mod == 5 && ct==5)break;
		if(mod == 10 && ct==10)break;
		if(mod == 20 && ct==20)break;
		
		
		switch(tolower(_getch()))//MOVIMIENTOS
		{
			case 'w':
				if(i>0)
				{
					if(nivel[i-1][j] == 'T')
					{
						
						ct = ct + 1;
						nivel[i][j] = 32;
						i = i - 1;
						nivel[i][j] = '#';
						cont = cont + 1;
						
					}else if(nivel[i-1][j] == 'M')
					{
						nivel[i][j] = 32;
						nivel[i-1][j] = 32;
						i = 0;
						j = 0;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else
					{
						nivel[i][j] = 32;
						i = i - 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}
				}
				break;
			case 's':
				if(i<n-1)
				{
					if(nivel[i+1][j] == 'T')
					{
						ct = ct + 1;
						nivel[i][j] = 32;
						i = i + 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else if(nivel[i+1][j] == 'M')
					{
						nivel[i][j] = 32;
						nivel[i+1][j] = 32;
						i = 0;
						j = 0;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else
					{
						nivel[i][j] = 32;
						i = i + 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}
					
				}
				break;
			case 'a':
				if(j>0)
				{
					if(nivel[i][j-1] == 'T')
					{
						ct = ct + 1;
						nivel[i][j] = 32;
						j = j - 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else if(nivel[i][j-1] == 'M')
					{
						nivel[i][j] = 32;
						nivel[i][j-1] = 32;
						i = 0;
						j = 0;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else
					{
						nivel[i][j] = 32;
						j = j - 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}
					
				}
				break;
			case 'd':
				if(j<m-1)
				{
					if(nivel[i][j+1] == 'T')
					{
						ct = ct + 1;
						nivel[i][j] = 32;
						j = j + 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else if(nivel[i][j+1] == 'M')
					{
						nivel[i][j] = 32;
						nivel[i][j+1] = 32;
						i = 0;
						j = 0;
						nivel[i][j] = '#';
						cont = cont + 1;
					}else
					{
						nivel[i][j] = 32;
						j = j + 1;
						nivel[i][j] = '#';
						cont = cont + 1;
					}
					
				}
				break;
			
			case 27:
				
				
				return 0;

			default:
				break;
		}
		
	}while(1);
	
	printf("\n					FELICIDADES GANASTE\n\n");
	printf("					");
	system("pause");
	return cont;

}


void mostrar_pantalla(char nivel[10][10], int cont, int tesoros)
{
	int i,j;
	printf("\n\n\n					[Movimientos: %d]\n", cont);
	printf("					[Tesoros: %d]\n\n", tesoros);
	for(i = 0; i < 10; i++)
	{
		printf("					");
		for(j = 0; j < 10; j++)
		{
			if(nivel[i][j] == 'M')
			{
				Color(RED, BLACK);
			}else if(nivel[i][j] == 'T')
			{
				Color(YELLOW, BLUE);	
			}else if(nivel[i][j] == '#')
			{
				
				Color(GREEN, BLACK);
			}else
			{
				Color(BLACK, LGREEN);
			}
			
			printf("[%c]", nivel[i][j]);
		}
		printf("\n");
	}
	Color(BLACK, WHITE);
	printf("\n\n					Arriba:  w // Abajo:  s\n\n					Izquierda: a // Derecha:  d \n");
	printf( "                                                \n");
	printf( "					Salir: esc                                   \n");

}
void mostrar_pantalla2(char nivel[10][15], int cont, int tesoros)
{
	int i,j;
	printf("\n\n\n					[Movimientos: %d]\n", cont);
	printf("					[Tesoros: %d]\n\n", tesoros);
	for(i = 0; i < 10; i++)
	{
		printf("					");
		for(j = 0; j < 15; j++)
		{
			if(nivel[i][j] == 'M')
			{
				Color(RED, BLACK);
			}else if(nivel[i][j] == 'T')
			{
				Color(YELLOW, BLUE);	
			}else if(nivel[i][j] == '#')
			{
				
				Color(GREEN, BLACK);
			}else
			{
				Color(BLACK, LGREEN);
			}
			
			printf("[%c]", nivel[i][j]);
		}
		printf("\n");
	}
	Color(BLACK, WHITE);
	printf("\n\n					Arriba:  w // Abajo:  s\n\n					Izquierda: a // Derecha:  d \n");
	printf( "                                                \n");
	printf( "					Salir: esc                                   \n");
}
void tdp()
{
	Color(BLACK, RED);
	printf( "\n\n\n\n\n					  _______                  _                      \n");
	printf( "					 |__   __|                (_)                     \n");
	printf( "					    | | ___ _ __ _ __ ___  _ _ __   ___           \n");
	printf( "					    | |/ _ \\ '__| '_ \\ _ \\| | '_ \\ / _ \\          \n");
	printf( "					    | |  __/ |  | | | | | | | | | | (_) |         \n");
	printf( "					    |_|\\___|_|  |_| |_| |_|_|_| |_|\\___/          \n");
	printf( "					                | |    | |                        \n");
	printf( "					              __| | ___| |                        \n");
	printf( "					  _____      / _\\ |/ _ \\ |                        \n");
	printf( "					 |  __ \\    | (_| |  __/ |                        \n");
	printf( "					 | |__) | __ \\__,_|\\___|_|__ __ _ _ __ ___   __ _ \n");
	printf( "					 |  ___/ '__/ _ \\ / _\\ | '__/ _\\ | '_ \\  _ \\/ _\\ |\n");
	printf( "					 | |   | | | (_) | (_| | | | (_| | | | | | | (_| |\n");
	printf( "					 |_|   |_|  \\___/ \\__, |_|  \\__,_|_| |_| |_|\\__,_|\n");
	printf( "					                   __/ |                          \n");
	printf( "					                  |___/                           \n");
	Color(BLACK, BLACK);
	exit(0);
	
}

void Color(int Background, int Text){ // Función para cambiar el color del fondo y/o pantalla

 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

 // Para cambiar el color, se utilizan números desde el 0 hasta el 255.
 // Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
 int    New_Color= Text + (Background * 16);

 SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
