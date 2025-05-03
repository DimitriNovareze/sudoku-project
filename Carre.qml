import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15


/* Un carré est composé de 9 case, 3 cases horizontales * 3 cases verticales */

/*Nous avons choisi de nous "compliqué la vie" en parcourant par carré, et non par ligne,
  afin de rendre l'aspect visuel du jeu plus jolie : Pour visualiser les espace entre
  les carrés.*/


Item {
    id : carreItem

    property int parentWidth: 0//accès à la taille du parent
    property int parentHeight: 0
    property int parentIndex: 0//Acces à l'index du parent


    function envoyer_valeur(app) {//Changer la valeur affiché dans la case quand on clique sur un chiffre.

        var i;
        var j;
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                var carr = repeater.itemAt(i).rep.itemAt(j).input // Cette ligne de code permet d'accéder à l'élément situé au carré i et à la case j dans notre sudoku.
                if (app === carr) {
                    var value = (app.text);
                    if (value === "") {//L'utilisateur a appuyé sur retour arrière.
                        sudoku.addValue(i,j,0)
                        sudoku.colorer_voisins(i,j);//Quand on appuie arrière alors qu'il y avait un chiffre, on le voit
                        set_color();
                    }
                    else if(!isNaN(parseInt(value))) {
                        sudoku.addValue(i, j, parseInt(value));
                        sudoku.colorer_voisins(i,j);//Quand on appuie arrière alors qu'il y avait un chiffre, on le voit
                        set_color();

                    }

                }
            }
        }

        var values = sudoku.values;
        for(var l=0;l<9;l++){
            for(var c=0;c<9;c++){

                var v = repeater.itemAt(l).rep.itemAt(c).input
                var val = values[l][c];
                if (val === "0") {
                    v.text = "";
                }
                else {
                v.text=values[l][c];

                }
            }
        }
    }
    property alias rep : repeater1

    Grid{
        id : grid
        x: 3; y:3
        rows:3; columns:3; spacing :1


        Repeater{ id : repeater1
            model : 9

            Rectangle{
                focus: true // Permettre à ce rectangle d'avoir le focus
                color : "#ffffff"
                width: (carreItem.parentWidth-6) / 3//Taille dynamique
                height: (carreItem.parentHeight-6) / 3
               // width : parent.width/3; height: parent.height/3
                //width: (grid.width - (grid.spacing * 4)) / 3 // Calcul de la largeur en fonction de la taille de la grille
                //height: (grid.height - (grid.spacing * 4)) / 3 // Calcul de la hauteur en fonction de la taille de la grille
                property alias input : input
                border.width : 1
                border.color : "#000000"

                TextInput{
                    id:input
                    color:'#333333'
                    width : parent.width
                    height:parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    readOnly: false
                    font.pointSize: 24
                    maximumLength: 1
                    onFocusChanged: {//Appel dans le text input pour changer la couleur des que on clique dans la case

                        sudoku.colorer_voisins(parentIndex,index)//On change la couleur des voisins pour aider la visualisation
                        set_color();
                    }
                    onTextEdited: {
                        envoyer_valeur(this);
                        var boo = sudoku.finish();
                        if (boo) {
                            finishText.text = "Bravo vous avez réussi en seulement "+chronoText+ "!";
                            finishPopup.open();
                        }
                    }
                }


            }
        }
    }
}
