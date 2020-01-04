import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import NLP 1.0

Window {

    visible: true

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    width: 640
    height: 480
    title: qsTr("Illuminary")

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            AppState.loadFile(fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    RowLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter
        Button {
            text: "Select document"
            onClicked: fileDialog.open()
        }
        Flow {
            Layout.fillWidth: true
            Layout.margins: 20
            spacing: 5
            Repeater {
                model: AppState.sentence
                Row {
                    Text {
                        text: word
                        font.family: "Arial"
                        font.pixelSize: 13
                    }
                }
            }
        }
    }

}
