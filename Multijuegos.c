#include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define NJugadoresMax 10

struct Tjugador
{
	char nombre[20];
	int npartidastotal;		// Partidas jugadas totales
	int npartresraya;		// Partidas jugadas a tres en raya
	int ngantresraya;		// Partidas ganadas a tres en raya
	int nparadiv;			// Partidas jugadas a las adivinanzas
	int nganadiv;			// Partidas ganadas a las adivinanzas
	int nparpie1;			// Partidas jugadas a piedra papel o tijera de un jugador
	int nganpie1; 			// Partidas ganadas a piedra papel o tijera de un jugador
	int nparpie2;			// Partidas jugadas a piedra papel o tijera de dos jugadores
	int nganpie2; 			// Partidas ganadas a piedra papel o tijera de dos jugadores
};

//DECLARACION FUNCIONES
int ExisteJugador(struct Tjugador jugadores[], char jugador[20], int njugadores);
void NuevoJugador(struct Tjugador jugadores[], int ijugador, char nombre[20]);
int TresEnRaya(struct Tjugador jugadores[], int ijugador1, int ijugador2);
void Adivinanzas(struct Tjugador jugadores[], int ijugador);
int PiedraPapelTijera(struct Tjugador jugadores[], int ijugador);
int PiedraPapelTijera2(struct Tjugador jugadores[], int ijugador1, int ijugador2);
int AperturaFichero (char nfichero[30]);



