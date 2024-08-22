# Projet Sokoban


Projet pour Techniques de Développement pour la L2S3 Informatique à Strasbourg.

### Version gcc
+ git version 2.37.1 (Apple Git-137.1)

### Principe du jeu

- Sokoban est un jeu de réflexion. Le but est de ranger les caisses sur des emplacements.  
- Le joueur peut uniquement pousser une caisse à la fois.
- Le joueur peut traverser les goals.
- Le niveau est gagné lorsque le joueur a mis une caisse sur tous les emplacements.
- Le joueur peut se déplacer avec les touches **h** (_gauche_), **j** (_bas_), **k** (_haut_) **l** (_droite_). 
- Pour quitter le jeu, tapez **q**.

**Interface console**

- Chaque symbole représente un élément:
    + **#** : mur
    + **@** : joueur
    + **$** : boîte
    + **.** : goal où mettre une boîte
    + **\*** : boîte sur un goal
    + **+** : joueur sur un goal

