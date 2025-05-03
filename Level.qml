import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {//Composant qui permet d'afficher le menu de départ pour choisir son niveau.
    id: window
    width: 600
    height: 400
    visible: true
    title: qsTr("Menu Niveau")

    Rectangle {
        id: rectangle
        color: "#f5f5f5"
        anchors.fill: parent

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "Veuillez choisir le mode de difficulté :"
                font.pixelSize: 24
            }

            Button {
                width: 200
                height: 50
                text: qsTr("Facile")
                Layout.alignment: Qt.AlignHCenter
                font.weight: Font.ExtraLight
                onClicked: {
                    sudoku.fix_level(1)
                    initialize()
                    window.close();
                }
            }

            Button {
                width: 200
                height: 50
                text: qsTr("Intermédiaire")
                Layout.alignment: Qt.AlignHCenter
                font.weight: Font.ExtraLight
                onClicked: {
                    sudoku.fix_level(2)
                    initialize()
                    window.close();
                }
            }

            Button {
                width: 200
                height: 50
                text: qsTr("Difficile")
                Layout.alignment: Qt.AlignHCenter
                font.weight: Font.ExtraLight
                onClicked: {
                    sudoku.fix_level(3)
                    initialize()
                    window.close();
                }
            }

            Button {
                width: 200
                height: 50
                text: qsTr("Extrême")
                Layout.alignment: Qt.AlignHCenter
                font.weight: Font.ExtraLight
                onClicked: {
                    sudoku.fix_level(4)
                    initialize()
                    window.close();
                }
            }

            Button {
                width: 200
                height: 50
                text: qsTr("Sauvegarde")
                Layout.alignment: Qt.AlignHCenter
                font.weight: Font.ExtraLight
                onClicked: {
                    sudoku.fix_level(5)
                    initialize()
                    window.close();
                }
            }
        }
    }
}