//PROGRAMA
int main()
{
	FILE *datos;
	int ver;
	int opcion, juego, apertura;
	int i, n, nganadas;
	int volverjugar;
	int ijugador1, ijugador2, siguientejugador = 0;
	char nombrejugador[20];	
	struct Tjugador jugadores[NJugadoresMax];

	printf ("BIENVENIDO A MULTIJUEGOS\nAVISO! ACTIVE LAS MAYUSCULAS\n\n");
	
	do {	
		printf("\nSelecciona una opcion: \n");
		printf("1 Jugador\n");
		printf("2 Jugadores\n");
		printf("3 Ver ficheros\n");
		printf("4 Ver Jugadores \n");
		printf("0 Salir del programa\n");
		
		scanf("%d", &opcion);
		if (opcion == 1)
		{
			printf ("Introduce tu nombre\n");
			scanf("%s", nombrejugador);
			ijugador1 = ExisteJugador(jugadores, nombrejugador, NJugadoresMax); 	// Comprobamos si este jugador ya ha jugado antes y esta su nombre en jugadores
			if (ijugador1 == -1) {
				// El jugador no existe
				ijugador1 = siguientejugador;
				if (ijugador1 == NJugadoresMax)	{ // Ya han jugado en maximo numero de jugadores permitido
					printf("Numero máximo de jugadores alcanzado (%d). Finalizar la partida", NJugadoresMax);
					return 0;
				}	else {
					// Se crea el nuevo jugador 
					NuevoJugador(jugadores,ijugador1,nombrejugador);
					printf ("Hola %s\n", jugadores[ijugador1].nombre);
					siguientejugador++;
				}			
			}	else {
				printf ("Hola de nuevo %s\n", jugadores[ijugador1].nombre);			
			} do {
				printf("\nSelecciona un juego\n");
				printf("A-Adivinanzas\n");
				printf("B-Piedra, papel o tijera\n");
				printf("M-Volver al menu principal\n");
				
				scanf("%s", &juego); 
				volverjugar = 1;
				switch(juego)		
				{
					case 'a':
					case 'A':		
						printf("\nBienvenido al juego de las adivinanzas\n");
						Adivinanzas(jugadores, ijugador1);	
						break;
						
					case 'b':
					case 'B':
						printf("\nBienvenido a piedra, papel o tijera\n");
						PiedraPapelTijera(jugadores, ijugador1);
						break;		
										
					case 'm':
					case 'M':
						volverjugar = 0;
						break;			
				}
			} while (volverjugar != 0);	
		}	
		else if (opcion == 2)
		{
			printf ("Introduce el nombre del primer jugador\n"); 
			scanf("%s", nombrejugador);
			ijugador1 = ExisteJugador(jugadores, nombrejugador, NJugadoresMax); // Comprobamos si este jugador ya ha jugado antes y esta su nombre en jugadores
			if (ijugador1 == -1){// El jugador no existe. Buscamos el primer elemento libre
				ijugador1 = siguientejugador;
				if (ijugador1 == -1){// Ya han jugado en maximo numero de jugadores permitido
					printf("Numero máximo de jugadores alcanzado (%d). Finalizar la partida", NJugadoresMax);
					return 0;
				}	else {// Se crea un nuevo jugador
					NuevoJugador(jugadores,ijugador1,nombrejugador);
					printf ("Hola %s\n", jugadores[ijugador1].nombre);
					siguientejugador++;
				}	
			} else
			{
				printf ("Hola de nuevo %s", jugadores[ijugador1].nombre);			
			}
			
			printf ("Introduce el nombre del segundo jugador\n");
			scanf("%s", nombrejugador); 
			ijugador2 = ExisteJugador(jugadores, nombrejugador, NJugadoresMax);// Comprobamos si este jugador ya ha jugado antes y esta su nombre en jugadores
			if (ijugador2 == -1){
				ijugador2 = siguientejugador;	// El jugador no existe. Buscamos el primer elemento libre
				if (ijugador2 == -1) {// Ya han jugado en maximo numero de jugadores permitido
					printf("Numero máximo de jugadores alcanzado (%d). Finalizar la partida", NJugadoresMax);
					return 0;
				} else	{ // Se crea un nuevo jugador
					NuevoJugador(jugadores,ijugador2,nombrejugador);
					printf ("Hola %s\n", jugadores[ijugador2].nombre);
					siguientejugador++;
				}}else	{
				printf (" Hola de nuevo %s\n", jugadores[ijugador1].nombre);			
			}
			do	{
				printf("Seleccionar un juego\n");	
				printf("A-Tres en raya\n");	
				printf("B-Piedra, papel o tijera\n");
				printf("M-Volver al menu principal\n");
				fflush(stdin);
				scanf("%c", &juego);
				volverjugar = 1;
				switch(juego)		
				{
					case 'a':
					case 'A':
						printf("\nBienvenido al Tres en raya\n");
						TresEnRaya(jugadores, ijugador1, ijugador2);	
						break;
					
					case 'b':
					case 'B':
						printf("\nBienvenido a piedra, papel o tijera\n");
						PiedraPapelTijera2(jugadores, ijugador1, ijugador2); 
						break;
						
					case 'm':	
					case 'M':			
						volverjugar = 0;	
						break;	
					
				}
			}while (volverjugar != 0);			
					 	
		}
			else if (opcion == 3) 		{ 
			do
			{
				printf ("Elige que fichero quieres abrir\n");
				printf("\t1 Adivinanzas\n \t2 Piedra, papel o tijera (1 jug)\n\t3 Piedra, papel tijera (2 jug)\n\t4 Tres en Raya\t\n0 Salir\n");
				scanf ("%d", &apertura);
				if (apertura == 1) 
				{	
					printf ("Estos son los ultimos resultados guardados de las Adivinanzas\n\n");
					AperturaFichero("ADIVINANZAS.txt"); 
				}
				else if (apertura == 2)
				{
					printf ("Estos son los ultimos resultados guardados de Piedra Papel o tijera de 1 jugador\n\n");
					AperturaFichero("PIEDRAPAPEL1.txt");
				}
				else if (apertura == 3)
				{
					printf ("Estos son los ultimos resultados guardados de Piedra Papel o tijera de 2 jugadores\n\n");
					AperturaFichero("PIEDRAPAPEL2.txt");					
				}
				else if (apertura == 4)
				{
					printf ("Estos son los ultimos resultados guardados de Tres en Raya\n\n");					
					AperturaFichero("TRESENRAYA.txt");
				}
			}while (apertura != 0);	
				
		}
		
			else if (opcion == 4) 		{			
			printf("\nNombre	Partidas	Partidas ganadas\n");
			for (i=0; i < siguientejugador; i++)
			{
				nganadas = jugadores[i].nganadiv+jugadores[i].nganpie1+jugadores[i].nganpie2+jugadores[i].ngantresraya;
				printf("%s\t%d\t\t%d\n",jugadores[i].nombre,jugadores[i].npartidastotal,nganadas);
			}
			printf("\n\n");
		}
		else
		{
			printf("Opcion incorrecta\n");
		}
	}while (opcion != 0);
	
	printf ("Quereis guardar los datos de todos los jugadores en un fichero?\n1 (Si) o 0 (no)\n");
	scanf("%d",&ver);
	if (ver == 1) 
	{
	
		printf ("Los resultados estan en PARTIDAS.txt\n");
		datos = fopen("PARTIDAS.txt", "w");
		fprintf (datos,"Jugador		NP		NPA		NPAG	NPT		NPTG 	NPP1	NPP1G	NPP2 	NPP2G");
		for (i=0; i < siguientejugador; i++)
		{
				nganadas = jugadores[i].nganadiv+jugadores[i].nganpie1+jugadores[i].nganpie2+jugadores[i].ngantresraya;
				fprintf(datos,"%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",jugadores[i].nombre,jugadores[i].npartidastotal,
					jugadores[i].nparadiv, jugadores[i].nganadiv,jugadores[i].npartresraya,jugadores[i].ngantresraya,
					jugadores[i].nparpie1,jugadores[i].nganpie1,jugadores[i].nparpie2,jugadores[i].nganpie2);
		}
		fclose(datos);
	}
	printf("Gracias por utilizar el programa.\n");
	return 0;
}

