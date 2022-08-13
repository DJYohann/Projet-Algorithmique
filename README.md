# Projet-Algorithmique

## Présentation

Projet de première année pour s'exercer aux compétences d'algorithmique et de structure de données en langage [C](https://fr.cppreference.com/w/c)

## Sujet 

[sujet.pdf](./docs/sujet.pdf)

## Fonctionnalités 

1. chargement des quatre fichiers en mémoire
2. affichage de la liste des jeux disponibles triée par type de Jeux, puis par ordre alphabétique de leur nom
3. affichage de la liste des emprunts en cours en mentionnant : le nom du jeu, l’identité de l’emprunteur ainsi que la date de l’emprunt ;
4. affichage de la liste des réservations pour un jeu donné ;
5. saisie et enregistrement d’un nouvel emprunt ou d’une réservation
	* création de l’adhérent si nouveau (avec contrôle de saisie) ;
	* enregistrement de l’emprunt ou de la réservation si possible ;
6. retour d’un jeux. 
	* retour déclenche l’examen des réservations pour peut être transformer une réservation en emprunt et faire parvenir le jeu à l’adhérent l’ayant réservé.
7. annulation d’une réservation (l’adhérent a changé d’avis , il ne désire plus réserver le jeux)
8. sauvegarde de l’ensemble des données dans les quatre fichiers.

## Utilisation

Au point d'entrée du dépôt

### Compilation 

```
make
```

### Éxecution

```
./src/prog argument
```

argument : 

* test : tester le programme
* main : lancer le programme

### Nettoyage 

```
make clean
```

## Auteurs

* [Loris CHAPON](https://github.com/Loris-Chapon)
* [Étienne CELLIER](https://github.com/etcllr)
* [Yohann BREUIL](https://github.com/DJYohann)