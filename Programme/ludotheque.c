#include "ludotheque.h"

/*
Auteur : Yohann
Titre : lireJeu
Finalité : lire un jeu dans un flot donné
Variable : jeu (Jeu) - structure Jeu
Paramètre : flot (FILE*) - flot de lecture
Retour : jeu (Jeu) - structure Jeu
*/

Jeu lireJeu(FILE* flot) {
	Jeu jeu;

	fscanf(flot, "%d\n", &jeu.idJeu);
	fgets(jeu.nom, 30, flot);
	jeu.nom[strlen(jeu.nom) - 1] = '\0';
	fscanf(flot, "%s %d", jeu.type, &jeu.nbExemp);

	return jeu;
}

/*
Auteur : Yohann
Titre : chargementJeux
Finalité : charger en mémoire le fichier des jeux
Variables : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
            jeu (Jeu) - structure Jeu
            fic (FILE*) - fichier de jeux
            i (int) - indice du tableau
Paramètres : nomFic (char*) - nom du fichier
			 			 nbjeux (int*) - nombre de jeux
Retours : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		  		nbjeux (int*) - nombre de jeux
*/

Jeu** chargementJeux(char *nomFic, int *nbjeux) {
	Jeu **tjeux;
	Jeu jeu;
	FILE* fic;
	int i;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	fscanf(fic, "%d",  nbjeux);

	tjeux = (Jeu**)malloc(*nbjeux * sizeof(Jeu));
	if (tjeux == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	for (i = 0; i < *nbjeux; i++) {
		tjeux[i] = (Jeu*)malloc(sizeof(Jeu));
		if (tjeux[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
			exit(1);
		}
		jeu = lireJeu(fic);
		*tjeux[i] = jeu;
	}

	fclose(fic);
	return tjeux;
}


/*
Auteur : Yohann
Titre : lireAdherent
Finalité : lire un adherent dans un flot donné
Variable : adh (Adherent) - structure Adherent
Paramètre : flot (FILE*) - flot de lecture
Retour : adh (Adherent) - structure Adherent
*/

Adherent lireAdherent(FILE* flot) {
	Adherent adh;

	fscanf(flot, "%d %s\n", &adh.idAdherent, adh.civilite);
	fgets(adh.nom, 30, flot);
	adh.nom[strlen(adh.nom) - 1] = '\0';
	fgets(adh.prenom, 30, flot);
	adh.prenom[strlen(adh.prenom) - 1] = '\0';
	fscanf(flot, "%d/%d/%d", &adh.dateInscription.jour, &adh.dateInscription.mois, &adh.dateInscription.annee);

	return adh;
}

/*
Auteur : Etienne
Titre : creationAdherent
Finalité : créer un nouvel adhérent
Variable : nouv (Adherent) - structure Adherent
Paramètres : nbadherents (int) - nombre d'adherents
						 nom (char*) - nom de l'adhérent
						 prenom (char*) - prénom de l'adhérent
Retour : nouv (Adherent) - structure Adherent
*/

Adherent creationAdherent(int nbadherents, char *nom, char *prenom) {
	Adherent nouv;

	nouv.idAdherent = nbadherents + 1;

	printf("Civilité (Mr ou Mme) : ");
	scanf("%s%*c", nouv.civilite);
	while (strcmp(nouv.civilite, "Mr") != 0 && strcmp(nouv.civilite, "Mme") != 0) {
		printf("Civilité (Mr ou Mme) : ");
		scanf("%s%*c", nouv.civilite);
	}

	strcpy(nouv.nom, nom);
	strcpy(nouv.prenom, prenom);

	printf("Date d'inscription : \n");
	printf("Jour : ");
	scanf("%d%*c", &nouv.dateInscription.jour);
	printf("Mois : ");
	scanf("%d%*c", &nouv.dateInscription.mois);
	printf("Année : ");
	scanf("%d%*c", &nouv.dateInscription.annee);

	return nouv;
}

/*
Auteur : Yohann
Titre : chargementAdherents
Finalité : charger en mémoire le fichier des adhérents
Variables : tadherents (Adherent**) - tableau de pointeur sur la structure Adherent
            adh (Adherent) - structure Adherent
            fic (FILE*) - fichier des adhérents
            i (int) - indice du tableau
Paramètres : nomFic (char*) - nom du fichier
			 			 nbadherents (int*) - nombre d'adhérents
Retours : tjeux (Jeu**) - tableau de pointeur sur la structure Adherent
		  		nbadherents (int*) - nombre d'adhérents
*/

Adherent** chargementAdherents(char *nomFic, int *nbadherents) {
	Adherent** tadherents;
	Adherent adh;
	FILE* fic;
	int i;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	fscanf(fic, "%d", nbadherents);

	tadherents = (Adherent**)malloc(*nbadherents * sizeof(Adherent));
	if (tadherents == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	for (i = 0; i < *nbadherents; i++) {
		tadherents[i] = (Adherent*)malloc(sizeof(Adherent));
		if (tadherents[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
			exit(1);
		}
		adh = lireAdherent(fic);
		*tadherents[i] = adh;
	}

	fclose(fic);
	return tadherents;
}

/*
Auteur : Etienne
Titre : ajoutAdherent
Finalité : ajouter un adhérent dans le tableau
Variables : nouvtab (Adherent**) - tableau dynamique de pointeur
					 nouvpointer (Adherent*) - pointeur sur la structure Adherent
Paramètres : tadherents (Adherent**) - tableau dynamique de pointeur
						 nbadherents (int*) - nombre d'adhérents
						 nouv (Adherent) - structure Adherent
Retour : tadherents (Adherent) - tableau dynamique de pointeur
*/

Adherent** ajoutAdherent(Adherent** tadherents, int* nbadherents, Adherent nouv)
{
 	Adherent** nouvtab;
	Adherent* nouvpointer;

	int i, j;

	(*nbadherents)++;
 	i = *nbadherents - 1;

 	nouvtab = (Adherent**)realloc(tadherents,*nbadherents * sizeof(Adherent));
	if (nouvtab == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}
	tadherents = nouvtab;

	for (j = 0; j < *nbadherents; j++) {
		nouvpointer = (Adherent*)realloc(tadherents[j], sizeof(Adherent));
		tadherents[j] = nouvpointer;
	}
	tadherents[i] = (Adherent*)malloc(sizeof(Adherent));
	if (tadherents[i] == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}
	*tadherents[i] = nouv;
	return tadherents;
}

/*
Auteur : Yohann
Titre : lireEmprunt
Finalité : lire un emprunt dans un flot donné
Variable : emp (Emprunt) - structure Emprunt
Paramètre : flot (FILE*) - flot de lecture
Retour : emp (Emprunt) - structure d'Emprunt
*/

Emprunt lireEmprunt(FILE* flot) {
	Emprunt emp;

	fscanf(flot, "%d %d %d %d/%d/%d", &emp.idEmprunt, &emp.idAdherent, &emp.idJeu,
		&emp.dateEmprunt.jour, &emp.dateEmprunt.mois, &emp.dateEmprunt.annee);

	return emp;
}

/*
Auteur : Etienne
Titre : creationEmprunt
Finalité : créer un emprunt
Variable : nouv (Emprunt) - structure Emprunt
Paramètres : nbemp (int) - nombre d'emprunts
             idAdh (int) - id Adherent
						 idJeu (int) - id Jeu
						 jour (int) - jour
						 mois (int) - mois
						 annee (int) - annee
Retour : nouv (Emprunt) - structure Emprunt
*/

Emprunt creationEmprunt(int nbemp, int idAdh, int idJeu, int jour, int mois, int annee)
{
	Emprunt nouv;

	nouv.idEmprunt = nbemp + 1;
	nouv.idAdherent = idAdh;
	nouv.idJeu = idJeu;
	nouv.dateEmprunt.jour = jour;
	nouv.dateEmprunt.mois = mois;
	nouv.dateEmprunt.annee = annee;

	return nouv;
}

/*
Auteur : Yohann
Titre : listeEmpruntsVide
Finalité : créer une liste chaînée de structure Emprunt vide
Variable : listemp (ListeEmp) - liste chaînée de structure Emprunt
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

ListeEmp listeEmpruntsVide(void) {
	return NULL;
}

/*
Auteur : Yohann
Titre : insererEnTeteEmp
Finalité : insérer en tête de liste un emprunt
Variable : m (MaillonEmp*) - pointeur sur un maillon de la liste
Paramètres : listemp (ListeEmp) - liste chaînée de structure Emprunt
			 emp (Emprunt) - structure Emprunt
Retour : m (MaillonEmp*) - pointeur sur un maillon de la liste
*/

ListeEmp insererEnTeteEmp(ListeEmp listemp, Emprunt emp) {
	MaillonEmp *m;

	m = (MaillonEmp*)malloc(sizeof(MaillonEmp));
	if (m == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	m->emp = emp;
	m->suiv = listemp;

	return m;
}



/*
Auteur : Yohann
Titre : insererEmp
Finalité : insérer dans la liste un emprunt
Paramètres : listemp (ListeEmp) - liste chaînée de structure Emprunt
             emp (Emprunt) - structure Emprunt
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

ListeEmp insererEmp(ListeEmp listemp, Emprunt emp) {
	if (listemp == NULL) {
		return insererEnTeteEmp(listemp, emp);
	}

	if (emp.dateEmprunt.annee < listemp->emp.dateEmprunt.annee ||
		(emp.dateEmprunt.annee == listemp->emp.dateEmprunt.annee && emp.dateEmprunt.mois < listemp->emp.dateEmprunt.mois) ||
		(emp.dateEmprunt.annee == listemp->emp.dateEmprunt.annee && emp.dateEmprunt.mois == listemp->emp.dateEmprunt.mois && emp.dateEmprunt.jour < listemp->emp.dateEmprunt.jour)) {
			return insererEnTeteEmp(listemp, emp);
	}


	listemp->suiv = insererEmp(listemp->suiv, emp);

	return listemp;
}

/*
Auteur : Yohann
Titre supprimerEnTeteEmp
Finalité : supprimer un enmprun en-tête de liste
Variable : m (MaillonEmp*) - pointeur sur maillon de la liste d'Emprunt
Paramètre : listemp (ListeEmp) - liste d'Emprunt
Retour : listemp (ListeEmp) - liste d'Emprunt
*/

ListeEmp supprimerEnTeteEmp(ListeEmp listemp) {
	MaillonEmp* m;

	if (listemp == NULL) {
		printf("Opération impossible\n");
		exit(1);
	}

	m = listemp;
	listemp = listemp->suiv;

	free(m);

	return listemp;
}

/*
Auteur : Yohann
Titre supprimerEmp
Finalité : supprimer un emprunt
Paramètres : listemp (ListeEmp) - liste chaînée
						 emp (Emprunt) - liste chaînée de Emprunt
Retour : listemp
*/

ListeEmp supprimerEmp(ListeEmp listemp, Emprunt emp) {
	if (listemp == NULL) {
		printf("Opération impossible\n");
		return listemp;
	}

	if (emp.idEmprunt < listemp->emp.idEmprunt) {
		return listemp;
	}

	if (emp.idEmprunt == listemp->emp.idEmprunt) {
		return supprimerEnTeteEmp(listemp);
	}

	listemp->suiv = supprimerEmp(listemp->suiv, emp);

	return listemp;
}

/*
Auteur : Yohann
Titre : chargementEmprunts
Finalité : charger en mémoire le fichier des emprunts
Variables : emp (Emprunt) - structure Emprunt
            fic (FILE*) - fichier des emprunts
Paramètres : nomFic (char*) - nom du fichier
			 listemp (ListeEmp) - liste chaînée de structure Emprunt
			 nbemp (int*) - nombre d'emprunts
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

ListeEmp chargementEmprunts(char *nomFic, ListeEmp listemp, int *nbemp) {
	Emprunt emp;
	FILE* fic;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	emp = lireEmprunt(fic);
	while(!feof(fic)) {
		listemp = insererEmp(listemp, emp);
		(*nbemp)++;
		emp = lireEmprunt(fic);
	}

	fclose(fic);
	return listemp;
}

/*
Auteur : Etienne
Titre : enregistrementEmprunt
Finalité : enregistrer un emprunt
Paramètres : listemp (ListeEmp) - liste chaînée
						 tadherents (Adherent) - tableau dynamique de pointeur
						 tjeux (Jeu) - tableau dynamique de pointeur
						 nbadherents (entier) - pointeur
						 nbjeux (entier) - pointeur
						 nbemp (entier) - pointeur
*/

ListeEmp enregistrementEmprunt(ListeEmp listemp, Adherent *tadherents[], Jeu* tjeux[], int *nbadherents, int nbjeux, int *nbemp)
{
	Emprunt nouv;
	Adherent adh;
	int jour, mois, annee;
	int idAdh, idJeu, posJeu;
	int nbEmpAdh;
	char nom[30], nomJeu[30];
	char prenom[30];



	printf("Nom du jeu emprunté : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';
	idJeu = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	if(idJeu == -1)
	{
		printf("Jeu non trouvé.\n");
		return listemp;
	}

	posJeu = recherchePosJeu(tjeux, idJeu, nbjeux);
	if (tjeux[posJeu]->nbExemp-1 < 0) {
		printf("Il n'y a plus d'exemplaires de ce jeu.\n" );
		return listemp;
	}


	printf("Nom emprunteur : ");
	fgets(nom, 30, stdin);
	nom[strlen(nom) - 1] = '\0';
	printf("Prénom emprunteur : ");
	fgets(prenom, 30, stdin);
	prenom[strlen(prenom) - 1] = '\0';
	idAdh = rechercheIdUtilisateur(tadherents, nom, prenom, *nbadherents);
	if ( idAdh == -1 ) {
		adh = creationAdherent(*nbadherents, nom, prenom);
		idAdh = adh.idAdherent;
		tadherents = ajoutAdherent(tadherents, nbadherents, adh);
	}

	nbEmpAdh = verificationNbEmprunts(listemp, idAdh);
	if (nbEmpAdh == 3) {
		printf("Nombre d'emprunts maximal atteint.\n");
		return listemp;
	}

	printf("Date d'emprunt\n");
	printf("Jour : ");
	scanf("%d%*c", &jour);
	printf("Mois : ");
	scanf("%d%*c", &mois);
	printf("Année : ");
	scanf("%d%*c", &annee);
	nouv = creationEmprunt(*nbemp, idAdh, idJeu, jour, mois, annee);
	listemp = insererEmp(listemp, nouv);
	tjeux[posJeu]->nbExemp--;
	(*nbemp)++;
	return listemp;
}

/*
Auteur : Etienne
Titre : VerificationNbEmprunts
Finalité : vérifier le nombre d'emprunt d'un adhérent
Variable : i (int) - nombre d'emprunt
Paramètres : listemp (ListeEmp) - liste chaînée d'Emprunt
             idAdh (int) - id Adherent
*/

int verificationNbEmprunts(ListeEmp listemp, int idAdh)
{
	int i = 0;
	while (listemp != NULL) {
		if(listemp->emp.idAdherent == idAdh)
			i++;
		listemp = listemp->suiv;
	}
	return i;
}

/*
Auteur : Yohann
Titre : lireReservation
Finalité : lire une réservation dans un flot donné
Variable : res (Reservation) - structure Reservation
Paramètre : flot (FILE*) - flot de lecture
Retour : res (Reservation) - structure Reservation
*/

Reservation lireReservation(FILE* flot) {
	Reservation res;

	fscanf(flot, "%d %d %d %d/%d/%d", &res.idReservation, &res.idAdherent, &res.idJeu,
		&res.dateReservation.jour, &res.dateReservation.mois, &res.dateReservation.annee);

	return res;
}

/*
Auteur : Etienne
Titre : creationReservation
Finalité : créer une réservation
Variable : nouv (Reservation) - structure Reservation
Paramètres : nbres (int) - nombre de réservations
            idAdh (int) - id adherent
						idJeu (int) - id jeu
						jour (int) - jour
						mois (int) - mois
						annee (int) - annee
Retour : nouv (Reservation) - structure Reservation
*/

Reservation creationReservation(int nbres, int idAdh, int idJeu, int jour, int mois, int annee)
{
	Reservation nouv;

	nouv.idReservation = nbres + 1;
	nouv.idAdherent = idAdh;
	nouv.idJeu = idJeu;
	nouv.dateReservation.jour = jour;
	nouv.dateReservation.mois = mois;
	nouv.dateReservation.annee = annee;

	return nouv;
}

/*
Auteur : Yohann
Titre : listeReservationsVide
Finalité : créer une liste chaînée de structure Reservation vide
Variable : listres (ListeRes) - liste chaînée de structure Reservation
Retour : listres (ListeRes) - liste chaînée de structure Reservation
*/

ListeRes listeReservationsVide(void) {
	return NULL;
}

/*
Auteur : Yohann
Titre : insererEnTeteRes
Finalité : insérer en tête de liste une réservation
Variable : m (MaillonRes*) - pointeur sur un maillon de la liste
Paramètres : listres (ListeRes) - liste chaînée de structure Reservation
 			 res (Reservation) - structure Reservation
Retour : m (MaillonRes*) - pointeur sur un maillon de la liste
*/

ListeRes insererEnTeteRes(ListeRes listres, Reservation res) {
	MaillonRes *m;

	m = (MaillonRes*)malloc(sizeof(MaillonRes));
	if (m == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	m->res = res;
	m->suiv = listres;

	return m;
}

/*
Auteur : Yohann
Titre : insererRes
Finalité : insérer dans la liste une réservation
Paramètres : listemp (ListeRes) - liste chaînée de structure Reservation
             emp (Reservation) - structure Reservation
Retour : listemp (ListeRes) - liste chaînée de structure Reservation
*/


ListeRes insererRes (ListeRes listres, Reservation res) {
	if (listres == NULL) {
		return insererEnTeteRes(listres, res);
	}

	if (res.dateReservation.annee < listres->res.dateReservation.annee ||
		(res.dateReservation.annee == listres->res.dateReservation.annee && res.dateReservation.mois < listres->res.dateReservation.mois) ||
		(res.dateReservation.annee == listres->res.dateReservation.annee && res.dateReservation.mois == listres->res.dateReservation.mois && res.dateReservation.jour < listres->res.dateReservation.jour)) {
			return insererEnTeteRes(listres, res);
	}


	listres->suiv = insererRes(listres->suiv, res);

	return listres;
}

/*
Auteur : Yohann
Titre supprimerEnTeteRes
Finalité : supprime en tête de liste
Variable : m (MaillonRes*) - pointeur sur maillon de la liste Reservation
Paramètre : listres (ListeRes) - liste de Reservation
Rettour : listres (ListeRes) - liste de Reservation
*/

ListeRes supprimerEnTeteRes(ListeRes listres) {
	MaillonRes *m;

	if (listres == NULL) {
		printf("Opération impossible\n");
		exit(1);
	}

	m = listres;
	listres = listres->suiv;
	free(m);

	return listres;
}

/*
Auteur : Yohann
Titre supprimerRes
Finalité : supprime une réservation
Variables : listres (ListeRes) - liste de Reservation
            res (Reservation) - structure de Reservation
Retour : listres (ListeRes) - liste de Reservation
*/

ListeRes supprimerRes(ListeRes listres, Reservation res) {
	if (listres == NULL) {
		return listres;
	}

	if (res.idReservation < listres->res.idReservation) {
		return listres;
	}

	if (res.idReservation == listres->res.idReservation) {
		return supprimerEnTeteRes(listres);
	}

	listres->suiv = supprimerRes(listres->suiv, res);

	return listres;
}

/*
Auteur : Yohann
Titre : chargementReservations
Finalité : charger en mémoire le fichier des réservations
Variables : res (Reservation) - structure Reservation
            fic (FILE*) - fichier des réservations
Paramètres : nomFic (char*) - nom du fichier
			 			 listres (ListeRes) - liste chaînée de structure Reservation
			 		 	 nbemp (int*) - nombre de réservations
Retour : listres (ListeRes) - liste chaînée de structure Reservation
*/

ListeRes chargementReservations(char *nomFic, ListeRes listres, int *nbres) {
	Reservation res;
	FILE* fic;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	res = lireReservation(fic);
	while (!feof(fic)) {
		listres = insererRes(listres, res);
		(*nbres)++;
		res = lireReservation(fic);
	}

	fclose(fic);
	return listres;
}

/*
Auteur : Etienne
Titre : enregistrementReservation
Finalité : enregistrer une réservation
Variables : listres (ListeRes) - liste chaînée de structure Reservation
           tadherents (Adherent**) - tableau d'adherent
					 tjeux (Jeu**) - tableau de jeu
					 nbadherents (int*) - nombre d'adherents
					 nbjeux (int) - nombre de jeux
					 nbres (int) - nombre de réservations
Retour : listres (ListeRes) - liste chaînée de structure Reservation
*/

ListeRes enregistrementReservation(ListeRes listres, Adherent *tadherents[], Jeu* tjeux[], int *nbadherents, int nbjeux, int *nbres) {
	Reservation nouv;
	Adherent adh;
	int jour, mois, annee;
	int idAdh, idJeu, posJeu;
	int nbResAdh;
	char nom[30], nomJeu[30];
	char prenom[30];

	printf("Nom du jeu reservé : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';
	idJeu = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	if(idJeu == -1)
	{
		printf("Jeu non trouvé.\n");
		return listres;
	}

	posJeu = recherchePosJeu(tjeux, idJeu, nbjeux);
	if (tjeux[posJeu]->nbExemp > 0) {
		printf("Ce jeu est disponible, vous pouvez l'emprunter.\n");
		return listres;
	}

	printf("Nom : ");
	fgets(nom, 30, stdin);
	nom[strlen(nom) - 1] = '\0';
	printf("Prénom : ");
	fgets(prenom, 30, stdin);
	prenom[strlen(prenom) - 1] = '\0';
	idAdh = rechercheIdUtilisateur(tadherents, nom, prenom, *nbadherents);
	if ( idAdh == -1 ) {
		adh = creationAdherent(*nbadherents, nom, prenom);
		idAdh = adh.idAdherent;
		tadherents = ajoutAdherent(tadherents, nbadherents, adh);
	}
	nbResAdh = verificationNbReservations(listres, idAdh);
	if (nbResAdh == 3) {
		printf("Nombre de réservations maximal atteint.\n");
		return listres;
	}

	printf("Date de réservation : \n");
	printf("Jour : ");
	scanf("%d%*c", &jour);
	printf("Mois : ");
	scanf("%d%*c", &mois);
	printf("Année : ");
	scanf("%d%*c", &annee);
	nouv = creationReservation(*nbres, idAdh, idJeu, jour, mois, annee);
	listres = insererRes(listres, nouv);
	(*nbres)++;
	return listres;
}

/*
Auteur : Etienne
Titre : VerificationNbReservations
Finalité : vérifie si le nombre de réservation maximal est atteint.
Paramètre : listres (ListeRes) - liste chaînée
						idAdh (int) - id adherent
Variable : i (int) - nombre de réservations
Retour : i (int) - nombre de réservations
*/

int verificationNbReservations(ListeRes listres, int idAdh)
{
	int i = 0;
	while (listres != NULL) {
		if(listres->res.idAdherent == idAdh)
			i++;
		listres = listres->suiv;
	}
	return i;
}

/*
Auteur : Loris
Titre : annulationReservation
Finalité : annuler une réservation
Variables : idjeu (int) - id Jeu
            idadh (int) - id Adherent
						idres (int) - id Reservation
						nom (char) - nom de l'adhérent
						prenom (char) - prenom de l'adhérent
						nomjeu (char) - nom du jeu
						res (Reservation) - structure Reservation
Paramètres : listres (ListeRes) - liste chaînée de structure Reservation
					  tjeux (Jeu**) - tableau de jeu
            tadherents (Adherent**) - tableau d'adherent
						nbjeux (int) - nombre de jeux
						nbadherents (int) - nombre d'adherents
						nbres (int*) - nombre de réservations
Retour : listres (ListeRes) - liste chaînée de structure Reservation
*/

ListeRes annulationReservation (ListeRes listres, Jeu* tjeux[], Adherent* tadherents[], int nbjeux, int nbadherents, int *nbres)
{
	int idjeu, idadh, idres;
	char nom[30], prenom[30], nomjeu[30];
	Reservation res;

	printf("Saisissez le nom du jeu dont vous voulez annuler la réservation : ");
	fgets(nomjeu, 30, stdin);
	nomjeu[strlen(nomjeu) - 1] = '\0';

	idjeu = rechercheIdJeu(tjeux, nomjeu, nbjeux);
	if (idjeu == -1)
	{
		printf("Ce jeu n'existe pas");
		return listres;
	}

	printf("Saisissez votre Nom : ");
	fgets(nom, 30, stdin);
	nom[strlen(nom) - 1] = '\0';
	printf("Saisissez votre Prénom : ");
	fgets(prenom, 30, stdin);
	prenom[strlen(prenom) - 1] = '\0';

	idadh = rechercheIdUtilisateur(tadherents, nom, prenom, nbadherents);
	if (idadh == -1)
	{
		printf("Cet utilisateur n'existe pas");
		return listres;
	}

	idres = rechercheIdReservation(listres, idjeu, idadh);
	if (idres == -1)
	{
		printf("La réservation n'existe pas");
		return listres;
	}

	rechercheReservation(listres, &res, idres);
	listres = supprimerRes(listres, res);

	afficherReservations(listres, *nbres);
	(*nbres)--;
	return listres;
}

/*
Auteur : Yohann
Titre : retourJeu
Finalité : retourner un jeu emprunté et débloqué une réservation sur le jeu en question
Paramètre : listemp (ListeEmp) - liste chaînée de listeEmp
						listres (ListeRes) - liste chaînée de réservations
						tjeux (Jeu) - tableau dynamique de pointeurs
						tadherents (Adherent) - tableau dynamique de pointeurs
						nbemp (int) - nombre d'emprunts
						nbres (int) - nombre de réservation
						nbjeux (int) - nombre de jeux
						nbadherents (int) - nombre d'adhérents
*/

void retourJeu(ListeEmp listemp, ListeRes listres, Jeu* tjeux[], Adherent* tadherents[],  int *nbemp, int *nbres, int nbjeux, int nbadherents) {
	int idJeu, idAdh, jour, mois, annee;
	char nomJeu[30], nomAdh[30], prenomAdh[30];
	Emprunt emp;

	printf("Nom du jeu : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';
	idJeu = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	if (idJeu == -1) {
		printf("Jeu non existant\n");
		return;
	}

	printf("Nom : ");
	fgets(nomAdh, 30, stdin);
	nomAdh[strlen(nomAdh) - 1] = '\0';
	printf("Prénom : ");
	fgets(prenomAdh, 30, stdin);
	prenomAdh[strlen(prenomAdh) - 1] = '\0';
	idAdh = rechercheIdUtilisateur(tadherents, nomAdh, prenomAdh, nbadherents);
	if (idAdh == -1) {
		printf("Utilisateur non existant\n");
		return;
	}

	while (listres != NULL) {
		if (idJeu == listres->res.idJeu) {
			printf("Date emprunt\n");
			printf("Jour : ");
			scanf("%d%*c", &jour);
			printf("Mois : ");
			scanf("%d%*c", &mois);
			printf("Année : ");
			scanf("%d%*c", &annee);
			emp = creationEmprunt(*nbemp, listres->res.idAdherent, idJeu, jour, mois, annee);
			(*nbemp)++;
			listemp = insererEmp(listemp, emp);
			listres = supprimerRes(listres, listres->res);
			(*nbres)--;
		}
		listres = listres->suiv;
	}

	while (listemp != NULL) {
		if (idJeu == listemp->emp.idJeu && idAdh == listemp->emp.idAdherent) {
			listemp = supprimerEmp(listemp, listemp->emp);
			(*nbemp)--;
		}
		listemp = listemp->suiv;
	}
}

/*
Auteur : Loris
Finalité : recherche une réservation
Paramètres : listres (ListeRes) - liste Reservation
						 res (Reservation) - structure Reservation
						 idres (int) - id reservation

*/

void rechercheReservation(ListeRes listres, Reservation* res, int idres) {
	while (listres != NULL)
	{
		if (idres == listres->res.idReservation) {
				*res = listres->res;
				break;
		}
		listres = listres->suiv;
	}
}

/*
Auteur : Loris
Titre : rechercheIdReservation
Finalité : rechercher une réservation
Paramètres : listres (ListeRes) - liste de Reservation
             idJeu (int) - id jeu
						 idAdh (int) - id adherent
*/

int rechercheIdReservation(ListeRes listres, int idJeu, int idAdh)
{
	while (listres != NULL)
	{
		if (idJeu == listres->res.idJeu && idAdh == listres ->res.idAdherent) {
				return listres->res.idReservation;
		}
		listres = listres->suiv;
	}
	return -1;
}

/*
Auteur : Yohann
Titre : rechercheIdJeu
Finalité : rechercher un jeu avec le nom et renvoyer son identifiant
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		     	   nomJeu (char*) - nom du jeu
		         nbjeux (int) - nombre de jeux
Retour : idJeu (int) - id jeu
*/

int rechercheIdJeu(Jeu *tjeux[], char *nomJeu, int nbjeux) {
	int i;

	for (i = 0; i < nbjeux; i++) {
		if (strcmp(nomJeu, tjeux[i]->nom) == 0) {
			return tjeux[i]->idJeu;
		}
	}

	return -1;
}

/*
Auteur : Loris
Titre : recherchePosJeu
Finalité : rechercher un jeu avec l'identifiant et renvoyer sa position
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		     	   idJeu (int) - id jeu
		         nbjeux (int) - nombre de jeux
Retour : i (int) - indice du tableau
*/

int recherchePosJeu(Jeu *tjeux[], int idJeu, int nbjeux)
{
	int i;
	for (i = 0; i < nbjeux; i++)
	{
		if (tjeux[i]->idJeu == idJeu)
			return i;
	}
	return -1;
}

/*
Auteur : Etienne
Titre : rechercheIdUtilisateur
Finalité : rechercher l'id d'un adhérent avec son nom et prenom
Variable : i (int) - indice du tableau
Paramètres : tadherents (Adherent**) - tableau de pointeur sur la structure Jeu
		     	   nom (char*) - nom de l'adherent
						 prenom (char*) - prenom de l'adherent
		         nbadherents (int) - nombre d'adherent
Retour : tadherents[i]->idAdherent (int) - id adherent
*/

int rechercheIdUtilisateur(Adherent *tadherents[], char *nom, char *prenom, int nbadherents)
{
	int i;
	for (i = 0; i < nbadherents; i++) {
		if (strcmp(tadherents[i]->nom, nom) == 0 && strcmp(tadherents[i]->prenom, prenom) == 0)
			return tadherents[i]->idAdherent;
	}
	return -1;
}

/*
Auteur : Yohann
Titre : rechercheDichoAdherent
Finalité : rechercher un adhérent avec l'identifiant et renvoyer l'indice
Variable : deb (int) - debut tableau
		       mil (int) - milieu tableau
		       fin (int) - fin tableau
Paramètres : tadh (Adherent**) - tableau d'adherent
             idAdherent (int) - id adherent
             nbadherents (int) - nombre adherents
Retour : mil - (int)
*/

int rechercheDichoAdherent(Adherent *tadh[], int idAdherent, int nbadherents) {
	int deb = 0, mil, fin = nbadherents - 1;

	while (deb <= fin) {
		mil = (deb + fin) / 2;

		if (idAdherent == tadh[mil]->idAdherent) {
			return mil;
		}

		if (idAdherent <= tadh[mil]->idAdherent) {
			fin = mil - 1;
		} else {
			deb = mil + 1;
		}
	}

	return deb;
}


/*
Auteur : Etienne
Titre : type
Finalité : trier les jeux par type
Variables : i (int) - variable pour boucle for
						pge (int) - position du plus grand
Paramètres : tabJeux (Jeu) - tableau dynamique de pointeur
Retour : pge (int) - position du plus grand
*/

int type(Jeu *tabJeux[], int tailleLogJeux) {
	int i, pge = 0;

	for (i = 0; i < tailleLogJeux; i++) {
		if (strcmp(tabJeux[pge]->type, tabJeux[i]->type) < 0) {
			pge = i;
		}
	}

	return pge;
}

/*
Auteur : Etienne
Titre : nom
Finalité : trier les jeux par ordre alphabétique
Variables : i (int) - variable pour boucle for
						pge (int) - position du plus grand
Paramètres : tabJeux (Jeu) - tableau dynamique de pointeur
						 tailleLogJeux (int) - nombre de jeux total
Retour : pge - entier "le plus grand"
*/

int nom(Jeu *tabJeux[], int tailleLogJeux) {
	int i, pge = 0;

	for (i = 0; i < tailleLogJeux; i++) {
		if (strcmp(tabJeux[pge]->type, tabJeux[i]->type) == 0) {
			if (strcmp(tabJeux[pge]->nom, tabJeux[i]->nom) < 0) {
				pge = i;
			}
		}
	}

	return pge;
}

/*
Auteur : Etienne
Titre : echanger
Finalité : échanger de places deux éléments d'un tableau
Variable : tmp (Jeu) - structre Jeu
Paramètres : tabJeux (Jeu) - tableau dynamique de pointeur
						 i (int) - position dans le tableau tabJeux
						 j (int) - position dans le tableau tabJeux
*/

void echanger(Jeu *tabJeux[], int i, int j) {
	Jeu *tmp;

	tmp = tabJeux[i];
  tabJeux[i] = tabJeux[j];
  tabJeux[j] = tmp;
}

/*
Auteur : Etienne
Titre : triTabJeux
Finalité : trier le tableau des jeux
Variables : taille (int) - taille logique du tableau
						pge (int) - position du plus grand type de jeu
Paramètres : tabJeux (Jeu**) - tableau dynamique de pointeur
						 tailleLogJeux (int) - nombre de jeux dans le tableau
*/

void triTabJeux(Jeu *tabJeux[], int tailleLogJeux) {
	int taille, pge;

	// Tri par type
  taille = tailleLogJeux;
	while (taille > 1) {
		pge = type(tabJeux, taille);
		echanger(tabJeux, pge, taille - 1);
		taille--;
	}

	// Tri alphabétique par type
	taille = tailleLogJeux;
	while (taille > 1) {
		pge = nom(tabJeux, taille);
		echanger(tabJeux, pge, taille - 1);
		taille--;
	}
}

/*
Auteur : Loris
Titre : affichageEmpruntsCours
Finalité : afficher tous les emprunts en cours
Paramètres : listempts (ListEmp) - liste chaînée de structre ListEmp
						 tjeu(Jeu**) - tableau dynamique de pointeur
						 tadherents(Adherent**) - tableau dynamique de pointeur
						 nbjeux (int) - nombre total de jeux
						 nbadherents (int) - nombre total d'adhérents
*/

void affichageEmpruntsCours (ListeEmp listempts, Jeu *tjeux[], Adherent *tadherents[], int nbjeux, int nbadherents) {
	int posJeu, posAdh;

	printf("Nom du Jeu emprunté\t\tIdentité\t\t\tDate d'emprunt\n");
	while (listempts != NULL) {
		posJeu = recherchePosJeu(tjeux, listempts->emp.idJeu, nbjeux);
		posAdh = rechercheDichoAdherent(tadherents, listempts->emp.idAdherent, nbadherents);

		printf("%s\t\t%s\t%s\t\t%d/%d/%d\n", tjeux[posJeu]->nom, tadherents[posAdh]->nom, tadherents[posAdh]->prenom,
		listempts->emp.dateEmprunt.jour, listempts->emp.dateEmprunt.mois, listempts->emp.dateEmprunt.annee);

		listempts = listempts->suiv;
	}
}

/*
Auteur : Etienne
Titre : afficherJeuDispo
Finalité : afficher le jeu disponnible
Paramètres : jeu(Jeu) - liste chaînée de structure Jeu
*/

void afficherJeuDispo(Jeu jeu) {
	printf("%s\t%s\t%d\n", jeu.nom, jeu.type, jeu.nbExemp);
}

/*
Auteur : Etienne
Titre : affichageJeuxDispos
Finalité : afficher tous les jeux disponnibles
Variable : i(int) - variable pou boucle while
Paramètres : tabJeux(Jeu**) - tableau dynamique de pointeur
						 tailleLogJeux (int) - nombre de jeux dans le tableau tabJeux
*/


void affichageJeuxDispos(Jeu *tabJeux[], int tailleLogJeux) {
	int i;

	printf("Nom\t\tType\tNb Exemplaire\n");

	for (i = 0; i < tailleLogJeux; i++) {
		if (tabJeux[i]->nbExemp > 0) {
			afficherJeuDispo(*tabJeux[i]);
		}
	}
}

/*
Auteur : Yohann
Titre : affichagReservationJeu
Finalité : afficher la liste de réservation pour un jeu donné
Variables : nomJeu (char*) - tableau du nom du jeu
            idJeu (int) - id du jeu
            pos (int) - position del'adhérent
Paramètre : listres (Reservations) - liste chaînée de structure Reservation
            tjeux (Jeu**) - tableau dynamique de pointeur
            tadh (Adherent**) - tableau dynamique de pointeur
            nbjeux (int) - nombre de jeux total
            nbadherents (int) - nombre d'adhérents total
*/

void affichageReservationJeu(ListeRes listres, Jeu *tjeux[], Adherent *tadh[], int nbjeux, int nbadherents) {
	char nomJeu[30];
	int idJeu, pos;

	printf("Nom du jeu : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';

	idJeu = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	if (idJeu == -1) {
		printf("\nJeu non existant\n");
	} else {
		printf("\nRéservations pour le jeu : %s\n", nomJeu);
		printf("Nom\t\tPrenom\t\tDate Reservation\n");
		while (listres != NULL) {
			if (idJeu == listres->res.idJeu) {
				pos = rechercheDichoAdherent(tadh, listres->res.idAdherent, nbadherents);
				printf("%s\t\t%s\t\t%d/%d/%d\n", tadh[pos]->nom, tadh[pos]->prenom, listres->res.dateReservation.jour,
					listres->res.dateReservation.mois, listres->res.dateReservation.annee);
			}
			listres = listres->suiv;
		}
	}
}

/*
Auteur : Loris
Titre : sauvegarderJeux
Finalité : sauvegarder les jeux en mémoire dans le fichier
Variables : flot (FILE*) - fichier d'écriture
            i (int) - variable pour bloucle while
Paramètres : tjeux (Jeu**) - tableau des jeux
             nomFic (char*) - fichier de sauvegarde
						 nbjeux (int) - nombre total de jeux
*/

void sauvegarderJeux(Jeu* tjeux[], char* nomFic, int nbjeux) {
	FILE *flot;
	int i = 0;

	flot=fopen(nomFic,"w");
	if (flot == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	fprintf(flot,"%d\n",nbjeux);
	while (i < nbjeux) {
		fprintf(flot,"%d\n",tjeux[i]->idJeu);
		fprintf(flot,"%s\n",tjeux[i]->nom);
		fprintf(flot,"%s %d\n",tjeux[i]->type,tjeux[i]->nbExemp);
		i=i+1;
	}
}

/*
Auteur : Loris
Titre : sauvegarderAdherents
Finalité : sauvegarder les adhérents en mémoire dans le fichier
Variables : flot (FILE*) - fichier d'écriture
            i (int) - variable pour boucle while
Paramètres : tadherents (Adherent**) - tableau des adhérents
             nomFic (char*) - fichier de sauvegarde
						 nbadherents (int) - nombre total d'adhérents
*/

void sauvegarderAdherents(Adherent* tadherents[], char* nomFic, int nbadherents) {
	FILE *flot;
	int i = 0;

	flot=fopen(nomFic,"w");
	if (flot == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	fprintf(flot,"%d\n",nbadherents);
	while (i < nbadherents) {
		fprintf(flot,"%d %s\n",tadherents[i]->idAdherent,tadherents[i]->civilite);
		fprintf(flot,"%s\n",tadherents[i]->nom);
		fprintf(flot,"%s\n",tadherents[i]->prenom);
		fprintf(flot,"%d/%d/%d\n",tadherents[i]->dateInscription.jour,tadherents[i]->dateInscription.mois,tadherents[i]->dateInscription.annee);
		i=i+1;
	}
}

/*
Auteur : Loris
Titre : sauvegarderEmprunts
Finalité : sauvegarder les emprunts en mémoire dans le fichier
Variables : flot (FILE*) - fichier d'écriture
            i (int) - variable pour boucle while
Paramètres : listemp (ListeEmp) - liste chaînée des emprunts
             nomFic (char*) - fichier de sauvegarde
						 nbemp (int) - nombre total d'emrpunts
*/

void sauvegarderEmprunts(ListeEmp listemp, char* nomFic, int nbemp) {
	FILE *flot;
	int i = 0;

	flot=fopen(nomFic,"w");
	if (flot == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}
	while (i < nbemp) {
		fprintf(flot,"%d %d %d %d/%d/%d\n",listemp->emp.idEmprunt,listemp->emp.idAdherent,listemp->emp.idJeu,
		listemp->emp.dateEmprunt.jour,listemp->emp.dateEmprunt.mois,listemp->emp.dateEmprunt.annee);
		i=i+1;
	}
}

/*
Auteur : Loris
Titre : sauvegarderReservations
Finalité : sauvegarder les réservation en mémoire dans le fichier
Variables : flot (FILE*) - flot d'écriture
            i (int) -variable pour boucle while
Paramètres : listres (ListeRes) - liste chaînée des réservations
             nomFic (char*) - fichier de sauvegarde
						 nbres (int) - nombre total de réservations
*/

void sauvegarderReservations(ListeRes listres, char* nomFic, int nbres) {
	FILE *flot;
	int i = 0;

	flot=fopen(nomFic,"w");
	if (flot == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}
	while(i < nbres){
		fprintf(flot,"%d %d %d %d/%d/%d\n",listres->res.idReservation,listres->res.idAdherent,listres->res.idJeu,
		listres->res.dateReservation.jour,listres->res.dateReservation.mois,listres->res.dateReservation.annee);
		i=i+1;
	}

}

/*
Auteur : Yohann
Titre : choixMenu
Finalité : Afficher le menu et saisir le choix
Variable : choix (int) - choix du menu
Retour : choix (int) - choix du menu
*/

int choixMenu(void) {
	int choix;

	system("clear");
	printf("1 - Affichage jeux disponibles\n");
	printf("2 - Affichage emprunts en cours\n");
	printf("3 - Affichage réservations pour un jeu\n");
	printf("4 - Saisie emprunt\n");
	printf("5 - Saisie réservation\n");
	printf("6 - Retour d'un jeu\n");
	printf("7 - Annulation d'une réservation\n");
	printf("8 - Sauvegarde des données\n");
	printf("9 - Quitter\n");

	printf("Choix : ");
	scanf("%d%*c", &choix);
	while (choix < 1 || choix > 9) {
		printf("Choix : ");
	 	scanf("%d%*c", &choix);
	}

	return choix;
}

/*
Auteurs : Etienne, Loris, Yohann
Titre : application
Finalité : application de la gestion de prêts de jeux de la ludothèque
Variables : ficjeux (char*) - fichier des jeux
 					  ficadherents (char*) - fichier des adherents
						ficemprunts (char*) - fichier des emprunts
						ficreservations (char*) fichier des réservations
						tjeux (Jeu**) - tableau dynamique de pointeur  sur la  structre Jeu
						tadherents (Adherent** ) - tableau dynamique de pointeurs sur la structure Adherent
						listempts (ListeEmp) - liste chaînée de la structure listEmp
						listres (ListeRes) - liste chaînée de la structure Reservation
						nbjeux (int) - nombre de jeux
						nbadherents (int) - nombre d'adherents
						nbempts (int) - nombre d'emprunts
						nbres (int) - nombre de réservations
						c (char) - caractère de saisie clavier
*/

void application(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichiers/adherents.don",
	*ficemprunts = "../Fichiers/emprunts.don", *ficreservations = "../Fichiers/reservations.don";

	Jeu **tjeux;
	Adherent** tadherents;
	ListeEmp listempts = listeEmpruntsVide();
	ListeRes listres = listeReservationsVide();

	int nbjeux = 0, nbadherents = 0, nbempts = 0, nbres = 0, choix;
	char c;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);
	listempts = chargementEmprunts(ficemprunts, listempts, &nbempts);
	listres = chargementReservations(ficreservations, listres, &nbres);

	triTabJeux(tjeux, nbjeux);

	choix = choixMenu();
	while (choix != 9) {
		switch(choix) {
			case 1:
				affichageJeuxDispos(tjeux, nbjeux);
				break;
			case 2:
				affichageEmpruntsCours(listempts, tjeux, tadherents, nbjeux, nbadherents);
				break;
			case 3:
				affichageReservationJeu(listres, tjeux, tadherents, nbjeux, nbadherents);
				break;
			case 4:
				listempts = enregistrementEmprunt(listempts, tadherents, tjeux, &nbadherents, nbjeux, &nbempts);
				break;
			case 5:
				listres = enregistrementReservation(listres, tadherents, tjeux, &nbadherents, nbjeux, &nbres);
				break;
			case 6:
				retourJeu(listempts, listres, tjeux, tadherents, &nbempts, &nbres, nbjeux, nbadherents);
				break;
			case 7:
				listres = annulationReservation(listres, tjeux, tadherents, nbjeux, nbadherents, &nbres);
				break;
			case 8:
				sauvegarderJeux(tjeux, ficjeux, nbjeux);
				sauvegarderAdherents(tadherents, ficadherents, nbadherents);
				sauvegarderEmprunts(listempts, ficemprunts, nbempts);
				sauvegarderReservations(listres, ficemprunts, nbres);
				printf("\nSauvegarde effectuée\n");
			default: break;
		}
		printf("\nAppuyez sur une touche pour continuer");
		c = getchar();
		choix = choixMenu();
	}

	sauvegarderJeux(tjeux, ficjeux, nbjeux);
	sauvegarderAdherents(tadherents, ficadherents, nbadherents);
	sauvegarderEmprunts(listempts, ficemprunts, nbempts);
	sauvegarderReservations(listres, ficemprunts, nbres);
	printf("\nSauvegarde effectuée\n");

	printf("\nAu revoir !\n");

	free(tjeux);
	free(tadherents);
}
