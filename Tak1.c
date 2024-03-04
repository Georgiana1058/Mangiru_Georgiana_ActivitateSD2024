#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Magazin {
    int id;
    char denumire[100];
    char categorie[100];
    int nrproduse;
    float *cantitate;
};

void citireMagazin(struct Magazin *m) {
    printf("ID: ");
    scanf("%d", &m->id);
    printf("Denumire: ");
    scanf("%s", m->denumire);
    printf("Categorie: ");
    scanf("%s", m->categorie);
    printf("Numar Produse: ");
    scanf("%d", &m->nrproduse);

    m->cantitate = (float *)malloc(m->nrproduse * sizeof(float));
    printf("Introduceti cantitatea produselor: ");
    for (int i = 0; i < m->nrproduse; i++) {
        scanf("%f", &m->cantitate[i]);
    }
}

void afisareMagazin(struct Magazin m) {
    printf("ID: %d\n", m.id);
    printf("Denumire: %s\n", m.denumire);
    printf("Categorie: %s\n", m.categorie);
    for (int i = 0; i < m.nrproduse; i++) {
        printf("Cantitate: %.2f\n", m.cantitate[i]);
    }
}

void eliberareMemorie(struct Magazin *m) {
    free(m->cantitate);
    m->cantitate = NULL;
}

int main() {
    struct Magazin t1;
    citireMagazin(&t1);
    afisareMagazin(t1);
    eliberareMemorie(&t1);

    return 0;
}
