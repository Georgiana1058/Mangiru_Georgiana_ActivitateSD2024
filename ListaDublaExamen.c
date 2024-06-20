#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
typedef struct Reteta Reteta;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;
struct Reteta {
	unsigned int nr_reteta;
	unsigned char nr_medicamente;
	float* medicamente;
	unsigned char* procente_compensare;
	char* nume_medic;
};
struct Nod {
	Reteta info;
	Nod* next;
	Nod* prev;
};
struct ListaDubla {
	Nod* head;
	Nod* tail;
};
Reteta initializare(unsigned int nr_reteta, unsigned char nr_medicamente, float* medicamente, unsigned char* procente_compensare, char* nume_medic) {
	Reteta r;
	r.nr_reteta = nr_reteta;
	r.nr_medicamente = nr_medicamente;
	r.medicamente = (float*)malloc(sizeof(float) * nr_medicamente);
	for (int i = 0; i < nr_medicamente; i++) {
		r.medicamente[i] = medicamente[i];
	}
	r.procente_compensare = (unsigned char*)malloc(sizeof(unsigned char) * nr_medicamente);
	for (int i = 0; i < nr_medicamente; i++) {
		r.procente_compensare[i] = procente_compensare[i];
	}
	r.nume_medic = (char*)malloc(sizeof(nume_medic) + 1);
	strcpy(r.nume_medic, nume_medic);
	return r;
}
void inserareLaInceput(ListaDubla* listaDubla, Reteta r) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(r.nr_reteta, r.nr_medicamente, r.medicamente, r.procente_compensare, r.nume_medic);
	nou->next = listaDubla->head;
	nou->prev = NULL;
	if (listaDubla->head == NULL) {
		listaDubla->head = nou;
		listaDubla->tail = nou;
	}
	else {
		listaDubla->head->prev = nou;
	}
	listaDubla->head = nou;
}
void inserareLaFinal(ListaDubla* listaDubla, Reteta r) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(r.nr_reteta, r.nr_medicamente, r.medicamente, r.procente_compensare, r.nume_medic);
	nou->next = NULL;
	nou->prev = NULL;
	if (listaDubla->head == NULL) {
		nou->prev = NULL;
		listaDubla->head = nou;
		listaDubla->tail = nou;
	}
	else {
		Nod* temp = listaDubla->tail;
		temp->next = nou;
		nou->prev = temp;
		listaDubla->tail = nou;
	}

}
void afisareReteta(Reteta r) {
	printf("Numar reteta %u\n", r.nr_reteta);
	printf("Numar medicamente %u\n", r.nr_medicamente);
	printf("Medicamente:\n");
	for (int i = 0; i < r.nr_medicamente; i++) {
		printf("%.2f\n", r.medicamente[i]);
	}
	printf("Procente compensatie:\n");
	for (int i = 0; i < r.nr_medicamente; i++) {
		printf("%u\n", r.procente_compensare[i]);
	}
	printf("Nume  medic: %s\n", r.nume_medic);

}

