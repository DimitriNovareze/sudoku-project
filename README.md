# Description

Ce projet est un jeu de Sudoku développé en C++, avec une interface graphique. Il permet aux utilisateurs de jouer au Sudoku, de choisir différents niveaux de difficulté, de vérifier leurs progrès et de voir la solution du puzzle.

## Fonctionnalités
* Choix de la difficulté : Les joueurs peuvent choisir le niveau de difficulté du puzzle Sudoku parmi quatre options :
Facile, Intermédiaire, Difficile et Extrême.
* Un bouton "Solution" est disponible pour afficher la solution complète du puzzle actuel à tout moment.
* Un bouton "Vérifier" permet aux joueurs de vérifier s'ils ont bien progressé sans révéler la solution entière. Si un chiffre placé ne viole pas les règles du Sudoku, il ne sera pas indiqué comme incorrect, même s'il ne correspond pas à la solution. Cela évite de révéler la solution lors de la vérification.
* Un bouton "Réinitialiser" permet de recommencer le puzzle, en effaçant toutes les entrées précédentes et en repartant de zéro.
Un chronomètre est situé en haut de la fenêtre, vous permettant de voir combien de temps vous avez mis pour résoudre le Sudoku. Un message de réussite apparaît à la fin du jeu.
* Un bouton "Sauvegarder" a été ajouté, permettant à l'utilisateur de sauvegarder une partie pour y revenir plus tard. Notez que les coups joués avant la sauvegarde ne pourront plus être modifiés lorsque vous chargerez la partie sauvegardée.
* Des couleurs ont été ajoutées pour simplifier la visualisation de la ligne, de la colonne et du carré de la case sélectionnée. Si vous appuyez sur une case déjà remplie, vous verrez en couleurs les autres cases contenant le même chiffre.

## Installation

Pour lancer le jeu Sudoku, suivez ces étapes :

* Téléchargez le fichier principal (zip) puis extrayez son contenu.
* Assurez-vous que le dossier contenant les fichiers s'appelle "sudoku-main".
* Ouvrez le projet avec Qt pour le construire et l'exécuter.
* Pour jouer, il vous suffit de sélectionner une case avec votre souris et d'entrer un chiffre. Vous pouvez effacer un chiffre en appuyant sur la touche "Retour arrière" de votre clavier.