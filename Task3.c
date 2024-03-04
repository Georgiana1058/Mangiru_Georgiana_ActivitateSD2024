#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100 // Lungimea maximă a unei linii în fișier

// Definirea structurii Magazin
typedef struct {
    int id;
    char denumire[50];
    char categorie[50];
    int nrproduse;
    float* cantitate;
} Magazin;

// Funcție pentru citirea unui obiect de tipul Magazin dintr-un fișier text
Magazin citesteMagazin(FILE* fisier) {
    Magazin magazin;
    fscanf(fisier, "%d %s %s %d", &magazin.id, magazin.denumire, magazin.categorie, &magazin.nrproduse);

    magazin.cantitate = (float*)malloc(magazin.nrproduse * sizeof(float));
    for (int i = 0; i < magazin.nrproduse; i++) {
        fscanf(fisier, "%f", &magazin.cantitate[i]);
    }

    return magazin;
}

// Funcție pentru citirea unui vector de obiecte de tipul Magazin dintr-un fișier text
Magazin* citesteVectorMagazine(const char* numeFisier, int* dimensiuneVector) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului!");
        exit(EXIT_FAILURE);
    }

    // Determinăm numărul de obiecte în fișier
    int nrObiecte = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fisier) != NULL) {
        nrObiecte++;
    }
    rewind(fisier);

    // Alocăm memorie pentru vectorul de obiecte
    Magazin* vector = (Magazin*)malloc(nrObiecte * sizeof(Magazin));
    if (vector == NULL) {
        printf("Eroare la alocarea memoriei!");
        exit(EXIT_FAILURE);
    }

    // Citim obiectele din fișier și le salvăm în vector
    for (int i = 0; i < nrObiecte; i++) {
        vector[i] = citesteMagazin(fisier);
    }

    *dimensiuneVector = nrObiecte;
    fclose(fisier);
    return vector;
}

// Funcție pentru a scrie un obiect de tipul Magazin într-un fișier text
void scrieMagazin(FILE* fisier, Magazin magazin) {
    fprintf(fisier, "%d %s %s %d ", magazin.id, magazin.denumire, magazin.categorie, magazin.nrproduse);
    for (int i = 0; i < magazin.nrproduse; i++) {
        fprintf(fisier, "%.2f ", magazin.cantitate[i]);
    }
    fprintf(fisier, "\n");
}

// Funcție pentru a scrie un vector de obiecte de tipul Magazin într-un fișier text
void scrieVectorMagazine(const char* numeFisier, Magazin* vector, int dimensiuneVector) {
    FILE* fisier = fopen(numeFisier, "w");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului!");
        exit(EXIT_FAILURE);
    }

    // Scriem fiecare obiect din vector în fișier
    for (int i = 0; i < dimensiuneVector; i++) {
        scrieMagazin(fisier, vector[i]);
    }

    fclose(fisier);
}

int main() {
    // Exemplu de utilizare pentru citirea unui vector de obiecte din fișier
    int dimensiuneVector;
    Magazin* vector = citesteVectorMagazine("magazin.txt", &dimensiuneVector);

    // Exemplu de utilizare pentru scrierea unui vector de obiecte în fișier
    scrieVectorMagazine("magazine_nou.txt", vector, dimensiuneVector);

    // Eliberăm memoria alocată pentru vectorul de obiecte
    for (int i = 0; i < dimensiuneVector; i++) {
        free(vector[i].cantitate);
    }


    return 0;
}
