#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define LINII_MAX 12
#define COLOANE_MAX 12

#define PORT 2103
extern int errno;

char *decodificare(int culoare)
{
	if (culoare == 1)
		return "Negru";
	return "Alb";
}
int generareCuloare()
{
	srand(time(NULL));
	if (rand() % 2)
		return 1; // culoarea Negru
	return 2;	  // culoarea Alb
}
int inversareCuloare(int culoare)
{
	return culoare == 2 ? 1 : 2;
}
void initializareTabla(int matrice[LINII_MAX][COLOANE_MAX], int dimensiune)
{
	if (dimensiune == 8)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < dimensiune; j++)
				if ((i + j) % 2 == 1)
					matrice[i][j] = 1;

		for (int i = 5; i < dimensiune; i++)
			for (int j = 0; j < dimensiune; j++)
				if ((i + j) % 2 == 1)
					matrice[i][j] = 2;
	}
	else
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < dimensiune; j++)
				if ((i + j) % 2 == 1)
					matrice[i][j] = 1;

		for (int i = 7; i < dimensiune; i++)
			for (int j = 0; j < dimensiune; j++)
				if ((i + j) % 2 == 1)
					matrice[i][j] = 2;
	}
}
void afisareTabla(int matrice[LINII_MAX][COLOANE_MAX], int dimensiune)
{
	if (dimensiune == 8)
	{
		printf("    0 1 2 3 4 5 6 7\n");
		printf("  |----------------\n");
		for (int i = 0; i < dimensiune; i++)
		{
			printf("%d | ", i);
			for (int j = 0; j < dimensiune; j++)
				if (matrice[i][j] == 0)
					printf("_ ");
				else if (matrice[i][j] == 1)
					printf("N ");
				else if (matrice[i][j] == 10)
					printf("n ");
				else if (matrice[i][j] == 2)
					printf("A ");
				else
					printf("a ");
			printf("\n");
		}
		printf("  |---------------\n");
	}
	else
	{
		printf("     0 1 2 3 4 5 6 7 8 9 10 11\n");
		printf("   |--------------------------\n");
		for (int i = 0; i < dimensiune; i++)
		{
			if (i < 10)
				printf("%d  | ", i);
			else
				printf("%d | ", i);
			for (int j = 0; j < dimensiune; j++)
				if (matrice[i][j] == 0)
					printf("_ ");
				else if (matrice[i][j] == 1)
					printf("N ");
				else if (matrice[i][j] == 10)
					printf("n ");
				else if (matrice[i][j] == 2)
					printf("A ");
				else
					printf("a ");
			printf("\n");
		}
		printf("   |-------------------------\n");
	}
}
int verificareMutare(int matrice[LINII_MAX][COLOANE_MAX], int linieStart, int coloanaStart, int linieDestinatie, int coloanaDestinatie, int jucator)
{
	if (matrice[linieDestinatie][coloanaDestinatie] != 0)
		return 0; //mutare invalida, pozitia trebuie sa fie goala pentru a muta in ea

	if (jucator == 1) //jucatorul cu culoarea Negru
	{
		if (matrice[linieStart][coloanaStart] == 1) //piesa normala
		{
			//verificare salt pe casuta goala
			if (linieDestinatie == linieStart + 1 && (coloanaDestinatie == coloanaStart - 1 || coloanaDestinatie == coloanaStart + 1))
				return 1;

			//verificare salt pe casuta ocupata de piesa Alba
			if (linieDestinatie == linieStart + 2)
			{
				if (coloanaDestinatie == coloanaStart - 2)
					if (matrice[linieDestinatie - 1][coloanaDestinatie + 1] == 2)
						return 2;
				if (coloanaDestinatie == coloanaStart + 2)
					if (matrice[linieDestinatie - 1][coloanaDestinatie - 1] == 2)
						return 2;
			}
		}
		if (matrice[linieStart][coloanaStart] == 10) //piesa incoronata
		{
			//verificare salt pe casuta goala
			if (linieDestinatie == linieStart - 1 && (coloanaDestinatie == coloanaStart - 1 || coloanaDestinatie == coloanaStart + 1))
				return 1;

			//verificare salt pe casuta ocupata de piesa Neagra
			if (linieDestinatie == linieStart - 2)
			{
				if (coloanaDestinatie == coloanaStart - 2)
					if (matrice[linieDestinatie + 1][coloanaDestinatie + 1] == 2)
						return 2;
				if (coloanaDestinatie == coloanaStart + 2)
					if (matrice[linieDestinatie + 1][coloanaDestinatie - 1] == 2)
						return 2;
			}
		}
	}

	if (jucator == 2)
	{
		if (matrice[linieStart][coloanaStart] == 2)
		{
			//verificare salt pe casuta goala
			if (linieDestinatie == linieStart - 1 && (coloanaDestinatie == coloanaStart - 1 || coloanaDestinatie == coloanaStart + 1))
				return 1;

			//verificare salt pe casuta ocupata de piesa Neagra
			if (linieDestinatie == linieStart - 2)
			{
				if (coloanaDestinatie == coloanaStart - 2)
					if (matrice[linieDestinatie + 1][coloanaDestinatie + 1] == 1)
						return 2;
				if (coloanaDestinatie == coloanaStart + 2)
					if (matrice[linieDestinatie + 1][coloanaDestinatie - 1] == 1)
						return 2;
			}
		}
		if (matrice[linieStart][coloanaStart] == 20)
		{
			//verificare salt pe casuta goala
			if (linieDestinatie = linieStart + 1 && (coloanaDestinatie == coloanaStart - 1 || coloanaDestinatie == coloanaStart + 1))
				return 1;

			//verificare salt pe casuta ocupata de piesa Alba
			if (linieDestinatie = linieStart + 2)
			{
				if (coloanaDestinatie == coloanaStart - 2)
					if (matrice[linieDestinatie - 1][coloanaDestinatie + 1] == 1)
						return 2;
				if (coloanaDestinatie == coloanaStart + 2)
					if (matrice[linieDestinatie - 1][coloanaDestinatie - 1] == 1)
						return 2;
			}
		}
	}
	return 0;
}
void executareMutare(int matrice[12][12], int dimensiune, int linieStart, int coloanaStart, int linieDestinatie, int coloanaDestinatie, int jucator, int rezultat)
{
	if (matrice[linieStart][coloanaStart] == jucator * 10) //daca piesa a fost incoronata anterior
		matrice[linieDestinatie][coloanaDestinatie] = jucator * 10;
	else
		matrice[linieDestinatie][coloanaDestinatie] = jucator;
	matrice[linieStart][coloanaStart] = 0;
	if (jucator == 1 && linieDestinatie == 7 && dimensiune == 8) //daca o piesa neagra ajunge in punctul de a se incorona
		matrice[linieDestinatie][coloanaDestinatie] = jucator * 10;
	else if (jucator == 2 && linieDestinatie == 0) //daca o piesa alba ajunge in punctul de a se incorona
		matrice[linieDestinatie][coloanaDestinatie] = jucator * 10;
	if (rezultat == 2) //cazul cand trebuie eliminata piesa peste care se face saltul
	{
		if (jucator == 1)
			if (coloanaDestinatie > coloanaStart)
				matrice[linieDestinatie - 1][coloanaDestinatie - 1] = 0;
			else
				matrice[linieDestinatie - 1][coloanaDestinatie + 1] = 0;

		if (jucator == 2)
			if (coloanaDestinatie > coloanaStart)
				matrice[linieDestinatie + 1][coloanaDestinatie - 1] = 0;
			else
				matrice[linieDestinatie + 1][coloanaDestinatie + 1] = 0;

		if (matrice[linieDestinatie][coloanaDestinatie] == jucator * 10)
		{
			if (jucator == 1)
			{
				if (coloanaDestinatie > coloanaStart)
					matrice[linieDestinatie + 1][coloanaDestinatie - 1] = 0;
				else
					matrice[linieDestinatie + 1][coloanaDestinatie + 1] = 0;
			}
			else
			{
				if (coloanaDestinatie > coloanaStart)
					matrice[linieDestinatie - 1][coloanaDestinatie - 1] = 0;
				else
					matrice[linieDestinatie - 1][coloanaDestinatie + 1] = 0;
			}
		}
	}
}
int castigatorJoc(int matrice[LINII_MAX][COLOANE_MAX], int dimensiune)
{
	int pieseAlbeRamase = 0;
	int pieseNegreRamase = 0;
	for (int i = 0; i < dimensiune; i++)
		for (int j = 0; j < dimensiune; j++)
			if (matrice[i][j] == 1 || matrice[i][j] == 10)
				pieseNegreRamase++;
			else if (matrice[i][j] == 2 || matrice[i][j] == 20)
				pieseAlbeRamase++;
	if (pieseNegreRamase == 0)
		return 2;
	if (pieseAlbeRamase == 0)
		return 1;
	return 0;
}

