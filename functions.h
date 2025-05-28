#include "stdio.h"
#ifndef functions
#define functions

#include "DATATYPE_H.h"

#ifdef _WIN32
	#define CLEAR_CONSOLE() system("cls")
#else
	#define CLEAR_CONSOLE() system("clear")
#endif

int mainMenu();
int filmMenu();
char* genrePrint(GENRE genre);
void createFile();
FILE* openFile(const char* mode);
void readFilms(FILM** arrayFilms);
void addFilm();
void showAllFilms(short unsigned enter);
void removeFilm();
void updateFilm();
int compareFilmsByName(const void* a, const void* b);
int compareFilmNameKey(const void* key, const void* element);
void sortFilmsByName(FILM* arrayFilms);
FILM* searchFilmByName(FILM* arrayFilms, int noFilms, const char* name);
void filmSearch();
void deleteFile();

#endif
