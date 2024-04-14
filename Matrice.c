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
Masina* adauga(Masina* v, Masina nou, int* nr) {

	Masina* copie = (Masina*)malloc(sizeof(Masina) * ((*nr) + 1));
	for (int i = 0; i < (*nr); i++) {
		copie[i] = v[i];
	}
	copie[(*nr)] = nou;
	free(v);
	(*nr)++;
	return copie;
}
Masina** citireFisier(const char* numetxt, Masina** a, int* nrColoane, int nrClustere) {
	FILE* f = fopen(numetxt, "r");
	if (f) {
		Masina nou;
		Masina* vector = NULL;
		char buffer[100];
		char delimitator[] = ",\n";
		*nrColoane = 0;
		while (fgets(buffer, 99, f)) {
			char* token = strtok(buffer, delimitator);
			nou.id = atoi(token);
			token = strtok(NULL, delimitator);
			nou.anFabricatie = atoi(token);
			token = strtok(NULL, delimitator);
			nou.pret = atof(token);
			token = strtok(NULL, delimitator);
			nou.marca = (char*)malloc(strlen(token) + 1);
			strcpy(nou.marca, token);
			int poz;
			if (nou.anFabricatie > 2000)
				poz = 0;
			else
			{
				poz = 1
					;
			}
			a[poz] = adauga(a[poz], nou, &(nrColoane[poz]));

		}
		fclose(f);
		return a;
	}
}
void afisare(Masina* m) {
	printf("Masina cu id ul:%i are pretul de %f si este din anul %i , marca %s\n", m->id, m->pret, m->anFabricatie, m->marca);
}

void afisareMatrice(Masina** v, int nrClustere, int* nrColoane) {
	for (int i = 0; i < nrClustere; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {

			afisare(&v[i][j]);
		}
		printf("\n");
	}
}
void dezalocare(Masina*** v, int** nrColoane, int* nrClustere) {
	for (int i = 0; i < (*nrClustere); i++) {
		for (int j = 0; j < (*nrColoane)[i]; j++)
			free((*v)[i][j].marca);

		free((*v)[i]);

	}
	free(*v);
	free(*nrColoane);
	*v = NULL;
	*nrClustere = 0;
	*nrColoane = NULL;
	printf("S-a dezalocat");
}
void modificarepret(Masina** m, int* nrColoane, int nrCluster) {
	for (int i = 0; i < nrColoane[nrCluster]; i++) {
		if (m[nrCluster][i].anFabricatie > 2005) m[nrCluster][i].pret += 50;
		else m[nrCluster][i].pret -= 50;
	}
}
float pretmediuMatrice(Masina** m, int* nrColoane, int nrClustere) {
	int suma = 0; int p = 1; int nr = 0;
	for (int i = 0; i < nrClustere; i++) {
		for (int j = 0; j < nrColoane[i]; j++)
		{
			suma += m[i][j].pret;
			nr++;
		}
	}

	return suma / nr;

}
float pretMediuCluster(Masina** m, int* nrColoane, int nrCluster) {
	float suma = 0; float nr = 0;
	for (int i = 0; i < nrColoane[nrCluster]; i++)
	{

		suma += m[nrCluster][i].pret;
		nr++;
	}


	if (nr > 0)
		return suma / nr;
}



void main() {
	int nr = 0;
	int nrClustere = 2;
	int* nrColoane = (int*)malloc(sizeof(int) * nrClustere);
	Masina** m = (Masina**)malloc(sizeof(Masina*) * nrClustere);
	for (int i = 0; i < nrClustere; i++) {
		nrColoane[i] = 0;
		m[i] = NULL;
	}

	citireFisier("masini.txt", m, nrColoane, nrClustere);
	afisareMatrice(m, nrClustere, nrColoane);
	printf("---------------------------\n");
	modificarepret(m, nrColoane, 0);
	afisareMatrice(m, nrClustere, nrColoane);
	printf("---------------------------\n");
	float medie = pretmediuMatrice(m, nrColoane, nrClustere);
	printf("Pretul mediu total este :%f\n", medie);
	printf("---------------------------\n");
	float mediec = pretMediuCluster(m, nrColoane, 1);
	printf("Pretul mediu in clustereul 1 este de:%f\n", mediec);
	printf("---------------------------\n");
	dezalocare(&m, &nrColoane, &nrClustere);
}