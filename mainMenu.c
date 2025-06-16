#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

typedef enum {
    FILMOVI = 1,
    IZLAZ = 0
}mainMenuOptions;

int mainMenu() {

    CLEAR_CONSOLE();

    printf("\n");
    printf("*********************************\n");
    printf("*    Dobrodosli u Videoteku!   *\n");
    printf("*********************************\n");
    printf("  1. FILMOVI                    \n");
    printf("  0. IZLAZ IZ PROGRAMA          \n");
    printf("*********************************\n");

    unsigned short option;
    unsigned short condition = 1;
    scanf("%hu", &option);
    getchar();

    switch ((mainMenuOptions)option) {
    case FILMOVI:
        while (condition) {
            condition = filmMenu();
        }
        break;
    case IZLAZ:
        printf("\nHvala sto ste koristili videoteku. Dovidjenja!\n");
        return 0;
    default:
        printf("\nNepoznata opcija! Pokusajte ponovo.\n");
        break;
    }
    return 1;
}
