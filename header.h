#pragma once

#define MAX_NAME_LENGTH 50 

typedef struct clan { 
	char ime[MAX_NAME_LENGTH];     
	char prezime[MAX_NAME_LENGTH];
	int id;
	char clanarina[3];
} CLAN;

void dodajClana(FILE* file);
void izbrisiClana(FILE* file, const int id);
void ispisClanova(const FILE* file);
int usporedbaClanova(const void* a, const void* b);
void sortClanova(CLAN* clanovi, int numClanova);
void ispisSortiranihClanovaPoImenu(FILE* file);
int usporedbaClanovaPoPrezimenu(const void* a, const void* b);
void sortClanovaPoPrezimenu(CLAN* clanovi, int numClanova);
void ispisSortiranihClanovaPoPrezimenu(FILE* file);
void pretrazivanje(const FILE* file, const int id);
void azurirajClana(FILE* file, const int id);
//void ispisClanarine(FILE* file);
