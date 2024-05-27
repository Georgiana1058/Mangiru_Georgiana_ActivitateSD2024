#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>



typedef struct Pacient Pacient;
typedef struct CoadaDePrioritate CoadaDePrioritate;

struct Pacient {
    char* nume;
    int varsta;
    char* conditie;
    int urgenta;
};

struct CoadaDePrioritate {
    Pacient* vector;
    int dimensiune;
    int dimensiuneTotala;
};


Pacient initPacient(const char* nume, int varsta, const char* conditie, int urgenta) {
    Pacient p;
    p.nume = malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(p.nume, nume);
    p.varsta = varsta;
    p.conditie = malloc(sizeof(char) * (strlen(conditie) + 1));
    strcpy(p.conditie, conditie);
    p.urgenta = urgenta;
    return p;
}

CoadaDePrioritate initCoadaDePrioritate(int dimensiune) {
    CoadaDePrioritate cp;
    cp.vector = malloc(sizeof(Pacient) * dimensiune);
    cp.dimensiune = 0;
    cp.dimensiuneTotala = dimensiune;
    return cp;
}


void afisarePacient(Pacient p) {
    printf("Pacientul cu numele %s, varsta %d, conditia %s si urgenta %d\n", p.nume, p.varsta, p.conditie, p.urgenta);
}


void afisareCoada(CoadaDePrioritate cp) {
    for (int i = 0; i < cp.dimensiune; i++) {
        afisarePacient(cp.vector[i]);
    }
}

void filtrareHeap(CoadaDePrioritate cp, int poz) {
    int poz_s = poz * 2 + 1;
    int poz_d = poz * 2 + 2;

    int poz_m = poz;
    if (poz_s < cp.dimensiune && cp.vector[poz_s].urgenta > cp.vector[poz_m].urgenta) {
        poz_m = poz_s;
    }

    if (poz_d < cp.dimensiune && cp.vector[poz_d].urgenta > cp.vector[poz_m].urgenta) {
        poz_m = poz_d;
    }

    if (poz_m != poz) {
        Pacient aux = cp.vector[poz];
        cp.vector[poz] = cp.vector[poz_m];
        cp.vector[poz_m] = aux;
        if (poz_m * 2 + 1 < cp.dimensiune) {
            filtrareHeap(cp, poz_m);
        }
    }
}


Pacient ExtragereHeap(CoadaDePrioritate* cp) {
    if (cp->dimensiune > 0) {
        Pacient aux = cp->vector[0];
        cp->vector[0] = cp->vector[cp->dimensiune - 1];
        cp->dimensiune--;

        for (int i = cp->dimensiune / 2 - 1; i >= 0; i--) {
            filtrareHeap(*cp, i);
        }
        return aux;
    }
    Pacient p = { NULL, 0, NULL, 0 };
    return p;
}


void afisareCoadaTotala(CoadaDePrioritate cp) {
    for (int i = 0; i < cp.dimensiuneTotala; i++) {
        afisarePacient(cp.vector[i]);
    }
}


void DezalocareCoada(CoadaDePrioritate* cp) {
    if (cp->vector != NULL) {
        while (cp->dimensiuneTotala > 0) {
            free(cp->vector[cp->dimensiuneTotala - 1].nume);
            free(cp->vector[cp->dimensiuneTotala - 1].conditie);
            cp->dimensiuneTotala--;
        }
        free(cp->vector);
        cp->vector = NULL;
        cp->dimensiune = 0;
    }
}

void main() {
    CoadaDePrioritate cp;
    cp = initCoadaDePrioritate(6);

    cp.vector[0] = initPacient("Ion Popescu", 30, "Atac de cord", 10);
    cp.vector[1] = initPacient("Maria Ionescu", 25, "Picior fracturat", 5);
    cp.vector[2] = initPacient("Ana Gheorghe", 40, "Accident vascular", 9);
    cp.vector[3] = initPacient("Vasile Mihai", 50, "Febră mare", 3);
    cp.vector[4] = initPacient("Elena Dobre", 20, "Accident rutier", 8);
    cp.vector[5] = initPacient("George Enescu", 60, "Durere toracică", 7);
    cp.dimensiune = 6;

    afisareCoada(cp);

    printf("\nDupa filtrare\n");
    for (int i = (cp.dimensiune / 2) - 1; i >= 0; i--) {
        filtrareHeap(cp, i);
    }

    afisareCoada(cp);

    printf("\nExtragere:\n");
    afisarePacient(ExtragereHeap(&cp));
    afisarePacient(ExtragereHeap(&cp));
    afisarePacient(ExtragereHeap(&cp));
    afisarePacient(ExtragereHeap(&cp));
    afisarePacient(ExtragereHeap(&cp));
    afisarePacient(ExtragereHeap(&cp));

    printf("\nCoada Totala:\n");
    afisareCoadaTotala(cp);

    DezalocareCoada(&cp);
}
