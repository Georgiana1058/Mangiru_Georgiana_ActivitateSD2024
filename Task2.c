#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definirea structurii Magazin
typedef struct {
    int id;
    char denumire[50];
    char categorie[50];
    int nrproduse;
    float* cantitate;
} Magazin;

// Funcție pentru a seta denumirea
void setDenumire(Magazin* magazin, const char* denumire) {
    strcpy(magazin->denumire, denumire);
}

// Funcție pentru a calcula cantitatea maximă
void cantitateaMaxima(Magazin* magazin) {
    float p = 0;
    for (int i = 0; i < magazin->nrproduse; i++) {
        if (p < magazin->cantitate[i]) {
            p = magazin->cantitate[i];
        }
    }
    printf("Cantitatea maxima este: %.2f\n", p);
}

// Funcție pentru a citi un obiect de tip Magazin
void citireMagazin(Magazin* magazin) {
    printf("ID: ");
    scanf("%d", &magazin->id);
    printf("Denumire: ");
    scanf("%s", magazin->denumire);
    printf("Categorie: ");
    scanf("%s", magazin->categorie);
    printf("Numar Produse: ");
    scanf("%d", &magazin->nrproduse);

    // Alocare memorie pentru cantitate
    magazin->cantitate = (float*)malloc(magazin->nrproduse * sizeof(float));

    printf("Introduceti cantitatea produselor: ");
    for (int i = 0; i < magazin->nrproduse; i++) {
        scanf("%f", &magazin->cantitate[i]);
    }
}

// Funcție pentru a afișa un obiect de tip Magazin
void afisareMagazin(Magazin* magazin) {
    printf("ID: %d\n", magazin->id);
    printf("Denumire: %s\n", magazin->denumire);
    printf("Categorie: %s\n", magazin->categorie);
    for (int i = 0; i < magazin->nrproduse; i++) {
        printf("Cantitate: %.2f\n", magazin->cantitate[i]);
    }
}

// Funcție pentru a crea un nou vector în care sunt copiate obiectele care îndeplinesc o anumită condiție
Magazin* copiazaObiecte(Magazin* vector, int dimensiune, int* dimensiuneNoua) {
    // Vom copia obiectele care au 'nrproduse' mai mare decât 2
    Magazin* nouVector = (Magazin*)malloc(dimensiune * sizeof(Magazin));
    *dimensiuneNoua = 0;

    for (int i = 0; i < dimensiune; i++) {
        if (vector[i].nrproduse > 2) {
            nouVector[*dimensiuneNoua] = vector[i];
            (*dimensiuneNoua)++;
        }
    }

    return nouVector;
}

// Funcție pentru a muta obiectele care îndeplinesc o anumită condiție într-un nou vector
Magazin* mutaObiecte(Magazin* vector, int dimensiune, int* dimensiuneNoua) {
    // Vom muta obiectele care au 'id' par într-un nou vector
    Magazin* nouVector = (Magazin*)malloc(dimensiune * sizeof(Magazin));
    *dimensiuneNoua = 0;

    for (int i = 0; i < dimensiune; i++) {
        if (vector[i].id % 2 == 0) {
            nouVector[*dimensiuneNoua] = vector[i];
            (*dimensiuneNoua)++;
        }
    }

    return nouVector;
}

// Funcție pentru a concatena doi vectori de obiecte
Magazin* concateneazaVectori(Magazin* vector1, int dimensiune1, Magazin* vector2, int dimensiune2, int* dimensiuneNoua) {
    *dimensiuneNoua = dimensiune1 + dimensiune2;
    Magazin* nouVector = (Magazin*)malloc((*dimensiuneNoua) * sizeof(Magazin));

    int index = 0;
    for (int i = 0; i < dimensiune1; i++) {
        nouVector[index++] = vector1[i];
    }
    for (int i = 0; i < dimensiune2; i++) {
        nouVector[index++] = vector2[i];
    }

    return nouVector;
}

// Funcția principală
int main() {
    // Alocare dinamică a unui vector cu cel puțin 5 obiecte de tip Magazin
    int dimensiuneVector = 5;
    Magazin* vector = (Magazin*)malloc(dimensiuneVector * sizeof(Magazin));

    // Citirea obiectelor din vector
    for (int i = 0; i < dimensiuneVector; i++) {
        printf("Introduceti detaliile pentru obiectul %d:\n", i + 1);
        citireMagazin(&vector[i]);
    }

    // Afisarea vectorului de obiecte
    printf("\nVectorul de obiecte:\n");
    for (int i = 0; i < dimensiuneVector; i++) {
        printf("Obiectul %d:\n", i + 1);
        afisareMagazin(&vector[i]);
        printf("\n");
    }

    // Crearea unui nou vector în care sunt copiate obiectele care îndeplinesc o anumită condiție
    int dimensiuneNoua;
    Magazin* vectorCopiaza = copiazaObiecte(vector, dimensiuneVector, &dimensiuneNoua);
    printf("\nVectorul de obiecte copiate:\n");
    for (int i = 0; i < dimensiuneNoua; i++) {
        printf("Obiectul %d:\n", i + 1);
        afisareMagazin(&vectorCopiaza[i]);
        printf("\n");
    }
    free(vectorCopiaza);

    // Mutarea obiectelor care îndeplinesc o anumită condiție într-un nou vector
    Magazin* vectorMuta = mutaObiecte(vector, dimensiuneVector, &dimensiuneNoua);
    printf("\nVectorul de obiecte mutate:\n");
    for (int i = 0; i < dimensiuneNoua; i++) {
        printf("Obiectul %d:\n", i + 1);
        afisareMagazin(&vectorMuta[i]);
        printf("\n");
    }
    free(vectorMuta);

    // Concatenarea a doi vectori de obiecte
    Magazin vector2[] = { {6, "Magazin1", "Categorie1", 2, (float[]) { 1.1, 2.2 }}, {7, "Magazin2", "Categorie2", 3, (float[]) { 3.3, 4.4, 5.5 }} };
    int dimensiuneVector2 = sizeof(vector2) / sizeof(vector2[0]);

    Magazin* vectorConcatenat;
    int dimensiuneVectorConcatenat;
    vectorConcatenat = concateneazaVectori(vector, dimensiuneVector, vector2, dimensiuneVector2, &dimensiuneVectorConcatenat);

    printf("\nVectorul de obiecte concatenat:\n");
    for (int i = 0; i < dimensiuneVectorConcatenat; i++) {
        printf("Obiectul %d:\n", i + 1);
        afisareMagazin(&vectorConcatenat[i]);
        printf("\n");
    }
    free(vectorConcatenat);

    // Eliberarea memoriei alocate pentru vectorul principal
    for (int i = 0; i < dimensiuneVector; i++) {
        free(vector[i].cantitate);
    }
    free(vector);

    return 0;
}
