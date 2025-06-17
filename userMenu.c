#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

typedef enum {
    SHOWALL = 1,
    SEARCH = 2,
    INSERT = 3,
    DELETE = 4,
    UPDATE = 5,
    BORROW = 6,
    RETURN = 0
}usernMenuOptions;

int userMenu() {

    CLEAR_CONSOLE();

    printf("\n");
    printf("*********************************\n");
    printf("*    CLANOVI   *\n");
    printf("*********************************\n");
    printf("  1. PRIKAZI SVE CLANOVE           \n");
    printf("  2. PRETRAGA                  \n");
    printf("  3. DODAJ CLANA                \n");
    printf("  4. OBRISI CLANA               \n");
    printf("  5. AZURIRAJ CLANA             \n");
    printf("  0. POVRATAK                  \n");
    printf("*********************************\n");

    unsigned short option;
    scanf("%hu", &option);
    getchar();

    switch (option) {
    case SHOWALL:
        
        break;
    case SEARCH:
        
        break;
    case INSERT:
        
        break;
    case DELETE:
        
        break;
    case UPDATE:
        
        break;
    case RETURN:
        return 0;
    default:
        printf("\nNepoznata opcija! Pokusajte ponovo.\n");
        break;
    }
    return 1;
}