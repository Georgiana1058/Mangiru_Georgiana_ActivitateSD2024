#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
typedef struct CursaFeroviara CursaFeroviara;
typedef struct Nod Nod;
struct CursaFeroviara {
	unsigned int numarCursa;
	char* dataCursa;
	unsigned short int numarBiletecumparate1Sau2[2];
	float pretBilet1sau2[2];
};
struct Nod {
	CursaFeroviara info;
	Nod* st;
	Nod* dr;
};
CursaFeroviara initializare(unsigned int numarCursa, char* dataCursa, unsigned short int numarBiletecumparate1Sau2[2], float pretBilet[2]) {
	CursaFeroviara c;
	c.numarCursa = numarCursa;
	c.dataCursa = (char*)malloc(strlen(dataCursa) + 1);
	strcpy(c.dataCursa, dataCursa);
	c.numarBiletecumparate1Sau2[0] = numarBiletecumparate1Sau2[0];
	c.numarBiletecumparate1Sau2[1] = numarBiletecumparate1Sau2[1];
	c.pretBilet1sau2[0] = pretBilet[0];
	c.pretBilet1sau2[1] = pretBilet[1];
	return c;
}
CursaFeroviara citireCursa(FILE* f) {
	CursaFeroviara c;
	fscanf(f, "%u", &c.numarCursa);
	char buffer[100];
	fscanf(f, "%s", buffer);
	c.dataCursa = (char*)malloc(strlen(buffer) + 1);
	strcpy(c.dataCursa, buffer);
	fscanf(f, "%u", &c.numarBiletecumparate1Sau2[0]);
	fscanf(f, "%u", &c.numarBiletecumparate1Sau2[1]);
	fscanf(f, "%f", &c.pretBilet1sau2[0]);
	fscanf(f, "%f", &c.pretBilet1sau2[1]);
	return c;
}
void inserareArbore(Nod** arbore, CursaFeroviara c) {
	if (*arbore) {
		if (c.numarCursa < (*arbore)->info.numarCursa) {
			inserareArbore(&((*arbore)->st), c);
		}
		else {
			inserareArbore(&((*arbore)->dr), c);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = initializare(c.numarCursa, c.dataCursa, c.numarBiletecumparate1Sau2, c.pretBilet1sau2);
		nou->st = NULL;
		nou->dr = NULL;
		*arbore = nou;
	}
}
Nod* citireArbore(char* numeFisier) {
	Nod* arbore = NULL;
	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* f = fopen(numeFisier, "r");
		int nrCurse = 0;
		fscanf(f, "%i", &nrCurse);
		for (int i = 0; i < nrCurse; i++) {
			CursaFeroviara c = citireCursa(f);
			inserareArbore(&arbore, c);
		}
		fclose(f);
		return arbore;
	}

}
int numarBilete(Nod* arbore) {
	if (arbore) {
		int nr = 0;
		nr += arbore->info.numarBiletecumparate1Sau2[1];
		nr += numarBilete(arbore->st);
		nr += numarBilete(arbore->dr);
	}
	else {
		return 0;
	}
}
void afisareCursa(CursaFeroviara c) {
	printf("\n");
	printf("Numar cursa %u\n", c.numarCursa);
	printf("Data cursa %s\n", c.dataCursa);
	printf("Numar bilete la clasa 1: %u\n", c.numarBiletecumparate1Sau2[0]);
	printf("Numar bilete la clasa 2: %u\n", c.numarBiletecumparate1Sau2[1]);
	printf("Pret bilete la clasa 1: %.2f\n", c.pretBilet1sau2[0]);
	printf("Pret bilete la clasa 2: %.2f\n", c.pretBilet1sau2[1]);
}
void afisareInOrdine(Nod* arbore) {
	if (arbore) {
		afisareInOrdine(arbore->st);
		afisareCursa(arbore->info);
		afisareInOrdine(arbore->dr);
	}
}
void dezalocareArbore(Nod** arbore) {
	if (*arbore) {
		dezalocareArbore(&((*arbore)->st));
		dezalocareArbore(&((*arbore)->dr));
		free((*arbore)->info.dataCursa);
		free(*arbore);
		*arbore = NULL;
	}
}
void dezalocareCursa(CursaFeroviara c) {
	free(c.dataCursa);
}
void modificaPret(Nod** arbore, char* data, float procent) {
	if (*arbore) {
		modificaPret(&((*arbore)->st), data, procent);
		modificaPret(&((*arbore)->dr), data, procent);
		if (strcmp((*arbore)->info.dataCursa, data) == 0) {
			(*arbore)->info.pretBilet1sau2[0] = ((*arbore)->info.pretBilet1sau2[0]) * (1 + procent / 100);

		}
	}
}
float incasari(CursaFeroviara c) {

	float suma = 0;
	suma += c.numarBiletecumparate1Sau2[0] * c.pretBilet1sau2[0] + c.numarBiletecumparate1Sau2[1] * c.pretBilet1sau2[1];
	return suma;
}
void incasariMaxime(Nod* arbore, CursaFeroviara* c, float* max) {
	if (arbore == NULL) {
		return;
	}
	float incasarCurente = incasari(arbore->info);
	if ((*max) <= incasarCurente) {
		(*max) = incasarCurente;
		*c = initializare(arbore->info.numarCursa, arbore->info.dataCursa, arbore->info.numarBiletecumparate1Sau2, arbore->info.pretBilet1sau2);
	}
	incasariMaxime(arbore->st, c, max);
	incasariMaxime(arbore->dr, c, max);

}

void main() {
	Nod* arbore = citireArbore("curse.txt");
	afisareInOrdine(arbore);
	printf("------------\n");
	int nrBilete = numarBilete(arbore);
	printf("Numar de bilete de la clasa a 2 a este %i\n", nrBilete);
	printf("------------\n");
	modificaPret(&arbore, "2024-06-23", 20);
	afisareInOrdine(arbore);
	printf("------------\n");
	CursaFeroviara c;
	float max = 0;
	incasariMaxime(arbore, &c, &max);
	afisareCursa(c);
	dezalocareCursa(c);
	dezalocareArbore(&arbore);

}