#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;
typedef struct ListaSimpla ListaSimpla;
typedef struct ListaDubluInlantuita ListaDubluInlantuita;

struct Elev {
    int id;
    int nrMedii;
    float* medii;
};

struct Nod {
    Elev info;
    Nod* st;
    Nod* dr;
};

struct ListaSimpla {
    Elev info;
    ListaSimpla* next;
};

struct ListaDubluInlantuita {
    Elev info;
    ListaDubluInlantuita* next;
    ListaDubluInlantuita* prev;
};

Nod* rotireDreapta(Nod* radacina) {
    Nod* nod = radacina->st;
    radacina->st = nod->dr;
    nod->dr = radacina;
    return nod;
}

Nod* rotireStanga(Nod* radacina) {
    Nod* nod = radacina->dr;
    radacina->dr = nod->st;
    nod->st = radacina;
    return nod;
}

int inaltime(Nod* radacina) {
    if (radacina == NULL)
        return 0;
    else {
        int inaltimeSt = inaltime(radacina->st);
        int inaltimeDr = inaltime(radacina->dr);
        return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
    }
}

int gradEchilibru(Nod* radacina) {
    int inaltimeSt = inaltime(radacina->st);
    int inaltimeDr = inaltime(radacina->dr);
    return inaltimeSt - inaltimeDr;
}

void inserareArbore(Nod** radacina, Elev e) {
    if (*radacina != NULL) {
        if ((*radacina)->info.id > e.id) {
            inserareArbore(&((*radacina)->st), e);
        }
        else {
            inserareArbore(&((*radacina)->dr), e);
        }

        int grad = gradEchilibru(*radacina);

        if (grad == 2) {
            if (gradEchilibru((*radacina)->st) >= 0) {
                *radacina = rotireDreapta(*radacina);
            }
            else {
                (*radacina)->st = rotireStanga((*radacina)->st);
                *radacina = rotireDreapta(*radacina);
            }
        }
        else if (grad == -2) {
            if (gradEchilibru((*radacina)->dr) <= 0) {
                *radacina = rotireStanga(*radacina);
            }
            else {
                (*radacina)->dr = rotireDreapta((*radacina)->dr);
                *radacina = rotireStanga(*radacina);
            }
        }
    }
    else {
        Nod* nod = (Nod*)malloc(sizeof(Nod));
        nod->info = e;
        nod->st = NULL;
        nod->dr = NULL;
        *radacina = nod;
    }
}

Elev citireElev(FILE* fp) {
    Elev e;
    fscanf(fp, "%d", &e.id);
    fscanf(fp, "%d", &e.nrMedii);
    e.medii = (float*)malloc(sizeof(float) * e.nrMedii);
    for (int i = 0; i < e.nrMedii; i++) {
        fscanf(fp, "%f", &e.medii[i]);
    }
    return e;
}

Nod* citireFisier(char* numeFisier) {
    Nod* arbore = NULL;
    if (!numeFisier) return NULL;
    else {
        FILE* fp = fopen(numeFisier, "r");
        int nrElevi;
        fscanf(fp, "%d", &nrElevi);
        for (int i = 0; i < nrElevi; i++) {
            Elev e = citireElev(fp);
            inserareArbore(&arbore, e);
        }
        fclose(fp);
    }
    return arbore;
}

void afisareElev(Elev e) {
    printf("Elevul cu id-ul %d are mediile: ", e.id);
    for (int i = 0; i < e.nrMedii; i++) {
        printf("%5.2f ", e.medii[i]);
    }
    printf("\n");
}

void afisareInOrder(Nod* arbore) {
    if (arbore != NULL) {
        afisareInOrder(arbore->st);
        afisareElev(arbore->info);
        afisareInOrder(arbore->dr);
    }
}

void afisarePreordine(Nod* arbore) {
    if (arbore != NULL) {
        afisareElev(arbore->info);
        afisarePreordine(arbore->st);
        afisarePreordine(arbore->dr);
    }
}

void afisarePostordine(Nod* arbore) {
    if (arbore != NULL) {
        afisarePostordine(arbore->st);
        afisarePostordine(arbore->dr);
        afisareElev(arbore->info);
    }
}

Nod* cautareNod(Nod* radacina, int id) {
    if (radacina == NULL || radacina->info.id == id)
        return radacina;
    if (radacina->info.id > id)
        return cautareNod(radacina->st, id);
    return cautareNod(radacina->dr, id);
}

void salvareInVectorPreordine(Nod* arbore, Elev* vector, int* index) {
    if (arbore != NULL) {
        vector[*index] = arbore->info;
        (*index)++;
        salvareInVectorPreordine(arbore->st, vector, index);
        salvareInVectorPreordine(arbore->dr, vector, index);
    }
}

void salvareInVectorInordine(Nod* arbore, Elev* vector, int* index) {
    if (arbore != NULL) {
        salvareInVectorInordine(arbore->st, vector, index);
        vector[*index] = arbore->info;
        (*index)++;
        salvareInVectorInordine(arbore->dr, vector, index);
    }
}

void salvareInVectorPostordine(Nod* arbore, Elev* vector, int* index) {
    if (arbore != NULL) {
        salvareInVectorPostordine(arbore->st, vector, index);
        salvareInVectorPostordine(arbore->dr, vector, index);
        vector[*index] = arbore->info;
        (*index)++;
    }
}