//FUNCIONES
int ExisteJugador(struct Tjugador jugadores[], char jugador[20], int njugadores)
{
	int i;
	for (i = 0; i < njugadores; i++)
	{
		if(strcmp(jugadores[i].nombre, jugador) == 0)
		{
			// El jugador ya ha jugado antes
			return i;
		}
	}
	return -1;
}

void NuevoJugador(struct Tjugador jugadores[], int ijugador, char nombre[20])
{
	strcpy(jugadores[ijugador].nombre, nombre);	
	jugadores[ijugador].npartidastotal = 0;
	jugadores[ijugador].npartresraya = 0;
	jugadores[ijugador].ngantresraya = 0;
	jugadores[ijugador].nparadiv = 0;
	jugadores[ijugador].nganadiv = 0;
	jugadores[ijugador].nparpie1 = 0;
	jugadores[ijugador].nganpie1 = 0;
	jugadores[ijugador].nparpie2 = 0;
	jugadores[ijugador].nganpie2 = 0; 
}

int TresEnRaya(struct Tjugador jugadores[], int ijugador1, int ijugador2) 
{
	FILE * ftres;
	int jugador=1, error, empate=0, ganar=0;
    int empates=0, partidas=0, ver;
    char c1='1', c2='2', c3='3', c4='4', c5='5', c6='6', c7='7', c8='8', c9='9';
	char tiro, marca, respuesta='y';
	int gananterior1, gananterior2;
	
	gananterior1 = jugadores[ijugador1].ngantresraya;
	gananterior2 = jugadores[ijugador2].ngantresraya;
	
    do{

        error=1;
        system("cls");
    
        printf("JUEGO DEL TRES EN RAYA\n");
        printf("\n %c | %c | %c\n",c1,c2,c3);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n",c4,c5,c6);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n\n",c7,c8,c9);

        if(jugador == 1)
        {
           marca = 'X';
        }
        else
        {
           marca = 'O';
        }
		if (jugador == 1)
		{
			printf("Turno de %s.",jugadores[ijugador1].nombre);			
		}
		else
		{
			printf("Turno de %s.",jugadores[ijugador2].nombre);			
		}		
        //printf("Turno del Jugador %s.",jugador);
        printf("\nEscribe la posicion donde colocas la ficha: ");

        fflush(stdin);

        scanf("%c",&tiro);

        if (tiro=='1' && c1=='1') {c1=marca;}
        else if (tiro=='2' && c2=='2') {c2 = marca;}
        else if (tiro=='3' && c3=='3') {c3 = marca;}
        else if (tiro=='4' && c4=='4') {c4 = marca;}
        else if (tiro=='5' && c5=='5') {c5 = marca;}
        else if (tiro=='6' && c6=='6') {c6 = marca;}
        else if (tiro=='7' && c7=='7') {c7 = marca;}
        else if (tiro=='8' && c8=='8') {c8 = marca;}
        else if (tiro=='9' && c9=='9') {c9 = marca;}
        else {printf("Error! Movimiento No Valido\n"); error=2;}

		if(c1=='X'||c1=='O')
        {
        	if(c2==c1&&c3==c1) {ganar = 1;}
            if(c4==c1&&c7==c1) {ganar = 1;}
        }

        if(c5=='X'||c5=='O')
        {
        	if (c1 == c5 && c9 == c5) {ganar = 1;}
            if (c2 == c5 && c8 == c5) {ganar = 1;}
            if (c4 == c5 && c6 == c5) {ganar = 1;}                          
            if (c3 == c5 && c7 == c5) {ganar = 1;}
        }
 
        if(c9=='X'||c9=='O')
        {
            if (c6 == c9 && c3 == c9) {ganar = 1;}
        	if (c7 == c9 && c8 == c9) {ganar = 1;}                       
        }

        if ((c1 != '1' && c2 != '2' && c3 != '3' &&
            c4 != '4' && c5 != '5' && c6 != '6' &&
            c7 != '7' && c8 != '8' && c9 != '9') && ganar == 0)
        {
              empate = 1;
        }

        if (ganar == 1 || empate == 1)
        {
        	system("cls");
            if (ganar == 1)
            {
				if (jugador == 1)
				{
            		printf( "%s Gana!\n\n",jugadores[ijugador1].nombre);
            		jugadores[ijugador1].ngantresraya++;
            	}
				else
				{
            		printf( "%s Gana!\n\n",jugadores[ijugador2].nombre);
            		jugadores[ijugador2].ngantresraya++;
				}
              	printf("\n %c | %c | %c\n",c1,c2,c3);                                
              	printf("---+---+---\n");
              	printf("\n %c | %c | %c\n",c4,c5,c6);
              	printf("---+---+---\n");
              	printf("\n %c | %c | %c\n\n",c7,c8,c9);
            }
             
            if (empate==1)
            {
                printf("%s y %s habeis empatado!\n",jugadores[ijugador1].nombre, jugadores[ijugador2].nombre);
                printf("\n %c | %c | %c\n",c1,c2,c3);
                printf("---+---+---\n");
                printf("\n %c | %c | %c\n",c4,c5,c6);
                printf("---+---+---\n");
                printf("\n %c | %c | %c\n\n",c7,c8,c9);   
                empates++;
            }
            jugadores[ijugador1].npartidastotal++;
            jugadores[ijugador1].npartresraya++;
            jugadores[ijugador2].npartidastotal++;
        	jugadores[ijugador2].npartresraya++;
        	partidas++;
            printf("Jugar de Nuevo: Y/N ?\n");  
            fflush(stdin);
            scanf("%c",&respuesta);
   
            if (respuesta=='y'||respuesta=='Y')
            {
                empate=0;
                jugador=2;
                ganar=0;
                c1='1';
                c2='2';
                c3='3';
                c4='4';
                c5='5';
                c6='6';
                c7='7';
                c8='8';
                c9='9';
            }
        }

        if(error==1)
        {
            if (jugador==1)
            {
               jugador=2;
            }
            else
            {
               jugador=1;
            }
        }
	}while(respuesta=='y'||respuesta=='Y');
	
	printf ("Quereis guardar vuestros resultados en un fichero?\n1 (Si) o 0 (no)\n");
	scanf("%d",&ver);
	if (ver == 1) 
	{
		//Fichero de Tres en Raya
		printf ("Tus resultados  estan en TRESENRAYA.txt\n\n");
		ftres = fopen("TRESENRAYA.txt", "w");
		fprintf (ftres,"Hola %s y %s\nHabeis jugado %d partidas a TRES EN RAYA\n", jugadores[ijugador1].nombre, jugadores[ijugador2].nombre, partidas);
		fprintf(ftres,"%s ha ganado %d partidas\n", jugadores[ijugador1].nombre, jugadores[ijugador1].ngantresraya-gananterior1);
		fprintf(ftres,"%s ha ganado %d partidas\n", jugadores[ijugador2].nombre, jugadores[ijugador2].ngantresraya-gananterior2);
		fprintf(ftres,"Y habeis empadado %d partidas\n", empates);
		fclose(ftres);
	}
	else
	{
		printf("Gracias por jugar\n");
	}	
	return 0;
}

