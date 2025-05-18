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
void createFile();
FILE* openFile(const char* mode);
void readFilms(int* noFilms, FILM** arrayFilms);
void addFilm();
void showAllFilms(short unsigned enter);
void deleteFilm();
void updateFilm();

#endif
