#include "f1.h"

int main() {
    atexit(oslobodi_memoriju); // Oslobodi memoriju pri izlasku iz programa
    ucitaj_podatke();
    izbornik();
    return 0;
}