void Adivinanzas(struct Tjugador jugadores[], int ijugador) 
{
	FILE * fadv;
	int respuesta, gana;
	char ver;
	int adivinar = 0;
	int salir;
	
	//Primera adivinanza
	printf("\nRedondo como la luna y blanco como la cal, me hacen de leche... ¿Quien soy?\n");
	printf("1 (Luna), 2(Queso), 3(Sal)\nRespuesta:\n");
	do
	{
		scanf("%d", &respuesta);
		salir = 1;
		if ((respuesta == 1) || (respuesta == 3))
		{
			printf("Respuesta incorrecta\n");
		}
		else if (respuesta == 2)
		{
			printf("Respuesta correcta\n");
			adivinar++;
	 	}
	 	else
	 	{
	 		printf("Respuesta No valida. Vuelve a intentarlo\n");
	 		salir = 0;
		}
	} while (salir==0);
		
	//Segunda adivinanza
	printf("\nTiene 4 patas y no puede andar, tiene cabezera y no sabe hablar \n 1(cama), 2(mesa), 3(silla)\nRespuesta:");
	do
	{
		scanf("%d", &respuesta);
		salir = 1;
		if (respuesta == 1) 
		{
			printf("Respuesta correcta\n");
			adivinar++;
	
		}
		else if ((respuesta == 2) || (respuesta ==3))
		{
			printf("Respuesta incorrecta\n");
		}
		else 
		{
			printf("Respuesta No valida. Vuelve a intentarlo\n");	
			salir = 0;
		}
	} while (salir == 0);
	
	//Tercera adivinanza
	printf("\nVuelo de noche, duermo de dia y nunca veras plumas en un ala mia  \n 1 (paloma), 2 (murielago), 3 (gaviota)\nRespuesta:");
	do
	{
		scanf("%d", &respuesta);
		salir = 1;
		if (respuesta == 2) 
		{
			printf("Respuesta correcta\n");
			adivinar++;
		}
		else if  ((respuesta == 1) || (respuesta == 3))
		{
			printf("Respuesta incorrecta\n");
		}
		else
		{
			printf("Respuesta No valida. Vuelve a intentarlo\n");
			salir = 0;	
		}
	} while (salir == 0);		
	
	if (adivinar == 3)
	{
		jugadores[ijugador].nganadiv++;
		printf("Enhorabuena %s, has acertado las tres adivinanzas\n",jugadores[ijugador].nombre);
	}
	else if ((adivinar == 2)||(adivinar == 1))
	{
		printf("Puedes hacerlo mejor %s, has acertado %d adivinanzas\n",jugadores[ijugador].nombre, adivinar);
	}
	else
	{
		printf("%s, no has acertado ninguna. Vuelve a intentarlo\n",jugadores[ijugador].nombre);		
	}
	
	jugadores[ijugador].nparadiv++;
	jugadores[ijugador].npartidastotal++;	
	
	printf ("\nQuires guardar tus resultados en un fichero?\n1 (Si) o 0 (no)\n");
	scanf("%d",&ver);
	if (ver == 1) 
	{
		//Fichero de adivinanzas
		printf ("Tus resultados  estan en ADIVINANZAS.txt\n");
		fadv = fopen("ADIVINANZAS.txt", "w");
		fprintf (fadv,"Hola %s\nHas jugado a ADIVINANZAS\n", jugadores[ijugador].nombre);
		fprintf (fadv,"Has adivinado un total de %d adivinanzas", adivinar);
		fclose(fadv);
	}
	else
	{
		printf("Gracias por jugar\n");
	}	
}

