#ifndef DATATYPE_H
#define DATATYPE_H

typedef enum genre{
    AKCIJA,
    AVANTURA,
    KOMEDIJA,
    DRAMA,
    HOROR,
    TRILER,
    ZNANSTVENA_FANTASTIKA,
    FANTAZIJA,
    KRIMINALISTICKI,
    MISTERIJA,
    ROMANSA,
    RATNI,
    WESTERN,
    ANIMIRANI,
    DOKUMENTARNI,
    MJUZIKL,
    OBITELJSKI,
    SPORT,
    POVIJESNI
} GENRE;

typedef struct film {
	int id;
	char name[51];
	GENRE genre;
	int duration;
	int year;
	int copies;
}FILM;

typedef struct user {
	int id;
	char name[21];
	char lastname[21];
	short noMovies;
	int* movies;
} USER;
#endif

