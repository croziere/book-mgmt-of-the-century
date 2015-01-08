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


Lecteur * lireLecteur (FILE *fe);
Emprunts * lireEmprunt (FILE *fe);
Ouvrage * lireOuvrage(FILE *fe);
int chargeOuvrages(Ouvrage * t[], int nbmax, char * nom);
int chargeLecteurs(Lecteur * t[], int nbmax, char * nom);
int chargeEmprunts(Emprunts * t[], int nbmax, char * nom);
Liste insertionEnTete(Liste l, Emprunts e);
int compareDate(Date d1, Date d2);

void test(void);