# Projet C++ de construction d'un labyrinthe aléatoire à resoudre.

## Description

Pour la génération du labyrinthe, de dimensions à choisie par l'utilisateur, on se base sur l'algorithme de parcours en profondeur (Depth First Search - DFS) suivi d'une supression partielle de murs afin de créer de la complexité avec des cycles.
Un affichage ASCII en terminal est proposé, et pour la partie jouable par l'utilisateur, un affichage graphique en utilisant la bibliothèque SFML. 
Dans la fenetre SFML, il est possible d'afficher le chemin le plus court, calculé à l'aide de l'algorithme A* (une variante de l'algorithme de Djikstra).
En plus, un chronometre est affiché afin de mésurer le temps écoulé entre le départ de la premiere cellule et l'arrivée à la cellule finale.

## Structure
Le projet a les dossier suivants:
 - src/ - le code source dans des fichiers .cpp
 - include/ - fichiers d'en-tête .hpp
 - assets/ - contient la police arial.ttf utilisée par SFML

## Prérequis

- Un compilateur C++ compatible **C++17** (clang++, g++, MSVC)
- **CMake ≥ 3.15**
- **SFML 3** avec les modules :
  - Graphics
  - Window
  - System
- Une police TrueType : `arial.ttf` (fournie dans `assets/`)

### Optionnel
- **Catch2** (uniquement pour compiler et exécuter les tests unitaires)

### Remarques
- SFML 2.x n’est pas supportée
- Aucun autre framework graphique n’est requis

## Build

On build ce projet avec CMake. Les etapes pour ce build sont :
 - 1 : Creer un dossier build 
```bash
    mkdir build
```
 - 2 : Se placer dans le dossier build
```bash
    cd build
```
 - 3 : Générer avec Cmake les fichiers de build
```bash
    cmake ..
```
 - 4 : Compiler
```bash
    make
```

Une fois ces etapes completes, on aura dans le dossier build les trois executables suivants :

 - maze_terminal : affichage ASCII dans le terminal du maze généré aléatoirement
 - sfml_window : simple affichage en fenetre SFML
 - sfml_game : un jeu où l'utilisateur doit résoudre le labyrinthe; la touche 'h' (pour hint) affiche la solution optimale.

## Utilisation

On compile depuis le dossier build avec la commande 
```bash
    ./nom_de_lexecutable.
```
Ensuite, l'utilisateur doit entrer le nombre de lignes et de colonnes du labyrinthe (entiers positifs).

## Specificité

### Génération du labyrinthe
L'algorithme DFS recursive backtrakcer crée à partir d'une grille remplie de murs un chemin entre le point de départ (en haut à gauche) et le point d'arrivée (en bas à droite). 
Il fonctionne en explorerant récursivement des voisins non visités choisis aléatoirement, en supprimant les murs entre les cellules connectées.
Lorsqu’une cellule n’a plus de voisins disponibles, l’algorithme revient en arrière grâce à une pile jusqu’à trouver une nouvelle cellule à explorer, garantissant que toutes les cellules sont visitées et que le labyrinthe est entièrement connexe.
Une fois ce labyrinthe parfait construit, une partie (20 pourcent) des murs situés près des culs-de-sac est supprimée aléatoirement afin d’introduire des cycles et de réduire le nombre de chemins sans issue et finalement rendre le labyrinthe plus difficile à résoudre.

### Résolution du labyrinthe

Pour la résolution du labyrinthe on a implémenté deux algorithmes : A* et Trémaux.
La solution qui s'affiche dans le jeu SFML à l'aide du clé 'h' est calculé avec A* puisque l'algorithme de Trémaux explore le labyrinthe sans évaluer la qualité globale des chemins, et donc peut conduire à des détours inutiles.

#### Algorithme A*
Cet algorithme est une variation de Djikstra mais avec une distance heuristique - ici la métrique Manhattan. 
Il explore les cellules en priorité selon un coût estimé combinant la longueur du chemin déjà parcouru et cette distance de Manhattan jusqu’à la sortie.
À chaque étape, A* sélectionne la cellule la plus prometteuse dans une file de priorité (un 'priority_queue'), met à jour les distances minimales connues et mémorise le prédécesseur de chaque cellule afin de reconstruire le chemin optimal.
Lorsque la cellule de sortie est atteinte, le chemin le plus court est reconstruit en remontant les prédécesseurs depuis la sortie jusqu’à l’entrée.

#### Algorithme de Trémaux
On explore le labyrinthe en profondeur à l’aide d’une pile en avançant vers des cellules accessibles encore non visitées.
Lorsqu’aucun mouvement n’est possible depuis une cellule, Trémaux effectue un retour en arrière (backtracking) en dépilant la position courante pour rechercher un autre chemin.
Le processus se poursuit jusqu’à atteindre la sortie, produisant un chemin valide entre l’entrée et la sortie, sans garantir l’optimalité du chemin mais avec une exploration systématique.


## Authors : BURNS Thomas et FISK Thomas

### Mail : thomas.fisk15@gmail.com 

### Github : tfisk98  


  
