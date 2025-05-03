#include "damiersudoku.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



DamierSudoku::DamierSudoku(QObject *parent) : QObject(parent) {
    std::cout<<"constructeur"<<std::endl;
    std::string filename("grilles/grilleDebutant.csv");
    for (int i = 0; i < 9; ++i) {
        QList<QString> row;
        for (int j = 0; j < 9; ++j) {
            damier[i][j] = 0; // Initialisation avec des cases vides
            row.append("white"); // Ajouter la couleur blanche à chaque case
        }
        colors.append(row);//Comme on met tout en blanc, pas besoin de faire un ordre bizarr..
    }
    std::cout<<"constructeur"<<std::endl;
    matriceToVectors();
    emit valChanged(); // Émet le signal indiquant que les valeurs ont été mises à jour
}

void DamierSudoku::init(int val) {
    set_grille(val);
    matriceToVectors();
    emit valChanged();
}
/* Si la gestion de csv ne marche pas, commenter la fonction précédente et utiliser ça
void DamierSudoku::init(int val) {
    set_grille(val);
    std::istringstream iss(grille);
    std::string ligne;
    int i = 0;

    while (std::getline(iss, ligne, ' ')) { // Séparer la chaîne par les espaces
        int j=0;
        for (int j_ligne=0; j_ligne<ligne.size(); j_ligne++) {
            switch(ligne[j_ligne]){
            case '9' :
                damier[i][j] = 9;
                std::cout<<damier[i][j]<<std::endl;
                j++;
                break;
            case '8': //Un switch sur ligne[j_ligne serai plus élégant
                damier[i][j] = 8;
                j++;
                break;
            case '7' :
                damier[i][j] = 7;
                j++;
                break;
            case '6' :
                damier[i][j] = 6;
                j++;

                break;

            case '5' :
                damier[i][j] = 5;
                j++;
                break;
            case '4' :
                damier[i][j] = 4;
                j++;
                break;

            case '3' :
                damier[i][j] = 3;
                j++;
                break;

            case '2' :
                damier[i][j] = 2;
                j++;
                break;

            case '1' :
                damier[i][j] = 1;
                j++;
                break;

            case '.' :
                damier[i][j] = 0;
                j++;
                break;
            //else if (ligne[j_ligne] == '|') {
            //  std::cout<<"rien à faire"<<std::endl;
            //}

        }
        }
        i++;
    }
    matriceToVectors();
    emit valChanged();
}*/

int DamierSudoku::GetValeur(int i, int j)  {
    return damier[i][j];
}

void DamierSudoku::Set(int i, int j, int valeur) {
    if (i < 0 || i >= 9 || j < 0 || j >= 9) {
        throw std::invalid_argument("Indices out of bounds.");
    }
    if (valeur<0 || valeur > 9) {
        throw std::invalid_argument("Value out of bounds.");
    }
    damier[i][j] = valeur;

}


int DamierSudoku::lire_grille(std::string level_grille){
    std::ifstream myFile(level_grille); //charger la grille ici

    int i = 0;
    if (!myFile.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier." << std::endl;
        return 0;// Quitte le programme avec un code d'erreur
    }

    std::string ligne1;
    std::string ligne[9];

    getline(myFile,ligne1,'\n');//La première ligne ne nous intéresse pas

    while(i<9){
        getline(myFile,ligne[0],'|');
        getline(myFile,ligne[1],'|');
        getline(myFile,ligne[2],'|');
        getline(myFile,ligne[3],'|');
        getline(myFile,ligne[4],'|');
        getline(myFile,ligne[5],'|');
        getline(myFile,ligne[6],'|');
        getline(myFile,ligne[7],'|');
        getline(myFile,ligne[8],'\n');
        std::cout<<ligne[0];
        for(int k=0;k<9;k++){
            if (ligne[k]!="."){
                damier[i][k]=std::stoi(ligne[k]);
            }
            else {
                damier[i][k]=0;//Utile quand on reinitialise le jeu.
            }
        }
        i++;
    }
    return 0;
}
void DamierSudoku::set_grille(int val){//Essayer de trouver une méthode pour ouvrir le csv au lieu de faire ça
    if (val == 1) {
        lire_grille("../sudoku-main/grilles/grilleDebutant.csv");
    } else if (val ==2) {
        lire_grille("../sudoku-main/grilles/grilleFacile.csv");
    }else if (val ==3) {
        lire_grille("../sudoku-main/grilles/grilleIntermediaire.csv");
    }else if (val ==4) {
        lire_grille("../sudoku-main/grilles/grilleExpert.csv");
    }else if (val==5) {
        lire_grille("../sudoku-main/grilles/grilleSauvegarder.csv");
    }
}

