#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
struct Masina {
	//nu avem metode in limbajul 
	char* marca;
	float capacitateCilindrica;
	int an;

};
void afisareMasina(const struct Masina* m) {
	if (m->marca != NULL) {
		printf("Marca: %s\n", m->marca);
	}
	printf("Capacitate cilindrica:%5.2f\n", m->capacitateCilindrica);
	printf("An:%d\n\n", m->an);

}
struct Masina initializareMasina(const char* marca, int an, float cc) {
	struct Masina m;
	m.an = an;
	m.capacitateCilindrica = cc;
	if (marca != NULL) {
		m.marca = malloc(strlen(marca) + 1);
		strcpy_s(m.marca, strlen(marca) + 1, marca);
	}
	else {
		m.marca = malloc(strlen("N/A") + 1);
		strcpy_s(m.marca, strlen("N/A") + 1, "N/A");
	}
	return m;
}
void dezalocareMasina(struct Masina* masina) {
	if (masina->marca != NULL) {
		free(masina->marca);
		masina->marca = NULL;
	}
}

int main() {
	struct Masina masina1;
	//Dacia
	masina1.marca = (char*)malloc(sizeof(char) * (strlen("Dacia") + 1));//pointer la void returneaza , un pointer generic care poate sa feie la toate datele
	strcpy_s(masina1.marca, strlen(masina1.marca) + 1, "Dacia");
	masina1.an = 2023;
	masina1.capacitateCilindrica = 1.9;
	afisareMasina(&masina1);
	dezalocareMasina(&masina1);
	struct Masina masina2 = initializareMasina("Ford", 2022, 2.49);
	afisareMasina(&masina2);
	dezalocareMasina(&masina2);
	afisareMasina(&masina2);//dencrit pointer acolo unde iti mai ramane ceva la memoria pe care ai sters o trebuie transmis masina prin pointer


	return 0;
}
