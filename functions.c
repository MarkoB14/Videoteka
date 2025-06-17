#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "DATATYPE_H.h"
#include "functions.h"

extern int noFilms;
int nextID;

void createFile() {
    FILE* pF = fopen("films.bin", "wb");
    if (pF == NULL) {
		perror("\nGreška pri kreiranju datoteke films.bin!\n");
		exit(EXIT_FAILURE);
    }

    noFilms = 0;
	nextID = 0;
    fwrite(&noFilms, sizeof(int), 1, pF);

    fclose(pF);
    printf("\nDatoteka nije postojala, pa je morala biti kreirana!\n");
}

FILE* openFile(const char* mode) {
	FILE* pF = fopen("films.bin", mode);
	if (pF == NULL) {
		createFile();
		pF = fopen("films.bin", mode);
	}
	return pF;
}

void readFilms(FILM** arrayFilms) {
	FILE* pF = openFile("rb");
	fread(&noFilms, sizeof(int), 1, pF);
	fseek(pF, noFilms * sizeof(FILM) - sizeof(int), SEEK_CUR);
	fread(&nextID, sizeof(int), 1, pF);
	*arrayFilms = (FILM*)calloc(noFilms, sizeof(FILM));
	if (*arrayFilms == NULL) {
		printf("\nNedovoljno memorije za ucitavanje filmova!\n");
		fclose(pF);
		return;	
	}
	fseek(pF, sizeof(int), SEEK_SET);
	fread(*arrayFilms, sizeof(FILM), noFilms, pF);
	fclose(pF);
}

char* genrePrint(const GENRE genre) {
	static const char* genreNames[] = {
		"AKCIJA", "AVANTURA", "KOMEDIJA", "DRAMA", "HOROR", "TRILER",
		"ZNANSTVENA FANTASTIKA", "FANTAZIJA", "KRIMINALISTICKI", "MISTERIJA",
		"ROMANSA", "RATNI", "WESTERN", "ANIMIRANI", "DOKUMENTARNI",
		"MJUZIKL", "OBITELJSKI", "SPORT", "POVIJESNI"
	};

	if (genre < 0 || genre >= sizeof(genreNames) / sizeof(genreNames[0]))
		return "-";

	return (char*)genreNames[genre];
}

void addFilm() {

	CLEAR_CONSOLE();

	FILM tempFilm = { 0 };

	FILE* pF = openFile("rb+");

	fseek(pF, noFilms * sizeof(FILM), SEEK_SET);
	fread(&nextID, sizeof(int), 1, pF);

	tempFilm.id = nextID;

	printf("\n");
	printf("*********************************\n");
	printf("*    DODAVANJE FILMA   *\n");

	printf("* 1. IME: ");
	fgets(tempFilm.name, sizeof(tempFilm.name), stdin);
	tempFilm.name[strcspn(tempFilm.name, "\n")] = 0;

	do
	{
		printf("* 2. ZANR: ");
		printf("\n0) AKCIJA                   1) AVANTURA");
		printf("\n2) KOMEDIJA                 3) DRAMA");
		printf("\n4) HOROR                    5) TRILER");
		printf("\n6) ZNANSTVENA FANTASTIKA    7) FANTAZIJA");
		printf("\n8) KRIMINALISTICKI          9) MISTERIJA");
		printf("\n10) ROMANSA                 11) RATNI");
		printf("\n12) WESTERN                 13) ANIMIRANI");
		printf("\n15) DOKUMENTARNI            14) MJUZIKL");
		printf("\n16) OBITELJSKI              17) SPORT");
		printf("\n18) POVIJESNI                        \n\n");

		scanf(" %d", &tempFilm.genre);
	} while (tempFilm.genre < 0 || tempFilm.genre > 18);
	

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
	nextID++;
	rewind(pF);
	fwrite(&noFilms, sizeof(int), 1, pF);

	fclose(pF);
}

void showAllFilms(const short unsigned enter) {

	CLEAR_CONSOLE();

	FILM* arrayFilms = NULL;
	
	FILE* pF = openFile("rb");

	readFilms(&arrayFilms);
	if(arrayFilms == NULL) {
		printf("\nNema filmova za ispis!\n");
		fclose(pF);
		getchar();
		return;
	}

	printf("** ISPIS SVIH FILMOVA **\n");
	printf("%-5s %-30s %-30s %-15s %-20s %-15s \n", "ID", "Ime filma", "Zanr", "Trajanje", "Godina Izdanja", "Broj primjeraka");

	printf("------------------------------------------------------------------------------------------------------------------------ \n");

	for (int i = 0; i < noFilms; i++) {
		printf("%-5d %-30s %-30s %-15d %-20d %-15d\n", (arrayFilms + i)->id, (arrayFilms + i)->name, genrePrint((arrayFilms+i)->genre),(arrayFilms + i)->duration, (arrayFilms + i)->year, (arrayFilms + i)->copies);
	}

	arrayFilms = NULL;
	free(arrayFilms);
	fclose(pF);

	if(enter) {
		printf("\nPritisnite 'ENTER' za povratak u izbornik...\n");
		getchar();
	}
	
}

