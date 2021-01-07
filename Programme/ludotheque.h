/* Librairies */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Énumérations */

typedef enum {FAUX, VRAI} Bool;
typedef enum {carte, construction, logique, plateau, tuile}Type;

/* Structures */

typedef struct {
	int jour;
	int mois;
	int annee;
} Date;

typedef struct {
	int idJeu;
	char nom[30];
	char type[13];
	int nbExemp;
} Jeu;

typedef struct {
	int idAdherent;
	char civilite[4];
	char nom[30];
	char prenom[30];
	Date dateInscription;
} Adherent;

typedef struct {
	int idEmprunt;
	int idAdherent;
	int idJeu;
	Date dateEmprunt;
} Emprunt;

typedef struct {
	int idReservation;
	int idAdherent;
	int idJeu;
	Date dateReservation;
} Reservation;

/* Listes chaînées */

typedef struct maillonEmp {
	Emprunt emp;
	struct maillonEmp *suiv;
} MaillonEmp ,*ListeEmp;

typedef struct maillonRes {
	Reservation res;
	struct maillonRes *suiv;
} MaillonRes, *ListeRes;

/* Fonctions */

Jeu lireJeu(FILE* flot);
Jeu** chargementJeux(char *nomFic, int *nbjeux);

Adherent lireAdherent(FILE* flot);
Adherent creationAdherent(int nbadherents);
Adherent** chargementAdherents(char *nomFic, int *nbadherents);

Emprunt lireEmprunt(FILE* flot);
ListeEmp listeEmpruntsVide(void);
ListeEmp insererEnTeteEmp(ListeEmp listemp, Emprunt emp);
ListeEmp insererEmp(ListeEmp listemp, Emprunt emp);
ListeEmp chargementEmprunts(char *nomFic, ListeEmp listemp, int *nbemp);

Reservation lireReservation(FILE* flot);
ListeRes listeReservationsVide(void);
ListeRes insererEnTeteRes(ListeRes listres, Reservation res);
ListeRes insererRes (ListeRes listres, Reservation res);
ListeRes chargementReservations(char *nomFic, ListeRes listres, int *nbres);

int rechercheIdJeu(Jeu *tjeux[], char *nomJeu, int nbjeux);
int rechercheDichoAdherent(Adherent *tadh[], int idAdherent, int nbadherents);
int rechercheDichoJeu(Jeu *tjeux[], int idJeu, int nbjeux);

int type(Jeu *tabJeux[], int tailleLogJeux);
int nom(Jeu *tabJeux[], int tailleLogJeux);
void echanger(Jeu *tabJeux[], int i, int j);
void triTabJeux(Jeu *tabJeux[], int tailleLogJeux);

void afficherJeuDispo(Jeu jeu);
void affichageJeuxDispos(Jeu *tabJeux[], int tailleLogJeux);
void affichageEmpruntsCours (ListeEmp listempts, Jeu *tjeux[], Adherent *tadherents[], int nbjeux, int nbadherents);
void affichageReservationJeu(ListeRes listres, Jeu *tjeux[], Adherent *tadh[], int nbjeux, int nbadherents);

int choixMenu(void);
void application(void);

/* Fonctions tests */

void afficherJeu(Jeu jeu);
void afficherJeux(Jeu **tjeux, int nbjeux);
void afficherAdherent(Adherent adh);
void afficherAdherents(Adherent** tadherents, int nbadherents);
void afficherEmprunt(Emprunt emp);
void afficherEmprunts(ListeEmp listemp, int nbempts);
void afficherReservation(Reservation res);
void afficherReservations(ListeRes listres, int nbres);
void testChargementFichiers(void);
