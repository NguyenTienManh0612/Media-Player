import QtQuick 2.12
import "../components"
import AppEnums 1.0
import QtMultimedia 5.12
import QtQuick.Layouts 1.6

Item {
    id: root

    VideoOutput {
        id: video_output
        width:  VPLAYER_CTRL.isFullScreenVideo ? parent.width : parent.width - 50
        height: VPLAYER_CTRL.isFullScreenVideo ? parent.height : parent.height - 50
        source: VPLAYER_CTRL
        visible: true
        anchors {
            top: VPLAYER_CTRL.isFullScreenVideo ? parent.top : statusBar.bottom
            topMargin: VPLAYER_CTRL.isFullScreenVideo ? 0 : 0
            horizontalCenter: parent.horizontalCenter
        }
        MouseArea {
            anchors.fill: parent
            onClicked: VPLAYER_CTRL.setIsFullScreenVideo(false)
        }
    }
    Rectangle {
        id: previousButton
        visible: !VPLAYER_CTRL.isFullScreenVideo
        width: 45; height: 45
        color: "transparent"
        Image {
            anchors.centerIn: parent
            source: "qrc:/images/previous.png"
            sourceSize.width: 52
            sourceSize.height: 52
        }
        //src: "qrc:/images/previous.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("previous button clicked")
                VPLAYER_CTRL.vprevious()
            }
        }
        anchors {
            right: playButton.left
            rightMargin: 40
            bottom: parent.bottom
            bottomMargin: 45
        }
    }
    Rectangle {
        id: playButton
        visible: !VPLAYER_CTRL.isFullScreenVideo
        width: 45; height: 45
        color: "transparent"
        Image {
            anchors.centerIn: parent
            source: VPLAYBACK_MODEL.videoPlayerState === 1 ? "qrc:/images/pause.png" : "qrc:/images/play.png"
            sourceSize.width: 52
            sourceSize.height: 52
        }
        //src: MPLAYBACK_MODEL.mediaPlayerState === 1 ? "qrc:/images/pause.png" : "qrc:/images/play.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("play pause button clicked")
                VPLAYER_CTRL.vplaypause()
            }
        }
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 45
        }
    }
    Rectangle {
        id: nextButton
        visible: !VPLAYER_CTRL.isFullScreenVideo
        color: "transparent"
        width: 45; height: 45
        //src: "qrc:/images/next.png"
        Image {
            anchors.centerIn: parent
            source: "qrc:/images/next.png"
            sourceSize.width: 52
            sourceSize.height: 52
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("next button clicked")
                VPLAYER_CTRL.vnext()
            }
        }
        anchors {
            left: playButton.right
            leftMargin: 40
            bottom: parent.bottom
            bottomMargin: 45
        }
    }

    CustomSliderV {
        visible: !VPLAYER_CTRL.isFullScreenVideo
        id: progressBar
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 60
        //maximumValue: MPLAYBACK_MODEL.duration
        //        value: MPLAYBACK_MODEL.position
        //        onSliderOnPressed: {
        //            MPLAYBACK_MODEL.setPosition(value)
        //        }
    }

//    Text {
//        id: videoName
//        text: VPLAYBACK_MODEL.currentVideoName
//        color: "red"
//        font.pixelSize: 10
//        font.bold: true
//        anchors {
//            top: statusBar.bottom
//            topMargin: 3
//            horizontalCenter: parent.horizontalCenter
//        }
//        visible: !VPLAYER_CTRL.isFullScreenVideo
//    }
    StatusBar {
        id: statusBar
        visible: !VPLAYER_CTRL.isFullScreenVideo
    }
}
