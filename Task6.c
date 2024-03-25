#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Magazin {
	int id;
	char* nume;
	int nrProduse;
};
struct Nod {
	struct Magazin* info;
	struct Nod* next;//nodul urmator 
	struct Nod* prev;//nodul anterior
};
struct ListaDubla {
	struct Nod* prim;//primul nod pentru a putea face operatii la inceput
	struct Nod* ultim;//ultimul nod pentru a putea face operatii la final

};
struct Magazin* initializareMagazin(int id, const char* nume, int nrProduse) {
	struct Magazin* magazin = (struct Magazin*)malloc(sizeof(struct Magazin) * 1);
	magazin->id = id;
	magazin->nume = (char*)malloc(sizeof(char) * (1 + strlen(nume)));
	strcpy(magazin->nume, nume);
	magazin->nrProduse = nrProduse;
	return magazin;

}
struct Nod* initializareNod(struct Magazin* info) {
	struct Nod* nod = (struct Nod*)malloc(sizeof(struct Nod) * 1);
	nod->info = info;
	nod->next = NULL;
	nod->prev = NULL;
	return nod;
}

void adaugaMagazin(struct ListaDubla* lista, struct Magazin* magazinNou) {
	struct Nod* nodNou = initializareNod(magazinNou);
	if (lista->prim == NULL) {
		lista->prim = nodNou;
		lista->ultim = nodNou;

	}
	else {
		lista->ultim->next = nodNou;
		nodNou->prev = lista->ultim;
		lista->ultim = nodNou;
	}
}
void citesteMagazine(const char* numeFisier, struct ListaDubla* lista) {
	FILE* f = fopen(numeFisier, "r");
	if (f == NULL) printf("Nu se descchide fisierul !");
	else {
		char buffer[100];
		while (fgets(buffer, sizeof(buffer), f) != NULL) {
			struct Magazin* magazinNou = (struct Magazin*)malloc(sizeof(struct Magazin));
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			magazinNou->id = atoi(token);
			token = strtok(NULL, delimitator);
			magazinNou->nume = (char*)malloc(sizeof(char) * (1 + strlen(token)));
			strcpy(magazinNou->nume, token);
			token = strtok(NULL, delimitator);
			magazinNou->nrProduse = atoi(token);
			adaugaMagazin(lista, magazinNou);
		}
		fclose(f);
	}
}
void afiseazaMagazin(struct Magazin* magazin)
{
	printf("Magazinul %s cu id-ul %i are un numar de %i produse\n", magazin->nume, magazin->id, magazin->nrProduse);
}
void afiseazaMagazine(struct ListaDubla* lista) {
	printf("Afisare magazine\n");
	struct Nod* current = lista->prim;
	while (current != NULL) {
		afiseazaMagazin(current->info);
		current = current->next;
	}
}

void dezalocareMagazine(struct ListaDubla* lista) {
	struct Nod* current = lista->prim;
	while (current != NULL) {
		struct Nod* temp = current;
		current = current->next;
		free(temp->info->nume);
		free(temp->info);
		free(temp);

	}
	lista->prim = NULL;
	lista->ultim = NULL;
}

void stergeNod(struct ListaDubla* lista, int pozitie) {
	struct Nod* current = lista->prim;
	int index = 0;
	while (current != NULL && index <=pozitie)
	{
		current = current->next;
		index++;
	}
	if (current == NULL) {
		printf("pozitie invalida\n");
		return;
	}
	if (current == lista->prim) {
		lista->prim = current->next;

	}
	if (current == lista->ultim) {
		lista->ultim = current->prev;
	}
	if (current->prev != NULL) {
		current->prev->next = current->next;
	}
	if (current->next != NULL) {
		current->next->prev = current->prev;
	}
	free(current->info->nume);
	free(current->info);
	free(current);
}
void insereazaSortat(struct ListaDubla* lista, struct Magazin* magazinNou) {
	struct Nod* current = lista->prim;
	while (current != NULL && current->info->id < magazinNou->id)
		current = current->next;
	struct Nod* nodNou = initializareNod(magazinNou);
	//Adaugam la final
	if (current == NULL) {
		lista->ultim->next = nodNou;
		nodNou->prev = lista->ultim;
		lista->ultim = nodNou;
	}
	//Adaugam la inceput
	else if (current->prev == NULL)
	{
		nodNou->next = lista->prim;
		lista->prim->prev = nodNou;
		lista->prim = nodNou;
	}
	//Adaugam la interior
	else {
		nodNou->prev = current->prev;
		nodNou->next = current;
		current->prev->next = nodNou;
		current->prev = nodNou;
	}
}
void afiseazaMagazineSortatCrescator(struct ListaDubla* lista) {
	printf("Afiseaza magazine crescator\n");
	struct Nod* current = lista->prim;
	while (current != NULL) {
		afiseazaMagazin(current->info);
		current = current->next;
	}
}
void afiseazaMagazineDescrescator(struct ListaDubla* lista) {
	printf("Afiseaza magazine descrescator\n");
	struct Nod* current = lista->ultim;
	while (current != NULL) {
		afiseazaMagazin(current->info);
		current = current->prev;
	}
}
int main() {
	struct ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	citesteMagazine("magazinelisteduble.txt", &lista);
	afiseazaMagazine(&lista);

	//Stergere Nod de pe o anumita pozitie
	printf("Sterg nodul de pe pozitia 2 \n");
	stergeNod(&lista, 2);
	afiseazaMagazine(&lista);
	printf("\n");
	//Inserare magazin sortat crescator dupa ID
	struct Magazin* magazin = initializareMagazin(4, "EduardSRL", 100);
	printf("Inserez un nou nod\n");
	insereazaSortat(&lista, magazin);
	afiseazaMagazine(&lista);
	printf("Afiseaza lista sortata crescator\n");
	afiseazaMagazineSortatCrescator(&lista);
	printf("Afiseaza lista sortata descrescator\n");
	afiseazaMagazineDescrescator(&lista);
	dezalocareMagazine(&lista);
	return 0;

}