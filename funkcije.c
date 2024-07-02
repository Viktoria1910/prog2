#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"


void dodajClana(FILE* file) {
	CLAN const* clan;
	clan = malloc(MAX_NAME_LENGTH * sizeof(CLAN));

	printf("Unesi podatke clana:\n");
	printf("Ime: ");
	scanf("%s", clan->ime);
	printf("Prezime: ");
	scanf("%s", clan->prezime);


	int result = 0;
	int id;
	int duplicateID = 0; // Koristi se da se zna ako je duplikat naden

	do {
		duplicateID = 0;

		printf("ID: ");
		result = scanf("%d", &clan->id);
		if (result != 1) {
			printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
			while (fgetc(stdin) != '\n');
			continue;
		}

		// gleda dali ima isti ID
		fseek(file, 0, SEEK_SET);
		while (fscanf(file, "%*s %*s %d %*s", &id) == 1) {
			if (id == clan->id) {
				printf("Clan s unesenim ID-om vec postoji. Odaberi drugi ID.\n");
				duplicateID = 1;
				break;
			}
		}

	} while (duplicateID);

	printf("Jel platila/platio clanarinu? (Da/Ne)");
	scanf("%2s", clan->clanarina);

	fprintf(file, "%s %s %d %s\n", clan->ime, clan->prezime, clan->id, clan->clanarina);
	printf("Clan je uspjesno dodan.\n");
	fclose(file);
	file = fopen("kud.txt", "a+");
	if (file == NULL) {
		perror("Greska pri otvaranju kud.txt");
	}
	free(clan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Brisanje Clana

void izbrisiClana(FILE* file, const int id) {
	FILE* tf = fopen("temp.txt", "w");
	if (tf == NULL) {
		perror("Greska pri otvaranju temp.txt");
		return;
	}

	CLAN* clan;
	clan = malloc(MAX_NAME_LENGTH * sizeof(CLAN));

	int pronaden = 0;

	while (fscanf(file, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, clan->clanarina) != EOF) {
		if (clan->id == id) {
			pronaden = 1;
			continue;
		}

		fprintf(tf, "%s %s %d %s\n", clan->ime, clan->prezime, clan->id, clan->clanarina);
	}

	fclose(file);
	fclose(tf);

	if (pronaden) {
		if (remove("kud.txt") != 0) {
			perror("Greska pri brisanju kud.txt"); //19
			return;
		}

		if (rename("temp.txt", "kud.txt") != 0) {
			perror("Greska pri preimenovanju temp.txt");
			return;
		}

		printf("Clan je izbrisan.\n");
	}
	else {
		remove("temp.txt"); //18
		printf("Clan nije pronaden.\n");
	}

	file = fopen("kud.txt", "a+");
	if (file == NULL) {
		perror("Greska pri otvaranju kud.txt");
	}

	free(clan);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ispis Clanova

void ispisClanova(const FILE* file) { //9, 10
	CLAN const* clan;
	clan = malloc(MAX_NAME_LENGTH * sizeof(CLAN));

	printf("Clanovi udruge:\n");
	while (fscanf(file, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, &clan->clanarina) != EOF) {
		printf("Ime i prezime: %s %s\n", clan->ime, clan->prezime);
		printf("ID: %d\n", clan->id);
		printf("Placena clananina?: %s\n-------------------------------------\n", clan->clanarina);
	}

	fclose(file);
	file = fopen("kud.txt", "a+"); //16
	if (file == NULL) {
		perror("Greska pri otvaranju kud.txt");
	}

	free(clan);
}
//11 const, 12
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sortiranje po imenu


int usporedbaClanova(const void* a, const void* b) {
	const CLAN* clanA = (const CLAN*)a;
	const CLAN* clanB = (const CLAN*)b;
	return strcmp(clanA->ime, clanB->ime);
}

void sortClanova(CLAN* clanovi, int numClanova) {
	qsort(clanovi, numClanova, sizeof(CLAN), usporedbaClanova);//20
}

void ispisSortiranihClanovaPoImenu(FILE* file) {
	CLAN* clanovi;
	int numClanova = 0;

	// Broji koliko ima clanova
	while (fscanf(file, "%*s %*s %*d %*s") == 0) {
		numClanova++;
	}

	// Alocira memoriju
	clanovi = malloc(numClanova * sizeof(CLAN));
	if (clanovi == NULL) {
		perror("Greska pri alokaciji memorije");
		return;
	}

	fseek(file, 0, SEEK_SET);

	// Cita clanove iz filea u polje
	int i;
	for (i = 0; i < numClanova; i++) {
		//clanovi[i] = malloc(numClanova * sizeof(CLAN));
		fscanf(file, "%s %s %d %s", clanovi[i].ime, clanovi[i].prezime, &clanovi[i].id, clanovi[i].clanarina);
	}

	// Poziva funkciju za sortiranje
	sortClanova(clanovi, numClanova);

	// Ispisuje Sortirano
	printf("Sortirani clanovi KUD-a po imenu:\n");
	for (i = 0; i < numClanova; i++) {
		printf("Ime i prezime: %s %s\n", clanovi[i].ime, clanovi[i].prezime);
		printf("ID: %d\n\n", clanovi[i].id);
		printf("Clanarina: %s\n-----------------------------------------\n", clanovi[i].clanarina);
	}

	// freea memoriju
	/*for (i = 0; i < numClanova; i++) {
		free(clanovi[i].ime);
		free(clanovi[i].prezime);
	}*/
	free(clanovi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sortiranje po prezimenu

int usporedbaClanovaPoPrezimenu(const void* a, const void* b) {
	const CLAN* clanA = (const CLAN*)a;
	const CLAN* clanB = (const CLAN*)b;
	return strcmp(clanA->prezime, clanB->prezime);
}

void sortClanovaPoPrezimenu(CLAN* clanovi, int numClanova) {
	qsort(clanovi, numClanova, sizeof(CLAN), usporedbaClanovaPoPrezimenu);
}

void ispisSortiranihClanovaPoPrezimenu(FILE* file) {
	CLAN* clanovi;
	int numClanova = 0;

	// Broji koliko ima clanova
	while (fscanf(file, "%*s %*s %*d %*s") == 0) {
		numClanova++;
	}

	// Alocira memoriju
	clanovi = malloc(numClanova * sizeof(CLAN));
	if (clanovi == NULL) {
		perror("Greska pri alokaciji memorije");
		return;
	}

	fseek(file, 0, SEEK_SET);

	// Cita clanove iz filea u polje
	int i;
	for (i = 0; i < numClanova; i++) {
		fscanf(file, "%s %s %d %s", clanovi[i].ime, clanovi[i].prezime, &clanovi[i].id, clanovi[i].clanarina);
	}

	// Poziva funkciju za sortiranje
	sortClanovaPoPrezimenu(clanovi, numClanova);

	// Ispisuje Sortirano
	printf("Sortirani clanovi KUD-a po prezimenu:\n");
	for (i = 0; i < numClanova; i++) {
		printf("Ime: %s %s\n", clanovi[i].ime, clanovi[i].prezime);
		printf("ID: %d\n", clanovi[i].id);
		printf("Placena clanarina?: %s\n---------------------------------------------\n", clanovi[i].clanarina);
	}

	// freea memoriju
	/*for (i = 0; i < numClanova; i++) {
		free(clanovi[i].ime);
		free(clanovi[i].prezime);
	}*/
	free(clanovi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//pretrazivanje
void pretrazivanje(const FILE* file, const int id) {

	CLAN const* clan;
	clan = malloc(MAX_NAME_LENGTH * sizeof(CLAN));



	int pronaden = 0;
	while (fscanf(file, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, clan->clanarina) != EOF) {
		if (clan->id == id) {
			pronaden = 1;
			continue;
		}
	}
	if (pronaden == 1) {
		printf("Clan je pronaden\n");
	
	}
	else {
		printf("Clan nije pronaden\n");
	}

	fclose(file);
	file = fopen("kud.txt", "a+");
	if (file == NULL) {
		perror("Greska pri otvaranju kud.txt");
	}
	free(clan);
}

// Funkcija za azuriranje clana
void azurirajClana(FILE* file, const int id) {
	FILE* tf = fopen("temp.txt", "w");
	if (tf == NULL) {
		perror("Greska pri otvaranju temp.txt");
		return;
	}

	CLAN* clan = malloc(sizeof(CLAN));
	if (clan == NULL) {
		perror("Greska pri alokaciji memorije");
		fclose(tf);
		return;
	}

	int pronaden = 0;

	// Postavljanje pokazivaèa na poèetak datoteke
	fseek(file, 0, SEEK_SET);

	while (fscanf(file, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, clan->clanarina) != EOF) {
		if (clan->id == id) {
			pronaden = 1;
			printf("Clan pronaden. Unesi nove podatke clana:\n");
			printf("Novo ime: ");
			scanf("%s", clan->ime);
			printf("Novo prezime: ");
			scanf("%s", clan->prezime);
			printf("Jel platila/platio clanarinu? (Da/Ne): ");
			scanf("%s", clan->clanarina);
		}
		fprintf(tf, "%s %s %d %s\n", clan->ime, clan->prezime, clan->id, clan->clanarina);
	}

	if (ferror(file)) {
		perror("Greska pri citanju iz datoteke");
	}
	fclose(file);
	fclose(tf);

	if (pronaden) {
		if (remove("kud.txt") != 0) {
			perror("Greska pri brisanju kud.txt");
			free(clan);
			return;
		}

		if (rename("temp.txt", "kud.txt") != 0) {
			perror("Greska pri preimenovanju temp.txt");
			free(clan);
			return;
		}
		printf("Clan je azuriran.\n");
	}
	else {
		remove("temp.txt");
		printf("Clan nije pronaden.\n");
	}

	free(clan);
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ispis clanarine

//void ispisClanarine(const char* file) {
//	FILE* file = fopen("kud.txt", "r");
//	if (file == NULL) {
//		perror("Greška pri otvaranju datoteke!");
//		return;
//	}
//
//	CLAN* clan = malloc(sizeof(CLAN));
//	if (clan == NULL) {
//		perror("Greška pri alokaciji memorije!");
//		fclose(file);
//		return;
//	}
//
//	char line[MAX_NAME_LENGTH * 3];
//
//	printf("Clanovi koji su platili clanarinu:\n");
//	while (fgets(line, sizeof(line), file)) {
//		if (sscanf(line, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, clan->clanarina) == 4) {
//			if (strcmp(clan->clanarina, "Da") == 0) {
//				printf("%s %s (ID:%d)\n", clan->ime, clan->prezime, clan->id);
//			}
//		}
//	}
//
//	rewind(file);  // Vraæanje datoteke na poèetak
//
//	printf("\nClanovi koji nisu platili clanarinu:\n");
//	while (fgets(line, sizeof(line), file)) {
//		if (sscanf(line, "%s %s %d %s", clan->ime, clan->prezime, &clan->id, clan->clanarina) == 4) {
//			if (strcmp(clan->clanarina, "Ne") == 0) {
//				printf("%s %s (ID:%d)\n", clan->ime, clan->prezime, clan->id);
//			}
//		}
//	}
//
//	free(clan);
//	fclose(file);
//}
//		

