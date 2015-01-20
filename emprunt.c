#include "global.h"

/**
 * Alloue un emprunt terminé et lit les données depuis un fichier
*/
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


/**
 * Alloue un emprunt en cours depuis le fichier lecteurs
*/
Emprunts * lireEnCours(FILE *fe)
{
	Emprunts *e;
	e = (Emprunts*)malloc(sizeof(Emprunts));
	if(e == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	fscanf(fe, "%d %d%*c%d%*c%d", &e->cote, &e->demprunt.jour, &e->demprunt.mois, &e->demprunt.annee);
	return e;
}

/**
 * Charge un tableau des emprunts terminés
*/
int chargeEmprunts (Emprunts * t[], int nbmax, char *nom)
{
	FILE *fe;
	Emprunts *emprunt;
	int i;
	
	fe = fopen(nom, "r");
	if(fe == NULL)
		return 0;

	emprunt = lireEmprunt(fe);

	while(feof(fe) == 0)
	{
		if(i == nbmax)
			return -2;

		t[i] = emprunt;
		emprunt = lireEmprunt(fe);
		i++;
	}
	fclose(fe);
	return i;
}

/**
 * Insert un emprunt en tête d'une liste l
*/
Liste insertionEnTete(Liste l, Emprunts *e)
{
	Maillon *x;
	x=(Maillon *)malloc(sizeof(Maillon));
	x->e = e;
	x->suivant = l;
	return x;
}


/**
 * Ajoute un emprunt au bon endroit dans la liste
*/
Liste insertionEmprunt (Liste l, Emprunts *e) 
{
	if (l == NULL) 
		return insertionEnTete(l, e); 

	if (compareDate(l->e->demprunt, e->demprunt) > 0)
		return insertionEnTete(l, e);

	l->suivant = insertionEmprunt(l->suivant, e);
	return l;
}

/**
 * Supprime la tête de liste de l
*/
Liste supprimerEnTete(Liste l)
{
	Maillon *temp;
	temp = l->suivant;
	free(l);
	return temp;
}

/**
 * Supprime l'emprunt de l'ouvrage o si trouvé dans l
*/
Liste supprimerEmprunt(Liste l, Ouvrage o)
{
	if(l == NULL)
		return NULL;
	if(l->e->cote == o.cote)
		return supprimerEnTete(l);
	l->suivant = supprimerEmprunt(l->suivant, o);
	return l;
}

/**
* Ajoute un emprunt terminé dans le tableau des emprunts
*/
int insertionHistorique(Emprunts** t, Emprunts *e, int nbemp)
{
	t[nbemp] = e;
	return nbemp + 1;
}


/**
 * Cherche dans une liste si un ouvrage est emprunté
*/
Booleen coteEstEmpruntee(Liste l, int cote)
{
	if(l == NULL)
		return FAUX;
	if(l->e->cote == cote)
	{
		return VRAI;
	}

	return coteEstEmpruntee(l->suivant, cote);
}

/**
 * Retourne VRAI si un ouvrage est en cours d'emprunt
*/
Booleen estEmprunte(Ouvrage o, Lecteur** l, int nblec)
{
	int i;
	for(i = 0; i < nblec; i++)
	{
		if(coteEstEmpruntee(l[i]->emps, o.cote))
		{
			return VRAI;
		}
	}

	return FAUX;
}

/**
* Retourne l'emprunt d'une cote dans une liste
*/
Emprunts * chercherEmprunt(Liste l, int cote)
{
	if(l == NULL)
		return NULL;

	if(l->e->cote == cote)
		return l->e;

	return chercherEmprunt(l->suivant, cote);
}

/**
* Retourne l'index du lecteur ayant emprunté o
*/
int chercherEmprunteur(Lecteur** l, int nblec, Ouvrage o)
{
	int i;
	for(i = 0; i < nblec; i++)
	{
		if(coteEstEmpruntee(l[i]->emps, o.cote))
		{
			return i;
		}
	}

	return -1;
}

/**
* Compte les emprunts de la liste l
*/
int compterEmprunts(Liste l)
{
	if(l == NULL) return 0;

	return 1 + compterEmprunts(l->suivant);
}

/**
* Affiche un emprunt (b = VRAI affiche la date de retour)
*/
void afficherUnEmprunt(Emprunts e, Booleen b, Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec)
{
	int poslec, posouvr;

	if(b == VRAI)
	{
		poslec = rechercheLecteur(e.numlec, tlec, nblec);
		if(poslec < 0)
			printf("(%d) N/A a emprunté ", e.numlec);
		else
			printf("(%d) %s %s a emprunté ", e.numlec, tlec[poslec]->prenom, tlec[poslec]->nom);
	}
	posouvr = rechercheOuvrage(e.cote, touvr, nbouvr);

	if(posouvr < 0)
		printf("(%d) N/A ", e.cote);
	else
		printf("(%d) %s ", e.cote, touvr[posouvr]->titre);
	if(b)
		printf("du ");
	else
		printf("emprunté le ");
	printDate(e.demprunt, 0);

	if(b == VRAI)
	{
		printf(" au ");
		printDate(e.dretour, 0);
	}

	printf("\n");
}

/**
* Affiche la liste des emprunts terminés
*/
void afficherEmprunts(Emprunts** t, int nbemp, Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec)
{
	int i;
	for (i = 0; i < nbemp; i++)
	{
		afficherUnEmprunt(*t[i], VRAI, touvr, nbouvr, tlec, nblec);
	}
}

/**
* Affiche les emprunts en cours dans l
*/
void afficherListeEmprunt(Liste l, Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec)
{
	if(l == NULL) return;
	printf("\t");
	afficherUnEmprunt(*l->e, FAUX, touvr, nbouvr, tlec, nblec);
	afficherListeEmprunt(l->suivant, touvr, nbouvr, tlec, nblec);
}

/**
* Affiche tous les emprunts en cours
*/
void afficherEmpruntsEnCours(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr)
{
	int i;
	for (i = 0; i < nblec; i++)
	{
		if(compterEmprunts(tlec[i]->emps) > 0) {
			afficherUnLecteur(*tlec[i]);
			afficherListeEmprunt(tlec[i]->emps, touvr, nbouvr, tlec, nblec);
			printf("\n");
		}
	}
}

/**
* Sauvegarde les emprunts d'une liste au format binaire
*/
void sauvegarderEnmpruntsEnCours(Liste l, FILE *fe)
{
	if(l == NULL)
		return;
	fwrite(l->e, sizeof(Emprunts), 1, fe);

	sauvegarderEnmpruntsEnCours(l->suivant, fe);
}

/**
* Libère la mémoire d'une liste d'emprunts
*/
void viderListe(Liste l)
{
	if(l == NULL) return;

	free(l->e);
	viderListe(l->suivant);
	free(l);
}