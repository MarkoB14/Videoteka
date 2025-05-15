#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATATYPE_H.h"

void clearConsole() {

	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void createFile() {
    FILE* pF = fopen("films.bin", "wb");
    if (pF == NULL) {
        printf("\nGreška pri kreiranju datoteke films.bin!\n");
		exit(EXIT_FAILURE);
    }

    int noFilms = 0;
    fwrite(&noFilms, sizeof(int), 1, pF);

    fclose(pF);
    printf("\nDatoteka nije postojala, pa je morala biti kreirana!\n");
}

void readFilms(int* noFilms, FILM** arrayFilms) {
	FILE* pF = fopen("films.bin", "rb");
	if (pF == NULL) {
		createFile();
		pF = fopen("films.bin", "rb");
	}
	fread(noFilms, sizeof(int), 1, pF);
	*arrayFilms = (FILM*)calloc(*noFilms, sizeof(FILM));
	if (*arrayFilms == NULL) {
		printf("\nNedovoljno memorije za ucitavanje filmova!\n");
		fclose(pF);
		return;	
	}
	fseek(pF, sizeof(int), SEEK_SET);
	fread(*arrayFilms, sizeof(FILM), *noFilms, pF);
	fclose(pF);
}

void addFilm() {

	clearConsole();

	FILM tempFilm = { 0 };
	int noFilms = 0;

	FILE* pF = fopen("films.bin", "rb+");
	if (pF == NULL) {
		createFile();
		pF = fopen("films.bin", "rb+");
	}

	fread(&noFilms, sizeof(int), 1, pF);
	tempFilm.id = noFilms;

	printf("\n");
	printf("*********************************\n");
	printf("*    DODAVANJE FILMA   *\n");

	printf("* 1. IME: ");
	fgets(tempFilm.name, sizeof(tempFilm.name), stdin);
	tempFilm.name[strcspn(tempFilm.name, "\n")] = 0;

	do
	{
		printf("* 2. ZANR: ");
		printf("\n0) DRAMA     1) KOMEDIJA");
		printf("\n2) AKCIJA    3) SCIFI");
		printf("\n4) FANTAZIJA 5) HOROR");
		printf("\n6) TRILER    7) ROMANSA");
		printf("\n8) MISTERIJA 9) ANIMIRANI\n");
		scanf(" %d", &tempFilm.genre);
	} while (tempFilm.genre < 0 || tempFilm.genre > 9);
	

	printf("* 3. TRAJANJE: ");
	scanf(" %d", &tempFilm.duration);

	printf("* 4. GODINA IZDANJA: ");
	scanf(" %d", &tempFilm.year);

	printf("* 5. BROJ PRIMJERAKA: ");
	scanf(" %d", &tempFilm.copies);
	printf("*********************************\n");
	
	fseek(pF, sizeof(int) + noFilms * sizeof(FILM), SEEK_SET);
	fwrite(&tempFilm, sizeof(FILM), 1, pF);

	noFilms++;
	rewind(pF);
	fwrite(&noFilms, sizeof(int), 1, pF);

	fclose(pF);
}

void showAllFilms(short unsigned enter) {

	clearConsole();

	FILE* pF = fopen("films.bin", "rb");
	int noFilms = 0;
	FILM* arrayFilms = NULL;
	
	if (pF == NULL) {
		createFile();
		pF = fopen("films.bin", "rb");
	}
	
	readFilms(&noFilms, &arrayFilms);
	if(arrayFilms == NULL) {
		printf("\nNema filmova za ispis!\n");
		fclose(pF);
		getchar();
		return;
	}

	printf("** ISPIS SVIH FILMOVA **\n");
	printf("%-5s %-30s %-10s %-15s %-20s %-15s\n", "ID", "Ime filma", "Zanr", "Trajanje", "Godina Izdanja", "Broj primjeraka");

	printf("--------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < noFilms; i++) {
		printf("%-5d %-30s %-10d %-15d %-20d %-15d\n", (arrayFilms + i)->id, (arrayFilms + i)->name, (arrayFilms + i)->genre, (arrayFilms + i)->duration, (arrayFilms + i)->year, (arrayFilms + i)->copies);
	}

	arrayFilms = NULL;
	free(arrayFilms);
	fclose(pF);

	if(enter) {
		printf("\nPritisnite 'ENTER' za povratak u izbornik...\n");
		getchar();
	}
	
}

void deleteFilm() {

	clearConsole();

	int noFilms = 0;
	int id = -1;
	FILM* arrayFilms = NULL;

	readFilms(&noFilms, &arrayFilms);

	if (noFilms == 0) {
		printf("\nNema filmova za brisanje!\n");
		getchar();
		return;
	}

	if (arrayFilms == NULL) {
		printf("\nNedovoljno memorije za ucitavanje filmova!\n");
		getchar();
		return;
	}

	showAllFilms(0);

	do {
		printf("\nUnesite ID filma koji želite obrisati: ");
		scanf(" %d", &id);
	} while (id < 0 || id >= noFilms);

	FILE* pF = fopen("films.bin", "wb+");
	if (pF == NULL) {
		printf("\nGreška pri otvaranju datoteke films.bin!\n");
		return;
	}

	fseek(pF, sizeof(int), SEEK_SET);

	for(int i = 0;i < noFilms; i++) {
		if((arrayFilms + i)->id != id) {
			if ((arrayFilms + i)->id > id) {
				(arrayFilms + i)->id--;
			}
			fwrite((arrayFilms + i), sizeof(FILM), 1, pF);
		}
	}

	noFilms--;
	rewind(pF);
	fwrite(&noFilms, sizeof(int), 1, pF);

	arrayFilms = NULL;
	free(arrayFilms);
	fclose(pF);
}

void updateFilm() {
	clearConsole();
	int noFilms = 0;
	int id = -1;
	FILM* arrayFilms = NULL;
	readFilms(&noFilms, &arrayFilms);
	if (noFilms == 0) {
		printf("\nNema filmova za azurirati!\n");
		getchar();
		return;
	}
	if (arrayFilms == NULL) {
		printf("\nNedovoljno memorije za ucitavanje filmova!\n");
		getchar();
		return;
	}
	showAllFilms(0);
	do {
		printf("\nUnesite ID filma koji zelite azurirati: ");
		scanf(" %d", &id);
		getchar();
	} while (id < 0 || id >= noFilms);
	FILM tempFilm = { 0 };
	tempFilm.id = id;
	printf("\n");
	printf("*********************************\n");
	printf("*    AZURIRANJE FILMA   *\n");
	printf("* 1. IME: ");
	fgets(tempFilm.name, sizeof(tempFilm.name), stdin);
	tempFilm.name[strcspn(tempFilm.name, "\n")] = 0;
	do
	{
		printf("* 2. ZANR: ");
		printf("\n0) DRAMA     1) KOMEDIJA");
		printf("\n2) AKCIJA    3) SCIFI");
		printf("\n4) FANTAZIJA 5) HOROR");
		printf("\n6) TRILER    7) ROMANSA");
		printf("\n8) MISTERIJA 9) ANIMIRANI\n");
		scanf(" %d", &tempFilm.genre);
	} while (tempFilm.genre < 0 || tempFilm.genre > 9);
	printf("* 3. TRAJANJE: ");
	scanf(" %d", &tempFilm.duration);
	printf("* 4. GODINA IZDANJA: ");
	scanf(" %d", &tempFilm.year);
	printf("* 5. BROJ PRIMJERAKA: ");
	scanf(" %d", &tempFilm.copies);
	printf("*********************************\n");
	FILE* pF = fopen("films.bin", "rb+");
	if (pF == NULL) {
		printf("\nGreška pri otvaranju datoteke films.bin!\n");
		return;
	}
	fseek(pF, sizeof(int) + id * sizeof(FILM), SEEK_SET);
	fwrite(&tempFilm, sizeof(FILM), 1, pF);

	fclose(pF);
	arrayFilms = NULL;
	free(arrayFilms);
}