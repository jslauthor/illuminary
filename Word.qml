import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

Item {

//    property list meter: []
    property int averageWidth: 10
    property real relativeSize: 1 // 0 to 1
    property color color: "black"
    property bool isEndOfSentence: false
    property int sentencePadding: 5
    property string word: ""

    width: wordVisualization.width + (isEndOfSentence ? sentencePadding : 0)

    Rectangle {
        id: wordVisualization
        width: Math.max(averageWidth * relativeSize, 3)
        height: parent.height
        color: parent.color

        MouseArea {
            id: mouseArea
            width: parent.width
            height: parent.height
            hoverEnabled: true
        }

        ToolTip {
            id: toolTip
            text: word
            visible: mouseArea.containsMouse
        }
    }
}