int PiedraPapelTijera(struct Tjugador jugadores[], int ijugador) 
{
	FILE * fppt1;
	int jug, op, r;
	int empate=0, perder = 0, ganar = 0;
	int partidas =0;
	int ver;

	printf("Para jugar ingresaras solo el numero que corresponda a tu eleccion:\n");
	do
	{		
		r=rand()%3;
		printf("0 (Piedra), 1(Papel), 2(Tijeras), 3(Salir)\n");
		
		printf("Selecciona un numero del menu anterior\n");
		scanf("%d", &jug);
		switch (jug)
		{
		case 0:
			printf("Elegiste Piedra\n");
			if (r==0)
			{
				printf("\t Yo elegi Piedra\n");
				printf("\t\tEmpate\n");
				empate++;
			 }
			else if (r==1)
			{
				printf("\t Yo elegi Papel\n");
				printf("\t\t¡Te gane!\n");
				perder++;
			}
			else if (r==2)
			{
				printf("\t Yo elegi Tijeras\n");
				printf("\t\tTu ganas\n");
				jugadores[ijugador].nganpie1++;
				ganar++;
			}
			jugadores[ijugador].nparpie1++;
			jugadores[ijugador].npartidastotal++;
			partidas++;
			break;
		case 1:
			printf("Elegiste Papel\n");
			if (r==0)
			{
	            printf("\t Yo elegi Piedra\n");
	            printf("\t\tTu ganas\n");
	            jugadores[ijugador].nganpie1++;
	            ganar++;
	        }
	        else if (r==1)
	        {
	            printf("\t Yo elegi Papel\n");
	            printf("\t\tEmpate\n");
	            empate++;
	        }
	        else if (r==2)
	        {
	            printf("\t Yo elegi Tijeras\n");
	            printf("\t\t¡Te gane!\n");
	            perder++;
	        }
			jugadores[ijugador].nparpie1++;
	        jugadores[ijugador].npartidastotal++;
	        partidas++;
			break;
		case 2 :
			printf("Elegiste Tijeras\n");
		    if (r==0)
		    {
		    	printf("\t Yo elegi Piedra\n");
		        printf("\t\t¡Te gane!\n");
		        perder++;
		    }	
			else if (r==1)
	        {
	            printf("\t Yo elegi Papel\n");
	            printf("\t\tTu ganas\n");
	            jugadores[ijugador].nganpie1++;
	            ganar++;
	        }
	        else if (r==2)
	        {
	            printf("\t Yo elegi Tijeras\n");
	            printf("\t\tEmpate\n");
	            empate++;
	        }
	        jugadores[ijugador].nparpie1++;
	        jugadores[ijugador].npartidastotal++;
	        partidas++;
		    break;
		case 3: 
			break;		
		default:
			printf("Por favor solo introduce los numeros que aparecen en el menu\n");
			break;
			}
		
	} while (jug != 3);
		
	printf ("Quieres guardar tus resultados en un fichero?\n1 (Si) o 0 (no)\n");
	scanf("%d",&ver);
	if (ver == 1) 
	{
		//Fichero de resultados de Piedra papel o tijera
		printf ("Tus resultados  estan en PIEDRAPAPEL1.txt\n");
		fppt1 = fopen("PIEDRAPAPEL1.txt", "w");
		fprintf (fppt1,"Hola %s\nHas jugado %d partidas a PIEDRA PAPEL Y TIJERA de un jugador\n", jugadores[ijugador].nombre,partidas);
		fprintf (fppt1,"Has ganado un total de %d partidas\n", ganar);
		fprintf (fppt1,"Y has ganado un total de %d partidas\n", empate);
		fclose(fppt1);
	}
	else
	{
		printf("Gracias por jugar\n");
	}	
}

