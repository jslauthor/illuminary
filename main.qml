import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12

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
            NLPParser.loadFile(fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    Button {
        text: "Select document"
        onClicked: fileDialog.open()
    }

}