void salvareInListaSimplaPreordine(Nod* arbore, ListaSimpla** cap) {
    if (arbore != NULL) {
        ListaSimpla* nou = (ListaSimpla*)malloc(sizeof(ListaSimpla));
        nou->info = arbore->info;
        nou->next = *cap;
        *cap = nou;
        salvareInListaSimplaPreordine(arbore->dr, cap);
        salvareInListaSimplaPreordine(arbore->st, cap);
    }
}

void salvareInListaSimplaInordine(Nod* arbore, ListaSimpla** cap) {
    if (arbore != NULL) {
        salvareInListaSimplaInordine(arbore->dr, cap);
        ListaSimpla* nou = (ListaSimpla*)malloc(sizeof(ListaSimpla));
        nou->info = arbore->info;
        nou->next = *cap;
        *cap = nou;
        salvareInListaSimplaInordine(arbore->st, cap);
    }
}

void salvareInListaSimplaPostordine(Nod* arbore, ListaSimpla** cap) {
    if (arbore != NULL) {
        salvareInListaSimplaPostordine(arbore->dr, cap);
        salvareInListaSimplaPostordine(arbore->st, cap);
        ListaSimpla* nou = (ListaSimpla*)malloc(sizeof(ListaSimpla));
        nou->info = arbore->info;
        nou->next = *cap;
        *cap = nou;
    }
}

void salvareInListaDubluInlantuitaPreordine(Nod* arbore, ListaDubluInlantuita** cap) {
    if (arbore != NULL) {
        ListaDubluInlantuita* nou = (ListaDubluInlantuita*)malloc(sizeof(ListaDubluInlantuita));
        nou->info = arbore->info;
        nou->next = *cap;
        if (*cap != NULL)
            (*cap)->prev = nou;
        nou->prev = NULL;
        *cap = nou;
        salvareInListaDubluInlantuitaPreordine(arbore->dr, cap);
        salvareInListaDubluInlantuitaPreordine(arbore->st, cap);
    }
}

void salvareInListaDubluInlantuitaInordine(Nod* arbore, ListaDubluInlantuita** cap) {
    if (arbore != NULL) {
        salvareInListaDubluInlantuitaInordine(arbore->dr, cap);
        ListaDubluInlantuita* nou = (ListaDubluInlantuita*)malloc(sizeof(ListaDubluInlantuita));
        nou->info = arbore->info;
        nou->next = *cap;
        if (*cap != NULL)
            (*cap)->prev = nou;
        nou->prev = NULL;
        *cap = nou;
        salvareInListaDubluInlantuitaInordine(arbore->st, cap);
    }
}

void salvareInListaDubluInlantuitaPostordine(Nod* arbore, ListaDubluInlantuita** cap) {
    if (arbore != NULL) {
        salvareInListaDubluInlantuitaPostordine(arbore->dr, cap);
        salvareInListaDubluInlantuitaPostordine(arbore->st, cap);
        ListaDubluInlantuita* nou = (ListaDubluInlantuita*)malloc(sizeof(ListaDubluInlantuita));
        nou->info = arbore->info;
        nou->next = *cap;
        if (*cap != NULL)
            (*cap)->prev = nou;
        nou->prev = NULL;
        *cap = nou;
    }
}

void stergereArbore(Nod** radacina) {
    if (*radacina) {
        stergereArbore(&((*radacina)->st));
        stergereArbore(&((*radacina)->dr));
        free((*radacina)->info.medii);
        free((*radacina));
        (*radacina) = NULL;
    }
}

void afisareListaSimpla(ListaSimpla* cap) {
    while (cap != NULL) {
        afisareElev(cap->info);
        cap = cap->next;
    }
}

void afisareListaDubluInlantuita(ListaDubluInlantuita* cap) {
    while (cap != NULL) {
        afisareElev(cap->info);
        cap = cap->next;
    }
}

void main() {
    Nod* arbore = citireFisier("Elevi.txt");

    printf("Afisare InOrder:\n");
    afisareInOrder(arbore);

    printf("\nAfisare PreOrder:\n");
    afisarePreordine(arbore);

    printf("\nAfisare PostOrder:\n");
    afisarePostordine(arbore);

    int idCautat = 3;
    Nod* nodCautat = cautareNod(arbore, idCautat);
    if (nodCautat != NULL) {
        printf("\nElevul cu id-ul %d a fost gasit.\n", idCautat);
    }
    else {
        printf("\nElevul cu id-ul %d nu a fost gasit.\n", idCautat);
    }

    int nrNoduri = 0;
    afisareInOrder(arbore);

    Elev* vector = (Elev*)malloc(sizeof(Elev) * nrNoduri);
    int index = 0;

    printf("\nSalvare in vector InOrder:\n");
    salvareInVectorInordine(arbore, vector, &index);
    for (int i = 0; i < nrNoduri; i++) {
        afisareElev(vector[i]);
    }

    ListaSimpla* listaSimpla = NULL;
    printf("\nSalvare in lista simpla InOrder:\n");
    salvareInListaSimplaInordine(arbore, &listaSimpla);
    afisareListaSimpla(listaSimpla);

    ListaDubluInlantuita* listaDubluInlantuita = NULL;
    printf("\nSalvare in lista dublu inlantuita InOrder:\n");
    salvareInListaDubluInlantuitaInordine(arbore, &listaDubluInlantuita);
    afisareListaDubluInlantuita(listaDubluInlantuita);

    stergereArbore(&arbore);
}
