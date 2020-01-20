import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {

//    property list meter: []
    property int averageWidth: 10
    property real relativeSize: 1 // 0 to 1
    property color color: "black"

    width: childrenRect.width

    Rectangle {
        width: Math.max(averageWidth * relativeSize, 3)
        height: parent.height
        color: parent.color
    }

}
