#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

int noFilms = 0;

typedef enum {
    SHOWALL = 1,
    SEARCH = 2,
    INSERT = 3,
    REMOVE = 4,
    UPDATE = 5,
    DELETE = 6,
    RETURN = 0
}filmMenuOptions;

int filmMenu() {

    CLEAR_CONSOLE();

    printf("\n");
    printf("*********************************\n");
    printf("*    FILMOVI   *\n");
    printf("*********************************\n");
    printf("  1. PRIKAZI SVE FILMOVE           \n");
    printf("  2. PRETRAGA                  \n");
    printf("  3. DODAJ FILM                \n");
    printf("  4. OBRISI FILM               \n");
    printf("  5. AZURIRAJ FILM             \n");
    printf("  6. OBRISI DATOTEKU           \n");
    printf("  0. POVRATAK                  \n");
    printf("*********************************\n");

    unsigned short option;
    scanf("%hu", &option);
	getchar();

    switch (option) {
    case SHOWALL:
        showAllFilms(1);
        break;
    case SEARCH:
        filmSearch();
        break;
    case INSERT:
        addFilm();
        break;
    case REMOVE:
        removeFilm();
        break;
    case UPDATE:
        updateFilm();
        break;
    case DELETE:
        deleteFile();
        break;
    case RETURN:
        return 0;
    default:
        printf("\nNepoznata opcija! Pokusajte ponovo.\n");
        break;
    }
    return 1;
}