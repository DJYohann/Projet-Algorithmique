#include "ludotheque.h"

/*
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
Titre : creationAdherent
Auteur : Etienne
Finalité : créer un nouvel adhérent
Variable : nouv (Adherent) - structure Adherent
Paramètre : nbadherents (int) - nombre d'adherents
Retour : nouv (Adherent) - structure Adherent
*/

Adherent creationAdherent(int nbadherents, char *nom, char *prenom) {
	Adherent nouv;

	nouv.idAdherent = nbadherents + 1;

	printf("Civilité : ");
	scanf("%s%*c", nouv.civilite);
	while (strcmp(nouv.civilite, "Mr") !=0 && strcmp(nouv.civilite, "Mme") !=0) {
		printf("Erreur, retapez.\n");
		printf("Civilité : ");
		scanf("%s%*c", nouv.civilite);
	}

	strcpy(nouv.nom, nom);
	strcpy(nouv.prenom, prenom);

	printf("Date d'inscription \n");
	printf("Jour : ");
	scanf("%d%*c", &nouv.dateInscription.jour);
	printf("Mois : ");
	scanf("%d%*c", &nouv.dateInscription.mois);
	printf("Année : ");
	scanf("%d%*c", &nouv.dateInscription.annee);

	return nouv;
}

/*
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
Titre : ajoutAdherent
Finalité :
Auteur : Etienne
*/

Adherent** ajoutAdherent(Adherent** tadherents, int* nbadherents, Adherent nouv)
{
 	Adherent** nouvtab;
	int i;

	(*nbadherents)++;
 	i = *nbadherents - 1;

	 //reallouer le tableau selon le nombre d'adhérents
 	nouvtab = (Adherent**)realloc(tadherents,*nbadherents * sizeof(Adherent));
	if (nouvtab == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}
	nouvtab[i] = (Adherent*)malloc(sizeof(Adherent));
	if (nouvtab[i] == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}
	*nouvtab[i] = nouv;
	return nouvtab;
}

/*
Titre : annulationReservation
Finalité :
auteur : Loris
*/

// void annulationReservation (int idJeu, Adherent**, listeEmp listemp, *nbadherents)
// {
// 	int i;
// 	char nom[30], prenom[30];
// 	printf("Saisissez votre Nom : ");
// 	fgets(nom, 30, stdin);
// 	printf("Saisissez votre Prénom : ")
// 	fgets(prenom, 30, stdin);
// 	while (i < *nbadherents)
// 	{
//
// 	}
// }

/*
Titre : listeEmpruntsVide
Finalité : créer une liste chaînée de structure Emprunt vide
Variable : listemp (ListeEmp) - liste chaînée de structure Emprunt
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

ListeEmp listeEmpruntsVide(void) {
	return NULL;
}

/*
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
Titre : insererEmp
Finalité : insérer dans la liste un emprunt
Paramètres : listemp (ListeEmp) - liste chaînée de structure Emprunt
             emp (Emprunt) - structure Emprunt
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

// TODO
// ListeEmp insererEmp(ListeEmp listemp, Emprunt emp) {
// 	if (listemp == NULL) {
// 		return insererEnTeteEmp(listemp, emp);
// 	}
//
// 	listemp->suiv = insererEmp(listemp->suiv, emp);
//
// 	return listemp;
// }

/*
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
		listemp = insererEnTeteEmp(listemp, emp);
		(*nbemp)++;
		emp = lireEmprunt(fic);
	}

	fclose(fic);
	return listemp;
}

/*
Titre : enregistrementEmprunt
Finalité :
Auteur : Etienne
*/

