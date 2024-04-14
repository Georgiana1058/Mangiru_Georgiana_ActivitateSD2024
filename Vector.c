#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct Masina Masina;
struct Masina {
	int id;
	float pret;
	int anFabricatie;
	char* marca;

};
Masina* adauga(Masina* masina, Masina noua, int* nr) {
	Masina* copie = (Masina*)malloc(sizeof(Masina) * ((*nr) + 1));
	for (int i = 0; i < (*nr); i++) {
		copie[i] = masina[i];
	}
	copie[(*nr)] = noua;
	free(masina);
	(*nr)++;
	return copie;
}



Masina* citirefisiervector(const char* numetxt, int* nr) {
	FILE* f = fopen(numetxt, "r");
	if (f) {
		Masina* v = NULL;
		*nr = 0;
		Masina n;
		char buffer[100];
		char delimitator[] = ",\n";
		while (fgets(buffer, 99, f) != NULL) {
			char* token = strtok(buffer, delimitator);
			n.id = atoi(token);
			token = strtok(NULL, delimitator);
			n.anFabricatie = atoi(token);
			token = strtok(NULL, delimitator);
			n.pret = atof(token);
			token = strtok(NULL, delimitator);
			n.marca = (char*)malloc(strlen(token) + 1);
			strcpy(n.marca, token);
			v = adauga(v, n, nr);
		}
		fclose(f);
		return v;
	}
	else printf("Nu se deschide fisierul");
	return NULL;
}
void afisare(Masina* n) {
	printf("Masina cu idul:%i are marca %s , pretul este de %f mii lei si este din anul %i \n", n->id, n->marca, n->pret, n->anFabricatie);
}
void afisareVector(Masina* v, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare(&v[i]);
	}
}
void CautaMarca(Masina* v, int nr, const char* marca) {

	int ok = 0;
	for (int i = 0; i < nr; i++) {
		if (strcmp(v[i].marca, marca) == NULL)
		{
			afisare(&v[i]);
			ok = 1;
		}
	}
	if (ok == 0)
		printf("Nu exista Marca!!");

}
float mediaPreturilor(Masina* v, int nr, float pretPrag) {
	int suma = 0; int nr1 = 0;
	for (int i = 0; i < nr; i++) {
		if (v[i].pret > pretPrag) {
			suma += v[i].pret;
			nr1++;
		}
	}
	return suma / nr1;
}
void dezalocare(Masina** v, int* nr) {
	for (int i = 0; i < (*nr); i++)
		free((*v)[i].marca);
	free(*v);
	*v = NULL;
	*nr = 0;
	printf("\nS-a dezalocat\n");
}
Masina* vectoranpeste2000(Masina* v, int nr, int* nrN) {
	*nrN = 0;
	for (int i = 0; i < nr; i++) {
		if (v[i].anFabricatie > 2000) {
			(*nrN)++;
		}
	}

	int k = 0;
	Masina* v1 = (Masina*)malloc(sizeof(Masina) * (*nrN));
	for (int i = 0; i < nr; i++) {
		if (v[i].anFabricatie > 2000) {
			v1[k].id = v[i].id;
			v1[k].anFabricatie = v[i].anFabricatie;
			v1[k].pret = v[i].pret;
			v1[k].marca = (char*)malloc(strlen(v[i].marca) + 1);
			strcpy(v1[k].marca, v[i].marca);
			k++;
		}
	}
	return v1;
}
Masina* concatenare(Masina* v1, Masina* v2, int nr1, int nr2, int* dim) {
	*dim = nr1 + nr2;
	Masina* concatenat = (Masina*)malloc(sizeof(Masina) * (*dim));
	int k = 0;
	for (int i = 0; i < nr1; i++) {
		concatenat[k++] = v1[i];
	}
	for (int i = 0; i < nr2; i++) {
		concatenat[k++] = v2[i];
	}
	return concatenat;
}
void main() {
	int nr = 0;
	Masina* v = citirefisiervector("masini.txt", &nr);
	printf("nr:%i\n", nr);
	afisareVector(v, nr);
	printf("----------------------------\n");
	CautaMarca(v, nr, "Logan");
	printf("----------------------------\n");
	float medie = mediaPreturilor(v, nr, 100);
	printf("Media este :%f\n", medie);
	printf("----------------------------\n");
	int nrN = 0;
	Masina* v1 = vectoranpeste2000(v, nr, &nrN);
	afisareVector(v1, nrN);
	printf("----------------------------\n");
	int dim = 0;
	Masina* vN = concatenare(v, v1, nr, nrN, &dim);

	afisareVector(vN, dim);
	printf("----------------------------\n");
	dezalocare(&v1, &nrN);
	//dezalocare(&vN, &dim);//aici deja ai dezalocat prin ceilalti 2 vectori fiindca ai facut shallow copy
	dezalocare(&v, &nr);
}