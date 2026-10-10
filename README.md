# Kapture

**Kapture** est un jeu de stratégie au tour par tour pour **deux joueurs**, développé en **C++** et jouable dans un terminal. Chaque joueur commande ses unités sur un plateau de 10 × 10 cases pour capturer le drapeau adverse et le rapporter à la position de départ de l'une de ses unités.

Ce projet a été réalisé dans le cadre d'un travail universitaire de **conception orientée objet**, par **Vincent Tourenne et Antony Ferry**.

## Fonctionnalités

* **Trois types d'unités** : éclaireurs (*scouts*), unités d'élite et chair à canon (*fodder*), avec des déplacements et des interactions de combat différents.
* **Terrains variés** : cases libres, forêts et rivières, qui modifient le coût des déplacements.
* **Brouillard de guerre** : chaque joueur découvre progressivement les cases autour de ses unités.
* **Combats de proximité** : résolution des affrontements selon le type des unités, avec une part d'aléatoire dans certains cas.
* **Gestion des drapeaux** : capture, perte et retour possible à leur emplacement initial.
* **Configuration par fichier texte** : disposition du plateau, positions initiales des unités et des drapeaux.

## Installation et lancement

### Prérequis

* **Windows** ;
* **Visual Studio 2022**, avec les outils de développement C++ pour ordinateur de bureau (compilateur MSVC, plateforme `v143`).

### Démarrage

1. Ouvrir `Kapture-VTAF/Kapture-VTAF.sln` dans Visual Studio.
2. Sélectionner **Kapture-VTAF-App** comme projet de démarrage.
3. Compiler, puis lancer l'application.

Le dépôt contient un plateau d'exemple dans **`Kapture.txt`**. L'application utilise par défaut le chemin relatif `../../Kapture.txt`, depuis son répertoire de travail. Il est également possible de lui fournir un autre fichier de configuration en argument :

    Kapture-VTAF-App.exe chemin\vers\configuration.txt

> **Note :** le `Makefile` à la racine utilise d'anciens chemins et n'est pas à jour. La solution Visual Studio est la méthode de compilation prévue pour cette version.

## Comment jouer ?

Les deux joueurs jouent **à tour de rôle**, sur le même terminal. À son tour, un joueur peut déplacer ses unités tant que leur budget de mouvement le permet, puis passer la main.

| Commande | Action |
| --- | --- |
| `move` | Choisir une unité, puis une case de destination adjacente. |
| `endTurn` | Terminer son tour. |
| `3,4` | Exemple de saisie de coordonnées (ligne, colonne). |

Les **éclaireurs** disposent de 5 points de déplacement par tour, les **unités d'élite** de 3 et la **chair à canon** de 2. Se déplacer sur une case libre coûte 1 point, entrer en forêt coûte 2 points et entrer dans une rivière consomme le budget total de l'unité.

Pour gagner, une unité capable de transporter un drapeau doit **récupérer celui de l'adversaire et revenir à sa position initiale**.

## Organisation du projet

    Kapture-VTAF/
    ├── Kapture-VTAF-App/    # Point d'entrée de l'application
    ├── Kapture-VTAF-Lib/    # Plateau, joueurs, unités et logique de jeu
    └── Kapture-VTAF-Tests/  # Tests unitaires GoogleTest
    
    Kapture.txt               # Configuration d'exemple
    UML.png                   # Diagramme UML

L'implémentation sépare notamment le **chargement de la configuration** (`GameParser`), la **gestion de la partie** (`GameManager`) et son **affichage en console** (`Renderer`).

## Tests

Le projet contient des tests unitaires **GoogleTest** consacrés au plateau, aux joueurs, aux unités et au gestionnaire de partie. Ils se trouvent dans `Kapture-VTAF-Tests/` et peuvent être lancés depuis **l'Explorateur de tests de Visual Studio**, après restauration des dépendances NuGet si nécessaire.

## Démonstration

[Voir la vidéo de démonstration sur YouTube](https://youtu.be/urSONZGLyCU)

Le [diagramme UML](UML.png) est également disponible dans le dépôt.
