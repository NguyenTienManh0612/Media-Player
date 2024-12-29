import QtQuick 2.12

Item {
    id: root
    property alias text: appName.text
    property alias imageSrc: appImage.source
    property alias imageWidth: appImage.sourceSize.width
    property alias imageHeight: appImage.sourceSize.height
    property alias imageAnchors: appImage.anchors
    signal clicked
    width: parent.width / 2.2
    height: parent.height / 2
    Rectangle {
        width: parent.width
        height: parent.width
        border.color: "blue"
        border.width: 1
        color: "#ededed"
        radius: 10
    }
    Text {
        id: appName
        anchors {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        font.bold: true
        font.pixelSize: 22
        color: "black"
    }
    Image {
        id: appImage
        anchors {
            top: appName.bottom
            topMargin: 2
            horizontalCenter: parent.horizontalCenter
        }
        //fillMode: Image.PreserveAspectFit
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
