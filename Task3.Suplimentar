#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct Apartament Apartament;
struct Apartament {
	int id;
	float pret;
	int nrCamere;
	char* strada;
};

Apartament initializare(int id, const char* strada, float pret, int nrCamere) {
	Apartament a;
	a.id = id;
	a.nrCamere = nrCamere;
	a.pret = pret;
	a.strada = (char*)malloc(strlen(strada) + 1);
	strcpy(a.strada, strada);
	return a;
}
Apartament* adauga(Apartament* v,Apartament a, int* nrA) {
	Apartament* copie = (Apartament*)malloc(sizeof(Apartament) * ((*nrA)+1));
	copie[(*nrA)] = a;
	for (int i = 0; i < (*nrA); i++) {
		copie[i] = v[i];
	}
	if (v)
		free(v);
	(*nrA)++;
	return copie;

}
Apartament* citireFisier(const char* numetxt, int* nr) {
	FILE* f = fopen(numetxt, "r");
	Apartament* v = NULL;
	if (f) {
		(*nr) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f)!=NULL) {
			Apartament c;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			c.id = atoi(token);
			token = strtok(NULL, delimitator);
			c.nrCamere = atoi(token);
			token = strtok(NULL, delimitator);
			c.pret = atof(token);
			token = strtok(NULL, delimitator);
			c.strada = (char*)malloc(strlen(token) + 1);
			strcpy(c.strada, token);

			v = adauga(v, c, nr);
		}
		fclose(f);
		return v;

	}
}
void scrierefisierapartament(FILE* f, Apartament* a) {
	fprintf(f, "%i,%i,%.2f,%s\n", a->id, a->nrCamere, a->pret, a->strada);
 }
void scriereinfisier(const char* numetxt, Apartament* v, int nr) {
	FILE* f = fopen(numetxt, "w");
	if (f) {
		for (int i = 0; i < nr; i++) {
			scrierefisierapartament(f, &v[i]);
		}
		fclose(f);
	}
	else printf("Eroare la descchidere");
	
}
void afisare(Apartament* v, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("Apartamentul cu id ul %i are %i camere, un pret de %.2f mii euro si se afla de strada %s\n", v[i].id, v[i].nrCamere, v[i].pret, v[i].strada);
	}
}
void dezalocare(Apartament** v, int* nr) {
	printf("S-a dezalocat");
	for (int i = 0; i < (*nr); i++) {
		free((*v)[i].strada);
	}
	free(*v);
	*v = NULL;
	*nr = 0;
}
	void main()
	{
		Apartament* v;
		int nr =0;
		v=citireFisier("apartamente.txt", &nr);
		afisare(v, nr);
		scriereinfisier("apartamente_nou.txt", v, nr);
		dezalocare(&v, &nr);
	    
	
	
	}