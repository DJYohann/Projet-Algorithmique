#include "ludotheque.h"

void afficherJeu(Jeu jeu) {
	printf("%d\t%s\t%s\t%d\n", jeu.idJeu, jeu.nom, jeu.type, jeu.nbExemp);
}

void afficherJeux(Jeu **tjeux, int nbjeux) {
	int i; 

	printf("Nb Jeux : %d\n", nbjeux);
	printf("ID Jeu\tNom\tType\tNb Exemplaire\n");
	for (i = 0; i < nbjeux; i++) {
		afficherJeu(*tjeux[i]);
	}
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

void testChargementFichiers(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichier/adherents.don";
	Jeu **tjeux;

	int nbjeux, i;

	tjeux = chargementJeux(ficjeux, &nbjeux);

	afficherJeux(tjeux, nbjeux);

	free(tjeux);
}

int main(int argc, char *argv[]) {
	testChargementFichiers();
	//programme();

	return EXIT_SUCCESS;
}
