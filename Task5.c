#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Magazin {
    int id;
    char* nume;
    int nrProduse;
    struct Magazin* next;
};


void adaugaMagazin(struct Magazin** lista, struct Magazin* magazinNou) {
    struct Magazin* current = *lista;
    if (*lista == NULL) {
        *lista = magazinNou;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = magazinNou;
    }
}


void citesteMagazine(const char* numeFisier, struct Magazin** lista) {
    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.");
        exit(1);
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        struct Magazin* magazinNou = (struct Magazin*)malloc(sizeof(struct Magazin));
        if (magazinNou == NULL) {
            printf("Eroare la alocarea memoriei.");
            exit(1);
        }

        char delimitator[] = ",\n";
        char* token = strtok(buffer, delimitator);
        magazinNou->id = atoi(token);
        token = strtok(NULL, delimitator);
        magazinNou->nume = (char*)malloc(strlen(token) + 1); // Alocare memorie pentru nume
        strcpy(magazinNou->nume, token); // Copierea numelui
        token = strtok(NULL, delimitator);
        magazinNou->nrProduse = atoi(token);

        magazinNou->next = NULL;
        adaugaMagazin(lista, magazinNou);
    }
    fclose(fisier);
}


void afiseazaMagazin(struct Magazin* magazin) {
    printf("ID: %d, Nume: %s, Nr. Produse: %d\n", magazin->id, magazin->nume, magazin->nrProduse);
}

void afiseazaMagazine(struct Magazin* lista) {
    printf("AFISARE MAGAZINE:\n");
    struct Magazin* current = lista;
    while (current != NULL) {
        afiseazaMagazin(current);
        current = current->next;
    }
}


void dezalocaMagazine(struct Magazin* lista) {
    struct Magazin* current = lista;
    while (current != NULL) {
        struct Magazin* temp = current;
        current = current->next;
        free(temp->nume);
        free(temp);
    }
}

// Functie pentru a sterge un nod de pe o pozitie data
void stergeNod(struct Magazin** lista, int pozitie) {
    if (*lista == NULL)
        return;
    struct Magazin* temp = *lista;
    if (pozitie == 0) {
        *lista = temp->next;
        free(temp->nume);
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < pozitie - 1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL)
        return;
    struct Magazin* next = temp->next->next;
    free(temp->next->nume);
    free(temp->next);
    temp->next = next;
}

// Functie pentru a insera un magazin in lista sortata crescator dupa ID
void insereazaSortat(struct Magazin** lista, struct Magazin* magazinNou) {
    struct Magazin* current;
    if (*lista == NULL || (*lista)->id >= magazinNou->id) {
        magazinNou->next = *lista;
        *lista = magazinNou;
    }
    else {
        current = *lista;
        while (current->next != NULL && current->next->id < magazinNou->id)
            current = current->next;
        magazinNou->next = current->next;
        current->next = magazinNou;
    }
}

// Functie pentru a salva in vector toate magazinele care au un numar de produse mai mare decat un prag dat
struct Magazin** salveazaMagazine(struct Magazin* inceput, int prag, int* dimensiuneVector) {
    *dimensiuneVector = 0;
    struct Magazin** rezultat = NULL;
    struct Magazin* temp = inceput;
    while (temp != NULL) {
        if (temp->nrProduse > prag) {
            rezultat = (struct Magazin**)realloc(rezultat, ((*dimensiuneVector) + 1) * sizeof(struct Magazin*));
            rezultat[(*dimensiuneVector)] = temp;
            (*dimensiuneVector)++;
        }
        temp = temp->next;
    }
    return rezultat;
}

// Functie pentru interschimbarea a doua noduri din lista
void interschimbaNoduri(struct Magazin** lista, int pozitie1, int pozitie2) {
    if (pozitie1 == pozitie2)
        return;
    struct Magazin* prev1 = NULL, * curr1 = *lista;
    for (int i = 0; curr1 != NULL && i < pozitie1; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }
    struct Magazin* prev2 = NULL, * curr2 = *lista;
    for (int i = 0; curr2 != NULL && i < pozitie2; i++) {
        prev2 = curr2;
        curr2 = curr2->next;
    }
    if (curr1 == NULL || curr2 == NULL)
        return;
    if (prev1 != NULL)
        prev1->next = curr2;
    else
        *lista = curr2;
    if (prev2 != NULL)
        prev2->next = curr1;
    else
        *lista = curr1;
    struct Magazin* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
}

int main() {
    struct Magazin* magazine = NULL;
    citesteMagazine("magazine.txt", &magazine);
    afiseazaMagazine(magazine);

    
    stergeNod(&magazine, 2); 
    printf("\nLista dupa stergerea nodului de pe pozitia 2:\n");
    afiseazaMagazine(magazine);

    //  Inserarea unui magazin in lista sortata crescator dupa ID
    struct Magazin* magazinNou = (struct Magazin*)malloc(sizeof(struct Magazin));
    magazinNou->id = 7;
    magazinNou->nume = (char*)malloc(sizeof(char) * (1 + strlen("Magazin 7")));
    strcpy(magazinNou->nume, "Magazin 7");
    magazinNou->nrProduse = 30;
    insereazaSortat(&magazine, magazinNou);
    printf("\nLista dupa inserarea unui magazin sortat crescator dupa ID:\n");
    afiseazaMagazine(magazine);

    // Salvarea in vector a magazinelor cu un numar de produse mai mare decat un prag dat
    int dimensiuneVector;
    struct Magazin** rezultat = salveazaMagazine(magazine, 20, &dimensiuneVector);
    printf("\nMagazinele cu un numar de produse mai mare decat 20:\n");
    for (int i = 0; i < dimensiuneVector; i++) {
        afiseazaMagazin(rezultat[i]);
    }

    interschimbaNoduri(&magazine, 1, 3); // Interschimbam nodurile de pe pozitiile 1 si 3
    printf("\nLista dupa interschimbarea nodurilor de pe pozitiile 1 si 3:\n");
    afiseazaMagazine(magazine);

  
    dezalocaMagazine(magazine);
    free(rezultat);

    return 0;
}
