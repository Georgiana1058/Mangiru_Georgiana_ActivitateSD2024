#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
typedef struct RaportAnalizeMedicale RaportAnalizeMedicale;
typedef struct Nod Nod;
typedef struct HashTable HashTable;
typedef struct AnalizaMedicala AnalizaMedicala;
typedef struct ListaSimpla ListaSimpla;
struct RaportAnalizeMedicale {
	unsigned int codRaport;
	unsigned int codPacient;
	unsigned char numarAnalize;
	char** denumiriAnalizeMedicale;
	float* valoriCalculatePerAnaliza;
	float* valoareReferintaPerAnaliza;
	char* dataRecoltariiAnalizelor;
};
struct AnalizaMedicala {
	unsigned int codPacient;
	int poz;
	char* dataRecoltariiAnalizelor;
};
struct Nod {
	RaportAnalizeMedicale info;
	Nod* next;
};
struct ListaSimpla {
	AnalizaMedicala info;
	ListaSimpla* next;
};
struct HashTable {
	int dim;
	Nod** vector;

};
AnalizaMedicala initializareAnalize(unsigned int codPacient, int poz, char* dataRecoltariiAnalizelor) {
	AnalizaMedicala a;
	a.codPacient = codPacient;
	a.poz = poz;
	a.dataRecoltariiAnalizelor = (char*)malloc(strlen(dataRecoltariiAnalizelor) + 1);
	strcpy(a.dataRecoltariiAnalizelor, dataRecoltariiAnalizelor);
	return a;
}
void inserareLainceput(Nod** listaSimpla, AnalizaMedicala a) {
	ListaSimpla* nou = (ListaSimpla*)malloc(sizeof(ListaSimpla));
	nou->info = initializareAnalize(a.codPacient, a.poz, a.dataRecoltariiAnalizelor);
	nou->next = *listaSimpla;
	*listaSimpla = nou;
}
RaportAnalizeMedicale initializare(unsigned int codRaport, unsigned int codPacient, unsigned char numarAnalize, char** denumiriAnalizeMedicale, float* valoriCalculatePerAnaliza, float* valoareReferintaPerAnaliza, char* dataRecoltariiAnalizelor) {
	RaportAnalizeMedicale r;
	r.codRaport = codRaport;
	r.codPacient = codPacient;
	r.numarAnalize = numarAnalize;
	r.denumiriAnalizeMedicale = (char**)malloc(sizeof(char*) * numarAnalize);
	for (int i = 0; i < numarAnalize; i++) {
		r.denumiriAnalizeMedicale[i] = (char*)malloc(strlen(denumiriAnalizeMedicale[i]) + 1);
		strcpy(r.denumiriAnalizeMedicale[i], denumiriAnalizeMedicale[i]);

	}
	r.valoriCalculatePerAnaliza = (float*)malloc(sizeof(float) * numarAnalize);
	for (int i = 0; i < numarAnalize; i++) {
		r.valoriCalculatePerAnaliza[i] = valoriCalculatePerAnaliza[i];
	}
	r.valoareReferintaPerAnaliza = (float*)malloc(sizeof(float) * numarAnalize);
	for (int i = 0; i < numarAnalize; i++) {
		r.valoareReferintaPerAnaliza[i] = valoareReferintaPerAnaliza[i];
	}
	r.dataRecoltariiAnalizelor = (char*)malloc(strlen(dataRecoltariiAnalizelor) + 1);
	strcpy(r.dataRecoltariiAnalizelor, dataRecoltariiAnalizelor);
	return r;

}
void dezalocareRaport(RaportAnalizeMedicale* r) {
	for (int i = 0; i < r->numarAnalize; i++) {
		free(r->denumiriAnalizeMedicale[i]);
	}
	free(r->denumiriAnalizeMedicale);
	free(r->valoriCalculatePerAnaliza);
	free(r->valoareReferintaPerAnaliza);
	free(r->dataRecoltariiAnalizelor);
}
HashTable initializareHash(int dim) {
	HashTable h;
	if (dim > 0) {
		h.dim = dim;
		h.vector = (Nod**)malloc(sizeof(Nod*) * dim);
		for (int i = 0; i < dim; i++) {
			h.vector[i] = NULL;

		}
		return h;
	}
	else {
		printf("Dimensiunea trebuie sa fie mai mare ca 0\n");
		return;
	}

}
int calculHash(int dim, char* data) {
	if (dim > 0) {
		int rezultat = strlen(data);
		rezultat = rezultat % dim;
		return rezultat;

	}
	else {
		printf("Dimensiunea trebuie sa fie mai mare ca 0\n");
		return 0;
	}

};
void inserareLaFinal(Nod** cap, RaportAnalizeMedicale r) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(r.codPacient, r.codRaport, r.numarAnalize, r.denumiriAnalizeMedicale, r.valoriCalculatePerAnaliza, r.valoareReferintaPerAnaliza, r.dataRecoltariiAnalizelor);
	nou->next = NULL;
	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}

}

void inserareInHash(HashTable* h, RaportAnalizeMedicale r) {
	if (h->dim > 0) {
		int poz = calculHash(h->dim, r.dataRecoltariiAnalizelor);
		inserareLaFinal(&(h->vector[poz]), r);
	}
}

