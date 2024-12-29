import QtQuick 2.12
import AppEnums 1.0
import "../helper/getCurrentTime.js" as CurrentTime
import "../helper/getCurrentDay.js" as CurrentDate
Rectangle {
    id: root
    color: "black"
    width: parent.width
    height: parent.height / 8
//    property bool isIconVisible: true
    Image {
        id: listMusic
        visible: (SCREEN_MODEL.currentScreen === "qrc:/qml/screens/MusicPlayerScreen.qml") ? true : false
        anchors {
            verticalCenter: parent.verticalCenter
            left: backHome.right
            leftMargin: 10
        }
        source: "qrc:/images/list.png"
        sourceSize.width: 60
        sourceSize.height: 60

        MouseArea {
            anchors.fill: parent
            onClicked: {
                SCREEN_CTRL.pushScreen(AppEnums.SCREEN_ID_MUSIC_LIST)
            }
        }
    }
    Image {
        id: backHome
        anchors {
            verticalCenter: parent.verticalCenter
            left: btn_back.right
            leftMargin: 10
        }
        //visible: isIconVisible
        source: "qrc:/images/home-default.png"
        sourceSize.width: 60
        sourceSize.height: 60

        MouseArea {
            anchors.fill: parent
            onClicked: {
                SCREEN_CTRL.setModeDisplay(false);
                SCREEN_CTRL.requestBackToHome();
                //MPLAYBACK_MODEL.requestSendMetaData();
                MPLAYER_CTRL.requestSendMetaData();
                if(SCREEN_MODEL.currentScreen === "qrc:/qml/screens/VideoPlayerScreen.qml")
                    VPLAYER_CTRL.requestSendMetaData();
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
        //visible: isIconVisible
        source: "qrc:/images/back-default.png"
        sourceSize.width: 48
        sourceSize.height: 48
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(SCREEN_CTRL.countScreenInStack() === 1){
                    SCREEN_CTRL.setModeDisplay(false);
                    SCREEN_CTRL.requestBackToHome();
                    MPLAYER_CTRL.requestSendMetaData();
                    VPLAYER_CTRL.requestSendMetaData();
                }else {
                    SCREEN_CTRL.popScreen()
                }
            }
        }
    }
    Image {
        id: btn_full_screen
        visible: (SCREEN_MODEL.currentScreen === "qrc:/qml/screens/VideoPlayerScreen.qml") ? true : false
        anchors {
            verticalCenter: parent.verticalCenter
            left: backHome.right
            leftMargin: 7
        }
        source: "qrc:/images/full-screen.png"
        sourceSize.width: 56
        sourceSize.height: 56
        MouseArea {
            anchors.fill: parent
            onClicked: {
                VPLAYER_CTRL.setIsFullScreenVideo(true)
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
