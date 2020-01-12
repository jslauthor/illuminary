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

        ProgressBar {
            visible: AppState.isAnalysisRunning
            value: AppState.analysisProgress
            indeterminate: true
        }

        ScrollView{
            id: scrollView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.interactive: true
            clip: true
            visible: !AppState.isAnalysisRunning
            Column {
//                Text {
//                    width: scrollView.width
//                    text: AppState.corpus
//                    wrapMode: Text.Wrap
//                }
                Flow {
                    width: scrollView.width
                    Layout.margins: 20
                    spacing: 0
                    Repeater {
                        model: AppState.analysis
                        RowLayout {
                            height: 30
                            width: 1
                            // Length shouldn't apply to punctuation
                            // Logarithmic height
                            // Special character for periods
                            Rectangle {
                                Layout.alignment: Qt.AlignCenter
                                width: parent.width
                                height: Math.min(parent.height * (model.word.length / AppState.averageWordLength), parent.height)
                                color: AppState.colors.getColor(model.pos)
                            }
                        }
                    }
                }
            }
        }


    }

}
