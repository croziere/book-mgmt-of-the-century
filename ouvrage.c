#include "global.h"

/**
 * Alloue un ouvrage depuis le fichier ouvrages
*/
Ouvrage * lireOuvrage(FILE *fe)
{
	Ouvrage * o;
	o = (Ouvrage*)malloc(sizeof(Ouvrage));
	if (o == NULL)
	{
		printf("Erreur d'allocation\n");
		exit(1);
	}
	fscanf(fe, "%d%*c", &o->cote);
	fgets(o->titre, TLONGCH, fe);
	o->titre[strlen(o->titre) - 1] = '\0';
	fgets(o->categ, TLONGCH, fe);
	o->categ[strlen(o->categ) - 1] = '\0';
	return o;
}


/**
 * Charge un tableau d'ouvrages depuis un fichier texte
*/
int chargeOuvrages(Ouvrage * t[], int nbmax, char * nom)
{
	FILE *fe;
	int i=0;
	Ouvrage *ouvrage;
	
	fe = fopen(nom, "r");
	if(fe == NULL) //Le fichier n'existe pas ou impossible à lire
		return 0;
	ouvrage = lireOuvrage(fe);
	
	while(feof(fe) == 0)
	{
		if (i == nbmax)
			return -2;
		t[i] = ouvrage;
		ouvrage = lireOuvrage(fe);
		i++;
	}
	fclose(fe);
	return i;
}

/**
 * Recherche (stricte) un ouvrage par sa cote, retourne son index dans le tableau
*/
int rechercheOuvrage(int cote, Ouvrage** t, int nb)
{
	int i;
	for (i = 0; i < nb; i++)
	{
		if (cote == t[i]->cote)
			return i;
	}
	return -1;
}

/**
 * Affiche (printf) un ouvrage et sa disponibilité
*/
void afficherUnOuvrage(Ouvrage o, Lecteur **tabl, int nblec)
{
	if(estEmprunte(o, tabl, nblec) == VRAI)
		printf("%d - %s\t\t - %s\t - *EMPRUNTE*\n", o.cote, o.titre, o.categ);
	else
		printf("%d - %s\t\t - %s\t - DISPONIBLE\n", o.cote, o.titre, o.categ);
}

/**
 * Affiche un tableau d'ouvrages
*/
void afficherOuvrages(Ouvrage** t, int nbouvr, Lecteur **tabl, int nblec)
{
	int i;
	for(i = 0; i < nbouvr; i++)
	{
		afficherUnOuvrage(*t[i], tabl, nblec);
	}
}