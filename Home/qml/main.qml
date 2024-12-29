import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: DBUS_CTRL.modeDisplay
    title: TRANSLATE_MODEL.STR_APP_TITLE
    width: 720
    height: 560
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowCloseButtonHint | Qt.CustomizeWindowHint
    property var layer_base: layer_base_1

    function reloadScreen() {
        layer_base.source = ""
        layer_base.source = SCREEN_MODEL.currentScreen
    }

    function switchLayerBase(from, to) {
        console.log("switchLayerBase");
        if (from.item !== null) {
            from.item.visible = false
            from.source = ""
        }
        if (to.item !== null) {
            to.item.visible = true
        }
        layer_base = from
    }

    // common screen loader
    Loader {
        id: layer_base_1
        anchors.fill: parent

        onLoaded: {
            switchLayerBase(layer_base_2, layer_base_1);
        }
    }

    Loader {
        id: layer_base_2
        anchors.fill: parent

        onLoaded: {
            switchLayerBase(layer_base_1, layer_base_2);
        }
    }
}