/* Si la gestion de csv ne marche pas commenter la fonction précédente et utiliser ça
void DamierSudoku::set_grille(int val){//Essayer de trouver une méthode pour ouvrir le csv au lieu de faire ça
    if (val == 1) {
        grille = ".|9|.|.|.|4|.|.|. .|.|.|.|.|.|.|.|8 .|.|.|.|.|.|.|3|6 .|7|6|.|3|.|.|4|. 9|.|3|.|.|7|.|.|2 2|.|8|9|.|.|.|.|5 .|8|7|4|.|.|.|.|. .|.|.|.|.|8|.|2|. .|2|.|.|.|.|7|.|9";

    } else if (val ==2) {
        grille = "4|.|.|2|7|5|.|8|. .|.|.|.|1|.|4|7|. .|.|.|.|.|.|9|.|5 7|.|.|3|.|.|.|.|4 .|2|1|.|.|4|.|.|. 8|3|.|.|9|1|.|5|2 .|.|.|.|.|.|.|.|. .|.|.|8|.|.|5|9|7 .|.|.|.|.|2|.|.|.";

    }else if (val ==3) {
        grille = ".|.|4|8|.|.|.|1|. .|.|.|9|.|1|.|2|. .|6|.|2|.|.|4|3|. .|.|.|3|.|.|.|8|9 .|1|.|.|7|.|.|.|. 7|.|.|.|.|.|.|.|. .|4|2|.|.|.|.|.|. 3|9|.|.|.|8|.|.|. 6|.|1|.|2|.|3|.|.";

    }else if (val ==4) {
        grille = ".|4|6|.|.|.|.|.|. .|.|.|.|7|.|.|.|. .|.|.|.|.|2|7|9|1 .|.|.|.|.|6|.|7|. 6|.|1|.|.|.|4|2|. .|.|.|.|9|.|.|.|. 2|.|4|.|.|.|8|.|. .|.|.|2|1|.|5|6|. .|.|.|.|5|.|.|.|9";

    }
}*/





bool DamierSudoku::isValid_sans_color() {//Meme fonction que isValid mais sans le changement de couleur (pour la fonction resolve)
    bool isValid = true;

    // Check rows and columns for duplicates
    for (int i = 0; i < 9; ++i) {
        bool row[9] = {false};
        bool col[9] = {false};
        for (int j = 0; j < 9; ++j) {
            // Row check
            if (damier[i][j] != 0) {
                if (row[damier[i][j] - 1]) {
                    isValid = false; // Duplicate in the same row

                }
                row[damier[i][j] - 1] = true;
            }
            // Column check
            if (damier[j][i] != 0) {
                if (col[damier[j][i] - 1]) {
                    isValid = false; // Duplicate in the same column

                }
                col[damier[j][i]- 1] = true;
            }
        }
    }

    // Check 3x3 squares
    for (int block = 0; block < 9; ++block) {
        bool square[9] = {false};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int row = (block / 3) * 3 + i;
                int col = (block % 3) * 3 + j;
                if (damier[row][col] != 0) {
                    if (square[damier[row][col] - 1]) {
                        isValid = false; // Duplicate in the same 3x3 block

                    }
                    square[damier[row][col] - 1] = true;
                }
            }
        }
    }

    emit colorChanged(); // Émettre le signal indiquant un changement de couleur
    return isValid;
}


