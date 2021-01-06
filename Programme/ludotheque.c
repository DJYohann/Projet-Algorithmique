#include "ludotheque.h"

/* 
Titre : lireJeu
Finalité : lire un jeu dans un flot donné
Variable : jeu (Jeu) - structure Jeu
Paramètre : flot (FILE*) - flot de lecture
Retour : jeu (Jeu) - structure Jeu
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
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	for (i = 0; i < *nbjeux; i++) {
		tjeux[i] = (Jeu*)malloc(sizeof(Jeu));
		if (tjeux[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
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
Variable : adh (Adherent) - structure Adherent
Paramètre : flot (FILE*) - flot de lecture
Retour : adh (Adherent) - structure Adherent
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
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	for (i = 0; i < *nbadherents; i++) {
		tadherents[i] = (Adherent*)malloc(sizeof(Adherent));
		if (tadherents[i] == NULL) {
			fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
			exit(1);
		}
		adh = lireAdherent(fic);	
		*tadherents[i] = adh;
	}

	fclose(fic);
	return tadherents;
}

/* 
Titre : listeEmpruntsVide
Finalité : créer une liste chaînée de structure Emprunt vide
Variable : listemp (ListeEmp) - liste chaînée de structure Emprunt
Retour : listemp (ListeEmp) - liste chaînée de structure Emprunt
*/

ListeEmp listeEmpruntsVide(void) {
	return NULL;
}

/* 
Titre : lireEmprunt
Finalité : lire un emprunt dans un flot donné
Variable : emp (Emprunt) - structure Emprunt
Paramètre : flot (FILE*) - flot de lecture
Retour : emp (Emprunt) - structure d'Emprunt
*/

Emprunt lireEmprunt(FILE* flot) {
	Emprunt emp;

	fscanf(flot, "%d %d %d %d/%d/%d", &emp.idEmprunt, &emp.idAdherent, &emp.idJeu, 
		&emp.dateEmprunt.jour, &emp.dateEmprunt.mois, &emp.dateEmprunt.annee);

	return emp;
}

/*
Titre : insererEnTeteEmp
Finalité : insérer en tête de liste un emprunt
Variable : e (MaillonEmp*) - pointeur sur un maillon de la liste 
Paramètres : listemp (ListeEmp) - liste chaînée de structure Emprunt
			 emp (Emprunt) - structure Emprunt
Retour : e (Emprunt*) - pointeur sur un maillon de structure Emprunt
*/

