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

void afficherEmprunts(Emprunts listemp, int nbempts) {
	printf("Nb Emprunts : %d\n", nbempts);
	printf("ID Emprunt\tID Adherent\tID Jeu\tDate Emprunt\n");

	while (listemp != NULL) {
		printf("%d\t%d\t%d\t%d/%d/%d\n", listemp->idEmprunt, listemp->idAdherent, listemp->idJeu, 
			listemp->dateEmprunt.jour, listemp->dateEmprunt.mois, listemp->dateEmprunt.annee);
		listemp = listemp->suiv;
	}
}

void afficherReservations(Reservations listres, int nbres) {
	printf("Nb Adherents : %d\n", nbres);
	printf("ID Reservation\tID Adherent\tID Jeu\n");

	while (listres != NULL) {
		printf("%d %d %d\n", listres->idReservation, listres->idAdherent,listres->idJeu);
		listres = listres->suiv;
	}
}

void testChargementFichiers(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichiers/adherents.don", 
	*ficemprunts = "../Fichiers/emprunts.don", *ficreservations = "../Fichiers/reservations.don";
	Jeu **tjeux;
	Adherent** tadherents;
	Emprunts listempts;
	Reservations listres;

	Emprunt emp;
	FILE* fic;

	listempts = initialiserEmprunts();
	listres = intialiserReservations();

	int nbjeux = 0, nbadherents = 0, nbempts = 0, nbres = 0;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);
	listempts = chargementEmprunts(ficemprunts, listempts, &nbempts);
	listres = chargementReservations(ficreservations, listres, &nbres);

	afficherJeux(tjeux, nbjeux);
	afficherAdherents(tadherents, nbadherents);
	afficherEmprunts(listempts, nbempts);
	afficherReservations(listres, nbres);

	free(tjeux);
	free(tadherents);
}

int main(int argc, char *argv[]) {
	testChargementFichiers();
	//programme();

	return EXIT_SUCCESS;
}
