#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAILLECH 50
#define TLONGCH 100
#define TMAXTAB 100

typedef struct {
	int jour;
	int mois;
	int annee;
}Date;

typedef enum { FAUX, VRAI }Booleen;

typedef struct {
	int numlec;
	int cote;
	Date demprunt;
	Date dretour;
}Emprunts;

typedef struct maillon {
	Emprunts *e;
	struct maillon *suivant;
}Maillon, *Liste;

typedef struct {
	int cote;
	char titre[TLONGCH];
	char categ[TLONGCH];
}Ouvrage;

typedef struct {
	int num;
	char nom[TAILLECH];
	char prenom[TAILLECH];
	char adresse[TLONGCH];
	Liste emps;
}Lecteur;