ListeEmp insererEnTeteEmp(ListeEmp listemp, Emprunt emp) {
	MaillonEmp *m;

	m = (MaillonEmp*)malloc(sizeof(MaillonEmp));
	if (m == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	m->emp = emp;
	m->suiv = listemp;

	return m;
}

/*
Titre : insererEmp
Finalité : insérer dans la liste un emprunt
Paramètres : listemp (Emprunts) - liste chaînée de structure Emprunt
             emp (Emprunt) - structure Emprunt
Retour : listemp (Emprunts) - liste chaînée de structure Emprunt
*/

ListeEmp insererEmp(ListeEmp listemp, Emprunt emp) {
	if (listemp == NULL) {
		return insererEnTeteEmp(listemp, emp);
	}

	if (emp.dateEmprunt.mois < (listemp->emp).dateEmprunt.mois) {
		return insererEnTeteEmp(listemp, emp);
	}

	// if (emp.dateEmprunt.annee == listemp->emp.dateEmprunt.annee && emp.dateEmprunt.mois == listemp->emp.dateEmprunt.mois && emp.dateEmprunt.jour == listemp->emp.dateEmprunt.jour) {
	// 	return insererEnTeteEmp(listemp, emp);
	// }

	listemp->suiv = insererEmp(listemp->suiv, emp);

	return listemp;
}

/*
Titre : chargementEmprunts
Finalité : charger en mémoire le fichier des emprunts
Variables : emp (Emprunt) - structure Emprunt
            fic (FILE*) - fichier des emprunts
Paramètres : nomFic (char*) - nom du fichier 
			 listemp (Emprunts) - liste chaînée de structure Emprunt
			 nbemp (int*) - nombre d'emprunts
Retour : listemp (Emprunts) - liste chaînée de structure Emprunt
*/

ListeEmp chargementEmprunts(char *nomFic, ListeEmp listemp, int *nbemp) {
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
Variable : listres (Reservations) - liste chaînée de structure Reservation
Retour : listres (Reservations) - liste chaînée de structure Reservation
*/

ListeRes listeReservationsVide(void) {
	return NULL;
}

/* 
Titre : lireReservation
Finalité : lire une réservation dans un flot donné
Variable : res (Reservation) - structure Reservation
Paramètre : flot (FILE*) - flot de lecture
Retour : res (Reservation) - structure Reservation
*/

Reservation lireReservation(FILE* flot) {
	Reservation res;

	fscanf(flot, "%d %d %d %d/%d/%d", &res.idReservation, &res.idAdherent, &res.idJeu, 
		&res.dateReservation.jour, &res.dateReservation.mois, &res.dateReservation.annee);

	return res;
}

/*
Titre : insererEnTeteRes
Finalité : insérer en tête de liste une réservation
Variable : r (Reservation*) - pointeur sur maillon de structure Reservation
Paramètres : listres (Reservations) - liste chaînée de structure Reservation
 			 res (Reservation) - structure Reservation
Retour : r (Reservation*) - pointeur sur maillon de structure Reservation
*/

ListeRes insererEnTeteRes(ListeRes listres, Reservation res) {
	MaillonRes *m;

	m = (MaillonRes*)malloc(sizeof(MaillonRes));
	if (m == NULL) {
		fprintf(stderr, "Allocation mémoire impossible\nFichier %s ligne %d", __FILE__, __LINE__);
		exit(1);
	}

	m->res = res;
	m->suiv = listres;

	return m;
}

/*
Titre : insererRes
Finalité : insérer dans la liste une réservation
Paramètres : listemp (Reservations) - liste chaînée de structure Reservation
             emp (Reservation) - structure Reservation
Retour : listemp (Reservations) - liste chaînée de structure Reservation
*/

// TODO
// Reservations insererRes (Reservations listres, Reservation res) {

// }

/*
Titre : chargementReservations
Finalité : charger en mémoire le fichier des réservations
Variables : res (Reservation) - structure Reservation
            fic (FILE*) - fichier des réservations
Paramètres : nomFic (char*) - nom du fichier 
			 listres (Reservations) - liste chaînée de structure Reservation
			 nbemp (int*) - nombre de réservations
Retour : listres (Reservations) - liste chaînée de structure Reservation
*/

ListeRes chargementReservations(char *nomFic, ListeRes listres, int *nbres) {
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
Titre : rechercheJeu
Finalité : rechercher un jeu avec le nom et renvoyer son identifiant
Variable : i (int) - indice du tableau
Paramètres : tjeux (Jeu**) - 
		     nomJeu (char*) - 
		     nbjeux (int) - 
Retour : idJeu (int) - 
*/

int rechercheJeu(Jeu *tjeux[], char *nomJeu, int nbjeux) {
	int i;

	for (i = 0; i < nbjeux; i++) {
		if (strcmp(tjeux[i]->nom, nomJeu) == 0) {
			return tjeux[i]->idJeu;
		}
	}

	return -1;
}

/* 
Titre : rechercheDichoAdherent
Finalité : rechercher un adhérent avec l'identifiant et renvoyer l'indice 
Variable : deb (int) - 
		   mil (int) - 
		   fin (int) -
Paramètres : tadh (Adherent**) - 
             idAdherent (int) - 
             nbadherents (int) -
Retour : mil - (int)
*/

int rechercheDichoAdherent(Adherent *tadh[], int idAdherent, int nbadherents) {
	int deb = 0, mil, fin = nbadherents - 1;

	while (deb <= fin) {
		mil = (deb + fin) / 2;

		if (idAdherent == tadh[mil]->idAdherent) {
			return mil;
		}

		if (idAdherent <= tadh[mil]->idAdherent) {
			fin = mil - 1;
		} else {
			deb =mil +1;
		}
	}

	return deb;
}

/* 
Titre : affichagReservationJeu
Finalité : afficher la liste de réservation pour un jeu donné
Variables : nomJeu (char*) - 
            idJeu (int) -
            pos (int) - 
Paramètre : listres (Reservations) - liste chaînée de structure Reservation
            tjeux (Jeu**) -
            tadh (Adherent**) -
            nbjeux (int) - 
            nbadherents (int) -  
*/

void affichagReservationJeu (ListeRes listres, Jeu *tjeux[], Adherent *tadh[], int nbjeux, int nbadherents) {
	char nomJeu[30];
	int idJeu, pos;

	printf("Nom du jeu : ");
	fgets(nomJeu, 31, stdin);
	nomJeu[strlen(nomJeu) - 1] = '\0';

	idJeu = rechercheJeu(tjeux, nomJeu, nbjeux);
	if (idJeu == -1) {
		printf("\nJeu non existant\n");
	} else {
		printf("\nRéservations pour le jeu : %s\n", nomJeu);
		printf("Nom\t\tPrenom\t\tDate Reservation\n");
		while (listres != NULL) {
			if (idJeu == listres->res.idJeu) {
				pos = rechercheDichoAdherent(tadh, listres->res.idAdherent, nbadherents);
				printf("%s\t\t%s\t\t%d/%d/%d\n", tadh[pos]->nom, tadh[pos]->prenom, listres->res.dateReservation.jour, 
					listres->res.dateReservation.mois, listres->res.dateReservation.annee);
			}
			listres = listres->suiv;
		}
	} 
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
Titre : application
Finalité : application de la gestion de prêts de jeux de la ludothèque
Variables : 
*/ 

void application(void) {
	char *ficjeux = "../Fichiers/jeux.don", *ficadherents = "../Fichiers/adherents.don", 
	*ficemprunts = "../Fichiers/emprunts.don", *ficreservations = "../Fichiers/reservations.don";

	Jeu **tjeux;
	Adherent** tadherents;
	ListeEmp listempts = listeEmpruntsVide();
	ListeRes listres = listeReservationsVide();

	int nbjeux = 0, nbadherents = 0, nbempts = 0, nbres = 0, choix;
	char c;

	tjeux = chargementJeux(ficjeux, &nbjeux);
	tadherents = chargementAdherents(ficadherents, &nbadherents);
	listempts = chargementEmprunts(ficemprunts, listempts, &nbempts);
	listres = chargementReservations(ficreservations, listres, &nbres);

	choix = choixMenu();
	while (choix != 8) {
		switch(choix) {
			case 1: 
				
				break;
			case 2: 
				
				break;
			case 3: 
				affichagReservationJeu(listres, tjeux, tadherents, nbjeux, nbadherents);
				break;
			case 4: 
				
				break;
			case 5: 
				
				break;
			case 6: 
				
				break;
			case 7: 
				
				break;
			default:
				
				break;
		}
		printf("\nAppuyez sur une touche pour continuer");
		c = getchar();
		choix = choixMenu();
	}

	printf("\nAu revoir !\n");

	free(tjeux);
	free(tadherents);
}