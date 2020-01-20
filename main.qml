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
            Layout.maximumWidth: 200
            Button {
                Layout.alignment: Qt.AlignTop
                text: "Select document"
                onClicked: fileDialog.open()
            }

            GroupBox {
                title: qsTr("Part of Speech Colors")
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.fill: parent
                    Repeater {
                        model: AppState.colors
                        Rectangle {
                            width: 20
                            height: 20
                            color: model.color
                        }
                    }

                }
            }

            GroupBox {
                title: qsTr("Word Dimensions")
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.fill: parent
                    Slider {
                        Layout.fillWidth: true
                        from: 1
                        value: VisualizationProperties.wordWidth
                        to: 100
                        onMoved: VisualizationProperties.wordWidth = value
                    }
                    Slider {
                        Layout.fillWidth: true
                        from: 1
                        value: VisualizationProperties.wordHeight
                        to: 100
                        onMoved: VisualizationProperties.wordHeight = value
                    }
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
                        Word {
                            averageWidth: VisualizationProperties.wordWidth
                            height: VisualizationProperties.wordHeight
                            relativeSize: model.word.length / model.averageLengthInSentence
                            color: AppState.colors.getColor(model.pos)
                        }
                    }
                }
            }
        }


    }

}
