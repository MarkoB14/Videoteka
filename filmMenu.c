#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

int noFilms = 0;

int filmMenu() {

    clearConsole();

    printf("\n");
    printf("*********************************\n");
    printf("*    FILMOVI   *\n");
    printf("*********************************\n");
    printf("  1. PRIKAZI SVE FILMOVE           \n");
    printf("  2. PRETRAGA                  \n");
    printf("  3. DODAJ FILM                \n");
    printf("  4. OBRISI FILM               \n");
    printf("  5. AZURIRAJ FILM             \n");
    printf("  0. POVRATAK                  \n");
    printf("*********************************\n");

    unsigned short option;
    scanf("%hu", &option);
	getchar();

    switch (option) {
    case 1:
        showAllFilms(1);
        break;
    case 2:
        printf("\nPRETRAGA!\n");
        break;
    case 3:
        addFilm();
        break;
    case 4:
        deleteFilm();
        break;
    case 5:
        updateFilm();
        break;
    case 0:
        return 0;
    default:
        printf("\nNepoznata opcija! Pokusajte ponovo.\n");
        break;
    }
    return 1;
}