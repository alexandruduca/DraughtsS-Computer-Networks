#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#define LINII_MAX 12
#define COLOANE_MAX 12
#define MESAJ_MUTARE "Este randul dumneavoastra!\n"
#define MESAJ_ASTEPTARE "Nu este randul dumneavoastra. Asteptati adversarul sa efectueze o mutare!\n"
#define MESAJ_LINIE_START "Linia piesei aleasa: "
#define MESAJ_COLOANA_START "Coloana piesei aleasa: "
#define MESAJ_LINIE_DESTINATIE "Linia unde vreti sa mutati: "
#define MESAJ_COLOANA_DESTINATIE "Coloana unde vreti sa mutati: "
#define MESAJ_INPUT_INVALID "Input invalid. Incercati din nou!\n"
#define MESAJ_VICTORIE "Felicitari! Ati castigat!\n"
#define MESAJ_INFRANGERE "Din pacate ati pierdut!\n"

char *decodificare(int culoare)
{
  if (culoare == 1)
    return "Negru";
  return "Alb";
}
void afisareTabla(int matrice[LINII_MAX][COLOANE_MAX], int dimensiune, int culoare)
{
  if (culoare == 1)
  {
    if (dimensiune == 8)
    {
      printf("    0 1 2 3 4 5 6 7\n");
      printf("  |----------------\n");
      for (int i = dimensiune - 1; i >= 0; i--)
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
      for (int i = dimensiune - 1; i >= 0; i--)
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
  else
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
}
void mesajJucator(int jucator, int culoare)
{
  if (jucator == culoare)
    printf("%s", MESAJ_MUTARE);
  else
    printf("%s", MESAJ_ASTEPTARE);
}
void mesajFinal(int castigator, int culoare)
{
  if (castigator == culoare)
    printf("%s", MESAJ_VICTORIE);
  else
    printf("%s", MESAJ_INFRANGERE);
}

extern int errno;

int port;

int main(int argc, char *argv[])
{
  int sd;                    // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare
  char msg[256];             // mesajul trimis
  int culoare = 0;
  int matrice[LINII_MAX][COLOANE_MAX] = {0};
  int linieStart;
  int coloanaStart;
  int linieDestinatie;
  int coloanaDestinatie;
  int piese;
  int jucator;
  int castigator = 0;
  int rezultat;
  int variatie = 0;
  int dimensiune;

  if (argc != 3)
  {
    printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }

  port = atoi(argv[2]);

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la socket().\n");
    return errno;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons(port);

  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Eroare la connect().\n");
    return errno;
  }

  bzero(msg, 100);
  printf("Introduceti un nume: ");
  fflush(stdout);
  // citirea numelui
  read(0, msg, 100);
  msg[strlen(msg) - 1] = '\0';
  // trimiterea numelui catre server
  write(sd, msg, 100);
  // citirea numelui adversarului
  read(sd, msg, 100);
  printf("Jucati impotriva lui %s\n", msg);
  fflush(stdout);
  read(sd, &culoare, sizeof(int));
  printf("Veti juca cu piesele de culoarea %s\n", decodificare(culoare));
  fflush(stdout);

  jucator = 1;
  while (culoare == jucator && variatie != 1 && variatie != 2)
  {
    printf("Ce tip de Dame vreti sa jucati?\n");
    printf("1. International Draughts\n");
    printf("2. Canadian / Sri Lankan Draughts\n");
    scanf("%d", &variatie);
    if (variatie != 1 && variatie != 2)
      printf("%s", MESAJ_INPUT_INVALID);
    else
      write(sd, &variatie, sizeof(int));
  }
  read(sd, &dimensiune, sizeof(int));

  while (castigator == 0)
  {
    for (int i = 0; i < dimensiune; i++)
      for (int j = 0; j < dimensiune; j++)
      {
        read(sd, &piese, sizeof(int));
        matrice[i][j] = piese;
      }
    afisareTabla(matrice, dimensiune, culoare);
    mesajJucator(jucator, culoare);
    rezultat = 0;
    while (jucator == culoare)
    {
      printf("%s", MESAJ_LINIE_START);
      scanf("%d", &linieStart);
      printf("%s", MESAJ_COLOANA_START);
      scanf("%d", &coloanaStart);
      printf("%s", MESAJ_LINIE_DESTINATIE);
      scanf("%d", &linieDestinatie);
      printf("%s", MESAJ_COLOANA_DESTINATIE);
      scanf("%d", &coloanaDestinatie);

      write(sd, &linieStart, sizeof(int));
      write(sd, &coloanaStart, sizeof(int));
      write(sd, &linieDestinatie, sizeof(int));
      write(sd, &coloanaDestinatie, sizeof(int));

      read(sd, &rezultat, sizeof(int));
      if (rezultat != 0)
        break;
      printf("%s", MESAJ_INPUT_INVALID);
      afisareTabla(matrice, dimensiune, culoare);
    }
    read(sd, &castigator, sizeof(int));
    read(sd, &jucator, sizeof(int));
  }
  for (int i = 0; i < dimensiune; i++)
    for (int j = 0; j < dimensiune; j++)
    {
      read(sd, &piese, sizeof(int));
      matrice[i][j] = piese;
    }
  afisareTabla(matrice, dimensiune, culoare);
  mesajFinal(castigator, culoare);

  close(sd);
}