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
	printf("%d\t\t%d\t\t%d\t%d/%d/%d\n", emp.idEmprunt, emp.idAdherent, emp.idJeu, 
		emp.dateEmprunt.jour, emp.dateEmprunt.mois, emp.dateEmprunt.annee);
}

void afficherReservation(Reservation res) {
	printf("%d\t\t%d\t\t%d\n", res.idReservation, res.idAdherent, res.idJeu);
}

void testChargementFichiers(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichiers/adherents.don";
	Jeu **tjeux;
	Adherent** tadherents;

	int nbjeux, nbadherents, i;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);

	afficherJeux(tjeux, nbjeux);
	afficherAdherents(tadherents, nbadherents);

	free(tjeux);
	free(tadherents);
}

int main(int argc, char *argv[]) {
	//testChargementFichiers();
	programme();

	return EXIT_SUCCESS;
}