void afisareListaCrescator(ListaDubla lista) {
	Nod* aux = lista.head;
	while (aux) {
		afisareReteta(aux->info);

		aux = aux->next;
	}

}
void afisareListaDescrescator(ListaDubla lista) {
	Nod* aux = lista.tail;
	while (aux) {
		afisareReteta(aux->info);

		aux = aux->prev;
	}

}
void dezalocare(ListaDubla* listaDubla) {
	Nod* aux = listaDubla->head;
	while (aux) {
		free(aux->info.nume_medic);
		free(aux->info.medicamente);
		free(aux->info.procente_compensare);
		Nod* temp = aux;
		aux = aux->next;
		free(temp);

	}
	listaDubla->head = NULL;
	listaDubla->tail = NULL;
	printf("Lista s-a dezalocat\n");
}
float incasareMedicament(ListaDubla listaDubla, int index) {
	Nod* aux = listaDubla.head;
	float suma = 0;
	if (index < aux->info.nr_medicamente) {
		while (aux) {
			suma += aux->info.medicamente[index];
			aux = aux->next;
		}
		return suma;
	}
	else {
		printf("Indexul medicamentului este prea mare\n");
		return 0;
	}
};
#pragma region
Reteta* reteteMedic(ListaDubla listaDubla, const char* numeMedic, int* nr) {
	*nr = 0;
	Nod* aux = listaDubla.head;
	while (aux) {
		if (strcmp(aux->info.nume_medic, numeMedic) == 0) {
			(*nr)++;
		}
		aux = aux->next;
	}
	if ((*nr) > 0) {
		Reteta* vector = (Reteta*)malloc(sizeof(Reteta) * (*nr));
		Nod* aux = listaDubla.head;
		int k = 0;
		while (aux) {
			if (strcmp(aux->info.nume_medic, numeMedic) == 0) {
				vector[k++] = initializare(aux->info.nr_reteta, aux->info.nr_medicamente, aux->info.medicamente, aux->info.procente_compensare, aux->info.nume_medic);

			}
			aux = aux->next;
		}
		return vector;
	}
	else {
		printf("Acest medic nu exista\n");
		return NULL;
	}


}
void afisareVector(Reteta* vector, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareReteta(vector[i]);
	}
}

void dezalocareVector(Reteta** vector, int* nr) {
	for (int i = 0; i < (*nr); i++) {
		free((*vector)[i].nume_medic);
		free((*vector)[i].medicamente);
		free((*vector)[i].procente_compensare);
	}
	free(*vector);
	*vector = NULL;
	*nr = 0;
	printf("Vectorul s-a dezaloca\n");
}
unsigned char totalComisionVector(Reteta* vector, int nr) {
	unsigned char suma = 0;
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < vector->nr_medicamente; j++) {
			suma += vector->procente_compensare[j];

		}

	}
	if (suma > 0) {
		return suma;
	}
	else {
		printf("Vectorul este NULL\n");
		return NULL;
	}

}

#pragma endregion
int numarMedicamente(ListaDubla listaDubla, int index) {
	Nod* aux = listaDubla.head;
	int nr = 0;
	if (index < aux->info.nr_medicamente) {
		while (aux) {
			nr++;
			aux = aux->next;
		}
		return nr;
	}
	else {
		printf("Indexul medicamentului nu exista\n");
		return 0;
	}
};


void main() {
	ListaDubla listaDubla = { NULL,NULL };
	Reteta retete[10];
	for (int i = 0; i < 10; i++) {
		unsigned int nr_reteta = i + 1;
		unsigned char nr_medicamente = 3;
		float medicamente[3] = { 10.00f + i , 15.00f + i,20.00f + i };
		unsigned char procente_compensare[3] = { 10 + i,20 + i,30 + i };
		char nume_medic[20];
		sprintf(nume_medic, "Medic %d", i + 1);
		retete[i] = initializare(nr_reteta, nr_medicamente, medicamente, procente_compensare, nume_medic);
		inserareLaFinal(&listaDubla, retete[i]);
	}

	printf("Afisare lista in ordine crescatoare:\n");
	afisareListaCrescator(listaDubla);

	printf("\nAfisare lista in ordine descrescatoare:\n");
	afisareListaDescrescator(listaDubla);
	float suma = incasareMedicament(listaDubla, 0);
	printf("Suma medicamentului este: %f\n", suma);
	printf("---------------------------\n");
	int nr = 0;
	Reteta* vector = reteteMedic(listaDubla, "Medic 2", &nr);
	afisareVector(vector, nr);
	printf("---------------------------\n");
	unsigned char suma2 = totalComisionVector(vector, nr);
	printf("Suma totala a incasarilor este %u\n", suma2);
	printf("---------------------------\n");
	int nrMedicamente = numarMedicamente(listaDubla, 0);
	printf("Numar de medicamente este %i\n", nrMedicamente);
	dezalocareVector(&vector, &nr);
	dezalocare(&listaDubla);

}