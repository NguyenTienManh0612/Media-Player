import QtQuick 2.12
import "../helper/getCurrentTime.js" as CurrentTime
import "../helper/getCurrentDay.js" as CurrentDate
Rectangle {
    id: root
    color: "black"
    width: parent.width
    height: parent.height / 8
    property bool isIconVisible: true
    Image {
        id: btn_home
        anchors {
            verticalCenter: parent.verticalCenter
            left: btn_back.right
            leftMargin: 10
        }
        visible: isIconVisible
        source: "qrc:/images/home-default.png"
        sourceSize.width: 60
        sourceSize.height: 60

        MouseArea {
            anchors.fill: parent
            onClicked: {
                SCREEN_CTRL.popToRoot()
            }
        }
    }

    Image {
        id: btn_back
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 15
        }
        visible: isIconVisible
        source: "qrc:/images/back-default.png"
        sourceSize.width: 48
        sourceSize.height: 48
        MouseArea {
            anchors.fill: parent
            onClicked: {
                SCREEN_CTRL.popScreen()
            }
        }
    }
    Text {
        id: currentTime
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 26
        font.bold: true
        text: CurrentTime.getCurrentDateTime()
    }
    Text {
        id: currentDate
        anchors {
            left: currentTime.right
            leftMargin: 5
            baseline: currentTime.baseline
        }
        color: "white"
        font.pixelSize: 17
        font.bold: false
        text: CurrentDate.getCurrentDate()
    }
}
