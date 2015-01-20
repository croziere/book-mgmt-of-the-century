#include "base.h"
#include "ouvrage.h"
#include "lecteur.h"
#include "emprunt.h"
#include "page.h"

int compareDate(Date d1, Date d2);
void printDate(Date d, int retour);
void viderStdin(void);
void purger(char * c);
void saisirUnEntier(int *i);
void chargerBinaire(Ouvrage** touvr, int *nbouvr, Lecteur** tlec, int *nblec, Emprunts** temp, int *nbemp);
void initialiser(Ouvrage **touvr, Lecteur **tlec, Emprunts **temp, int *nbouvr, int *nblec, int *nbemp);
void sauvegarder(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr, Emprunts** temp, int nbemp);
void vider(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr, Emprunts** temp, int nbemp);
void welcomeChezUs (void);
void menu (void);
void globale (void);