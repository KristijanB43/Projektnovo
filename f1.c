#include "f1.h"

typedef enum {
    IZLAZ = 0,
    UNOS_VOZACA,
    CITANJE_VOZACA,
    BRISANJE_VOZACA,
    AZURIRANJE_PODATAKA,
    SORTIRANJE_VOZACA
} opcije;

const char* timovi[] = {
    "Red Bull",
    "Mercedes",
    "McLaren",
    "Ferrari",
    "Alpine",
    "Aston Martin",
    "Visa Cash App RB",
    "Williams",
    "Kick Sauber",
    "Haas"
};

void prikazi_timove() {
    printf("\n-----------------------------------\n");
    printf("Odaberite tim:\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, timovi[i]);
    }
}

void oslobodi_memoriju() {
    if (vozaci) {
        free(vozaci);
        vozaci = NULL;
    }
}

void provjeri_kapacitet() {
    if (broj_vozaca >= kapacitet_vozaca) {
        kapacitet_vozaca = kapacitet_vozaca == 0 ? INITIAL_CAPACITY : kapacitet_vozaca * 2;
        vozac* novi_vozaci = realloc(vozaci, kapacitet_vozaca * sizeof(vozac));
        if (!novi_vozaci) {
            perror("Greska pri alociranju memorije");
            oslobodi_memoriju();
            exit(EXIT_FAILURE);
        }
        vozaci = novi_vozaci;
    }
}

void spremi_podatke() {
    FILE* file = fopen(FILENAME, "w");
    if (!file) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    for (int i = 0; i < broj_vozaca; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%d\n", vozaci[i].id, vozaci[i].ime, vozaci[i].prezime, vozaci[i].drzava, vozaci[i].tim, vozaci[i].dob, vozaci[i].bodovi);
    }

    fclose(file);
    printf("Podaci uspjesno azurirani u datoteci.\n");
    printf("-----------------------------------\n");
}

void unos_vozaca() {
    if (broj_vozaca >= MAX_VOZACI) {
        printf("Dosegnut maksimalan broj vozaca.\n");
        return;
    }

    provjeri_kapacitet();

    vozac novi_vozac;
    globalni_id++;
    novi_vozac.id = globalni_id;

    printf("\nUnesite ime vozaca: ");
    scanf("%s", novi_vozac.ime);
    printf("Unesite prezime vozaca: ");
    scanf("%s", novi_vozac.prezime);
    printf("Unesite drzavu vozaca: ");
    scanf("%s", novi_vozac.drzava);

    int izbor_tima;
    do {
        prikazi_timove();
        printf("-----------------------------------\n");
        printf("Unesite broj tima (1-10): ");
        if (scanf("%d", &izbor_tima) != 1 || izbor_tima < 1 || izbor_tima > 10) {
            printf("Neispravan unos. Pokusajte ponovo.\n");
            while (getchar() != '\n'); // Čišćenje ulaza
        }
        else {
            strcpy(novi_vozac.tim, timovi[izbor_tima - 1]);
            break;
        }
    } while (1);

    printf("Unesite dob vozaca: ");
    while (scanf("%d", &novi_vozac.dob) != 1) {
        printf("Neispravan unos. Unesite ponovo dob: ");
        while (getchar() != '\n'); // Čišćenje ulaza
    }
    printf("Unesite broj bodova vozaca: ");
    while (scanf("%d", &novi_vozac.bodovi) != 1) {
        printf("Neispravan unos. Unesite ponovo broj bodova: ");
        while (getchar() != '\n'); // Čišćenje ulaza
    }

    vozaci[broj_vozaca++] = novi_vozac;

    printf("\n-----------------------------------\n");
    printf("Vozac uspjesno dodan.\n");
    printf("-----------------------------------\n");

    spremi_podatke();
}