bool DamierSudoku::isValid() {
    bool isValid = true;

    // Check rows and columns for duplicates
    for (int i = 0; i < 9; ++i) {
        bool row[9] = {false};
        bool col[9] = {false};
        for (int j = 0; j < 9; ++j) {
            // Row check
            if (damier[i][j] != 0) {
                if (row[damier[i][j] - 1]) {
                    isValid = false; // Duplicate in the same row
                    colors[j/3+(i/3)*3][j%3+3*(i%3)] = "red"; // Mettre en rouge la case en erreur
                }
                row[damier[i][j] - 1] = true;
            }
            // Column check
            if (damier[j][i] != 0) {
                if (col[damier[j][i] - 1]) {
                    isValid = false; // Duplicate in the same column
                    colors[i/3+(j/3)*3][i%3+3*(j%3)] = "red"; // Mettre en rouge la case en erreur
                }
                col[damier[j][i]- 1] = true;
            }
        }
    }

    // Check 3x3 squares
    for (int block = 0; block < 9; ++block) {
        bool square[9] = {false};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int row = (block / 3) * 3 + i;
                int col = (block % 3) * 3 + j;
                if (damier[row][col] != 0) {
                    if (square[damier[row][col] - 1]) {
                        isValid = false; // Duplicate in the same 3x3 block
                        colors[block][j+3*i] = "red"; // Mettre en rouge la case en erreur
                    }
                    square[damier[row][col] - 1] = true;
                }
            }
        }
    }

    emit colorChanged(); // Émettre le signal indiquant un changement de couleur
    return isValid;
}






void DamierSudoku::addValue(int Carre, int Case, int value) {
    //En entrée nous n'avons pas la ligne et la colonne mais le carré dans lequel on se situe
    // Et la case dans le carré dans laquel on se situe.
    // On match donc sur les différent carre possible.

    int ligne, colonne;
    switch(Carre){
    case 0:
        colonne = Case%3;
        ligne = Case/3;
        break;
    case 1:
        colonne = Case%3+3;
        ligne = Case/3;
        break;
    case 2:
        colonne = Case%3+6;
        ligne = Case/3;
        break;
    case 3:
        colonne = Case%3;
        ligne = Case/3+3;
        break;
    case 4:
        colonne = Case%3+3;
        ligne = Case/3+3;
        break;
    case 5:
        colonne = Case%3+6;
        ligne = Case/3+3;
        break;
    case 6:
        colonne = Case%3;
        ligne = Case/3+6;
        break;
    case 7:
        colonne = Case%3+3;
        ligne = Case/3+6;
        break;
    case 8:
        colonne = Case%3+6;
        ligne = Case/3+6;
        break;
    }

    std::cout<<"je suis la"<<std::endl;
    //Vérifier que l'on peut écrire dans cette case


    Set(ligne, colonne, value);
    matriceToVectors(); //Transforme en vecteur pour le qml.
    emit valChanged(); // Émettre le signal valueChanged



}


bool DamierSudoku::finish() {
    bool nozero = true;
    for (int i = 0;i<9;i++) {
        for (int j=0;j<9;j++) {
            if (damier[i][j] ==0){
                nozero = false;
            }
        }
    }
    return (nozero && isValid());
}

bool DamierSudoku::resolve(){//ia qui résout le sodoku ('donner sa langue au chat')
    for (int i = 0;i<9;i++) {
        for (int j=0;j<9;j++) {
            if(damier[i][j]==0) {
                for (int k=0;k<9;k++) {
                    Set(i,j,k+1);
                    if (!isValid_sans_color()) {
                        Set(i,j,0);
                    } else{
                        if (resolve()) {
                            return true;
                        } else {
                            Set(i,j,0);//Backtrack
                        }
                    }
                } return false; //If no valid move found
            }
        }
    }
    matriceToVectors();
    emit valChanged();
    return true;
}




void DamierSudoku::fix_level(int i) {
    level = i;
    emit level_fix(); //Signal
}


void DamierSudoku::changeColor(int i, int j, const QString& color) {
    if (i >= 0 && i < 9 && j >= 0 && j < 9) {
        colors[i][j] = color; // Modifier la couleur de la case
        emit colorChanged(); // Émettre le signal indiquant un changement de couleur
    }
}

