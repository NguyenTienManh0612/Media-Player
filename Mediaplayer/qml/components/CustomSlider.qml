import QtQuick 2.12
import QtQuick.Controls 2.12
import "../helper/msToHMS.js" as MsToHMS
Item {
    id: root
    property bool isPlaying: false
    property int songPosition: 0
    property int songDuration: 0
    property real progressBarStep: 0
    //signal positionAdjusted(int currentPosition)
//    Connections {
//        id: playerModelConnection
//        target: MPLAYBACK_MODEL

//        onDurationChanged: {
//            songDuration = duration
//            progressBarStep = 500000/songDuration //slider width = 500
//            console.log("Duration = " + MPLAYBACK_MODEL.duration)
//        }
//    }
    property alias value: songProgressBar.value
    //property alias maximumValue: songProgressBar.maximumValue
    property alias sliderWidth: songProgressBar.width
    property alias sliderHeight: songProgressBar.height

    signal sliderOnPressed()

    width: parent.width
    height: 8
    Slider {
        id: songProgressBar
        from: 0
        to: MPLAYBACK_MODEL.duration / 1000
        //stepSize: 1000
        orientation: Qt.Horizontal
        value: MPLAYBACK_MODEL.position / 1000
        //snapMode: Slider.SnapOnRelease
        anchors {
            left: positionText.right
            leftMargin: 10
        }

        width: 500
        height: belowProgressBar.implicitHeight

        background:Rectangle {
            id: belowProgressBar
            implicitHeight: 7
            width: parent.width
            radius: 31
            color: "#DEDDE3"
            opacity: 90

            Rectangle {
                id: aboveProcessBar
                width: songProgressBar.visualPosition * parent.width
                height: parent.height + 1
                radius: 37
                color: "#007bbc"
            }
        }
        handle: Item{}
//        onPressedChanged: {
//            if(!pressed)
//                sliderOnPressed()
//        }
//        Binding {
//            target: songProgressBar
//            property: "value"
//            when: !songProgressBar.pressed
//        }
        onMoved: {
            if (MPLAYBACK_MODEL.currentMediaIndex < 0) {
                console.log("Position adjusted, but no song is selected")
                value = 0
            } else{
                //MPLAYER_CTRL.pause()
                MPLAYBACK_MODEL.position = value
                //root.positionAdjusted(MPLAYBACK_MODEL.position)
                if (value < MPLAYBACK_MODEL.duration / 1000){
                    //MPLAYER_CTRL.play()
                    MPLAYER_CTRL.setMediaPosition(valueAt(position*1000))
                }
                console.log(value, "<-- Slider position")
            }
        }
    }
    Text {
        id: durationText
        text: MPLAYBACK_MODEL.duration === 0 ? MPLAYBACK_MODEL.currentMusicLength : MsToHMS.msToHMS(MPLAYBACK_MODEL.duration)
        anchors {
            left: songProgressBar.right
            leftMargin: 10
            verticalCenter: songProgressBar.verticalCenter
        }
        font.pointSize: 10
        font.bold: true
        color: "darkslategrey"
    }

    Text {
        id: positionText
        text: MsToHMS.msToHMS(MPLAYBACK_MODEL.position)
        anchors {
            left: parent.left
            verticalCenter: songProgressBar.verticalCenter
        }
        font.pointSize: 10
        font.bold: true
        color: "darkslategrey"
    }
//    Timer {
//        id: songTimer
//        interval: 1000
//        running: false
//        repeat: true
//        onTriggered: {
//            if (MPLAYBACK_MODEL.position < 400){
//                MPLAYBACK_MODEL.position = MPLAYBACK_MODEL.position + progressBarStep
//            } else {
//                running = false
//                animation.paused = true
//                playButtonImage.source = playButtonUrl
//            }
//        }
//    }
//    Component.onCompleted: {
//        positionAdjusted.connect(MPLAYBACK_MODEL.handleCurrentPositionChanged())
//    }
}
