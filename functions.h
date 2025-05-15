#ifndef functions
#define functions

#include "DATATYPE_H.h"

void clearConsole();
int mainMenu();
int filmMenu();
void createFile();
void readFilms(int* noFilms, FILM** arrayFilms);
void addFilm();
void showAllFilms(short unsigned enter);
void deleteFilm();
void updateFilm();

#endif
