#include "bibliotheque.h"

void afficherJeu(Jeu jeu) {
	printf("%d\t%s\t%s\t%d\n", jeu.idJeu, jeu.nom, jeu.type, jeu.nbExemp);
}

void afficherAdherent(Adherent adh) {
	printf("%d\t\t%s\t\t%s\t%s\t%d/%d/%d\n", adh.idAdherent, adh.civilite, adh.nom, 
		adh.prenom, adh.dateInscription.jour, adh.dateInscription.mois, adh.dateInscription.annee);
}

void afficherEmprunt(Emprunt emp) {
	printf("%d\t\t%d\t\t%d\t%d/%d/%d\n", emp.idEmprunt, emp.idAdherent, emp.idJeu, 
		emp.dateEmprunt.jour, emp.dateEmprunt.mois, emp.dateEmprunt.annee);
}

void afficherReservation(Reservation res) {
	printf("%d\t\t%d\t\t%d\n", res.idReservation, res.idAdherent, res.idJeu);
}

void testLectureFichiers(void) {
	FILE *fjeux, *fadherents, *femprunts, *freservations;
	Jeu jeu;
	Adherent adh;
	Emprunt emp;
	Reservation res;

	fjeux = fopen("../Fichiers/jeux.don", "r");
	if (fjeux == NULL) {
		printf("Ouverture impossible\n");
	}

	fadherents = fopen("../Fichiers/adherents.don", "r");
	if (fadherents == NULL) {
		printf("Ouverture impossible\n");
	}

	femprunts = fopen("../Fichiers/emprunts.don", "r");
	if (femprunts == NULL) {
		printf("Ouverture impossible\n");
	}

	freservations = fopen("../Fichiers/reservations.don", "r");
	if (freservations == NULL) {
		printf("Ouverture impossible\n");
	}

	jeu = lireJeu(fjeux);
	adh = lireAdherent(fadherents);
	emp = lireEmprunt(femprunts);
	res = lireReservation(freservations);

	printf("ID Jeu\tNom\t\tType\tNb Exemplaires\n");

	afficherJeu(jeu);

	printf("\nID Adherent\tCivilité\tNom\tPrénom\tDate Inscription\n");

	afficherAdherent(adh);

	printf("\nID Emprunt\tID Adherent\tID Jeu\tDate Emprunt\n");

	afficherEmprunt(emp);

	printf("\nID Reservation\tID Adherent\tID Jeu\n");

	afficherReservation(res);
}

int main(int argc, char *argv[]) {
	testLectureFichiers();
	//programme();

	return EXIT_SUCCESS;
}
