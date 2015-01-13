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
	l->emps = NULL;
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

int chargeEmprunts (Lecteur * t[], int nb, char * nom)
{
	FILE *fe;
	int pos;
	Emprunts *emprunt;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return -1;
	printf("Lecture des emprunts\n");
	emprunt = lireEmprunt(fe);
	
/*#magie*/ 

	while(feof(fe) == 0)
	{
		printf("Boucle\n");
		pos = rechercheLecteur(emprunt->numlec, t, nb);
		printf("%d\n", pos);
		if ( pos < 0) 
			printf("l'utilisateur %d n'existe pas!", emprunt->numlec);
		else 
			t[pos]->emps = insertionEmprunt(t[pos]->emps, emprunt);

		printf("%d\n", t[pos]->emps->e->cote);

		emprunt = lireEmprunt(fe);
	}
	
	return 0;
}

int rechercheLecteur (int numrech, Lecteur *t[], int nb) //tableau pas trié, peut etre quil faut le trier
{
	int i; 
	for (i=0; i<nb; i++)
	{	
		if ( numrech == t[i]->num) 
			return i;
	}
	return -1;
}



Liste insertionEnTete(Liste l, Emprunts *e)
{
	Maillon *x;
	x=(Maillon *)malloc(sizeof(Maillon));
	x->e = e;
	printf("%d\n", e->cote);
	x->suivant = l;
	return x;
}

int compareDate(Date d1, Date d2)
{
	if (d1.annee > d2.annee)
		return 1;
	else if (d1.annee < d2.annee)
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

Liste insertionEmprunt (Liste l, Emprunts *e) 
{
	printf("Insertion\n");
	if (l == NULL) 
		return insertionEnTete(l, e); 

	if (compareDate(l->e->demprunt, e->demprunt) > 0)
		return insertionEnTete(l, e);

	l->suivant = insertionEmprunt(l->suivant, e);
	return l;
}





void test(void)
{
	Date d1 = {1, 9, 1996}, d2 = {1, 6, 1996};
	Ouvrage * touvr[100];
	Lecteur * tlec[100];
	Emprunts * temp[100];
	int nbouvr, nblec, nbemp;
	int i, pos;
	
	nbouvr = chargeOuvrages(touvr, 100, "ouvrage.dat");
	
	for(i = 0; i < nbouvr; i++) {
		printf("%d %s %s\n", touvr[i]->cote, touvr[i]->titre, touvr[i]->categ);
	}
	
	nblec = chargeLecteurs(tlec, 100, "lecteur.dat");
	printf("%d", nblec);

	for(i = 0; i < nblec; i++) {
		
		printf("%d %s %s %s\n", tlec[i]->num, tlec[i]->nom, tlec[i]->prenom, tlec[i]->adresse);
		printf("%d\n", i);
	}

	printf("Fonction charger emprunts\n");

	chargeEmprunts(tlec, nblec, "emprunt.dat");
	
	//printf("%d\n", tlec[0]->emps->e->cote);

	//printf("%d\n", compareDate(d1,d2));
}