void afisareRaport(RaportAnalizeMedicale r) {
	printf("\n");
	printf("Cod pacient %u\n", r.codPacient);
	printf("Cod raport %u\n", r.codRaport);
	printf("Numar analize %u\n", r.numarAnalize);
	printf("Denumirii analize\n");
	for (int i = 0; i < r.numarAnalize; i++) {
		printf("%s\n", r.denumiriAnalizeMedicale[i]);
	}
	printf("Valori calculate per Analiza\n");
	for (int i = 0; i < r.numarAnalize; i++) {
		printf("%.2f\n", r.valoriCalculatePerAnaliza[i]);
	}
	printf("Valori de referinta per Analiza\n");
	for (int i = 0; i < r.numarAnalize; i++) {
		printf("%.2f\n", r.valoareReferintaPerAnaliza[i]);
	}
	printf("Data recoltarii:%s\n", r.dataRecoltariiAnalizelor);
}
void afisareHash(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		Nod* p = h.vector[i];
		while (p) {
			afisareRaport(p->info);
			p = p->next;
		}
	}
}
void dezalocare(HashTable* h) {
	for (int i = 0; i < (*h).dim; i++)
	{
		Nod* aux = h->vector[i];
		while (aux) {
			Nod* temp = aux;
			dezalocareRaport(&aux->info);
			aux = aux->next;
			free(temp);
		}
	}
	free(h->vector);
	h->vector = NULL;
	h->dim = 0;
	printf("Tabela s-a dezalocat\n");

}
int numarAnalize(HashTable h, char* data) {
	int nr = 0;
	int poz = calculHash(h.dim, data);

	Nod* p = h.vector[poz];
	while (p) {
		if (strcmp(p->info.dataRecoltariiAnalizelor, data) == 0) {
			nr += p->info.numarAnalize;
		}
		p = p->next;
	}

	if (nr > 0) {
		return nr;
	}
	else {
		printf("Nu exista aceasta data!\n");
		return 0;
	}
	free(p);
}
int numarRapoarte(HashTable h, char* data) {
	int nr = 0;
	int poz = calculHash(h.dim, data);
	Nod* p = h.vector[poz];
	while (p) {
		if (strcmp(p->info.dataRecoltariiAnalizelor, data) == 0) {
			nr++;
		}
		p = p->next;
	}
	if (nr > 0) {
		return nr;
	}
	else {
		printf("Nu exista rapoarte in aceasta data\n");
		return 0;
	}
	free(p);
}
void creareListaSimpla(HashTable h, ListaSimpla** lista, char* data) {
	int poz = calculHash(h.dim, data);
	Nod* p = h.vector[poz];
	while (p) {
		if (strcmp(p->info.dataRecoltariiAnalizelor, data) == 0) {
			AnalizaMedicala a = initializareAnalize(p->info.codPacient, poz, p->info.dataRecoltariiAnalizelor);
			inserareLainceput(lista, a);
		}
		p = p->next;
	}
	free(p);
}
void afisareLista(ListaSimpla* lista) {

	while (lista) {
		printf("Data recoltarii analizelor %s\n", lista->info.dataRecoltariiAnalizelor);
		printf("Valorea pozitiei din tabela hash %i\n", lista->info.poz);

		printf("Cod pacient %u\n", lista->info.codPacient + 1);
		lista = lista->next;
	}
}
void dezalocareLista(ListaSimpla** lista) {
	while (*lista) {
		free((*lista)->info.dataRecoltariiAnalizelor);
		ListaSimpla* aux = *lista;
		(*lista) = (*lista)->next;
		free(aux);

	}
	printf("Lista simpla s-a dezalocat\n");
}
void main() {
	int dim = 10;
	HashTable h = initializareHash(10);
	for (int i = 0; i < dim; i++) {

		unsigned int codRaport = i;
		unsigned int codPacient = i + 1;
		unsigned char numarAnalize = 2;
		char** denumiriAnalizeMedicale = (char**)malloc(sizeof(char*) * numarAnalize);
		for (int j = 0; j < numarAnalize; j++) {
			denumiriAnalizeMedicale[j] = (char*)malloc(sizeof(char) * 20);
			sprintf(denumiriAnalizeMedicale[j], "Analiza %d", i + j + 1);
		}

		float* valoriCalculatePerAnaliza = (float*)malloc(sizeof(float) * numarAnalize);
		valoriCalculatePerAnaliza[0] = 10.00f + i;
		valoriCalculatePerAnaliza[1] = 11.00f + i;
		float* valoareReferintaPerAnaliza = (float*)malloc(sizeof(float) * numarAnalize);
		valoareReferintaPerAnaliza[0] = 11.00f + i;
		valoareReferintaPerAnaliza[1] = 12.00f + i;
		char* dataRecoltariiAnalizelor = (char*)malloc(sizeof(char) * 30);
		sprintf(dataRecoltariiAnalizelor, "%d.0%d.2024", i + 1, i);
		RaportAnalizeMedicale r = initializare(codRaport, codPacient, numarAnalize, denumiriAnalizeMedicale, valoriCalculatePerAnaliza, valoareReferintaPerAnaliza, dataRecoltariiAnalizelor);
		inserareInHash(&h, r);
		for (int j = 0; j < numarAnalize; j++) {
			free(denumiriAnalizeMedicale[j]);
		}

		free(denumiriAnalizeMedicale);
		free(valoareReferintaPerAnaliza);
		free(valoriCalculatePerAnaliza);
		free(dataRecoltariiAnalizelor);

	}
	afisareHash(h);
	printf("----------------------\n");

	int nr = numarAnalize(h, "9.08.2024");
	printf("Numar de analize din 9.08.2024 este:%i\n", nr);
	printf("----------------------\n");
	int nrR = numarRapoarte(h, "8.07.2024");
	printf("Numar de rapoarte din 8.07.2024 este:%i\n", nrR);

	ListaSimpla* lista = NULL;
	creareListaSimpla(h, &lista, "7.06.2024");
	afisareLista(lista);
	dezalocareLista(&lista);
	dezalocare(&h);
}