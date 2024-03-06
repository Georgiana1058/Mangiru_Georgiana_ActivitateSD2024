#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}

	if (vector)
		free(vector);

	(*dimensiune)++;

	return copie;
}


struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	FILE* f = fopen(numeFisier, "r");

	if (f != NULL)
	{
		(*nrAeroporturi) = 0;
		char buffer[100];

		//fgets-citeste o linie intreaga, returneaza char*, string de caractere
		//fread-tot asa poate citi o linie intreaga
		// sau mai putem folosi fscanf
		//static sau dinamic? static de 100, dinamic-sizeof de cine? mai intai ar trebui sa citim
		//chit ca e static sau dinamic ar fi tot 100 dar dinamic ar trebui sa l si dealocam
		while (fgets(buffer, 99, f) != NULL)
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);//strtok-pt a face despartirea dupa virgula
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);

		}
		fclose(f);

	}
	return vectorAeroporturi;

}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu id: %d cu numele %s are %d terminale.\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);

}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	printf("AFISARE VECTOR:\n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

/*struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int idCautat) {
	struct Aeroport* aeroport = NULL;

	for (int i = 0; i < dim; i++)
	{
		if (aeroporturi[i].id == idCautat)
		{
			return aeroporturi[i];
		}
	}
	struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = -1;
	aeroport.nume = malloc(sizeof(char) * (1 + strlen("N/A")));
	strcpy(aeroport.nume, "N/A");
	return aeroport;
}
*/
void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++)
	{
		free((*aeroporturi)[i].nume);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void main() {
	int dimensiune = 3;

	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);

	dezalocareVector(&aeroporturi, &dimensiune);

}