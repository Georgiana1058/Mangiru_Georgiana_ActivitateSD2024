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

};
Masina initializare(int id, int anFabricatie, float pret, const char* marca) {
	Masina noua;
	noua.id = id;
	noua.anFabricatie = anFabricatie;
	noua.pret = pret;
	noua.marca = (char*)malloc(sizeof(char) * (1 + strlen(marca)));
	strcpy(noua.marca, marca);
	return noua;
}
Nod* inserareLaInceput(Nod* cap, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(m.id, m.anFabricatie, m.pret, m.marca);
	nou->next = cap;
	return nou;
}
Nod* inserareLaSfarsit(Nod** cap, Masina m) {
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
	sfarsit->info = initializare(m.id, m.anFabricatie, m.pret, m.marca);
	sfarsit->next = NULL;
	if (*cap) {
		Nod* capA = (*cap);
		while (capA->next) {

			capA = capA->next;
		}
		capA->next = sfarsit;
	}
	else {
		*cap = sfarsit;
	}

}
void afisare(Nod* cap) {
	while (cap) {
		printf("Masina cu marca %s are pretul de %.2f ,fiind din anul %i si are idul: %i\n", cap->info.marca, cap->info.pret, cap->info.anFabricatie, cap->info.id);
		cap = cap->next;
	}
}
void stergeLista(Nod** cap) {
	while (*cap) {
		free((*cap)->info.marca);
		Nod* copie = (*cap);
		*cap = (*cap)->next;
		free(copie);
	}
}
char* CeaMaiNouaMasina(Nod* cap) {
	float min = 100;
	char* marca_aux = NULL;
	while (cap) {
		int nr = 2024 - cap->info.anFabricatie;
		if (nr < min)
		{
			min = nr;
			marca_aux = cap->info.marca;
		}

		cap = cap->next;
	}
	char* marca = (char*)malloc(strlen(marca_aux) + 1);
	strcpy(marca, marca_aux);
	return marca;
}
void main() {
	Masina b1 = initializare(1, 2008, 200, "Logan");
	Masina b2 = initializare(2, 2010, 100, "Ford");
	Masina b3 = initializare(3, 2008, 700, "Audi");
	Masina b4 = initializare(4, 2018, 500, "BMW");
	Masina b5 = initializare(5, 2012, 800, "Mercedes");
	Nod* cap = NULL;
	cap = inserareLaInceput(cap, b1);
	cap = inserareLaInceput(cap, b2);
	inserareLaSfarsit(&cap, b3);
	inserareLaSfarsit(&cap, b4);
	inserareLaSfarsit(&cap, b5);
	afisare(cap);
	printf("--------------------\n");
	char* marca = CeaMaiNouaMasina(cap);
	printf("%s", marca);
	stergeLista(&cap);
	afisare(cap);
	free(b1.marca);
	free(b2.marca);
	free(b3.marca);
	free(b4.marca);
	free(b5.marca);

}