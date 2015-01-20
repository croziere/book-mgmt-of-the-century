Lecteur * lireLecteur (FILE *fe, int *nbemp);
int chargeLecteurs(Lecteur ** t, int nbmax, char * nom);
int rechercheLecteur(int numrech, Lecteur *t[], int nb);
void afficherUnLecteur(Lecteur l);
void afficherLecteurs(Lecteur **l, int nblec);