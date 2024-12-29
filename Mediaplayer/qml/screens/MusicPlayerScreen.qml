import QtQuick 2.12
import QtQuick.Controls 2.12
import AppEnums 1.0
import "../components"
Item {
    id: musicPlayer

    StatusBar {
        id: statusBar
    }
    ScrollingText {
        id: trackTitle
        text.text: (MPLAYBACK_MODEL.currentSongTitle === "") ?
                   (TRANSLATE_MODEL.STR_TITLE + " : " + TRANSLATE_MODEL.STR_UNKNOWN) :
                   (TRANSLATE_MODEL.STR_TITLE + " : " + MPLAYBACK_MODEL.currentSongTitle) // || "Unknown Title"
        //color: "white"
        text.font.pixelSize: 18
        width: parent.width / 2 - 5
        isAllowScroll: true
        anchors {
            left: parent.left
            leftMargin: 60
            top: statusBar.bottom
            topMargin: 100
        }
    }

    ScrollingText {
        id: trackArtist
        text.text: (MPLAYBACK_MODEL.currentArtistName === "")?
                   (TRANSLATE_MODEL.STR_ARTIST + " : " + TRANSLATE_MODEL.STR_UNKNOWN):
                   (TRANSLATE_MODEL.STR_ARTIST + " : " + MPLAYBACK_MODEL.currentArtistName)//MPLAYBACK_MODEL.currentArtistName || "Unknown Artist"
        //color: "gray"
        text.font.pixelSize: 14
        width: parent.width / 2 - 5
        isAllowScroll: true
        anchors {
            left: parent.left
            leftMargin: 60
            top: trackTitle.bottom
            topMargin: 10
        }
    }

    ScrollingText {
        id: trackAlbum
        text.text: (MPLAYBACK_MODEL.currentAlbumName === "") ?
                   (TRANSLATE_MODEL.STR_ALBUM + " : " + TRANSLATE_MODEL.STR_UNKNOWN) :
                   (TRANSLATE_MODEL.STR_ALBUM + " : " + MPLAYBACK_MODEL.currentAlbumName)//MPLAYBACK_MODEL.currentAlbumName || "Unknown Album"
        //color: "gray"
        text.font.pixelSize: 14
        width: parent.width / 2 - 5
        isAllowScroll: true
        anchors {
            left: parent.left
            leftMargin: 60
            top: trackArtist.bottom
            topMargin: 3
        }
    }
    Image {
        id: coverArtImage
        width: 250
        height: 250
        fillMode: Image.PreserveAspectFit
        source: MPLAYBACK_MODEL.coverArt
        anchors {
            right: parent.right
            rightMargin: 40
            top: statusBar.bottom
            topMargin: 40
        }
    }
    Rectangle {
        width: 45; height: 45
//        color: "red"
//        opacity: 0.5
        id: previousButton
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
                MPLAYER_CTRL.mprevious()

            }
        }
        anchors {
            left: parent.left
            leftMargin: 130
            top: trackAlbum.bottom
            topMargin: 75
        }
    }
    Rectangle {
        id: playButton
        width: 45; height: 45
        color: "transparent"
        Image {
            anchors.centerIn: parent
            source: MPLAYBACK_MODEL.mediaPlayerState === 1 ? "qrc:/images/pause.png" : "qrc:/images/play.png"
            sourceSize.width: 52
            sourceSize.height: 52
        }
        //src: MPLAYBACK_MODEL.mediaPlayerState === 1 ? "qrc:/images/pause.png" : "qrc:/images/play.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("play pause button clicked")
                MPLAYER_CTRL.mplaypause()
            }
        }
        anchors {
            left: previousButton.right
            leftMargin: 40
            top: trackAlbum.bottom
            topMargin: 75
        }
    }
    Rectangle {
        id: nextButton
        width: 45; height: 45
        color: "transparent"
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
                MPLAYER_CTRL.mnext()
            }
        }
        anchors {
            left: playButton.right
            leftMargin: 40
            top: trackAlbum.bottom
            topMargin: 75
        }
    }
    CustomSlider {
        id: progressBar
        anchors {
            left: parent.left
            leftMargin: 60
            bottom: parent.bottom
            bottomMargin: 20
        }
//        value: MPLAYBACK_MODEL.position / 1000
//        onSliderOnPressed: {
//            MPLAYBACK_MODEL.setMediaPosition(value * 1000)
//        }
    }

//        Slider {
//            id: positionSlider
//            width: parent.width * 0.8
//            value: MPLAYBACK_MODEL.position
//            onValueChanged: {
//                if (Math.abs(positionSlider.value - MPLAYBACK_MODEL.position) > 1000) {
//                    MPLAYBACK_MODEL.setPosition(positionSlider.value)
//                }
//            }
//        }
}