int PiedraPapelTijera2(struct Tjugador jugadores[], int ijugador1, int ijugador2) 
{
	FILE *fppt2;
	int ver;
	int victoria1=0, victoria2=0, empate=0;	
	int partidas = 0;
	int guardar;
	char caracter1;
	char caracter2;
	int gananterior1, gananterior2;
	
	gananterior1 = jugadores[ijugador1].nganpie2;
	gananterior2 = jugadores[ijugador2].nganpie2;
	
	do
	{		
		fflush(stdin);
		printf ("%s introduce tu eleccion: I(piedra), P(papel), T(tijera), E (salir)\n ",jugadores[ijugador1].nombre);
		scanf ("%c", &caracter1);
		if (caracter1 != 'E')
		{
	   		fflush(stdin);
   			printf ("%s introduce tu eleccion: I(piedra), P(papel), T(tijera), E (salir)\n ",jugadores[ijugador2].nombre);
   			scanf ("%c", &caracter2);
   	
   			if (caracter1=='T' && caracter2=='I')
   			{	
   				printf ("La piedra rompe a las tijeras, gana %s\n\n",jugadores[ijugador2].nombre);
   				jugadores[ijugador2].nganpie2++;
   			}
   			else if(caracter1=='T' && caracter2=='P')
   			{
   				printf ("Las tijeras cortan al papel, gana %s\n\n",jugadores[ijugador1].nombre);
   				jugadores[ijugador1].nganpie2++;
   			}
	   		else if (caracter1=='P' && caracter2=='I')
	   		{
	   			printf ("El papel cubre a la piedra, gana %s\n\n",jugadores[ijugador1].nombre);
	   			jugadores[ijugador1].nganpie2++;
	   		}
	   		else if (caracter1=='I' && caracter2=='T')
	   		{
	   			printf ("La piedra rompe a las tijeras, gana %s\n\n",jugadores[ijugador1].nombre);
	   			jugadores[ijugador1].nganpie2++;
	   		}
	   		else if(caracter1=='P'&& caracter2=='T')
	   		{
	   			printf ("Las tijeras cortan al papel, gana %s\n\n",jugadores[ijugador2].nombre);
	   			jugadores[ijugador2].nganpie2++;
	   		}
	   		else if (caracter1=='I'&& caracter2=='P')
	   		{
	   			printf ("El papel cubre a la piedra, gana %s\n\n",jugadores[ijugador2].nombre);
	   			jugadores[ijugador2].nganpie2++;
	   		}	
	   		else if (caracter1=='I'&& caracter2=='I')
	   		{
	   			printf ("Ambos sacais piedra, empate\n\n");
	   			empate++;
	   		}
	   		else if (caracter1=='P'&& caracter2=='P')
	   		{
	   			printf ("Ambos sacais papel, empate\n\n");
	   			empate++;
	   		}
	   		else if (caracter1=='T'&& caracter2=='T')
	   		{
	   			printf ("Ambos sacais tijera, empate\n\n");
	   			empate++;
	   		} 
	   		else 
	   		{
	   			printf ("\nIntroduce una letra valida, recuerda las MAYUSCULAS\n");
	   			partidas++;	
			}
		}		
	} while (caracter1 != 'E'); 
				
	printf ("Quereis guardar vuestros resultados en un fichero?\n1 (Si) o 0 (no)\n");
	scanf("%d",&ver);
	if (ver == 1) 
	{
		//Fichero de resultados de Piedra papel o tijera
		printf ("Los resultados estan en PIEDRAPAPEL2.txt\n");
		fppt2 = fopen("PIEDRAPAPEL2.txt", "w");
		fprintf (fppt2,"Hola %s y %s\nHabeis jugado %d partidas a PIEDRA PAPEL O TIJERA\n", jugadores[ijugador1].nombre, jugadores[ijugador2].nombre, partidas);
		fprintf(fppt2,"%s ha ganado %d partidas\n", jugadores[ijugador1].nombre, jugadores[ijugador1].nganpie2-gananterior1);
		fprintf(fppt2,"%s ha ganado %d partidas\n", jugadores[ijugador2].nombre, jugadores[ijugador2].nganpie2-gananterior2);
		fprintf(fppt2,"Y habeis empadado %d partidas\n", empate);
		fclose(fppt2);
	}
	else
	{
		printf("Gracias por jugar\n");
	}	
	return 0;	
}

int AperturaFichero (char nfichero[30]) 
{
	FILE * fnombre;
	int c;
			
	fnombre = fopen(nfichero, "r");		
	if (fnombre == NULL) 
	{
		printf("Fichero no encontrado\n");
		return 0;
	}
		
	//Leer fichero
	while ((c = fgetc(fnombre))  != EOF) 
	{
		printf("%c",c);
	}
	printf("\n\n");				
	
	//Cerrar fichero
	fclose(fnombre);	
}

