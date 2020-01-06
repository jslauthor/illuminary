import QtQml.Models 2.12
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

    width: 1024
    height: 768
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
        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            Button {
                Layout.alignment: Qt.AlignTop
                text: "Select document"
                onClicked: fileDialog.open()
            }

            Repeater {
                model: AppState.colors
                Rectangle {
                    width: 20
                    height: 20
                    color: model.color
                }
            }

        }


        ColumnLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Text {
                Layout.fillWidth: true
                text: AppState.corpus
                wrapMode: Text.Wrap
            }
            Flow {
                Layout.fillWidth: true
                Layout.margins: 20
                spacing: 1
                Repeater {
                    model: AppState.analysis
                    Rectangle {
                        width: 1
                        height: 10
                        color: "black"
                    }
                }
            }
        }
    }

}
