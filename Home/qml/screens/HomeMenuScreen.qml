import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import AppEnums 1.0
import "../components"
Item {
    id: root
    property int currIdx: 0
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: currIdx
        Page {
            id: mediaPage
            BaseButton {
                id: music
                anchors {
                    left: parent.left
                    leftMargin: 25
                    verticalCenter: parent.verticalCenter
                }

                text: TRANSLATE_MODEL.STR_MUSIC_TITLE
                imageSrc: DBUS_CTRL.currentCoverArt || "qrc:/images/music-default.png" //||
                imageWidth: 180
                imageHeight: 180
                onClicked: {
                    console.log("music app")
                    DBUS_CTRL.requestDisplayMusicPlayer()
                    DBUS_CTRL.setModeDisplay(false)
                }
                ScrollingText {
                    id: title_text
                    text.text: (DBUS_CTRL.currentTitle === "")? TRANSLATE_MODEL.STR_TITLE + " : " + TRANSLATE_MODEL.STR_UNKNOWN
                                                           :(TRANSLATE_MODEL.STR_TITLE + " : " + DBUS_CTRL.currentTitle)
                    text.font.pixelSize: 15
                    //text.font.bold: true
                    width: parent.width / 2
                    isAllowScroll: true
                    anchors {
                        left: parent.left
                        leftMargin: 80
                        bottom: parent.bottom
                        bottomMargin: 20
                    }
                }
                ScrollingText {
                    id: artist_text
                    text.text: (DBUS_CTRL.currentArtist === "")? TRANSLATE_MODEL.STR_ARTIST + " : " + TRANSLATE_MODEL.STR_UNKNOWN
                                                           :(TRANSLATE_MODEL.STR_ARTIST + " : " + DBUS_CTRL.currentArtist)

                    text.font.pixelSize: 15
                    //text.font.bold: true
                    width: parent.width / 2
                    isAllowScroll: true
                    anchors {
                        left: parent.left
                        leftMargin: 80
                        bottom: parent.bottom
                        bottomMargin: 0
                    }
                }
            }
            BaseButton {
                id: video
                anchors {
                    left: music.right
                    leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }

                text: TRANSLATE_MODEL.STR_VIDEO_TITLE
                imageSrc: "qrc:/images/video-default.png"
                imageWidth: 200
                imageHeight: 200
                onClicked: {
                    console.log("video app")
                    DBUS_CTRL.requestDisplayVideoPlayer()
                    DBUS_CTRL.setModeDisplay(false)
                }
                ScrollingText {
                    id: videoName
                    text.text: (DBUS_CTRL.currentVideoName === "") ? TRANSLATE_MODEL.STR_UNKNOWN : DBUS_CTRL.currentVideoName;
                    text.font.pixelSize: 20
                    width: video.width / 2
                    isAllowScroll: true
                    anchors {
                        right: parent.right
                        rightMargin: 80
                        bottom: parent.bottom
                        bottomMargin: 0
                    }
                }
            }
        }
        Page {
            id: settingPage
            BaseButton {
                id: setting
                anchors {
                    left: parent.left
                    leftMargin: 30
                    verticalCenter: parent.verticalCenter
                }

                text: TRANSLATE_MODEL.STR_SETTINGS
                imageSrc: "qrc:/images/setting.png"
                imageWidth: 200
                imageHeight: 200

                onClicked: {
                    console.log("setting app")
                    SCREEN_CTRL.pushScreen(AppEnums.SCREEN_ID_HOME_SETTUP)
                    currIdx = 1
                }
            }
        }
    }
    PageIndicator {
        id: indicator
        count: swipeView.count
        currentIndex: swipeView.currentIndex
        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: swipeView.horizontalCenter
        anchors.bottomMargin: 10
        delegate: Rectangle {
            width: 30
            height: 8
            color: "blue"
            opacity: index === indicator.currentIndex ? 0.6: 0.2
        }
    }

    StatusBar {
        id: statusBar
        isIconVisible: false
    }
}
