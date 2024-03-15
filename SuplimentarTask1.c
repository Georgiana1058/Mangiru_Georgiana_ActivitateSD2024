#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Bursa {
	char* nume;
	int an_studiu;
	char* specializare;
	float medie;
	char* tip_bursa;

};
void afisare(const struct Bursa* bursa) {
	if (bursa->nume != NULL && bursa->specializare != NULL && bursa->tip_bursa != NULL) {
		printf("Nume:%s\n", bursa->nume);
		printf("Specializare:%s\n", bursa->specializare);
		printf("Tip bursa:%s\n", bursa->tip_bursa);
	}

	printf("An studiu:%i\n", bursa->an_studiu);
	printf("Medie:%.2f\n", bursa->medie);
}
struct Bursa initializare(const char* nume, int an_studiu, const char* specializare, float medie, const char* tip_bursa) {
	struct Bursa bursa;
	bursa.an_studiu = an_studiu;
	bursa.medie = medie;
	if (nume != NULL) {
		bursa.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(bursa.nume, nume);

	}
	else {
		bursa.nume = malloc(strlen("N/A") + 1);
		strcpy(bursa.nume, "N/A");
	}
	if (specializare != NULL) {
		bursa.specializare = malloc(sizeof(char) * (strlen(specializare) + 1));
		strcpy(bursa.specializare, specializare);

	}
	else {
		bursa.specializare = malloc(strlen("N/A") + 1);
		strcpy(bursa.specializare, "N/A");
	}
	if (tip_bursa != NULL) {
		bursa.tip_bursa = malloc(sizeof(char) * (strlen(tip_bursa) + 1));
		strcpy(bursa.tip_bursa, tip_bursa);

	}
	else {
		bursa.tip_bursa = malloc(strlen("N/A") + 1);
		strcpy(bursa.tip_bursa, "N/A");
	}
	return bursa;

}
void setmedie(struct Bursa* bursa, float medie) {
	bursa->medie = medie;
}
void dezalocare(struct Bursa* bursa) {
	if (bursa->nume != NULL) {
		free(bursa->nume);
		bursa->nume = NULL;
	}
	if (bursa->specializare != NULL) {
		free(bursa->specializare);
		bursa->specializare = NULL;
	}
	if (bursa->tip_bursa != NULL) {
		free(bursa->tip_bursa);
		bursa->tip_bursa = NULL;
	}
}
void bursaDePerformanta(struct Bursa* bursa) {
	if ((bursa->medie) >= 9.50) {
		printf("Studentul se incadreaza la Bursa de Performanta: =)\n");
		free(bursa->tip_bursa);
		bursa->tip_bursa = malloc(strlen("Bursa de Performanta") + 1);
		strcpy(bursa->tip_bursa, "Bursa de Performanta");
		afisare(bursa);
	}
	else {
		printf("Studentul nu se incadreaza la Bursa de Performanta:  = (\n");
		afisare(bursa);

	}
}
void main() {
	struct Bursa bursa1;
	bursa1.an_studiu = 2;
	bursa1.medie = 8.18;
	bursa1.nume = (char*)malloc(sizeof(char) * (strlen("Mangiru Georgiana") + 1));
	strcpy(bursa1.nume, "Mangiru Georgiana");
	bursa1.specializare = (char*)malloc(sizeof(char) * (strlen("Informatica Economica") + 1));
	strcpy(bursa1.specializare, "Informatica Economica");
	bursa1.tip_bursa = (char*)malloc(sizeof(char) * (strlen("Bursa de merit") + 1));
	strcpy(bursa1.tip_bursa, "Bursa de merit");
	afisare(&bursa1);
	printf("\n");
	struct Bursa bursa2 = initializare("Matei Bianca", 2, "Informatica Economica", 9.50, "Bursa de Merit");
	afisare(&bursa2);
	printf("\n");
	printf("Am schimbat media:\n"); setmedie(&bursa1, 9.09);
	afisare(&bursa1);
	printf("\n");
	bursaDePerformanta(&bursa1);
	printf("\n");
	bursaDePerformanta(&bursa2);
	dezalocare(&bursa2);
	dezalocare(&bursa1);

}