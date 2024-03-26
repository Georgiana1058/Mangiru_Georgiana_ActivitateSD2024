//SEMINAR6-SDD
//Subiect: lista dubla inlantuita 
//dezavantaje-avem mai multe legaturi si putem gresi usor
//dezavantaje-ocupa mai mult-pointeri suplimentari
//avantaje-il putem parcurge cum vrem
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//typedef = o eticheta, un alias
typedef struct Biblioteca Biblioteca;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

typedef struct Nod Nod;
struct Nod {
    Biblioteca info;
    Nod* next;
    Nod* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    Nod* head;
    Nod* tail;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {
    //lista goala e transmisa prin obiect
    //cream nod si ii alocam spatiu pe heap nu pe stack
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = b;
    nod->next = listaDubla->head;
    nod->prev = NULL;
    if (listaDubla->head) {
        listaDubla->head->prev = nod;
    }
    else {
        listaDubla->head = nod;
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
}

void afisareListaInceput(ListaDubla listaDubla) {
    while (listaDubla.head) {
        printf("Biblioteca: %s; Nr cititori: %d; Nr carti: %d \n", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
        listaDubla.head = listaDubla.head->next;
    }
    printf("\n");
}

void stergereNodNume(ListaDubla* listaDubla, const char* nume) {
    Nod* aux = listaDubla->head;
    //iese din while cand gaseste numele, sau la final
    while (aux && strcmp(nume, aux->info.nume) != 0) {
        aux = aux->next;
    }
    //nodul poate fi primul, ulmtimul, la mijloc, sau poate fi singurul
    if (aux)
    {
        if (aux == listaDubla->head)
        {
            if (aux == listaDubla->tail)
            {

                listaDubla->tail = NULL;
                listaDubla->head = NULL;

            }
            else
            {
                listaDubla->head = listaDubla->head->next;
                listaDubla->head->prev = NULL;
            }


        }
        else
        {
            if (aux == listaDubla->tail)
            {
                aux->prev->next = NULL;
                listaDubla->tail = aux->prev;
            }
            else
            {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
        }
        free(aux->info.nume);
        free(aux);
    }

}

void stergereLista(ListaDubla* listaDubla) {
    while (listaDubla->head)
    {
        free(listaDubla->head->info.nume);
        Nod* aux = listaDubla->head;
        listaDubla->head = listaDubla->head->next;
        free(aux);
    }

    listaDubla->head = NULL;
    listaDubla->tail = NULL;
}

//sa se calculeze nr total de carti din toate bibliotecile dar sa se inceapa cu ultima
int nrCartiTotal(ListaDubla listaDubla) {
    int rezultat = 0;
    while (listaDubla.tail)
    {
        rezultat += listaDubla.tail->info.nrCarti;
        listaDubla.tail = listaDubla.tail->prev;
    }
    return rezultat;
}

void main() {

    Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);

    ListaDubla listaDubla;
    listaDubla.head = NULL;
    listaDubla.tail = NULL;

    inserareInceput(&listaDubla, b1);
    inserareInceput(&listaDubla, b2);
    inserareInceput(&listaDubla, b3);

    afisareListaInceput(listaDubla);

    int rezultat = nrCartiTotal(listaDubla);
    printf("Nr total de carti este-> %d", rezultat);

    //apelez mai intai sa stearga din mijloc,dupa primul, dupa cel care ramane singur
    /*stergereNodNume(&listaDubla, "Ioan Slavici");
    afisareListaInceput(listaDubla);

    stergereNodNume(&listaDubla, "Mihai Eminescu");
    afisareListaInceput(listaDubla);

    stergereNodNume(&listaDubla, "Tudor Arghezi");
    afisareListaInceput(listaDubla);*/

    stergereLista(&listaDubla);
    afisareListaInceput(listaDubla);




}