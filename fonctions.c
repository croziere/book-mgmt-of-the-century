#include "fonctions.h"

Lecteur * lireLecteur (FILE *fe)
{
	Lecteur *l;
	l = (Lecteur*)malloc(sizeof(Lecteur));
	if (l == NULL)
	{
		printf("Erreur frère, on a un soucis appelle les urgences");
		exit(1);
	}
	fscanf(fe, "%d %s %s %s", &l->num, l->nom, l->prenom, l->adresse);
	return l;
}

Emprunts * lireEmprunt (FILE *fe)
{
	Emprunts *e;
	e = (Emprunts*)malloc(sizeof(Emprunts));
	if (e==NULL)
	{
		printf("Violation d'ordinateur par E.T... Loading... 99%... DONE!");
		exit(1);
	}
	fscanf(fe, "%d %d %d%*c%d%*c%d %d%*c%d%*c%d", &e->numlec, &e->cote, &e->demprunt.jour, &e->demprunt.mois, &e->demprunt.annee, &e->dretour.jour, &e->dretour.mois, &e->dretour.annee);
	return e;
}

Ouvrage * lireOuvrage(FILE *fe)
{
	Ouvrage * o;
	o = (Ouvrage*)malloc(sizeof(Ouvrage));
	if (o == NULL)
	{
		printf("On est pas tout seul, negro");
		exit(1);
	}
	fscanf(fe, "%d %s %s", &o->cote, o->titre, o->categ);
	
	return o;
}

int chargeOuvrages(Ouvrage * t[], int nbmax, char * nom)
{
	FILE *fe;
	int i=0;
	Ouvrage *ouvrage;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return -1;
	ouvrage = lireOuvrage(fe);
	
	while(feof(fe) == 0)
	{
		if (i == nbmax)
			return -2;
		t[i] = ouvrage;
		ouvrage = lireOuvrage(fe);
		i++;
	}
	
	return i;
}

int chargeLecteurs(Lecteur * t[], int nbmax, char * nom)
{
	FILE *fe;
	int i = 0;
	Lecteur *lecteur;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return -1;
	
	lecteur = lireLecteur(fe);
	
	while(feof(fe) == 0)
	{
		if(i == nbmax)
			return -2;
		t[i] = lecteur;
		lecteur = lireLecteur(fe);
		i++;
	}
	
	return i;
}

int chargeEmprunts(Emprunts * t[], int nbmax, char * nom)
{
	FILE *fe;
	int i = 0;
	Emprunts *emprunt;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return -1;
	
	emprunt = lireEmprunt(fe);
	
	while(feof(fe) == 0)
	{
		if(i == nbmax)
			return -2;
		t[i] = emprunt;
		emprunt = lireEmprunt(fe);
		i++;
	}
	
	return i;
}

Liste insertionEnTete(Liste l, Emprunt e)
{
	Maillon *x;
	x=(Maillon*)malloc (sizeof(Maillon));
	x->e=e;
	x->suivant=l;
	return x;
}

int compareDate(Date d1, Date d2)
{
	if (d1.annee > d2.annee)
		return 1;
	else if (d1.annee < d2.anee)
		return -1;
	else
	{ 
		if (d1.mois > d2.mois)
			return 1; 
		else if (d1.mois < d2.mois) 
			return -1;
		else 
		{
			if (d1.jour > d2.jour)
				return -1;
			else if (d1.jour < d2.jour)
				return 1;
			else 
				return 0;
		}
	}
}

void test(void)
{
	Date d1 = {01, 09, 1996}, d2 = { 01,06,1996};
	Ouvrage * touvr[100];
	Lecteur * tlec[100];
	Emprunts * temp[100];
	int nbouvr, nblec, nbemp;
	int i;
	
	nbouvr = chargeOuvrages(touvr, 100, "ouvrage.dat");
	
	for(i = 0; i < nbouvr; i++) {
		printf("%d %s %s\n", touvr[i]->cote, touvr[i]->titre, touvr[i]->categ);
	}
	
	nblec = chargeLecteurs(tlec, 100, "lecteur.dat");
	
	for(i = 0; i < nblec; i++) {
		printf("%d %s %s %s\n", tlec[i]->num, tlec[i]->nom, tlec[i]->prenom, tlec[i]->adresse);
	}
	
	nbemp = chargeEmprunts(temp, 100, "emprunt.dat");
	
	for(i = 0; i < nbemp; i++) {
		printf("%d %d %d/%d/%d %d/%d/%d\n", temp[i]->cote, temp[i]->numlec, temp[i]->demprunt.jour, temp[i]->demprunt.mois, temp[i]->demprunt.annee, temp[i]->dretour.jour, temp[i]->dretour.mois, temp[i]->dretour.annee);
	}
	printf("%d", compareDate(d1,d2));
}