void citanje_vozaca() {
    if (broj_vozaca == 0) {
        printf("Nema unesenih vozaca.\n");
        return;
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("|  ID |         Ime        |        Prezime       |     Drzava     |          Tim         | Godine |  Bodovi  |\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < broj_vozaca; i++) {
        printf("| %3d | %18s | %20s | %14s | %20s | %6d | %8d |\n", vozaci[i].id, vozaci[i].ime, vozaci[i].prezime, vozaci[i].drzava, vozaci[i].tim, vozaci[i].dob, vozaci[i].bodovi);
    }
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void brisanje_vozaca() {
    int id;
    printf("\n-----------------------------------\n");
    printf("Unesite ID vozaca kojeg zelite izbrisati: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    int found = 0;
    for (int i = 0; i < broj_vozaca; i++) {
        if (vozaci[i].id == id) {
            for (int j = i; j < broj_vozaca - 1; j++) {
                vozaci[j] = vozaci[j + 1];
            }
            broj_vozaca--;
            found = 1;
            printf("Vozac uspjesno obrisan.\n");
            break;
        }
    }

    if (!found) {
        printf("\n-----------------------------------\n");
        printf("Vozac sa ID %d nije pronaden.\n", id);
        printf("-----------------------------------\n");
    }

    spremi_podatke();
}

void azuriraj_podatke() {
    citanje_vozaca();

    int id;
    printf("\nUnesite ID vozaca kojeg zelite azurirati:\n");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    int found = 0;
    for (int i = 0; i < broj_vozaca; i++) {
        if (vozaci[i].id == id) {
            found = 1;

            printf("\nUnesite novo ime vozaca (trenutno: %s): ", vozaci[i].ime);
            scanf("%s", vozaci[i].ime);
            printf("Unesite novo prezime vozaca (trenutno: %s): ", vozaci[i].prezime);
            scanf("%s", vozaci[i].prezime);
            printf("Unesite novu drzavu vozaca (trenutno: %s): ", vozaci[i].drzava);
            scanf("%s", vozaci[i].drzava);

            int izbor_tima;
            do {
                prikazi_timove();
                printf("Unesite novi tim vozaca (trenutno: %s): ", vozaci[i].tim);
                if (scanf("%d", &izbor_tima) != 1 || izbor_tima < 1 || izbor_tima > 10) {
                    printf("Neispravan unos. Pokusajte ponovo.\n");
                    while (getchar() != '\n'); // Čišćenje ulaza
                }
                else {
                    strcpy(vozaci[i].tim, timovi[izbor_tima - 1]);
                    break;
                }
            } while (1);
            printf("Unesite novu dob vozaca (trenutno: %d): ", vozaci[i].dob);
            while (scanf("%d", &vozaci[i].dob) != 1) {
                printf("Neispravan unos. Unesite ponovo dob: ");
                while (getchar() != '\n'); // Čišćenje ulaza
            }
            printf("Unesite novi broj bodova vozaca (trenutno: %d): ", vozaci[i].bodovi);
            while (scanf("%d", &vozaci[i].bodovi) != 1) {
                printf("Neispravan unos. Unesite ponovo broj bodova: ");
                while (getchar() != '\n'); // Čišćenje ulaza
            }
            printf("\n-----------------------------------\n");
            printf("Vozac uspjesno azuriran.\n");
            printf("-----------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\n-----------------------------------\n");
        printf("Vozac sa ID %d nije pronaden.\n", id);
        printf("-----------------------------------\n");
    }

    spremi_podatke();
}

void quicksort(vozac* arr, int left, int right, kriterij_sortiranja kriterij) {
    if (left >= right) {
        return;
    }

    int i = left, j = right;
    vozac pivot = arr[(left + right) / 2];

    while (i <= j) {
        switch (kriterij) {
        case BODOVI_UZLAZNO:
            while (arr[i].bodovi < pivot.bodovi) i++;
            while (arr[j].bodovi > pivot.bodovi) j--;
            break;
        case BODOVI_SILAZNO:
            while (arr[i].bodovi > pivot.bodovi) i++;
            while (arr[j].bodovi < pivot.bodovi) j--;
            break;
        case IME_UZLAZNO:
            while (strcmp(arr[i].ime, pivot.ime) < 0) i++;
            while (strcmp(arr[j].ime, pivot.ime) > 0) j--;
            break;
        case IME_SILAZNO:
            while (strcmp(arr[i].ime, pivot.ime) > 0) i++;
            while (strcmp(arr[j].ime, pivot.ime) < 0) j--;
            break;
        case ID_UZLAZNO:
            while (arr[i].id < pivot.id) i++;
            while (arr[j].id > pivot.id) j--;
            break;
        case ID_SILAZNO:
            while (arr[i].id > pivot.id) i++;
            while (arr[j].id < pivot.id) j--;
            break;
        }

        if (i <= j) {
            vozac temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) quicksort(arr, left, j, kriterij);
    if (i < right) quicksort(arr, i, right, kriterij);
}

void sortiraj_vozace() {
    if (broj_vozaca < 2) {
        printf("Nema dovoljno vozaca za sortiranje.\n");
        return;
    }

    int izbor;
    printf("\nOdaberite kriterij za sortiranje:\n");
    printf("1. Bodovi - (Uzlazno)\n");
    printf("2. Bodovi - (Silazno)\n");
    printf("3. Ime - (Uzlazno)\n");
    printf("4. Ime - (Silazno)\n");
    printf("5. ID - (Uzlazno)\n");
    printf("6. ID - (Silazno)\n");
    printf("Izbor: ");
    if (scanf("%d", &izbor) != 1 || izbor < 1 || izbor > 6) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    kriterij_sortiranja kriterij = izbor - 1; 
    quicksort(vozaci, 0, broj_vozaca - 1, kriterij);

    printf("\n-----------------------------------\n");
    printf("Vozaci sortirani.\n");
    printf("-----------------------------------\n");

    citanje_vozaca();
    spremi_podatke();
}

void ucitaj_podatke() {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    if (filesize == 0) {
        fclose(file);
        return;
    }

    while (!feof(file)) {
        provjeri_kapacitet();

        vozac novi_vozac;
        if (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d\n", &novi_vozac.id, novi_vozac.ime, novi_vozac.prezime, novi_vozac.drzava, novi_vozac.tim, &novi_vozac.dob, &novi_vozac.bodovi) == 7) {
            vozaci[broj_vozaca++] = novi_vozac;
            if (novi_vozac.id > globalni_id) {
                globalni_id = novi_vozac.id;
            }
        }
    }

    fclose(file);
}

void kopiraj_datoteku(const char* source, const char* dest) {
    FILE* src = fopen(source, "rb");
    if (!src) {
        perror("Greska pri otvaranju izvorne datoteke");
        return;
    }

    FILE* dst = fopen(dest, "wb");
    if (!dst) {
        perror("Greska pri otvaranju odredisne datoteke");
        fclose(src);
        return;
    }

    char buffer[BUFSIZ];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, n, dst) != n) {
            perror("Greska pri pisanju u odredisnu datoteku");
            break;
        }
    }

    fclose(src);
    fclose(dst);
}

void izbornik() {
    int izbor;
    do {
        printf("\n-----------------------------------\n");
        printf("1. Unos novog vozaca\n");
        printf("2. Ispis vozaca\n");
        printf("3. Brisanje vozaca\n");
        printf("4. Azuriranje vozaca\n");
        printf("5. Sortiranje vozaca\n");
        printf("0. Izlaz\n");
        printf("-----------------------------------\n");
        printf("Izbor: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos. Pokusajte ponovo.\n");
            while (getchar() != '\n'); // Čišćenje ulaza
            continue;
        }

        switch (izbor) {
        case UNOS_VOZACA:
            unos_vozaca();
            break;
        case CITANJE_VOZACA:
            citanje_vozaca();
            break;
        case BRISANJE_VOZACA:
            brisanje_vozaca();
            break;
        case AZURIRANJE_PODATAKA:
            azuriraj_podatke();
            break;
        case SORTIRANJE_VOZACA:
            sortiraj_vozace();
            break;
        case IZLAZ:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Neispravan unos. Pokusajte ponovo.\n");
        }
    } while (izbor != IZLAZ);
}
