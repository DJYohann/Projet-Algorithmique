#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ludotheque.h"

void afficherJeu(Jeu jeu) {
	printf("%d\t%s\t%s\t%d\n", jeu.idJeu, jeu.nom, jeu.type, jeu.nbExemp);
}

void afficherJeux(Jeu **tjeux, int nbjeux) {
	int i;

	printf("Nb Jeux : %d\n", nbjeux);
	printf("ID Jeu\tNom\t\tType\tNb Exemplaire\n");
	for (i = 0; i < nbjeux; i++) {
		afficherJeu(*tjeux[i]);
	}
}

void afficherAdherent(Adherent adh) {
	printf("%d\t\t%s\t\t%s\t\t%s\t\t%d/%d/%d\n", adh.idAdherent, adh.civilite, adh.nom,
		adh.prenom, adh.dateInscription.jour, adh.dateInscription.mois, adh.dateInscription.annee);
}

void afficherAdherents(Adherent** tadherents, int nbadherents) {
	int i;

	printf("Nb Adherents : %d\n", nbadherents);
	printf("ID Adherent\tCivilité\tNom\t\t\tPrénom\t\t\tDate Inscription\n");
	for (i = 0; i < nbadherents; i++) {
		afficherAdherent(*tadherents[i]);
	}
}

void afficherEmprunt(Emprunt emp) {
	printf("%d %d %d %d/%d/%d\n", emp.idEmprunt, emp.idAdherent, emp.idJeu, emp.dateEmprunt.jour,
		emp.dateEmprunt.mois, emp.dateEmprunt.annee);
}

void afficherEmprunts(ListeEmp listemp, int nbempts) {
	printf("Nb Emprunts : %d\n", nbempts);
	printf("ID Emprunt\tID Adherent\tID Jeu\tDate Emprunt\n");

	while (listemp != NULL) {
		afficherEmprunt(listemp->emp);
		listemp = listemp->suiv;
	}
}

void afficherReservation(Reservation res) {
	printf("%d %d %d %d/%d/%d\n", res.idReservation, res.idAdherent, res.idJeu, res.dateReservation.jour,
		res.dateReservation.mois, res.dateReservation.annee);
}

void afficherReservations(ListeRes listres, int nbres) {
	printf("Nb Reservations : %d\n", nbres);
	printf("ID Reservation\tID Adherent\tID Jeu\tDate Reservation\n");

	while (listres != NULL) {
		afficherReservation(listres->res);
		listres = listres->suiv;
	}
}

void test(void) {
	char *ficjeux = "./src/files/jeux.don", *ficadherents = "./src/files/adherents.don",
	*ficemprunts = "./src/files/emprunts.don", *ficreservations = "./src/files/reservations.don";
	Jeu **tjeux;
	Adherent** tadherents;
	ListeEmp listempts;
	ListeRes listres;

	char nomJeu[30];
	int id;

	listempts = listeEmpruntsVide();
	listres = listeReservationsVide();

	int nbjeux = 0, nbadherents = 0, nbempts = 0, nbres = 0;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);
	listempts = chargementEmprunts(ficemprunts, listempts, &nbempts);
	listres = chargementReservations(ficreservations, listres, &nbres);

	triTabJeux(tjeux, nbjeux);

	afficherJeux(tjeux, nbjeux);
	printf("\n");
	afficherAdherents(tadherents, nbadherents);
	printf("\n");
	afficherEmprunts(listempts, nbempts);
	printf("\n");
	afficherReservations(listres, nbres);
	printf("\n");

	printf("Nom du jeu : ");
	fgets(nomJeu, 30, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';

	id = rechercheIdJeu(tjeux, nomJeu, nbjeux);
	printf("ID : %d\n", id);

	free(tjeux);
	free(tadherents);
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Argument manquant\ntest pour tester\nmain pour lancer le programme\n");
		return EXIT_FAILURE;
	} else {
		if (strcmp(argv[1], "test") == 0) {
			test();
			return EXIT_SUCCESS;
		} else if (strcmp(argv[1], "main") == 0) {
			application();
			return EXIT_SUCCESS;
		} else {
			fprintf(stderr, "Argument non existant\ntest pour tester\nmain pour lancer le programme\n");
			return EXIT_FAILURE;
		}
	}
}
