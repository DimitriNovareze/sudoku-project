import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12


Window {
    id : root
    color: "#e6ecfa"
    width: 800+5
    height: 650+5
    visible: true
    title: qsTr("Sudoku")


    property double startTime : 0//L'heur où on commence à jouer
    property string chronoText: "00:00"//Initialise a zero

    function getTime() {
        var date = new Date();
        return date.getTime();
    }

    Rectangle {//Rectangle pour afficher un chrono
        anchors.fill: parent
        color: "lightblue"
        Text {
            text: "Chrono: " + chronoText
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 24
            color: "white"
        }
    }

    Timer {
        id: timer
        interval: 1000 // Met à jour le chrono toutes les secondes
        running: true
        repeat: true
        onTriggered: {
            chronoText = formatTime((getTime() - startTime) / 1000);
        }
    }

    function formatTime(seconds) {//Pour mettre au bon format
        var h = padZero(Math.floor(seconds / 3600));
        var m = padZero(Math.floor(seconds % 3600 / 60));
        var s = padZero(Math.floor(seconds % 60));
        return h + ":" + m + ":" + s;
    }

    function padZero(num) {
        return (num < 10 ? "0" : "") + num;//ajoute un zéro devant le nombre si celui-ci est inférieur à 10 (1 ->01)
    }


    function resolver() {//Fonction pour résoudre le sudoku
        sudoku.init(sudoku.lvl);
        sudoku.resolve();//Appel à la fonction C++
        var values = sudoku.values;//On met à jour les nouvelles valeurs
        for (var i = 0; i < 9; i++) {
            for (var j = 0; j < 9; j++) {
                var cell = repeater.itemAt(i).rep.itemAt(j).input;
                cell.text = values[i][j]//Et ici on affiche les valeurs
            }
        }
    }

    function check() {//Fonction qui permet de vérifier s'il y a des erreurs dans notre sudoku
        var isValid = sudoku.isValid();
        set_color();
        if (isValid) {
            resultText.text = "Jusqu'à présent, tout va bien !"; // Update the popup text
        } else {
            resultText.text = "Erreur détectée, vérifiez vos entrées !"; // Update the popup text
        }
        resultPopup.open(); // Open the popup after setting the text
    }

    function sauv() {
        sudoku.sauver();
        sauverText.text = "La partie a été sauvegardée !
Une fois la partie sauvegardée chargée,
vous ne pourrez plus modifier vos coups déjà joués !";
        sauverPopup.open();
    }

    function set_color() {
        var coul = sudoku.couleurs; // Récupère les nouvelles couleurs de la grille Sudoku
        for (var i = 0; i < 9; i++) {
            for (var j = 0; j < 9; j++) {
                var cell = repeater.itemAt(i).rep.itemAt(j);
                // Couleur par défaut pour les cases vides
                cell.color = coul[i][j]; // Ou toute autre couleur que vous souhaitez pour les cases vides
            }
        }
    }

    function initialize() {
        startTime = new Date().getTime()
        var lvl = sudoku.lvl;
        sudoku.init(lvl);
        var coul = sudoku.couleurs; // Récupère les nouvelles couleurs de la grille Sudoku
        var values = sudoku.values;
        if (values) {
            for (var i = 0; i < 9; i++) {
                for (var j = 0; j < 9; j++) {
                    var cell_for_color=repeater.itemAt(i).rep.itemAt(j);
                    var cell = repeater.itemAt(i).rep.itemAt(j).input;
                    if (values[i] && values[i][j] !== undefined) { // Vérifie si la ligne et la colonne sont définies
                        cell_for_color.color = coul[i][j]; // Ou toute autre couleur que vous souhaitez pour les cases vides
                        cell.text = values[i][j];
                        if (values[i][j] !== '0') {
                            cell.readOnly = true; // Si c'est une case préremplie, ne pas la changer
                            cell.color = "#000000";//On met le texte en nori
                            cell.font.bold = true;
                        } else {
                            cell.readOnly = false;
                            cell.text = "";
                        }
                    }
                }
            }
        }

    }


    property alias repeater : repeater // Pour pouvoir appeler les carrés

    Rectangle{
        id : background
        x:3
        y:3
        color : "black"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        width : root.height-60
        height : root.height-60//Taille dynamique
    Grid{
        id : grid
        //anchors.fill: parent  // Utilisation des ancres pour remplir le parent
        x: 3
        y:3
        rows:3
        columns:3
        spacing :2
        Repeater{//Un sudoku est composé de 9 Carré
            id : repeater
            model : 9

            Carre{
                id : case1
                width : (background.width-6)/3
                height: (background.height-6)/3
                parentWidth: (background.width - 6)/3//Taille dynamique
                parentHeight: (background.height - 6)/3
                parentIndex: index
            }
        }
    }
}

    Button {
        id: button_check
        width: 132
        height: 40
        text: qsTr("Vérifier")
        anchors.bottom: parent.bottom // Mettre en bas de la page
        highlighted: false // Pas en surbrillance
        anchors.horizontalCenterOffset: -100 //Décalage horizontale
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10 // la marge entre le bas du bouton et le bord inférieur de son parent
        font.weight: Font.ExtraLight
        font.pointSize: 12 //Taille du texte
        onClicked:{ check();
            button_check.highlighted = true
        }
    }




    Button {
        id: button_restart
        x: 500
        y: 710
        width: 132
        height: 40
        text: qsTr("Réinitialiser")
        Material.background: "#008080"
        Material.foreground: "#FFFFFF"
        Material.elevation: 2
        anchors.bottom: parent.bottom
        highlighted: false
        anchors.horizontalCenterOffset: 300
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
        font.weight: Font.ExtraLight
        font.pointSize: 12
        onClicked: {
            initialize(); //On (re)initialise quand le bouton est cliqué
            button_restart.highlighted = true;
        }
    }


    Button {
            id: button_resolve
            width: 132
            height: 40
            text: qsTr("Solution")
            anchors.bottom: parent.bottom
            highlighted: false
            anchors.horizontalCenterOffset: -300
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 10
            font.weight: Font.ExtraLight
            font.pointSize: 12
            onClicked:{ resolver();
                button_resolve.highlighted = true
            }
        }
    Button {
            id: sauvegarder
            width: 132
            height: 40
            text: qsTr("Sauvegarder")
            anchors.bottom: parent.bottom
            highlighted: false
            anchors.horizontalCenterOffset: 100
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 10
            font.weight: Font.ExtraLight
            font.pointSize: 12
            onClicked:{ sauv();
                sauvegarder.highlighted = true
            }
        }

    Level{
        id :level
        visible: true
    }


    Popup {
        id: resultPopup
        width: 200
        height: 100
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        Text {
            id: resultText
            anchors.centerIn: parent
        }
    }

Popup {
    id: sauverPopup
    width: 400
    height: 200
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Text {
        id: sauverText
        anchors.centerIn: parent
    }
}

Popup {
    id: finishPopup
    width: 400
    height: 200
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Text {
        id: finishText
        anchors.centerIn: parent
    }
}


}
