void pageLecteurs(Lecteur** l, int nblec);
void pageOuvrages(Ouvrage** o, int nbouvr, Lecteur **tlec, int nblec);
void pageModifierAdresse(Lecteur** l, int nblec);
void pageInscriptionLecteur(Lecteur** tabl, int *nblec);
void pageSuppressionLecteur(Lecteur** tabl, int *nblec);
void pageHistoriqueEmprunts(Emprunts** t, int nbemp, Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec);
void pageEmpruntsEnCours(Lecteur** tlec, int nblec, Ouvrage** touvr, int nbouvr);
void pageNouvelEmprunt(Ouvrage** touvr, int nbouvr, Lecteur** tlec, int nblec);
void pageRetourOuvrage(Lecteur** tlec, int nblec, Emprunts** temp, int *nbemp, Ouvrage** touvr, int nbouvr);
