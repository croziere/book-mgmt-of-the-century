#include "global.h"


/**
 * Compare deux dates d1 et d2
 * Retourne :
 * 0 <=> d1 == d2
 * 1 <=> d1 > d2 (d1 plus récent)
 * -1 <=> d1 < d2 (d1 plus ancien)
*/
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

/**
 * Affiche (printf) une date d au format dd/mm/yyyy
*/
void printDate(Date d, int retour)
{
	printf("%d/%d/%d", d.jour, d.mois, d.annee);

	if(retour == 1)
		printf("\n");
}

/**
* Vide le flux stdin pour éviter les erreurs
*/
void viderStdin(void)
{
	int c;
	while((c = getchar()) != '\n' && c != EOF) //On lit les caractère en trop dans stdin
	{}
}

/**
* Remplace le \n final par \0 et vide stdin si on dépasse la taille de lecture
*/
void purger(char * c) 
{
	char *fin = strchr(c, '\n');

	if(fin)
	{
		*fin = 0;
	}
	else
	{
		viderStdin();
	}
}


/**
* Permet de saisir sans erreurs un entier
*/
void saisirUnEntier(int *i)
{
	char val[20];
	int ret, nb;

	fgets(val, sizeof(val), stdin);
	purger(val);

	ret = sscanf(val, "%d", &nb);

	while(ret != 1)
	{
		printf("\nAttention, vous devez saisir un nombre : ");
		fgets(val, sizeof(val), stdin);
		purger(val);

		ret = sscanf(val, "%d", &nb);
	}

	*i = nb;
}

/**
* Charge les données depuis le fichier de sauvegarde binaire
*/
void chargerBinaire(Ouvrage** touvr, int *nbouvr, Lecteur** tlec, int *nblec, Emprunts** temp, int *nbemp)
{
	FILE *fe;
	Lecteur *l;
	Emprunts *e;
	Ouvrage *o;
	int i, j, nbenc;
	fe = fopen("data.save", "rb");

	fread(nblec, sizeof(int), 1, fe);


	for(i = 0; i < *nblec; i++)
	{
		l = (Lecteur *)malloc(sizeof(Lecteur));
		if(l == NULL)
		{
			printf("Erreur d'allocation\n");
			exit(1);
		}
		fread(l, sizeof(Lecteur), 1, fe);
		l->emps = NULL;
		fread(&nbenc, sizeof(int), 1, fe);
		if(nbenc > 0)
		{
			for(j = 0; j < nbenc; j++)
			{
				e = (Emprunts *)malloc(sizeof(Emprunts));
				if(e == NULL)
				{
					printf("Erreur d'allocation\n");
					exit(1);
				}
				fread(e, sizeof(Emprunts), 1, fe);
				l->emps = insertionEmprunt(l->emps, e);
			}
		}
		tlec[i] = l;
	}

	fread(nbouvr, sizeof(int), 1, fe);

	for(i = 0; i < *nbouvr; i++)
	{
		o = (Ouvrage *)malloc(sizeof(Ouvrage));
		fread(o, sizeof(Ouvrage), 1, fe);
		touvr[i] = o;
	}

	fread(nbemp, sizeof(int), 1, fe);

	for(i = 0; i < *nbemp; i++)
	{
		e = (Emprunts *)malloc(sizeof(Emprunts));
		fread(e, sizeof(Emprunts), 1, fe);
		temp[i] = e;
	}

	fclose(fe);
}

/**
* Initialise le programme : Depuis la sauvegarde ou depuis les fichiers texte ou vide
*/
void initialiser(Ouvrage **touvr, Lecteur **tlec, Emprunts **temp, int *nbouvr, int *nblec, int *nbemp)
{
	char choix;
	//Si sauvegarde présente, charger la sauvegarde.
	if(fopen("data.save", "rb") != NULL) //Sauvegarde présente, on charge directement
	{
		chargerBinaire(touvr, nbouvr, tlec, nblec, temp, nbemp);
	}
	else //On demande si il veut commencer avec des données vides ou importer
	{
		printf("Pas de sauvegarde présente, voulez vous commencer avec une bibliothèque vide (O/n) ? ");

		scanf("%c%*c", &choix);
		if(choix == 'O' || choix == 'o')
		{
			*nbouvr = 0;
			*nblec = 0;
			*nbemp = 0;
		}
		else
		{
			*nbouvr = chargeOuvrages(touvr, TMAXTAB, "ouvrage.dat");
			*nblec = chargeLecteurs(tlec, TMAXTAB, "lecteur.dat");
			*nbemp = chargeEmprunts(temp, TMAXTAB,"emprunt.dat");
		}
	}
}

/**
* Sauvegarde les tableaux dans le fichier binaire data.save
*/
void sauvegarder(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr, Emprunts** temp, int nbemp)
{
	FILE *fe;
	int i, nbenc;
	Liste l;
	fe = fopen("data.save", "wb");
	if(fe == NULL)
		printf("Erreur de création de la sauvegarde...\n");

	fwrite(&nblec, sizeof(int), 1, fe); //Nombre de lecteurs

	for(i = 0; i < nblec; i++)
	{
		l = tlec[i]->emps;
		fwrite(tlec[i], sizeof(Lecteur), 1, fe);
		nbenc = compterEmprunts(tlec[i]->emps);

		fwrite(&nbenc, sizeof(int), 1, fe);
		if(nbenc > 0)
		{
			sauvegarderEnmpruntsEnCours(l, fe);
		}
	}

	fwrite(&nbouvr, sizeof(int), 1, fe);

	for(i = 0; i < nbouvr; i++)
	{
		fwrite(touvr[i], sizeof(Ouvrage), 1, fe);
	}

	fwrite(&nbemp, sizeof(int), 1, fe);

	for(i = 0; i < nbemp; i++)
	{
		fwrite(temp[i], sizeof(Emprunts), 1, fe);
	}

	fclose(fe);

}