int main()
{
	struct sockaddr_in server; // structura folosita de server
	struct sockaddr_in from;
	int sd; //descriptorul de socket
	int optval = 1;
	char player1[100];
	char player2[100];
	int culoarePlayer1;
	int culoarePlayer2;
	int matrice[LINII_MAX][COLOANE_MAX] = {0};
	int linieStart;
	int coloanaStart;
	int linieDestinatie;
	int coloanaDestinatie;
	int jucator;
	int castigator = 0;
	int rezultat;
	int variatie;
	int dimensiune;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("[server]Eroare la socket().\n");
		return errno;
	}

	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	bzero(&server, sizeof(server));
	bzero(&from, sizeof(from));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		perror("[server]Eroare la bind().\n");
		return errno;
	}

	if (listen(sd, 1) == -1)
	{
		perror("[server]Eroare la listen().\n");
		return errno;
	}

	while (1)
	{
		int client1, client2;
		int length = sizeof(from);

		printf("[server]Asteptam la portul %d...\n", PORT);
		fflush(stdout);

		client1 = accept(sd, (struct sockaddr *)&from, &length);
		client2 = accept(sd, (struct sockaddr *)&from, &length);

		if (client1 < 0)
		{
			perror("[server]Eroare la accept().\n");
			continue;
		}
		if (client2 < 0)
		{
			perror("[server]Eroare la accept().\n");
			continue;
		}

		int pid;
		if ((pid = fork()) == -1)
		{
			close(client1);
			close(client2);
			continue;
		}
		else if (pid > 0)
		{
			// parinte
			close(client1);
			close(client2);
			while (waitpid(-1, NULL, WNOHANG))
				;
			continue;
		}
		else if (pid == 0)
		{
			// copil
			close(sd);
			bzero(player1, 100);
			bzero(player2, 100);

			//citirea numelui jucatorului 1 (client1)
			read(client1, player1, 100);
			printf("[server]Am primit de la clientul 1 numele: %s\n", player1);
			//citirea numelui jucatorului 2 (client2)
			read(client2, player2, 100);
			printf("[server]Am primit de la clientul 2 numele: %s\n", player2);

			//trimitere nume jucator2 catre jucator1
			write(client1, &player2, 100);
			//trimitere nume jucator1 catre jucator2
			write(client2, &player1, 100);

			//generare random a culorii jucatorilor
			culoarePlayer1 = generareCuloare();
			write(client1, &culoarePlayer1, sizeof(int));
			printf("[server]Culoare player1: %s = %d\n", decodificare(culoarePlayer1), culoarePlayer1);
			culoarePlayer2 = inversareCuloare(culoarePlayer1);
			write(client2, &culoarePlayer2, sizeof(int));
			printf("[server]Culoare player2: %s = %d\n", decodificare(culoarePlayer2), culoarePlayer2);

			if (culoarePlayer1 == 1)
				read(client1, &variatie, sizeof(int));
			else
				read(client2, &variatie, sizeof(int));
			
			if (variatie == 1)
				dimensiune = 8;
				else
				dimensiune = 12;
			write(client1, &dimensiune, sizeof(int));
			write(client2, &dimensiune, sizeof(int));

			initializareTabla(matrice, dimensiune);
			// matrice[0][0] = 1;
			// matrice[1][1] = 2;

			jucator = 1;

			while (castigator == 0)
			{
				for (int i = 0; i < dimensiune; i++)
					for (int j = 0; j < dimensiune; j++)
					{
						write(client1, &matrice[i][j], sizeof(int));
						write(client2, &matrice[i][j], sizeof(int));
					}
				afisareTabla(matrice, dimensiune);
				rezultat = 0;
				int client = jucator == culoarePlayer1 ? client1 : client2;
				while (rezultat == 0)
				{
					read(client, &linieStart, sizeof(int));
					read(client, &coloanaStart, sizeof(int));
					read(client, &linieDestinatie, sizeof(int));
					read(client, &coloanaDestinatie, sizeof(int));
					rezultat = verificareMutare(matrice, linieStart, coloanaStart, linieDestinatie, coloanaDestinatie, jucator);
					write(client, &rezultat, sizeof(int));
				}
				executareMutare(matrice, dimensiune, linieStart, coloanaStart, linieDestinatie, coloanaDestinatie, jucator, rezultat);
				castigator = castigatorJoc(matrice, dimensiune);
				write(client1, &castigator, sizeof(int));
				write(client2, &castigator, sizeof(int));
				jucator = inversareCuloare(jucator);
				write(client1, &jucator, sizeof(int));
				write(client2, &jucator, sizeof(int));
			}
			for (int i = 0; i < dimensiune; i++)
				for (int j = 0; j < dimensiune; j++)
				{
					write(client1, &matrice[i][j], sizeof(int));
					write(client2, &matrice[i][j], sizeof(int));
				}

			close(client1);
			close(client2);
			exit(0);
		}

	} /* while */
} /* main */