void DamierSudoku::colorer_ligne(int i, int l){
    // coloriage dans les carrés i à i+3 de la ligne l
    for(int k =i;k<i+3;k++)
        for(int m=l*3;m<l*3+3;m++)
            colors[k][m]="#cccccc";
}

void DamierSudoku::colorer_colonne(int i, int c){
    // coloriage dans tous les carrés de la colonne i (entre 0 et 2) de la colonne c (entre 0 et 2 également)
    for (int k=i;k<i+7;k+=3)
        for (int m=c;m<c+7;m+=3)
            colors[k][m]="#cccccc";//On a rangé les couleurs par carré donc un peu compliqué à trouver la colonne..
}

void DamierSudoku::colorer_voisins( int Carre,int Case){
    // reset les couleurs de toute la grille au blanc
    for(int k =0;k<9;k++){
        for(int j =0;j<9;j++){
            colors[k][j]="white";
        }
    }

    // recolore les cases du carré selectionné
    for(int k =0;k<9;k++){
        colors[Carre][k]="#cccccc";
    }

    //colorer les lignes horizontales
    switch(Carre/3){
    case 0:
        colorer_ligne(0,Case/3);
        break;
    case 1:
        colorer_ligne(3,Case/3);
        break;
    case 2:
        colorer_ligne(6,Case/3);
        break;
    }
    // colorer les lignes verticales
    switch(Carre%3){
    case 0:
        colorer_colonne(0,Case%3);
        break;
    case 1:
        colorer_colonne(1,Case%3);
        break;
    case 2:
        colorer_colonne(2,Case%3);
        break;
    }
    // coloriage des cases avec le même chiffre
    int chiffre = damier[3*(Carre/3)+(Case/3)][3*(Carre%3)+(Case%3)];
    if (chiffre){
        for (int square=0;square<9;square++){//Attention on va parcourir par carre/case
            for (int little_square=0;little_square<9;little_square++){
                if (damier[3*(square/3)+(little_square/3)][3*(square%3)+(little_square%3)]==chiffre){
                    colors[square][little_square]="#9eaac8";
                }
            }
        }
    }
    emit colorChanged();
}


void DamierSudoku::writeCSV(const int damier[9][9], const std::string& filename) {
    std::ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        std::cerr << "Erreur: Impossible de créer le fichier." << std::endl;
        return;
    }
    csvFile << "Derniere grille sauvegardé" << std::endl; // En-tête du fichier CSV

    // Écriture du damier dans le fichier CSV
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j > 0) {
                csvFile << "|";
            }
            if (damier[i][j] == 0) {
                csvFile << ".";
            } else {
                csvFile << damier[i][j];
            }
        }
        csvFile << std::endl;
    }

    csvFile.close();
    std::cout << "Fichier CSV créé avec succès !" << std::endl;
}

void DamierSudoku::sauver() {
    writeCSV(damier,"../sudoku-main/grilles/grilleSauvegarder.csv");
}

void DamierSudoku::matriceToVectors(){
    //passage d'un tableau damier de taille 9x9 de int à valeurs qui est une QList<QString>>
    QList<QString> case1,case2,case3,case4,case5,case6,case7,case8,case9;
    // On a choisi de remplir par carré pour simplifier le code dans le qml (on aura juste à parcourir simplement).
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            case1.append(QString::number(damier[i][j]));
            case2.append(QString::number(damier[i][j+3]));//Attention à l'ordre de remplissage
            case3.append(QString::number(damier[i][j+6]));
            case4.append(QString::number(damier[i+3][j]));
            case5.append(QString::number(damier[i+3][j+3]));
            case6.append(QString::number(damier[i+3][j+6]));
            case7.append(QString::number(damier[i+6][j]));
            case8.append(QString::number(damier[i+6][j+3]));
            case9.append(QString::number(damier[i+6][j+6]));
        }
    }
    valeurs = {case1,case2,case3,case4,case5,case6,case7,case8,case9};
}










