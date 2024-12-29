import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    Rectangle {
        id: decrease
        width: 30
        height: 30
        border.color: "#124462"; border.width: 1; radius: 15;
        anchors {
            left: parent.left
            //leftMargin: 10
        }
        Rectangle {anchors.centerIn: parent; width: parent.width / 2; height: 2; color: "#124462"}

        MouseArea {
            anchors.fill: parent
            onClicked: slider.value -= 1;
        }
    }

    Slider {
        id: slider
        minimumValue: 0; maximumValue: 10;
        value: DBUS_CTRL.currentVolume
        stepSize: 1
        anchors {
            left: decrease.right
            leftMargin: 10
            verticalCenter: decrease.verticalCenter
        }
        width: 250; height: 16
        onValueChanged: {
            DBUS_CTRL.setCurrentVolume(slider.value);
            DBUS_CTRL.requestChangeVolume();
        }
//        background: Rectangle {
//            id: progressVol
//            width: 250; height: 15
//            anchors.verticalCenter: parent.verticalCenter
//            border.width: 1; border.color: "#124462"
//            Rectangle {
//                id: currentVol
//                color: "#62B3F5"
//                height: parent.height
//                width: parent.width * slider.visualPosition//parent.width * control.value / 10
//            }
//        }
//        handle: Rectangle {
//            anchors.centerIn: parent
//            border.color: "#124462"
//            border.width: 1
//            width: 30
//            height: 30
//            radius: 15
//            Text {
//                anchors.centerIn: parent
//                text: slider.value
//            }
//        }
        style: SliderStyle {
            groove: Rectangle {
                id: progressVol
                width: 250; height: 15
                anchors.verticalCenter: parent.verticalCenter
                border.width: 1; border.color: "#124462"
                radius: 8
                Rectangle {
                    id: currentVol
                    color: "#62B3F5"
                    height: parent.height
                    radius: 8
                    width: parent.width * control.value / control.maximumValue
                }
            }
            handle: Rectangle {
                anchors.centerIn: parent
                border.color: "#124462"
                border.width: 1
                width: 30
                height: 30
                radius: 15
                Text {
                    anchors.centerIn: parent
                    text: slider.value
                }
            }
        }
        //onMoved: {}
//        background:Rectangle {
//            implicitHeight: 7
//            width: parent.width
//            radius: 31
//            color: "#DEDDE3"
//            opacity: 90

//            Rectangle {
//                id: aboveProcessBar
//                width: songProgressBar.visualPosition * parent.width
//                height: parent.height + 1
//                radius: 37
//                color: "#007bbc"
//            }
//        }
    }

    Rectangle {
        id: increase
        width: 30
        height: 30

        border.color: "#124462"; border.width: 1; radius: 15;

        Rectangle {anchors.centerIn: parent; width: parent.width / 2; height: 2; color: "#124462"}
        Rectangle {anchors.centerIn: parent; rotation: 90; width: parent.width / 2; height: 2; color: "#124462"}

        MouseArea {
            anchors.fill: parent
            onClicked: {
                slider.value += 1;
            }
        }
        anchors {
            left: slider.right
            leftMargin: 10
        }
    }
}
