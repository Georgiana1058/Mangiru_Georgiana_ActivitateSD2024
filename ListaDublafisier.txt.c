#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct Student Student;
struct Student {
	int cod;
	float medie;
	float varsta;
	char* nume;
};
typedef struct Nod Nod;
struct Nod {
	Student info;
	Nod* next;
	Nod* prev;

};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* head;
	Nod* tail;
};
Student initializare(int cod, float medie, float varsta, const char* nume) {
	Student s;
	s.cod = cod;
	s.medie = medie;
	s.varsta = varsta;
	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(s.nume, nume);
	return s;
}
void inserareLaInceput(ListaDubla* listadubla, Student s) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = s;
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
void afisare(Student s) {
	printf("Nume:%s Medie:%.2f Varsta:%f Cod:%i\n ", s.nume, s.medie, s.varsta, s.cod);
}
void afisareLista(ListaDubla listadubla) {
	Nod* current = listadubla.head;
	while (current) {
		afisare(current->info);
		current = current->next;

	}
}
void citirefisier(const char* numetxt, ListaDubla* listadubla) {
	FILE* f = fopen(numetxt, "r");
	if (f) {
		char buffer[100];
		char delimitator[] = ",\n";
		Student s;
		while (fgets(buffer, 99, f)) {
			char* token = strtok(buffer, delimitator);
			s.cod = atoi(token);
			token = strtok(NULL, delimitator);
			s.medie = atof(token);
			token = strtok(NULL, delimitator);
			s.nume = (char*)malloc(strlen(token) + 1);
			strcpy(s.nume, token);
			token = strtok(NULL, delimitator);
			s.varsta = atof(token);
			inserareLaInceput(listadubla, s);

		}

		fclose(f);
	}
}
void stergereNodDupaNume(ListaDubla* listadubla, const char* nume) {
	Nod* nod = listadubla->head;
	while (nod && strcmp(nod->info.nume, nume) != 0) {
		nod = nod->next;
	}
	if (nod) {
		if (nod == listadubla->head) {
			if (nod == listadubla->tail) {
				listadubla->head = NULL;
				listadubla->tail = NULL;
			}
			else {
				listadubla->head->prev = nod->next;
			}
		}
		else {
			if (nod == listadubla->tail) {
				listadubla->tail = nod->prev;
				nod->prev->next = NULL;

			}
			else {
				nod->prev->next = nod->next;
				if (nod->next) {
					nod->next->prev = nod->prev;
				}
				nod->prev->next = nod->next;
			}
		}
		free(nod->info.nume);
		free(nod);
	}
}

void stergeLista(ListaDubla* listadubla) {
	while (listadubla->head)
	{
		free(listadubla->head->info.nume);
		Nod* aux = listadubla->head;
		listadubla->head = listadubla->head->next;
		free(aux);
	}
	listadubla->head = NULL;
	listadubla->tail = NULL;
	printf("S-a sters lista");
}
void main() {
	Student s1 = initializare(1, 9, 20, "Georgiana");
	Student s2 = initializare(2, 8.5, 21, "Alex");
	Student s3 = initializare(3, 7.9, 20, "Bianca");
	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;
	inserareLaInceput(&lista, s1);
	inserareLaInceput(&lista, s2);
	inserareLaInceput(&lista, s3);
	citirefisier("studenti.txt", &lista);
	afisareLista(lista);
	printf("--------------------\n");
	stergereNodDupaNume(&lista, "Georgiana");
	afisareLista(lista);
	stergeLista(&lista);

}