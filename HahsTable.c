#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
typedef struct Student Student;
struct Student {
	int cod;
	char* nume;
	float varsta;
	float medie;
};
typedef struct Nod Nod;
struct Nod {
	Student info;
	Nod* next;
};
typedef struct Hash Hash;
struct Hash {
	Nod** vector;
	int dim;
};
Student initializare(int cod, const char* nume, float varsta, float medie) {
	Student s;
	s.cod = cod;
	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.medie = medie;
	s.varsta = varsta;
	return s;
}
Hash initializareHash(int dim) {
	Hash hash;
	hash.dim = dim;
	hash.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++)
	{
		hash.vector[i] = NULL;
	}
	return hash;
}
int calculHash(int medie, int dim) {
	if (dim > 0) {
		return medie % dim;
	}
	else return -1;
}
void inseareLaFinal(Nod** cap, Student s) {
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
	sfarsit->info = initializare(s.cod, s.nume, s.varsta, s.medie);
	sfarsit->next = NULL;
	if (*cap) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = sfarsit;

	}
	else {
		*cap = sfarsit;
	}
}

void inserareHash(Hash hash, Student s) {
	if (hash.dim > 0) {
		int poz = calculHash(s.medie, hash.dim);

		if (hash.vector[poz] != NULL) {
			inseareLaFinal(&(hash.vector[poz]), s);

		}
		else {
			inseareLaFinal(&(hash.vector[poz]), s);
		}

	}
}
void afisare(Student s) {
	printf("Studentul %s cod:%i medie%f varsta:%f\n", s.nume, s.cod, s.medie, s.varsta);
}
void afisareLista(Nod* cap) {
	while (cap) {
		afisare(cap->info);
		cap = cap->next;
	}
}
void afisareHash(Hash hash) {
	for (int i = 0; i < hash.dim; i++) {
		printf("Clusterul:%d\n\n", i + 1);
		afisareLista(hash.vector[i]);

	}
}
void dezalocareLista(Nod** cap) {
	while (*cap) {
		free((*cap)->info.nume);
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
}
void dezalocare(Hash* hash) {
	for (int i = 0; i < hash->dim; i++) {
		if (hash->vector[i]) {
			dezalocareLista(&(hash->vector[i]));
			hash->vector[i] = NULL;
		}
	}
	free(hash->vector);
	hash->vector = NULL;
	hash->dim = 0;
}
void afisareStudentDupaMedie(float medie, Hash hash) {
	int poz = calculHash(medie, hash.dim);
	if (poz >= 0 && poz < hash.dim) {
		if (hash.vector[poz]) {
			Nod* p = hash.vector[poz];
			while (p && p->info.medie != medie) {
				p = p->next;
			}
			if (p) {
				afisare(p->info);
			}
			else {
				printf("Nu exista!!");
			}
		}
		else {
			printf("Nu exista!!");
		}
	}
}
void stergereDupaMedie(float medie, Hash* hash) {
	int poz = calculHash(medie, hash->dim);
	if (poz >= 0 && poz < hash->dim) {
		Nod* prev = NULL;
		Nod* nod = hash->vector[poz];
		while (nod && nod->info.medie != medie) {
			prev = nod;
			nod = nod->next;
		}
		if (nod) {
			if (prev == NULL) {
				hash->vector[poz] = nod->next;
			}
			else {
				prev->next = nod->next;
			}
			free(nod->info.nume);
			free(nod);
			printf("S-a sters!!\n");
		}
	}
}
void stergeDupaNumesiMedie(float medie, const char* nume, Hash* hash) {
	int poz = calculHash(medie, hash->dim);
	if (poz >= 0 && poz < hash->dim) {
		Nod* prev = NULL;
		Nod* nod = hash->vector[poz];
		while (nod && nod->info.medie != medie && strcmp(nod->info.nume, nume) != 0) {
			prev = nod;
			nod = nod->next;
		}
		if (nod) {
			if (prev == NULL) {
				hash->vector[poz] = nod->next;
			}
			else {
				prev->next = nod->next;
			}
			free(nod->info.nume);
			free(nod);
			printf("S-a dezalocat\n");
		}
	}
}
Student* vectorVarstaData(float varsta, Hash hash, int* nrStudenti) {
	*nrStudenti = 0;
	for (int i = 0; i < hash.dim; i++) {
		Nod* nod = hash.vector[i];
		while (nod) {
			if (nod->info.varsta == varsta)

			{
				(*nrStudenti)++;
			}
			nod = nod->next;
		}

	}
	Student* vector = (Student*)malloc(sizeof(Student) * (*nrStudenti));
	int k = 0;
	for (int i = 0; i < hash.dim; i++) {
		Nod* nod = hash.vector[i];
		while (nod) {
			if (nod->info.varsta == varsta)

			{
				vector[k++] = initializare(nod->info.cod, nod->info.nume, nod->info.varsta, nod->info.medie);
			}
			nod = nod->next;
		}

	}
	return vector;
}
void afisareVector(Student* v, int nrStudenti) {
	printf("Afisare vector\n");
	for (int i = 0; i < nrStudenti; i++) {
		afisare(v[i]);
	}
	printf("\n\n");
}
void main() {
	Student s1 = initializare(1, "George", 19, 9);
	Student s2 = initializare(2, "Bianca", 20, 9.5);
	Student s3 = initializare(3, "Ionut", 20, 8.79);
	Hash hash = initializareHash(3);
	inserareHash(hash, s1);
	inserareHash(hash, s2);
	inserareHash(hash, s3);
	int* nr = 0;
	Student* vector = vectorVarstaData(20, hash, &nr);
	afisareVector(vector, nr);
	printf("------------------------\n");
	afisareStudentDupaMedie(9, hash);
	printf("------------------------\n");
	afisareHash(hash);
	printf("------------------------\n");
	stergereDupaMedie(8.79, &hash);
	stergeDupaNumesiMedie(9, "George", &hash);
	printf("------------------------\n");
	afisareHash(hash);
	dezalocare(&hash);

}