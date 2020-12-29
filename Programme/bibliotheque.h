/* Librairies */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Reservation;

/* Définitions fonctions */

int choixMenu(void);
void programme(void);