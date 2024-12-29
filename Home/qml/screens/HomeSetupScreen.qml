import "../components"
import QtQuick 2.12
import AppEnums 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.5

Item {
    id: root
    property bool isSelect: true
    ColumnLayout {
        id: colum1
        spacing: -1
        width: 150
        height: parent.height
        anchors.top: status_bar.bottom
        Rectangle {
            width: parent.width
            height: 50
            border.width: 1; border.color: "blue"
            color: "#e6e6fa"
            Text {
                anchors.fill: parent
                anchors.leftMargin: 5
                verticalAlignment: Text.AlignVCenter
                text: TRANSLATE_MODEL.STR_LANGUAGE
                font.pixelSize: 20
                font.bold: isSelect
                color: isSelect?"red":"black"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: isSelect = true;
            }
        }

        Rectangle {
            width: parent.width
            height: 50
            border.width: 1; border.color: "blue"
            color: "#e6e6fa"
            Text {
                anchors.fill: parent
                anchors.leftMargin: 5
                verticalAlignment: Text.AlignVCenter
                text: TRANSLATE_MODEL.STR_VOLUME
                font.pixelSize: 20
                font.bold: !isSelect
                color: !isSelect?"red":"black"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: isSelect = false;
            }
        }
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "#e6e6fa"
            border {
                width: 1
                color: "blue"
            }
        }
    }

    ButtonGroup {id: radioGroup}
    ColumnLayout {
        visible: isSelect
        id: colum2
        spacing: -1
        width: root.width - colum1.width
        height: parent.height
        anchors.left: colum1.right
        anchors.top: status_bar.bottom
        RadioButton {
            id: btn1
            checked: (TRANSLATE_MODEL.currentLanguage === "English")
            implicitHeight: 50
            text: TRANSLATE_MODEL.STR_ENGLISH
            contentItem: Text {
                text: btn1.text
                color: btn1.checked?"red":"black"
                font.pixelSize: 18; font.bold: btn1.checked
                leftPadding: btn1.indicator.width + btn1.spacing
                verticalAlignment: Text.AlignVCenter
            }

            onToggled: {
                if(checked){
                    TRANSLATE_MODEL.setTranslation("AppLanguage_en")
                    TRANSLATE_MODEL.setCurrentLanguage("English")
                    TRANSLATE_CTRL.requestChangeLanguage();
                }
            }

            ButtonGroup.group: radioGroup
        }
        Rectangle {
            height: 1
            color: "blue"
            width: colum2.width - 20
            Layout.alignment: Qt.AlignHCenter
        }

        RadioButton {
            id: btn2
            checked: (TRANSLATE_MODEL.currentLanguage === "VietNam")
            implicitHeight: 50
            text: TRANSLATE_MODEL.STR_VIETNAMESE
            contentItem: Text {
                text: btn2.text
                color: btn2.checked?"red":"black"
                font.pixelSize: 18; font.bold: btn2.checked
                leftPadding: btn2.indicator.width + btn2.spacing
                verticalAlignment: Text.AlignVCenter
            }

            onToggled: {
                if(checked){
                    TRANSLATE_MODEL.setTranslation("AppLanguage_vi")
                    TRANSLATE_MODEL.setCurrentLanguage("VietNam")
                    TRANSLATE_CTRL.requestChangeLanguage();
                }
            }

            ButtonGroup.group: radioGroup
        }
        Rectangle {
            height: 1
            color: "blue"
            width: colum2.width - 20
            Layout.alignment: Qt.AlignHCenter
        }
        Item {
            Layout.fillHeight: true
        }
    }

    VolumeSetting {
        visible: !isSelect
        anchors {
            left: colum1.right
            leftMargin: 130
            top: status_bar.bottom
            topMargin: 210

        }
    }
    StatusBar {
        id: status_bar
        isIconVisible: true
    }
}

