import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import "terminalUVK.js" as MyScript
// Создаём объект диалогового окна
Dialog {
    id: dialselectputinadviga
    property string name
    property var internalModel
    property string objectName1
    width: 300
    height: 100

    // Создаём содержимое диалогового окна
    contentItem: Rectangle {
        width: 300
        height: 100
        color: "#f7f7f7"

        // Область для сообщения диалогового окна
        Rectangle {

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: dividerHorizontal.top
            color: "#f7f7f7"  // Задаём цвет области

            // Задаём сообщение диалогового окна
            Label {
                id: textLabel
                text: "Переключить режим роспуска на "+name
                color: "black"
                anchors.centerIn: parent
            }
        }

        // Создаём горизонтальный разделитель с помощью Rectangle
        Rectangle {
            id: dividerHorizontal
            color: "#d7d7d7"
            height: 2 // Устанавливаем ширину в два пикселя
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: row.top
        }

        Row {
            id: row
            height: 50
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            Button {
                id: dialogButtonCancel
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 1

                // Стилизуем кнопку
                style: ButtonStyle {
                    background: Rectangle {
                        color: control.pressed ? "#d7d7d7" : "#f7f7f7"
                        border.width: 0
                    }

                    label: Text {
                        text: qsTr("Да")
                        color: "black"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                onClicked: {

                    putnadviga.currentSelection = (putnadviga.currentSelection+1) % putnadviga.items.length;//
                    putnadviga.colorRect =MyScript.getColore(otcepsModel.getPutNadviga(putnadviga.currentSelection))
                    dialselectputinadviga.close()
                }
            }

            Rectangle {
                id: dividerVertical
                width: 2
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: "#d7d7d7"
            }

            Button {
                id: dialogButtonOk
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 1
                style: ButtonStyle {
                    background: Rectangle {
                        color: control.pressed ? "#d7d7d7" : "#f7f7f7"
                        border.width: 0
                    }

                    label: Text {
                        text: qsTr("Нет")
                        color: "black"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                onClicked: {
                    dialselectputinadviga.close();
                }
            }
        }
    }
}
