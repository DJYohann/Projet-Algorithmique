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
Titre : chargementJeux
Finalité : charger en mémoire le fichier des jeux
Variables : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
            jeu (Jeu) - structure Jeu
            fic (FILE*) - fichier de jeux
            i (int) - indice du tableau 
Paramètres : nomFic (char*) - nom du fichier 
			 nbjeux (int*) - nombre de jeux
Retours : tjeux (Jeu**) - tableau de pointeur sur la structure Jeu
		  nbjeux (int*) - nombre de jeux
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
	
	fclose(fic);
	return tjeux;
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
Titre : chargementAdherents
Finalité : charger en mémoire le fichier des adhérents
Variables : tadherents (Adherent**) - tableau de pointeur sur la structure Adherent
            adh (Adherent) - structure Adherent
            fic (FILE*) - fichier des adhérents
            i (int) - indice du tableau 
Paramètres : nomFic (char*) - nom du fichier 
			 nbadherents (int*) - nombre d'adhérents
Retours : tjeux (Jeu**) - tableau de pointeur sur la structure Adherent
		  nbadherents (int*) - nombre d'adhérents
*/

Adherent** chargementAdherents(char *nomFic, int *nbadherents) {
	Adherent** tadherents;
	Adherent adh;
	FILE* fic;
	int i;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	fscanf(fic, "%d", nbadherents);

	tadherents = (Adherent**)malloc(*nbadherents * sizeof(Adherent));
	if (tadherents == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\n");
		exit(1);
	}

	for (i = 0; i < *nbadherents; i++) {
		tadherents[i] = (Adherent*)malloc(sizeof(Adherent));
		if (tadherents[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\n");
			exit(1);
		}
		adh = lireAdherent(fic);	
		*tadherents[i] = adh;
	}

	fclose(fic);
	return tadherents;
}

/* 
Titre : intialiserEmprunts
Finalité : initialiser la liste chaînée des emprunts
Variable : listemp (Emprunts) - liste chaînée des emprunts
Retour : listemp (Emprunts) - liste chaînée des emprunts
*/

Emprunts initialiserEmprunts(void) {
	Emprunts listemp = NULL;

	return listemp;
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
Titre : insererEnTete
Finalité : insérer en tête de liste un emprunt
Variable : e (Emprunts*) - 
Paramètres : listemp (Emprunts) - 
			 emp (Emprunt) - 
Retour : e (Emprunts*) - 
*/

Emprunts insererEnTeteEmp(Emprunts listemp, Emprunt emp) {
	Emprunt *e;

	e = (Emprunt*)malloc(sizeof(Emprunt));
	if (e == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\n");
		exit(1);
	}

	e->idEmprunt = emp.idEmprunt;
	e->idAdherent = emp.idAdherent;
	e->idJeu = emp.idJeu;
	e->dateEmprunt.jour = emp.dateEmprunt.jour;
	e->dateEmprunt.mois = emp.dateEmprunt.mois;
	e->dateEmprunt.annee = emp.dateEmprunt.annee;
	e->suiv = listemp;

	return e;
}

/*
Titre : inserer
Finalité : insérer dans la liste un emprunt
Paramètres : listemp (Emprunts) - 
             emp (Emprunt) - 
Retour : listemp (Emprunts) - 
*/

Emprunts insererEmp(Emprunts listemp, Emprunt emp) {
	if (listemp == NULL) {
		return insererEnTeteEmp(listemp, emp);
	}

	if (emp.dateEmprunt.mois < listemp->dateEmprunt.mois) {
		return insererEnTeteEmp(listemp, emp);
	}

	if (emp.dateEmprunt.annee == listemp->dateEmprunt.annee && emp.dateEmprunt.mois == listemp->dateEmprunt.mois && emp.dateEmprunt.jour == listemp->dateEmprunt.jour) {
		return insererEnTeteEmp(listemp, emp);
	}

	listemp->suiv = insererEmp(listemp->suiv, emp);

	return listemp;
}

/*
Titre : chargementEmprunts
Finalité : charger en mémoire le fichier des emprunts
Variables : emp (Emprunt) - 
            fic (FILE*) - 
            nbemp (int) - 
Paramètres : nomFic (char*) - nom du fichier 
			 listemp (Emprunts) - 
Retour : listemp (Emprunts) -
*/

Emprunts chargementEmprunts(char *nomFic, Emprunts listemp, int *nbemp) {
	Emprunt emp;
	FILE* fic;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	emp = lireEmprunt(fic);
	while(!feof(fic)) {
		listemp = insererEmp(listemp, emp);
		(*nbemp)++;
		emp = lireEmprunt(fic);
	}

	fclose(fic);
	return listemp;
}

/* 
Titre : intialiserReservations
Finalité : initialiser la liste chaînée des réservations
Variable : listres (Reservations) - liste chaînée des réservations
Retour : listres (Reservations) - liste chaînée des réservations
*/

Reservations intialiserReservations(void) {
	Reservations listres = NULL;

	return listres;
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
Titre : 
Finalité : 
*/

Reservations insererEnTeteRes(Reservations listres, Reservation res) {
	Reservation *r;

	r = (Reservation*)malloc(sizeof(Reservation));
	if (r == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\n");
		exit(1);
	}

	r->idReservation = res.idReservation;
	r->idAdherent = res.idAdherent;
	r->idJeu = res.idJeu;
	r->suiv = listres;

	return r;
}

/*
Titre : 
Finalité : 
*/

// Reservations insererRes (Reservations listres, Reservation res) {

// }

/*
Titre : 
Finalité : 
*/

Reservations chargementReservations(char *nomFic, Reservations listres, int *nbres) {
	Reservation res;
	FILE* fic;

	fic = fopen(nomFic, "r");
	if (fic == NULL) {
		fprintf(stderr, "Ouverture du fichier %s impossible\nFichier %s ligne %d\n", nomFic, __FILE__,  __LINE__);
		exit(1);
	}

	res = lireReservation(fic);
	while (!feof(fic)) {
		listres = insererEnTeteRes(listres, res);
		(*nbres)++;
		res = lireReservation(fic);
	}

	fclose(fic);
	return listres;
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
	printf("2 - Affichage emprunts en cours\n");
	printf("3 - Affichage réservations pour un jeu\n");
	printf("4 - Saisie emprunt\n");
	printf("5 - Saisie réservation\n");
	printf("6 - Retour d'un jeu\n");	
	printf("7 - Annulation d'une réservation\n");
	printf("8 - Quitter\n");
	
	printf("Choix : ");
	scanf("%d%*c", &choix);
	while (choix < 1 || choix > 8) {
		printf("Choix : ");
	 	scanf("%d%*c", &choix);
	} 

	return choix;
}

/* 
Titre : programme
Finalité : application ludotheque
Variables : 
Paramètres : 
*/ 

void programme(void) {
	int choix;
	char c;

	// TODO - Chargement 

	choix = choixMenu();
	while (choix != 8) {

		printf("\nAppuyez sur une touche pour continuer");
		c = getchar();
		choix = choixMenu();
	}

	printf("\nAu revoir !\n");
}