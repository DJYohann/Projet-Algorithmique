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

typedef struct {
	int idEmprunt;
	int idAdherent;
	int idJeu;
	Date dateEmprunt;
	struct maillon *suiv;
} Emprunt ,*Emprunts;

typedef struct {
	int idReservation;
	int idAdherent;
	int idJeu;
	struct maillon *suiv;
} Reservation, *Reservations;

/* Fonctions */

Jeu lireJeu(FILE* flot);
Adherent lireAdherent(FILE* flot);
Emprunt lireEmprunt(FILE* flot);
Emprunts intialiserEmprunts(void);
Reservation lireReservation(FILE* flot);
Reservations intialiserReservations(void);

Jeu** chargementJeux(char *nomFic, int *nbjeux);
Adherent** chargementAdherents(char *nomFic, int *nbadherents);

int choixMenu(void);
void programme(void);

/* Fonctions tests */

void afficherJeu(Jeu jeu);
void afficherJeux(Jeu **tjeux, int nbjeux);
void afficherAdherent(Adherent adh);
void afficherAdherents(Adherent** tadherents, int nbadherents)
void afficherEmprunt(Emprunt emp);
void afficherReservation(Reservation res);
void testChargementFichiers(void);