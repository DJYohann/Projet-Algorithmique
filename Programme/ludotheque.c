#include "ludotheque.h"

/* 
Titre : lireJeu
Finalité : lire un jeu dans un flot donné
Variable : jeu (Jeu) - jeu à lire
Paramètre : flot (FILE*) - flot de lecture
Retour : jeu (Jeu) - jeu
*/

Jeu lireJeu(FILE* flot) {
	Jeu jeu;

	fscanf(flot, "%d\n", &jeu.idJeu);
	fgets(jeu.nom, 31, flot);
	jeu.nom[strlen(jeu.nom) - 1] = '\0';
	fscanf(flot, "%s %d", jeu.type, &jeu.nbExemp);

	return jeu;
}

/*
Titre : lireAdherent
Finalité : lire un adherent dans un flot donné
Variable : adh (Adherent) - adherent à lire
Paramètre : flot (FILE*) - flot de lecture
Retour : adh (Adherent) - adherent
*/

Adherent lireAdherent(FILE* flot) {
	Adherent adh;

	fscanf(flot, "%d %s\n", &adh.idAdherent, adh.civilite);
	fgets(adh.nom, 31, flot);
	adh.nom[strlen(adh.nom) - 1] = '\0';
	fgets(adh.prenom, 31, flot);
	adh.prenom[strlen(adh.prenom) - 1] = '\0';
	fscanf(flot, "%d/%d/%d", &adh.dateInscription.jour, &adh.dateInscription.mois, &adh.dateInscription.annee);

	return adh;
}

/* 
Titre : lireEmprunt
Finalité : lire un emprunt dans un flot donné
Variable : emp (Emprunt) - emprunt à lire
Paramètre : flot (FILE*) - flot de lecture
Retour : emp (Emprunt) - emprunt
*/

Emprunt lireEmprunt(FILE* flot) {
	Emprunt emp;

	fscanf(flot, "%d %d %d %d/%d/%d", &emp.idEmprunt, &emp.idAdherent, &emp.idJeu, 
		&emp.dateEmprunt.jour, &emp.dateEmprunt.mois, &emp.dateEmprunt.annee);

	return emp;
}

/* 
Titre : lireReservation
Finalité : lire une réservation dans un flot donné
Variable : res (Reservation) - réservation à lire
Paramètre : flot (FILE*) - flot de lecture
Retour : res (Reservation) - réservation
*/

Reservation lireReservation(FILE* flot) {
	Reservation res;

	fscanf(flot, "%d %d %d", &res.idReservation, &res.idAdherent, &res.idJeu);

	return res;
}

/* 
Titre : chargementJeux
Finalité : charger en mémoire le fichier des jeux
Variables : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
            jeu (Jeu) - structure Jeu
            fic (FILE*) - fichier de jeux
            i (int) - indice du tableau 
Paramètres : nomFic (char*) - nom du fichier 
			 nbJeux (int*) - nombre de jeux
Retours : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		  nbJeux (int*) - nombre de jeux
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
		fprintf(stderr, "Allocation mémoire impossible\n");
		exit(1);
	}

	for (i = 0; i < *nbjeux; i++) {
		tjeux[i] = (Jeu*)malloc(sizeof(Jeu));
		if (tjeux[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\n");
			exit(1);
		}
		jeu = lireJeu(fic);	
		*tjeux[i] = jeu;
	}
	
	return tjeux;
}

Adherent** chargementAdherent(char *nomFic, int *nbadherents) {
	Adherent** tadherents;
	Adherent adh;
	FILE* fic;
	int i;

	
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
	printf("2 - Affichage liste emprunts\n");
	printf("3 - Affichage liste réservations\n");
	printf("4 - Saisie emprunt ou réservation\n");
	printf("5 - Retour d'un jeu\n");	
	printf("6 - Annulation d'une réservation\n");
	printf("7 - Quitter\n");
	
	printf("Choix : ");
	scanf("%d%*c", &choix);
	while (choix < 1 || choix > 7) {
		printf("Choix : ");
	 	scanf("%d%*c", &choix);
	} 

	return choix;
}

/* 
Titre : programme
Finalité : application ludotheque
*/ 

void programme(void) {
	int choix;
	char c;

	// TODO - Chargement 

	choix = choixMenu();
	while (choix != 7) {

		printf("\nAppuyez sur une touche pour continuer");
		c = getchar();
		choix = choixMenu();
	}

	printf("\nAu revoir !\n");
}