#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include <ctype.h>

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
	printf( "					  _______                                       \n");
	printf( "					 |__   __|                                      \n");
	printf( "					    | | _ __  ___   __ _  ___  _   _  _ __  ___ \n");
	printf( "					    | || '__|/ _ \\ / _\\ |/ __|| | | || '__|/ _ \\\n");
	printf( "					    | || |  |  __/| (_| |\\__ \\| |_| || |  |  __/\n");
	printf( "					    |_||_|  _\\___| \\__,_||___/ \\__,_||_|   \\___|\n");
	printf( "					           / __ \\                   | |         \n");
	printf( "					          | |  | | _   _   ___  ___ | |_        \n");
	printf( "					          | |  | || | | | / _ \\/ __|| __|       \n");
	printf( "					          | |__| || |_| ||  __/\\__ \\| |_        \n");
	printf( "					           \\___\\_\\ \\__,_| \\___||___/ \\__|       \n");
	printf( "					                                                \n");
	printf( "					                                                \n");
	printf( "					                                                \n");
	printf( "					                %2c Modo facil                                \n", move2[0]);
	printf( "					                %2c Modo Normal                                \n", move2[1]);
	printf( "					                %2c Modo dificil                                \n", move2[2]);
	printf( "					                                                \n");
	printf( "					                %2c Salir                                \n", move2[3]);
	printf( "					                                                \n");
	printf( "					          | Movimientos ultima partida: %d  |                              \n", pasada);
	printf( "					          |  Record de movimientos: %d      |                          \n", record);
	printf( "					                                                \n");
	printf( "					            [ W  arriba  //  S  abajo ]                                \n");
	printf( "                                                \n");

}


int selec(char move[], int i)
{
	int record = 0, pasada = 0;
	
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
				if(record == 0)record = pasada;
				
				if(pasada < record)record = pasada;
				
				if(pasada == -1)return -1;
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
	
	int mod;
	
	mod = ct;
	srand(time(NULL));
	
	char nivel[n][m];
	
	int i = 0, j = 0, cont = 0;
	
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
		if(m == 10)
		{
			i = rand()%10;
			j = rand()%10;
		}else
		{
			i = rand()%10;
			j = rand()%15;
		}
		if(nivel[i][j] == 32)
		{
			nivel[i][j] = 'T';
			cont = cont + 1;
		}
	}while(cont != ct);
	
	cont = 0;	
	do //PONER TESOROS RANDOM
	{
		if(m == 10)
		{
			i = rand()%10;
			j = rand()%10;
		}else
		{
			i = rand()%10;
			j = rand()%15;
		}

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
				if(i<n)
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
				if(j<m)
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
				return cont;
			
			default:
				break;
		}
		
	}while(1);
	
	printf("\nFELICIDADES GANASTE\n");
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
			printf("[%c]", nivel[i][j]);
		}
		printf("\n");
	}
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
			printf("[%c]", nivel[i][j]);
		}
		printf("\n");
	}
	printf("\n\n					Arriba:  w // Abajo:  s\n\n					Izquierda: a // Derecha:  d \n");
	printf( "                                                \n");
	printf( "					Salir: esc                                   \n");
}
void tdp()
{
	printf( "					  _______                  _                      \n");
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
	printf( "                                                \n");
	printf( "                                                \n");
	printf( "                                                \n");
	
}
