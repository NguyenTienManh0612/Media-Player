import QtQuick 2.12

Rectangle {
    id: root
    property string src: ""
    signal clicked
    width: 80
    height: 200
    color: "red"
    //radius: root.width / 2
    anchors {
        bottom: parent.bottom
        bottomMargin: 80
    }
    Image {
        anchors.centerIn: parent
        source: src
        sourceSize.width: 52
        sourceSize.height: 52
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
