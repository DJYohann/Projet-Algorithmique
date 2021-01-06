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

void testChargementFichiers(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichiers/adherents.don", 
	*ficemprunts = "../Fichiers/emprunts.don", *ficreservations = "../Fichiers/reservations.don";
	Jeu **tjeux;
	Adherent** tadherents;
	ListeEmp listempts;
	ListeRes listres;

	listempts = listeEmpruntsVide();
	listres = listeReservationsVide();

	int nbjeux = 0, nbadherents = 0, nbempts = 0, nbres = 0;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);
	listempts = chargementEmprunts(ficemprunts, listempts, &nbempts);
	listres = chargementReservations(ficreservations, listres, &nbres);

	afficherJeux(tjeux, nbjeux);
	printf("\n");
	afficherAdherents(tadherents, nbadherents);
	printf("\n");
	afficherEmprunts(listempts, nbempts);
	printf("\n");
	afficherReservations(listres, nbres);
	printf("\n");

	free(tjeux);
	free(tadherents);
}

int main(int argc, char *argv[]) {
	testChargementFichiers();
	//application();

	return EXIT_SUCCESS;
}
