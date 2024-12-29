import QtQuick 2.12
import AppEnums 1.0
import "../components"
import "../helper/getNameSong.js" as GetNameSong
Item {
    id: musicList
    Text {
        anchors.centerIn: parent
        text: TRANSLATE_MODEL.STR_LIST_EMPTY
        visible: MPLAYBACK_MODEL.currentFilePath === ""
    }


    property int currentSongIndex: -1
    property alias musicList: musicListView
    ListView {
        id: musicListView
        width: parent.width
        height: parent.height * 7/8
        currentIndex: currentSongIndex
        anchors {
            left: parent.left
            leftMargin: 5
            top: parent.top
            topMargin: 60
        }
        boundsBehavior: Flickable.StopAtBounds
        model: MLIST_MODEL

        delegate: Item {
            width: parent.width
            height: 35
            Rectangle {
                visible: MPLAYBACK_MODEL.currentFilePath !== ""
                width: parent.width
                height: 1
                color: "#5b9bd5"
                anchors {
                    top: scrollText.bottom
                    topMargin: 8
                }
            }
            Image {
                id: musicPlaying
                source: "qrc:/images/musiclist-playing.png"
                visible: MPLAYBACK_MODEL.currentFilePath === model.filePath
                sourceSize.width: 20
                sourceSize.height: 20
                anchors {
                    left: parent.left
                    leftMargin: 8
                    verticalCenter: scrollText.verticalCenter
                }
            }
            ScrollingText {
                id: scrollText
                //text.font.family: customFont.name
                width: parent.width / 2 - 5
                text.text: GetNameSong.getSongTitle(model.filePath)
                isAllowScroll: MPLAYBACK_MODEL.currentFilePath === model.filePath//index === musicListView.currentIndex
                text.font.bold: MPLAYBACK_MODEL.currentFilePath === model.filePath
                text.color: (MPLAYBACK_MODEL.currentFilePath === model.filePath) ? "red" : "black"
                //isMERegion: true
                anchors {
                    left: MPLAYBACK_MODEL.currentFilePath === model.filePath ? musicPlaying.right : parent.left
                    leftMargin: 8
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(MPLAYBACK_MODEL.currentFilePath !== model.filePath){
                        //MPLAYBACK_MODEL.setMediaPlayerState(0)//MPLAYBACK_MODEL.setCurrentStatus(0) // set current status is stopped
                        MPLAYBACK_MODEL.setMediaPlayerState(0)
                        MPLAYBACK_MODEL.setCurrentFilePath(model.filePath)
                        console.log(model.filePath)//setCurrentMediaName(modelData)
                        MPLAYER_CTRL.mplaypause()
                    }
                }
            } 
        }
    }
    StatusBar {
    }
}
