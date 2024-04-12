#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>

typedef struct Mall Mall;
struct Mall {
	int id;
	char* denumire;
	char* locatie;
	int nrMagazine;

};

Mall initializare(int id, const char* denumire, const char* locatie, int nrMagazine) {
	Mall m;
	m.id = id;
	m.denumire = (char*)malloc(1 + strlen(denumire));
	strcpy(m.denumire, denumire);
	m.locatie = (char*)malloc(1 + strlen(locatie));
	strcpy(m.locatie, locatie);
	m.nrMagazine = nrMagazine;
	return m;


};
Mall* copiazaNObiecte(Mall* m, int nr, int* nrCopiate, int nrMagMin) {

	*nrCopiate = 0;
	int k = 0;
	if (nr > 0 && m != NULL) {
		for (int i = 0; i < nr; i++) {
			if (nrMagMin < m[i].nrMagazine) {
				(*nrCopiate)++;


			}
		}
		Mall* c = (Mall*)malloc(sizeof(Mall) * (*nrCopiate));

		for (int i = 0; i < nr; i++) {
			if (nrMagMin < m[i].nrMagazine) {
				c[k++] = initializare(m[i].id, m[i].denumire, m[i].locatie, m[i].nrMagazine);


			}
		}
		return c;
	}


	return 0;
}
Mall* magazineDinMallCuIdImpar(Mall* m, int nr, int* nrNou) {
	if (nr > 0 && m != NULL) {
		for (int i = 0; i < nr; i++)
			if (m[i].id % 2 == 1)
				(*nrNou)++;
		Mall* c = (Mall*)malloc(sizeof(Mall) * (*nrNou));
		int k = 0;
		for (int i = 0; i < nr; i++)
			if (m[i].id % 2 == 1)
			{
				c[k].denumire = (Mall*)malloc(strlen(m[i].denumire) + 1);
				strcpy(c[k].denumire, m[i].denumire);
				c[k].locatie = (Mall*)malloc(strlen(m[i].locatie) + 1);
				strcpy(c[k].locatie, m[i].locatie);
				c[k].id = m[i].id;
				c[k].nrMagazine = m[i].nrMagazine;
				k++;
			}

		return c;
	}
	return 0;
}

void afisare(Mall* v, int nr) {
	if (nr > 0 && v != NULL)
		for (int i = 0; i < nr; i++) {
			printf("\n%s%d are id-ul:%i si se afla in %s , avand un numar total de %i de magazin\n", v[i].denumire, i + 1, v[i].id, v[i].locatie, v[i].nrMagazine);
		}
};
void dezalocare(Mall** m, int* nr) {

	for (int i = 0; i < *nr; i++) {
		free((*m)[i].denumire);
		free((*m)[i].locatie);
	}
	free(*m);
	(*m) = NULL;
	(*nr) = 0;
	printf("\nS-a dezalocat\n");
}
Mall* concatenare(Mall* v, Mall* p, int nr1, int nr2, int* nrN) {
	*nrN = nr1 + nr2;
	Mall* concatenat = (Mall*)malloc(sizeof(Mall) * (*nrN));
	int ind = 0;
	for (int i = 0; i < nr1; i++) {
		concatenat[ind++] = v[i];
	}
	for (int i = 0; i < nr2; i++) {
		concatenat[ind++] = p[i];
	}
	return concatenat;
}
void main() {
	int nr = 5;
	Mall* v = (Mall*)malloc(sizeof(Mall) * nr);
	for (int i = 0; i < nr; i++) {
		v[i] = initializare(i + 1, "Mall", "Bucuresti", (i + 1) * 10);
	}
	afisare(v, nr);
	printf("-----------------------------");
	int nrCopiate = 0;
	Mall* c = copiazaNObiecte(v, nr, &nrCopiate, 30);
	afisare(c, nrCopiate);
	int* nrNou = 0;
	Mall* vector = magazineDinMallCuIdImpar(v, nr, &nrNou);

	printf("------------------------------");
	afisare(vector, nrNou);
	int nrN = 0;
	Mall* concatenat = concatenare(c, vector, nrCopiate, nrNou, &nrN);
	printf("---------------");
	afisare(concatenat, nrN);
	dezalocare(&c, &nrCopiate);
	dezalocare(&vector, &nrNou);
	dezalocare(&v, &nr);

}