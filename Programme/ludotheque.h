/* Librairies */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Énumérations */

typedef enum {FAUX, VRAI} bool;

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

typedef struct emprunt {
	int idEmprunt;
	int idAdherent;
	int idJeu;
	Date dateEmprunt;
	struct emprunt *suiv;
} Emprunt ,*Emprunts;

typedef struct reservation {
	int idReservation;
	int idAdherent;
	int idJeu;
	Date dateReservation;
	struct reservation *suiv;
} Reservation, *Reservations;

/* Fonctions */

Jeu lireJeu(FILE* flot);
Jeu** chargementJeux(char *nomFic, int *nbjeux);

Adherent lireAdherent(FILE* flot);
Adherent** chargementAdherents(char *nomFic, int *nbadherents);

Emprunt lireEmprunt(FILE* flot);
Emprunts initialiserEmprunts(void);
Emprunts insererEnTeteEmp(Emprunts listemp, Emprunt emp);
Emprunts insererEmp(Emprunts listemp, Emprunt emp);
Emprunts chargementEmprunts(char *nomFic, Emprunts listemp, int *nbemp);

Reservation lireReservation(FILE* flot);
Reservations intialiserReservations(void);
Reservations insererEnTeteRes(Reservations listres, Reservation res);
Reservations insererRes (Reservations listres, Reservation res);
Reservations chargementReservations(char *nomFic, Reservations listres, int *nbres);


int choixMenu(void);
void application(void);

/* Fonctions tests */

void afficherJeu(Jeu jeu);
void afficherJeux(Jeu **tjeux, int nbjeux);
void afficherAdherent(Adherent adh);
void afficherAdherents(Adherent** tadherents, int nbadherents);
void afficherEmprunts(Emprunts listemp, int nbempts);
void afficherReservations(Reservations listres, int nbres);

void testChargementFichiers(void);