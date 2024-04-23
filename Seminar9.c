#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
typedef struct Elev Elev;
struct Elev {
	int id;
	int nrMedii;
	float* medii;

};
typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};
void inserareArbore(Nod** radacina, Elev e) {
	if (*radacina) {
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);
		}
	}
	else {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		// aici se insereaza intotdeauna nodul frunza
		*radacina = nod;
	}
}
Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = (float*)malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &(e.medii[i]));
	}
	return e;
}Nod* citireFisier(char* numeFisier) {

	Nod* arbore = NULL;
	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);
		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);
		}
		fclose(fp);

	}
	return arbore;
}
void afisareElev(Elev e) {
	printf("Elevul cu Id-ul:% d are mediile:\n", e.id);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%5.2f", e.medii[i]);
	}
	printf("\n");
}
void afisareInOrder(Nod* arbore) {
	//in ordine -SRD
	//pre ordine-RSD
	//post ordine-SDR
	if (arbore) {
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);

	}

}
float calculeazaSumaNote(Nod* arbore, int* nrNote) {
	if (arbore) {
		float suma = 0;
		//r
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];

		}
		(*nrNote) += arbore->info.nrMedii;
		//dr
		float  sumaD = calculeazaSumaNote(arbore->st, nrNote);
		//st
		float sumaS = calculeazaSumaNote(arbore->dr, nrNote);

		return suma + sumaD + sumaS;
	}
	else {
		return 0;
	}
}
float calculeazaMediaGenerala(Nod* arbore) {
	float nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0) {
		return (suma / nrNote);

	}
	else {
		return 0;
	}


}
void main() {
	Nod* arbore = citireFisier("elevi.txt");
	afisareInOrder(arbore);
	printf("Media este:%f", calculeazaMediaGenerala(arbore));
}