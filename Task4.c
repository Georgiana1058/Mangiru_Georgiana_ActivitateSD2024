#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

struct Magazin {
    int id;
    char denumire[50];
    char categorie[50];
    int nrproduse;
    float* cantitate;
};

// Functia care citeste un obiect de tipul magazin din fisier
struct Magazin citesteMagazin(FILE* fisier) {
    struct Magazin magazin;
    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, fisier);

    sscanf(buffer, "%d %49s %49[^\n] %d", &magazin.id, magazin.denumire, magazin.categorie, &magazin.nrproduse);
    magazin.cantitate = (float*)malloc(magazin.nrproduse * sizeof(float));
    fgets(buffer, MAX_LINE_LENGTH, fisier);
    char* token = strtok(buffer, " ");
    int i = 0;
    while (token != NULL && i < magazin.nrproduse) {
        sscanf(token, "%f", &magazin.cantitate[i]);
        token = strtok(NULL, " ");
        i++;
    }
    return magazin;
}

// Functia care citeste un vector de obiecte de tipul magazin din fisier
struct Magazin* citesteVectorMagazine(const char* numefisier, int* dimensiuneVector) {
    FILE* fisier = fopen(numefisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschidere");
        exit(1);
    }

    int nrobiecte = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fisier) != NULL) {
        nrobiecte++;
    }
    rewind(fisier);

    struct Magazin* vector = (struct Magazin*)malloc(nrobiecte * sizeof(struct Magazin));
    if (vector == NULL) {
        printf("Eroare de memorie");
        exit(1);
    }

    for (int i = 0; i < nrobiecte; i++) {
        vector[i] = citesteMagazin(fisier);
    }

    *dimensiuneVector = nrobiecte;
    fclose(fisier);
    return vector;
}

// Functia care afiseaza un obiect de tipul magazin
void afiseazaMagazin(struct Magazin magazin) {
    printf("Shop ID: %d\n", magazin.id);
    printf("Name: %s\n", magazin.denumire);
    printf("Category: %s\n", magazin.categorie);
    printf("Number of products: %d\n", magazin.nrproduse);
    printf("Product quantities: ");
    for (int i = 0; i < magazin.nrproduse; i++) {
        printf("%.2f ", magazin.cantitate[i]);
    }
    printf("\n");
}

// Functia care afiseaza un vector de obiecte de tipul magazin
void afiseazaVectorMagazine(struct Magazin* vector, int dimensiuneVector) {
    for (int i = 0; i < dimensiuneVector; i++) {
        afiseazaMagazin(vector[i]);
    }
}

int main() {
    int dimensiuneVector;
    struct Magazin* vector = citesteVectorMagazine("magazin.txt", &dimensiuneVector);
    afiseazaVectorMagazine(vector, dimensiuneVector);

    // Eliberez memoria
    for (int i = 0; i < dimensiuneVector; i++) {
        free(vector[i].cantitate);
    }
    free(vector);

    return 0;
}
