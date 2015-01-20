#include "global.h"

/**
 * Alloue un lecteur et lit les données depuis un fichier
*/
Lecteur * lireLecteur (FILE *fe, int *nbemp)
{
	Lecteur *l;
	l = (Lecteur*)malloc(sizeof(Lecteur));
	if (l == NULL)
	{
		printf("Erreur d'allocation.\n");
		exit(1);
	}
	fscanf(fe, "%d%*c", &l->num);
	
	fgets(l->prenom, TAILLECH, fe);
	l->prenom[strlen(l->prenom) - 1] = '\0';
	fgets(l->nom, TAILLECH, fe);
	l->nom[strlen(l->nom) - 1] = '\0';
	fgets(l->adresse, TLONGCH, fe);	
	l->adresse[strlen(l->adresse) - 1] = '\0';
	
	fscanf(fe, "%d%*c", nbemp);
	l->emps = NULL;
	return l;
}

/**
 * Charge un tableau de lecteurs avec leur liste d'emprunts en cours
*/
int chargeLecteurs(Lecteur ** t, int nbmax, char * nom)
{
	FILE *fe;
	int i = 0, nbemp, j;
	Lecteur *lecteur;
	Emprunts *emp;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return 0; //Impossible d'ouvrir le fichier : tableau vide
	
	lecteur = lireLecteur(fe, &nbemp);
	
	while(feof(fe) == 0)
	{
		if(i == nbmax)
			return -2;
		if(nbemp > 0)
		{
			for(j = 0; j < nbemp; j++) //On créé la liste des emprunts en cours
			{
				emp = lireEnCours(fe);
				emp->numlec = lecteur->num;
				lecteur->emps = insertionEmprunt(lecteur->emps, emp);
			}
		}
		*(t+i) = lecteur;
		lecteur = lireLecteur(fe, &nbemp);
		i++;
	}
	fclose(fe);
	return i;
}


/**
 * Recherche (stricte) un lecteur par son numéro et retourne son index
*/
int rechercheLecteur(int numrech, Lecteur *t[], int nb) //tableau pas trié, peut etre quil faut le trier
{
	int i; 
	for (i=0; i<nb; i++)
	{	
		if ( numrech == t[i]->num) 
			return i;
	}
	return -1;
}


/**
 * Affiche (printf) un lecteur l
*/
void afficherUnLecteur(Lecteur l)
{
	printf("%d - %s %s - %s\n", l.num, l.prenom, l.nom, l.adresse);
}

/**
 * Affiche un tableau de lecteurs
 */
void afficherLecteurs(Lecteur **l, int nblec)
{
	int i;
	for(i = 0; i < nblec; i++)
	{
		afficherUnLecteur(*l[i]);
	}
}