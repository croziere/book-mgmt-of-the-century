#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLECH 50
#define TLONGCH 100

typedef struct {
	int numlec;
	int cote;
	Date demprunt;
	Date dretour;
}Emprunts;

typedef struct maillon {
	Emprunts e;
	struct maillon *suivant;
}Maillon, *Liste;

typedef struct {
	int jour;
	int mois;
	int annee;
}Date;

typedef struct {
	int cote;
	char titre[TAILLECH];
	char categ[TAILLECH];
}Ouvrage;

typedef struct {
	int num;
	char nom[TAILLECH];
	char prenom[TAILLECH];
	char adresse[TLONGCH];
	Emprunts ** emps;
}Lecteur;
