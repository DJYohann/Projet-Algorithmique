#include "bibliotheque.h"

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