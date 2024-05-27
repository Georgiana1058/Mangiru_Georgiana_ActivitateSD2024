#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

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

void inserareArbore(Nod** radacina, Elev e) {
    if ((*radacina) != NULL) {
        if ((*radacina)->info.id > e.id) {
            inserareArbore(&((*radacina)->st), e);
        }
        else {
            inserareArbore(&((*radacina)->dr), e);
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
    e.medii = malloc(sizeof(float) * e.nrMedii);
    for (int i = 0; i < e.nrMedii; i++) {
        fscanf(fp, "%f", &(e.medii[i]));
    }
    return e;
}

Nod* citireFisier(char* numeFisier) {
    Nod* arbore = NULL;
    if (!numeFisier) {
        return NULL;
    }
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
    printf("Elevul cu id-ul %d are un nr de %d medii, mediile sunt: ", e.id, e.nrMedii);
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

float calculeazaMedieElev(Elev e) {
    if (e.nrMedii != 0) {
        float suma = 0;
        for (int i = 0; i < e.nrMedii; i++) {
            suma += e.medii[i];
        }
        return suma / e.nrMedii;
    }
    else {
        return 0;
    }
}

float calculeazaSumaNote(Nod* arbore, int* nrNote) {
    if (arbore != NULL) {
        float suma = 0;
        for (int i = 0; i < arbore->info.nrMedii; i++) {
            suma += arbore->info.medii[i];
        }
        (*nrNote) += arbore->info.nrMedii;
        float sumaSt = calculeazaSumaNote(arbore->st, nrNote);
        float sumaDr = calculeazaSumaNote(arbore->dr, nrNote);
        return suma + sumaDr + sumaSt;
    }
    else {
        return 0;
    }
}

float calculeazaMediaGenerala(Nod* arbore) {
    int nrNote = 0;
    float suma = calculeazaSumaNote(arbore, &nrNote);
    printf("Numarul de note %d \n", nrNote);
    if (nrNote > 0) {
        return suma / nrNote;
    }
    else {
        return 0;
    }
}


Nod* stergeNod(Nod* radacina, int id) {
    if (radacina == NULL) return radacina;

    if (id < radacina->info.id) {
        radacina->st = stergeNod(radacina->st, id);
    }
    else if (id > radacina->info.id) {
        radacina->dr = stergeNod(radacina->dr, id);
    }
    else {
        if (radacina->st == NULL) {
            Nod* temp = radacina->dr;
            free(radacina->info.medii);
            free(radacina);
            return temp;
        }
        else if (radacina->dr == NULL) {
            Nod* temp = radacina->st;
            free(radacina->info.medii);
            free(radacina);
            return temp;
        }

        Nod* temp = radacina->dr;
        while (temp && temp->st != NULL) temp = temp->st;

        radacina->info = temp->info;
        radacina->dr = stergeNod(radacina->dr, temp->info.id);
    }
    return radacina;
}


int inaltimeArbore(Nod* radacina) {
    if (radacina == NULL) return 0;
    int inaltimeSt = inaltimeArbore(radacina->st);
    int inaltimeDr = inaltimeArbore(radacina->dr);
    return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
}


Nod* subarboreCuInaltimeaMaiMare(Nod* radacina) {
    if (radacina == NULL) return NULL;
    int inaltimeSt = inaltimeArbore(radacina->st);
    int inaltimeDr = inaltimeArbore(radacina->dr);
    return inaltimeSt >= inaltimeDr ? radacina->st : radacina->dr;
}


int numarNoduri(Nod* radacina) {
    if (radacina == NULL) return 0;
    return 1 + numarNoduri(radacina->st) + numarNoduri(radacina->dr);
}


Nod* subarboreCuMaiMulteNoduri(Nod* radacina) {
    if (radacina == NULL) return NULL;
    int noduriSt = numarNoduri(radacina->st);
    int noduriDr = numarNoduri(radacina->dr);
    return noduriSt >= noduriDr ? radacina->st : radacina->dr;
}

void main() {
    Nod* arbore = NULL;
    arbore = citireFisier("elevi.txt");
    afisareInOrder(arbore);
    printf("Media este %5.2f \n", calculeazaMediaGenerala(arbore));


    int idDeSters = 3;
    arbore = stergeNod(arbore, idDeSters);
    printf("Arbore dupa stergerea nodului cu ID %d:\n", idDeSters);
    afisareInOrder(arbore);


    Nod* subarboreInalt = subarboreCuInaltimeaMaiMare(arbore);
    if (subarboreInalt != NULL) {
        printf("Subarborele cu inaltimea mai mare:\n");
        afisareInOrder(subarboreInalt);
    }


    Nod* subarboreNoduri = subarboreCuMaiMulteNoduri(arbore);
    if (subarboreNoduri != NULL) {
        printf("Subarborele cu mai multe noduri:\n");
        afisareInOrder(subarboreNoduri);
    }
}
