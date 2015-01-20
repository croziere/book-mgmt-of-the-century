Ouvrage * lireOuvrage(FILE *fe);
int chargeOuvrages(Ouvrage * t[], int nbmax, char * nom);
int rechercheOuvrage(int cote, Ouvrage** t, int nb);
void afficherUnOuvrage(Ouvrage o, Lecteur **tabl, int nblec);
void afficherOuvrages(Ouvrage** t, int nbouvr, Lecteur **tabl, int nblec);