void removeFilm() {

	CLEAR_CONSOLE();

	int id = -1;
	FILM* arrayFilms = NULL;

	readFilms(&arrayFilms);

	if (noFilms == 0) {
		printf("\nNema filmova za brisanje!\n");
		getchar();
		return;
	}

	showAllFilms(0);

	printf("\nUnesite ID filma koji zelite obrisati: ");
	scanf(" %d", &id);

	FILE* pF = fopen("films.bin", "wb+");
	if (pF == NULL) {
		printf("\nGreska pri otvaranju datoteke films.bin!\n");
		return;
	}

	fseek(pF, sizeof(int), SEEK_SET);

	noFilms--;

	for(int i = 0;i <= noFilms; i++) {
		if((arrayFilms + i)->id != id) {
			fwrite((arrayFilms + i), sizeof(FILM), 1, pF);
		}
	}

	rewind(pF);
	fwrite(&noFilms, sizeof(int), 1, pF);

	arrayFilms = NULL;
	free(arrayFilms);
	fclose(pF);
}

void updateFilm() {

	CLEAR_CONSOLE();

	int id = -1;

	FILM* arrayFilms = NULL;
	readFilms(&arrayFilms);

	if (noFilms == 0) {
		printf("\nNema filmova za azurirati!\n");
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
		printf("\n0) AKCIJA                   1) AVANTURA");
		printf("\n2) KOMEDIJA                 3) DRAMA");
		printf("\n4) HOROR                    5) TRILER");
		printf("\n6) ZNANSTVENA FANTASTIKA    7) FANTAZIJA");
		printf("\n8) KRIMINALISTICKI          9) MISTERIJA\n");
		printf("\n10) ROMANSA                 11) RATNI\n");
		printf("\n12) WESTERN                 13) ANIMIRANI\n");
		printf("\n15) DOKUMENTARNI            14) MJUZIKL\n");
		printf("\n16) OBITELJSKI              17) SPORT\n");
		printf("\n18) POVIJESNI                        \n");

		scanf(" %d", &tempFilm.genre);
	} while (tempFilm.genre < 0 || tempFilm.genre > 18);

	printf("* 3. TRAJANJE: ");
	scanf(" %d", &tempFilm.duration);

	printf("* 4. GODINA IZDANJA: ");
	scanf(" %d", &tempFilm.year);

	printf("* 5. BROJ PRIMJERAKA: ");
	scanf(" %d", &tempFilm.copies);

	printf("*********************************\n");

	FILE * pF = openFile("rb+");
	
	fseek(pF, sizeof(int) + id * sizeof(FILM), SEEK_SET);
	fwrite(&tempFilm, sizeof(FILM), 1, pF);

	fclose(pF);
	arrayFilms = NULL;
	free(arrayFilms);
}

int compareFilmsByName(const void* a, const void* b) {
	const FILM* filmA = (const FILM*)a;
	const FILM* filmB = (const FILM*)b;
	return strcmp(filmA->name, filmB->name);
}

int compareFilmNameKey(const void* key, const void* element) {
	const char* nameKey = (const char*)key;
	const FILM* film = (const FILM*)element;
	return strcmp(nameKey, film->name);
}

void sortFilmsByName(FILM* arrayFilms) {
	if (arrayFilms == NULL || noFilms <= 1) {
		return;
	}
	qsort(arrayFilms, noFilms, sizeof(FILM), compareFilmsByName);
}


void filmSearch() {

	CLEAR_CONSOLE();

	FILM* arrayFilms = NULL;
	FILM* foundFilm = NULL;

	char filmName[51];

	printf("*********************************\n");
	printf("*    PRETRAGA FILMA   *\n");
	printf("* IME: ");
	fgets(filmName, sizeof(filmName), stdin);
	filmName[strcspn(filmName, "\n")] = '\0';

	readFilms(&arrayFilms);

	sortFilmsByName(arrayFilms);

	foundFilm = (FILM*)bsearch(filmName, arrayFilms, noFilms, sizeof(FILM), compareFilmNameKey);

	if (foundFilm != NULL) {
		printf("FILM PRONADJEN!\n");

		printf("%-5s %-30s %-30s %-15s %-20s %-15s \n", "ID", "Ime filma", "Zanr", "Trajanje", "Godina Izdanja", "Broj primjeraka");

		printf("------------------------------------------------------------------------------------------------------------------------\n");

		printf("%-5d %-30s %-30s %-15d %-20d %-15d\n", foundFilm->id, foundFilm->name, genrePrint(foundFilm->genre), foundFilm->duration, foundFilm->year, foundFilm->copies);
		
	}
	else {
		printf("FILM NIJE PRONADJEN!");
	}

	printf("\nPritisnite 'ENTER' za povratak u izbornik...\n");
	getchar();
}

void deleteFile() {
	printf("Zelite li uistinu obrisati datoteku 'films.bin'?\n");
	printf("Utipkajte 'da' ako uistinu zelite obrisati datoteku u suprotnom utipkajte 'ne' !\n");
	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (!strcmp("da", potvrda)) {

		potvrda[0] = '\0';

		printf("Utipkajte 'da' ako zelite napraviti backup u suprotnom utipkajte 'ne' !\n");

		scanf("%2s", potvrda);

		if (!strcmp("da", potvrda)) {
			rename("films.bin", "films_backup.bin");
		}
		else {
			remove("films.bin") == 0 ? printf("Uspjesno obrisana datoteka!\n") : printf("Neuspjesno brisanje datoteke!\n");
		}
	}
}