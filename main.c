#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "funkcije.c"
#include "header.h"



int main(void) {
	FILE* file = fopen("kud.txt", "a+");
	if (file == NULL) {
		perror("Greska pri otvaranju datoteke");
		return 1;
	}

	int odabir, id;
	char ch[2];
	CLAN clan;

	do {
		printf("Izbornik:\n"); 
		printf("1. Dodaj clanove\n");
		printf("2. Izbrisi clanove\n");
		printf("3. Ispisi listu clanova\n");
		printf("4. Sortiraj po imenu\n");
		printf("5. Sortiraj po prezimenu\n");
		printf("6. Pretrazivanje\n");
		printf("7. Azuriraj clana\n");
		printf("8. Izlaz\n");
		printf("Tvoj odabir: ");

		static int result = 0;
		static int duzina; 
		do
		{
			scanf("%s", ch);
			duzina = strlen(ch);
			if (duzina > 1)
			{
				printf("Krivi unos. Molimo unesute ponovo.\n");
			}
		} while (duzina > 1);
		printf("\n");



		switch (ch[0]) {
		case '1':
			dodajClana(file);
			break;
		case '2':
			printf("Upisi ID clana kojeg zelite izbrisati: ");

			result = 0;
			do {
				result = scanf("%d", &id);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				if (result != 1) {
					printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
					while (fgetc(stdin) != '\n');
				}
			} while (result != 1);

			izbrisiClana(file, id);
			break;
		case '3':
			fseek(file, 0, SEEK_SET); 
			ispisClanova(file);
			break;

		case '4':
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoImenu(file);
			break;
		case '5':
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoPrezimenu(file);
			break;
		case '6':
			printf("Unesite ID clana kojeg pretrazujete\n");
			result = 0;
			do {
				result = scanf("%d", &id);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				if (result != 1) {
					printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
					while (fgetc(stdin) != '\n');
				}
			} while (result != 1);
			fseek(file, 0, SEEK_SET);
			pretrazivanje(file, id);
			break;

		case '7':
			printf("Unesite ID clana kojeg zelite azurirati\n");
			result = 0;
			do {
				result = scanf("%d", &id);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				if (result != 1) {
					printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
					while (fgetc(stdin) != '\n');
				}
			} while (result != 1);
			fseek(file, 0, SEEK_SET);
			azurirajClana(file, id);
			break;
			
		case '8':
			printf("Izlazak iz programa.\n");
			break;
		default:
			printf("Pogresan unos. Molimo unesite ponovno.\n");
			while (fgetc(stdin) != '\n');
			break;
		}
		printf("\n");

	} while (ch[0] != '8');
	fclose(file);

	return 0;
}