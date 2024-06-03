
#ifndef F1_H
#define F1_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LENGTH 100
#define FILENAME "formula1_data.txt"
#define INITIAL_CAPACITY 10
#define MAX_VOZACI 100  

typedef struct {
    int id;
    char ime[MAX_LENGTH];
    char prezime[MAX_LENGTH];
    char drzava[MAX_LENGTH];
    char tim[MAX_LENGTH];
    int dob;
    int bodovi;
} vozac;

typedef enum {
    BODOVI_UZLAZNO,
    BODOVI_SILAZNO,
    IME_UZLAZNO,
    IME_SILAZNO,
    ID_UZLAZNO,
    ID_SILAZNO
} kriterij_sortiranja;

static vozac* vozaci = NULL;
static int broj_vozaca = 0;
static int kapacitet_vozaca = 0;
static int globalni_id = 0;

void unos_vozaca();
void citanje_vozaca();
void brisanje_vozaca();
void azuriraj_podatke();
void spremi_podatke();
void sortiraj_vozace(kriterij_sortiranja kriterij);
void izbornik();
void ucitaj_podatke();
void kopiraj_datoteku(const char* source, const char* dest);
void quicksort(vozac* arr, int left, int right, kriterij_sortiranja kriterij);
void oslobodi_memoriju();

#endif // F1_H