/**
* Libère la mémoire du programme
*/
void vider(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr, Emprunts** temp, int nbemp)
{
	int i;

	for(i = 0; i < nblec; i++)
	{
		viderListe(tlec[i]->emps);
		free(tlec[i]);
	}

	for(i = 0; i < nbouvr; i++)
	{
		free(touvr[i]);
	}

	for(i = 0; i < nbemp; i++)
	{
		free(temp[i]);
	}
}

/**
* Affiche le plus beau de tous les animaux, le PONEY !!! <3
*/
void welcomeChezUs (void)
{
 	system("clear");
 	printf("\t  ,  ,.~'''''~~..\n");
	printf("\t  )\\,)\\`-,       `~._                                     .--._\n");
	printf("\t  \\  \\ | )           `~._                   .-'''''-._   /     `.\n");
	printf("\t _/ ('  ( _(\\            `~~,__________..-''          `-<        \\ \n");
	printf("\t )   )   `   )/)   )         \\                            \\,-.    |\n");
	printf("\t') /)`      \\` \\,-')/\\      (                             \\ /     |\n");
	printf("\t(_(\\ /7      |.   /'  )'  _(`                              Y      |\n");
	printf("\t    \\       (  `.     ')_/`                                |      /\n");
	printf("\t     \\       \\   \\                                         |)    (\n");
	printf("\t      \\ _  /\\/   /         -- BIENVENUE --                 (      `~.\n");
	printf("\t       `-._)     |                                        / \\        `,\n");
	printf("\t                 |                          |           .'   )      (`\n");
	printf("\t                 \\                        _,\\          /     \\_    (`\n");
	printf("\t                  `.,      /       __..'7'   \\         |       )  (\n");
	printf("\t                  .'     _/`-..--''      `.   `.        \\      `._/\n");
	printf("\t                .'    _.j     /            `-.  `.       \\ \n");
	printf("\t              .'   _.'   \\    |               `.  `.      \\ \n");
	printf("\t             |   .'       ;   ;               .'  .'`.     \\ \n");
	printf("\t             \\_  `.       |   \\             .'  .'   /    .'\n");
	printf("\t               `.  `-, __ \\   /           .'  .'     |   (\n");
	printf("\t                 `.  `'` \\|  |           /  .-`     /   .'\n");
	printf("\t                   `-._.--t  ;          |_.-)      /  .'\n");
	printf("\t                          ; /           \\  /      / .'\n");
	printf("\t                         / /             `'     .' /\n");
	printf("\t                        /,_\\                  .',_(\n");
	printf("\t                       /___(                 /___(\n");
 	
 	getchar();
 	system("clear");

 }

/**
* Affiche le menu principal
*/
void menu (void)
{
		system("clear");
		printf("---------- Menu Principal ----------\n");
		printf("\n");
		printf("1 -> Afficher la liste des lecteurs\n");
		printf("2 -> Inscrire un nouveau lecteur\n");
		printf("3 -> Supprimer un lecteur\n");
		printf("4 -> Modifier l'adresse d'un lecteur \n");
		printf("5 -> Afficher tous les ouvrages\n");
		printf("6 -> Afficher les emprunts en cours\n");
		printf("7 -> Historique des emprunt\n");
		printf("8 -> Enregistrer un nouvel emprunt\n");
		printf("9 -> Enregistrer un retour d'ouvrages\n");
		printf("10 -> Surpriiise!\n");
		printf("\n");
		printf("0 -> quitter le programme.\n");
}

/**
* Fonction globale appelée au lancement du programme
*/
void globale (void)
{
	Ouvrage * touvr[TMAXTAB]; //Tableau des ouvrages
	Lecteur * tlec[TMAXTAB]; //Tableau des lecteurs
	Emprunts * temp[TMAXTAB]; //Tableau des emprunts terminés
	int nbouvr, nblec, nbemp, choix=-1;

	system("clear");
	initialiser(touvr, tlec, temp, &nbouvr, &nblec, &nbemp); //Chargement des données
	welcomeChezUs(); //Magic
	menu(); //Affichage du menu

	printf("Fais ton choix, tapes ton numéro : ");
	saisirUnEntier(&choix);

	while (choix != 0) //Appel des pages en fonction du choix
	{
		if (choix == 1)
			pageLecteurs(tlec, nblec);
		if (choix == 2)
			pageInscriptionLecteur(tlec, &nblec);
		if (choix == 3)
			pageSuppressionLecteur(tlec, &nblec);
		if (choix == 4)
			pageModifierAdresse(tlec, nblec);
		if (choix == 5)
			pageOuvrages(touvr, nbouvr, tlec, nblec);
		if (choix == 6)
			pageEmpruntsEnCours(tlec, nblec, touvr, nbouvr);
		if (choix == 7)
			pageHistoriqueEmprunts(temp, nbemp, touvr, nbouvr, tlec, nblec);
		if (choix == 8)
			pageNouvelEmprunt(touvr, nbouvr, tlec, nblec);
		if (choix == 9)
			pageRetourOuvrage(tlec, nblec, temp, &nbemp, touvr, nbouvr);
		if (choix == 10)
			welcomeChezUs();

		menu();
		printf("Fais ton choix, tapes ton numéro : ");
		saisirUnEntier(&choix);
	}

	sauvegarder(tlec, nblec, touvr, nbouvr, temp, nbemp); //On quitte, sauvegarder les données

	vider(tlec, nblec, touvr, nbouvr, temp, nbemp); //Vide la mémoire

	system("clear"); //Good Bye !
}