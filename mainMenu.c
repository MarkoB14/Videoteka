﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

int mainMenu() {

    clearConsole();

    printf("\n");
    printf("*********************************\n");
    printf("*    Dobrodosli u Videoteku!   *\n");
    printf("*********************************\n");
    printf("  1. FILMOVI                    \n");
    printf("  2. KORISNICI                  \n");
    printf("  0. IZLAZ IZ PROGRAMA          \n");
    printf("*********************************\n");

    unsigned short option;
    unsigned short condition = 1;
    scanf("%hu", &option);
    getchar();

    switch (option) {
    case 1:
        while (condition) {
            condition = filmMenu();
        }
        break;
    case 2:
        printf("\nOdabrali ste opciju 'KORISNICI'.\n");
        break;
    case 0:
        printf("\nHvala sto ste koristili videoteku. Dovidjenja!\n");
        return 0;
    default:
        printf("\nNepoznata opcija! Pokusajte ponovo.\n");
        break;
    }
    return 1;
}
