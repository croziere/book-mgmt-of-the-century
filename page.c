#include "global.h"

/**
 * Affiche la page : Lecteurs
*/
void pageLecteurs(Lecteur** l, int nblec)
{
	system("clear");
	printf("---------- Lecteurs ----------\n");
	afficherLecteurs(l, nblec);
	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

/**
 * Affiche la page : Ouvrages
*/
void pageOuvrages(Ouvrage** o, int nbouvr, Lecteur **tlec, int nblec)
{
	system("clear");
	printf("---------- Ouvrages ----------\n");
	afficherOuvrages(o, nbouvr, tlec, nblec);
	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageModifierAdresse(Lecteur** l, int nblec) /*nblec : nb total de lecteurs*/
{
	int numpers, pos;
	system("clear");
	printf("---------- Modification d'une adresse ----------\n");
	afficherLecteurs(l, nblec);
	printf("Numero du lecteur (-1 retour) : ");
	saisirUnEntier(&numpers);
	if(numpers < 0)
		return;
	pos = rechercheLecteur(numpers, l, nblec);
	
	while(pos < 0)
	{
		printf("Erreur, le lecteur n'existe pas\n");
		printf("Retaper un numero de lecteur (-1 retour) : ");
		saisirUnEntier(&numpers);
		if(numpers < 0)
			return;

		pos = rechercheLecteur(numpers, l, nblec);
	}

	printf("Lecteur a modifier :\n");
	afficherUnLecteur(*l[pos]);

	printf("Entrez la nouvelle adresse : ");
	fgets(l[pos]->adresse, TLONGCH, stdin);

	purger(l[pos]->adresse);

	printf("\nModification effectuee :\n");
	afficherUnLecteur(*l[pos]);

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageInscriptionLecteur(Lecteur** tabl, int *nblec)
{
	int numlec;
	char *prelec, *nomlec, *adrlec;
	Lecteur *l;

	prelec = (char *)malloc(sizeof(char)*TAILLECH);
	nomlec = (char *)malloc(sizeof(char)*TAILLECH);
	adrlec = (char *)malloc(sizeof(char)*TLONGCH);
	l = (Lecteur *)malloc(sizeof(Lecteur));

	system("clear");
	printf("---------- Inscription d'un lecteur ----------\n");
	printf("Numero du lecteur (-1 retour) : ");
	saisirUnEntier(&numlec);
	if(numlec < 0)
	{
		free(prelec);
		free(nomlec);
		free(adrlec);
		free(l);
		return;
	}

	while(rechercheLecteur(numlec, tabl, *nblec) >= 0)
	{
		printf("Le code %d est déjà utilisé, merci de choisir à nouveau (-1 retour) : ", numlec);
		saisirUnEntier(&numlec);
		if(numlec < 0)
		{
			free(prelec);
			free(nomlec);
			free(adrlec);
			free(l);
			return;
		}
	}

	printf("Prenom : ");
	fgets(prelec, TAILLECH, stdin);
	purger(prelec);
	printf("Nom : ");
	fgets(nomlec, TAILLECH, stdin);
	purger(nomlec);
	printf("Adresse : ");
	fgets(adrlec, TLONGCH, stdin);
	purger(adrlec);

	// On rentre les valeurs du nouveau lecteur dans le tableau de lecteurs
	l->num = numlec;
	strcpy(l->prenom, prelec);
	strcpy(l->nom, nomlec);
	strcpy(l->adresse, adrlec);

	tabl[*nblec] = l;
	*nblec = *nblec + 1;

	printf("L'inscription du nouveau lecteur c'est bien passée, GOOD JOB!\n");

	afficherUnLecteur(*tabl[*nblec - 1]);

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();    //attendre avant d'appuyer sur entrer
	system("clear");
}

void pageSuppressionLecteur(Lecteur** tabl, int *nblec)
{
	int numlec, pos, i;

	system("clear");
	printf("---------- Suppression d'un lecteur ----------\n");
	afficherLecteurs(tabl, *nblec);
	printf("Numero du lecteur a supprimer (-1 retour) : ");
	saisirUnEntier(&numlec);
	if(numlec < 0)
		return;

	pos = rechercheLecteur (numlec, tabl, *nblec);

	while (pos < 0)
	{
		printf("\n Desole, le numéro de lecteur n'existe pas\n");
		printf("\n");
		printf("Retaper un numéro de lecteur (-1 retour) : ");
		saisirUnEntier(&numlec);
		if(numlec < 0)
			return;
		pos = rechercheLecteur (numlec, tabl, *nblec);
	}

	free(tabl[pos]);

	for (i = pos+1; i < *nblec; i++)
	{
		tabl[i-1] = tabl[i]; //on prend la valeur de la ligne suivante et on la met a pos i 
	}
	*nblec = *nblec - 1;

	printf("\nLe lecteur a bien ete supprime....FELICITATION!\n\n");

	afficherLecteurs(tabl, *nblec);

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageHistoriqueEmprunts(Emprunts** t, int nbemp, Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec)
{
	system("clear");
	printf("---------- Historique des emprunts ----------\n");
	
	afficherEmprunts(t, nbemp, touvr, nbouvr, tlec, nblec);

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageEmpruntsEnCours(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr)
{
	system("clear");
	printf("---------- Emprunts en cours ----------\n");
	
	afficherEmpruntsEnCours(tlec, nblec, touvr, nbouvr);

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageNouvelEmprunt(Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec)
{
	int cote, posouvr, numlec, poslec;
	char choix;
	Emprunts *e;
	Booleen erreur = FAUX;
	time_t dateSecondes;
	struct tm *date;

	system("clear");
	printf("---------- Ajout d'un nouvel emprunt ----------\n");
	afficherOuvrages(touvr, nbouvr, tlec, nblec);

	printf("\nNumero de la cote du livre (-1 retour) : ");
	saisirUnEntier(&cote);
	if (cote == -1)
		return;

	posouvr = rechercheOuvrage(cote, touvr, nbouvr);
	if (posouvr >= 0)
	{
		if (estEmprunte(*touvr[posouvr], tlec, nblec))
		{
			erreur = VRAI;
		}
	}
	else
		erreur = VRAI;

	while(erreur)
	{
		erreur = FAUX;
		if (posouvr >= 0)
		{
			if (estEmprunte(*touvr[posouvr], tlec, nblec))
			{
				printf("Cet ouvrage est déjà emprunté\n");
			}
		}
		else
			printf("Cet ouvrage n'existe pas\n");

		printf("Retapez une cote (-1 retour) : ");
		saisirUnEntier(&cote);
		if (cote == -1)
			return;

		posouvr = rechercheOuvrage(cote, touvr, nbouvr);
		if (posouvr >= 0)
		{
			if (estEmprunte(*touvr[posouvr], tlec, nblec))
			{
				erreur = VRAI;
			}
		}
		else
			erreur = VRAI;
	}

	printf("\n");
	afficherLecteurs(tlec, nblec);

	printf("\nNumero du lecteur : ");
	saisirUnEntier(&numlec);

	poslec = rechercheLecteur(numlec, tlec, nblec);
	while(poslec < 0)
	{
		printf("Ce lecteur n'existe pas\n");
		
		printf("Numero du lecteur : ");
		saisirUnEntier(&numlec);

		poslec = rechercheLecteur(numlec, tlec, nblec);
	}

	printf("\n");
	afficherUnLecteur(*tlec[poslec]);
	afficherUnOuvrage(*touvr[posouvr], tlec, nblec);
	printf("\nVoulez-vous ajouter l'emprunt suivant (O/N) ? ");

	scanf("%c", &choix);
	purger(&choix);
	if (choix == 'O' || choix == 'o')
	{
		e = (Emprunts*)malloc(sizeof(Emprunts));
		e->numlec = tlec[poslec]->num;
		e->cote = touvr[posouvr]->cote;

		time(&dateSecondes);
		date = localtime(&dateSecondes);
		e->demprunt.jour = date->tm_yday+1;
		e->demprunt.mois = date->tm_mon+1;
		e->demprunt.annee = date->tm_year+1900;

		tlec[poslec]->emps = insertionEmprunt(tlec[poslec]->emps, e);

		printf("L'emprunt a bien été ajouté\n");
	}
	else
	{
		printf("Annulation\n");
	}

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageRetourOuvrage(Lecteur** tlec, int nblec, Emprunts** temp, int *nbemp, Ouvrage** touvr, int nbouvr)
{
	int posouvr, cote, poslec;
	Booleen erreur = FAUX;
	Emprunts *e;
	time_t dateSecondes;
	struct tm *date;

	system("clear");
	printf("---------- Retour d'ouvrage ----------\n");
	afficherOuvrages(touvr, nbouvr, tlec, nblec);
	printf("\nNumero de la cote du livre (-1 retour) : ");
	saisirUnEntier(&cote);
	if (cote == -1)
		return;

	posouvr = rechercheOuvrage(cote, touvr, nbouvr);
	if (posouvr >= 0)
	{
		if (estEmprunte(*touvr[posouvr], tlec, nblec) == FAUX)
		{
			erreur = VRAI;
		}
	}
	else
		erreur = VRAI;

	while(erreur)
	{
		erreur = FAUX;
		if (posouvr >= 0)
		{
			if (estEmprunte(*touvr[posouvr], tlec, nblec) == FAUX)
			{
				printf("Cet ouvrage n'est pas emprunté\n");
			}
		}
		else
			printf("Cet ouvrage n'existe pas\n");

		printf("Retapez une cote (-1 retour) : ");
		saisirUnEntier(&cote);
		if (cote == -1)
			return;

		posouvr = rechercheOuvrage(cote, touvr, nbouvr);
		if (posouvr >= 0)
		{
			if (estEmprunte(*touvr[posouvr], tlec, nblec) == FAUX)
			{
				erreur = VRAI;
			}
		}
		else
			erreur = VRAI;
	}

	//Ajout historique
	poslec = chercherEmprunteur(tlec, nblec, *touvr[posouvr]);
	e = chercherEmprunt(tlec[poslec]->emps, touvr[posouvr]->cote);
	if(e == NULL)
	{
		printf("Erreur de récupération de l'emprunt\n");
		return;
	}

	time(&dateSecondes);
	date = localtime(&dateSecondes);
	e->dretour.jour = date->tm_yday+1;
	e->dretour.mois = date->tm_mon+1;
	e->dretour.annee = date->tm_year+1900;
	*nbemp = insertionHistorique(temp, e, *nbemp);
	//Suppression de la liste
	tlec[poslec]->emps = supprimerEmprunt(tlec[poslec]->emps, *touvr[posouvr]);

	printf("Le retour de l'ouvrage (%d) %s a bien été enregistré\n", touvr[posouvr]->cote, touvr[posouvr]->titre);


	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}

void pageAjouterOuvrage(Ouvrage** touvr, int *nbouvr)
{
	int cote, posouvr;
	char titre[TLONGCH], categ[TLONGCH], c;
	Ouvrage* o; 

	system("clear");
	printf("---------- Ajout d'ouvrage ----------\n");
	printf("\nNouvelle cote de l'ouvrage (-1 retour) : ");
	saisirUnEntier(&cote);
	if (cote == -1)
		return;
	posouvr = rechercheOuvrage(cote, touvr, *nbouvr);
	while(posouvr >= 0)
	{
		printf("L'ouvrage %d existe déjà (%s)\n", cote, touvr[posouvr]->titre);
		printf("\nNouvelle cote de l'ouvrage (-1 retour) : ");
		saisirUnEntier(&cote);
		if (cote == -1)
			return;
		posouvr = rechercheOuvrage(cote, touvr, *nbouvr);	
	}

	printf("Titre de l'ouvrage : ");
	fgets(titre, TLONGCH, stdin);
	purger(titre);
	printf("Catégorie : ");
	fgets(categ, TLONGCH, stdin);
	purger(categ);

	o = (Ouvrage *)malloc(sizeof(Ouvrage));
	if(o == NULL)
	{
		printf("Erreur d'allocation\n");
		return;
	}

	o->cote = cote;
	strcpy(o->titre, titre);
	strcpy(o->categ, categ);

	printf("Votre ouvrage : %d - %s - %s\n", o->cote, o->titre, o->categ);

	printf("Confirmez vous l'ajout ? (O/n) \n");

	scanf("%c", &c);
	purger(&c);

	if(c == 'o' || c == 'O')
	{
		if(*nbouvr == TMAXTAB)
		{
			printf("Tableau trop petit\n");
			getchar();
			return;
		}

		touvr[*nbouvr] = o;
		*nbouvr = *nbouvr + 1;

		printf("Ajout de (%d) %s réussi !\n", o->cote, o->titre);

	}
	else
	{
		printf("Annulation\n");
		free(o);
	}

	printf("\nAppuyez sur Entrée pour revenir au menu");
	getchar();
	system("clear");
}