ListeEmp enregistrementEmprunt(ListeEmp listemp, Adherent *tadherents[], Jeu* tjeux[], int *nbadherents, int nbjeux, int *nbemp)
{
	Emprunt nouv;
	Adherent adh;
	int jour, mois, annee;
	int idAdh, idJeu;
	char nom[30], nomJeu[30];
	char prenom[30];

	printf("Veuillez saisir votre nom : ");
	fgets(nom, 30, stdin);
	nom[strlen(nom) - 1] = '\0';
	printf("Veuillez saisir votre prénom : ");
	fgets(prenom, 30, stdin);
	prenom[strlen(prenom) - 1] = '\0';
	idAdh = rechercheIdUtilisateur(tadherents, nom, prenom, *nbadherents);
	if ( idAdh == -1 ) {
		adh = creationAdherent(*nbadherents, nom, prenom);
		idAdh = adh.idAdherent;
		tadherents = ajoutAdherent(tadherents, nbadherents, adh);
	}
	printf("Saisir nom du jeux : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';
	idJeu = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	if(idJeu == -1)
	{
		printf("Jeu non trouvé.\n");
		return listemp;
	}
	printf("Saisir le jour de l'emprunt : ");
	scanf("%d%*c", &jour);
	printf("Saisir le mois de l'emprunt : ");
	scanf("%d%*c", &mois);
	printf("Saisir l'année de l'emprunt : ");
	scanf("%d%*c", &annee);
	nouv = creationEmprunt(*nbemp, idAdh, idJeu, jour, mois, annee);
	listemp = insererEnTeteEmp(listemp, nouv);
	(*nbemp)++;
	return listemp;
}

/*
Titre : enregistrementReservation
Finalité :
Auteur : Etienne
*/

ListeRes enregistrementReservation(ListeRes listres, Adherent *tadherents[], Jeu* tjeux[], int *nbadherents, int nbjeux, int *nbres) {
	return NULL;
}

/*
Titre : creationEmprunt
Finalité :
Auteur : Etienne
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
Titre : listeReservationsVide
Finalité : créer une liste chaînée de structure Reservation vide
Variable : listres (ListeRes) - liste chaînée de structure Reservation
Retour : listres (ListeRes) - liste chaînée de structure Reservation
*/

ListeRes listeReservationsVide(void) {
	return NULL;
}

/*
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
Titre : insererRes
Finalité : insérer dans la liste une réservation
Paramètres : listemp (ListeRes) - liste chaînée de structure Reservation
             emp (Reservation) - structure Reservation
Retour : listemp (ListeRes) - liste chaînée de structure Reservation
*/

// TODO
// ListeRes insererRes (ListeRes listres, Reservation res) {

// }

/*
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
		listres = insererEnTeteRes(listres, res);
		(*nbres)++;
		res = lireReservation(fic);
	}

	fclose(fic);
	return listres;
}

/*
Titre : rechercheIdJeu
Finalité : rechercher un jeu avec le nom et renvoyer son identifiant
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		     	   nomJeu (char*) -
		         nbjeux (int) - nombre de jeux
Retour : idJeu (int) -
*/

int rechercheIdJeu(Jeu *tjeux[], char *nomJeu, int nbjeux) {
	int i;

	for (i = 0; i < nbjeux; i++) {
		if (strcmp(tjeux[i]->nom, nomJeu) == 0) {
			return tjeux[i]->idJeu;
		}
	}

	return -1;
}

/*
Titre : recherchePosJeu
Auteur : Loris
Finalité : rechercher un jeu avec l'identifiant et renvoyer sa position
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		     	   nomJeu (char*) -
		         nbjeux (int) - nombre de jeux
Retour : idJeu (int) -
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
Titre : rechercheIdUtilisateur
Auteur : Etienne
Finalité : rechercher un jeu avec l'identifiant et renvoyer sa position
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		     	   nomJeu (char*) -
		         nbjeux (int) - nombre de jeux
Retour : idJeu (int) -
*/

int rechercheIdUtilisateur(Adherent *tadherents[], char *nom, char *prenom, int nbadherents)
{
	int i;
	for (i = 0; i < nbadherents; i++)
	{
		if (strcmp(tadherents[i]->nom, nom) == 0 && strcmp(tadherents[i]->prenom, prenom) == 0)
			return tadherents[i]->idAdherent;
	}
	return -1;
}

/*
Titre : rechercheDichoAdherent
Finalité : rechercher un adhérent avec l'identifiant et renvoyer l'indice
Variable : deb (int) -
		       mil (int) -
		       fin (int) -
Paramètres : tadh (Adherent**) -
             idAdherent (int) -
             nbadherents (int) -
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
Titre : type
Finalité :
Variables :
Paramètres :
Retour :
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
Titre : nom
Finalité :
Variables :
Paramètres :
Retour :
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
Titre : echanger
Finalité :
Variable :
Paramètres :
*/

void echanger(Jeu *tabJeux[], int i, int j) {
	Jeu *tmp;

	tmp = tabJeux[i];
  tabJeux[i] = tabJeux[j];
  tabJeux[j] = tmp;
}

/*
Titre : triTabJeux
Finalité :
Variables :
Paramètres :
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
Titre : affichageEmpruntsCours
Auteur : Loris
Finalité :
Paramètres :
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
Titre : afficherJeuDispo
Finalité :
Paramètres :
*/

void afficherJeuDispo(Jeu jeu) {
	printf("%s\t%s\t%d\n", jeu.nom, jeu.type, jeu.nbExemp);
}

/*
Titre : affichageJeuxDispos
Finalité :
Variable :
Paramètres :
*/


void affichageJeuxDispos(Jeu *tabJeux[], int tailleLogJeux) {
	int i;

	printf("Nom\t\tType\tNb Exemplaire\n");

	for (i = 0; i < tailleLogJeux; i++) {
		afficherJeuDispo(*tabJeux[i]);
	}
}

/*
Titre : affichagReservationJeu
Finalité : afficher la liste de réservation pour un jeu donné
Variables : nomJeu (char*) -
            idJeu (int) -
            pos (int) -
Paramètre : listres (Reservations) - liste chaînée de structure Reservation
            tjeux (Jeu**) -
            tadh (Adherent**) -
            nbjeux (int) -
            nbadherents (int) -
*/

void affichageReservationJeu(ListeRes listres, Jeu *tjeux[], Adherent *tadh[], int nbjeux, int nbadherents) {
	char nomJeu[30];
	int idJeu, pos;

	printf("Nom du jeu : ");
	fgets(nomJeu, 31, stdin);
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
	printf("8 - Quitter\n");

	printf("Choix : ");
	scanf("%d%*c", &choix);
	while (choix < 1 || choix > 8) {
		printf("Choix : ");
	 	scanf("%d%*c", &choix);
	}

	return choix;
}

/*
Titre : application
Finalité : application de la gestion de prêts de jeux de la ludothèque
Variables :
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
	while (choix != 8) {
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
				afficherJeux(tjeux, nbjeux);
				afficherEmprunts(listempts, nbempts);
				listempts = enregistrementEmprunt(listempts, tadherents, tjeux, &nbadherents, nbjeux, &nbempts);
				afficherAdherents(tadherents, nbadherents);
				afficherEmprunts(listempts, nbempts);
				break;
			case 5:

				break;
			case 6:

				break;
			case 7:
				exit(1);

				break;
			default:

				break;
		}
		printf("\nAppuyez sur une touche pour continuer");
		c = getchar();
		choix = choixMenu();
	}

	printf("\nAu revoir !\n");

	free(tjeux);
	free(tadherents);
}
