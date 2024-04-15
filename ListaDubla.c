#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
typedef struct Masina Masina;
struct Masina {
	int id;
	int anFabricatie;
	float pret;
	char* marca;
};
typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* head;
	Nod* tail;
};
Masina initializare(int id, int anFabricatie, float pret, const char* marca) {
	Masina noua;
	noua.id = id;
	noua.anFabricatie = anFabricatie;
	noua.pret = pret;
	noua.marca = (char*)malloc(1 + strlen(marca));
	strcpy(noua.marca, marca);
	return noua;
}
void inserareLaInceput(ListaDubla* listadubla, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(m.id, m.anFabricatie, m.pret, m.marca);
	nou->next = listadubla->head;
	nou->prev = NULL;
	if (listadubla->head) {
		listadubla->head->prev = nou;


	}
	else {
		listadubla->head = nou;
		listadubla->tail = nou;
	}
	listadubla->head = nou;
}
void afisare(ListaDubla* listadubla) {
	Nod* current = listadubla->head;
	while (current) {
		printf("Masina din anul %i, marca %s are pretul %f si id-ul:%i\n", current->info.anFabricatie, current->info.marca, current->info.pret, current->info.id);
		current = current->next;
	}
}
void stergeNodDupaNume(ListaDubla* listadubla, const char* marca) {
	Nod* aux = listadubla->head;
	while (aux && strcmp(aux->info.marca, marca) != 0)
	{
		aux = aux->next;
	}
	if (aux) {
		if (aux == listadubla->head)
		{
			if (aux == listadubla->tail)
			{
				listadubla->head = NULL;
				listadubla->tail = NULL;
			}
			else {
				listadubla->head = listadubla->head->next;
				listadubla->head->prev = NULL;

			}
		}
		else {
			if (aux == listadubla->tail) {
				aux->prev->next = NULL;
				listadubla->tail = aux->prev;
			}
			else {

				aux->prev->next = aux->next;
				if (aux->next) {
					aux->next->prev = aux->prev;
				}
				aux->prev->next = aux->next;
			}
		}
		free(aux->info.marca);
		free(aux);
	}
}
void stergere(ListaDubla* listadubla) {
	while (listadubla->head) {
		free(listadubla->head->info.marca);
		Nod* aux = listadubla->head;
		listadubla->head = listadubla->head->prev;
		free(aux);
	}
	listadubla->head = NULL;
	listadubla->tail = NULL;
	printf("S-a sters lista\n");
}
float pretMediu(ListaDubla* listadubla) {
	float suma = 0;
	int nr = 0;
	while (listadubla->tail) {
		suma += listadubla->tail->info.pret;
		nr++;
		listadubla->tail = listadubla->tail->prev;
	}
	return suma / nr;
}
void main() {
	ListaDubla listadubla;
	listadubla.head = NULL;
	listadubla.tail = NULL;
	Masina m1 = initializare(1, 2023, 700, "Mercedes");
	Masina m2 = initializare(2, 2024, 800, "Audi");
	Masina m3 = initializare(3, 2018, 900, "Tesla");
	inserareLaInceput(&listadubla, m2);
	inserareLaInceput(&listadubla, m1);
	inserareLaInceput(&listadubla, m3);
	afisare(&listadubla);
	float medie = pretMediu(&listadubla);
	printf("Pretul mediu al unei masini este:%f\n", medie);
	stergeNodDupaNume(&listadubla, "Audi");
	afisare(&listadubla);
	stergere(&listadubla);
}