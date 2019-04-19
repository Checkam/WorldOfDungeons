# WorldOfDungeons
Projet de L2 Informatique fait en C dans le cadre d'un module.  
Son objectif est de concevoir un Survival Game en 2D. Il s'agit d'un jeu de type Bac à Sable.

## Auteurs
Maxence Despres, Mathieu Vaudeleau, Tibane et Jasmin Galbrun

## Fait Avec
* [VSCode](https://code.visualstudio.com/) - Editeur de texte
* [Atom](https://atom.io/) - Editeur de texte

## Inspiration
* [Minecraft](https://www.minecraft.net/fr-fr/)
* [Terraria](https://terraria.org/)


# Installation

## Prérequis
- Système Unix
- La librairie SDL2

## Systeme verifiée :
- Ubuntu 18.04

#### Installation de la SDL2 sur Linux

Commande à éxecuter dans un terminal.
```shell
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

## Clonage du jeu
Récupérer le dépôt Git :
```shell
git clone https://github.com/Checkam/WorldOfDungeons
```

## Compilation du jeu
Ouvrir un terminal et se placer dans le dossier du jeu.

Pour accéder aux options de compilation :
```shell
make help
```

Pour compiler le jeu :
```shell
make clean all
```

Pour compiler les tests :
```shell
make clean test
```
Les éxecutables se trouvent dans le dossier bin/
