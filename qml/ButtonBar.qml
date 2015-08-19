import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import SimpleChess 1.0

Rectangle {
    width: parent.width
    height: 35
    color: palette.window

    anchors {
        left: parent.left
        top: parent.top
        right: parent.right
        leftMargin: 5
        topMargin: 5
    }

    signal start
    signal stop
    signal load
    signal save
    signal prev
    signal next

    RowLayout {
        Layout.fillWidth: true

        Button {
            id: btn_start
            text: "&Start"
            onClicked: parent.parent.state == "screen_2" ? stop() : start()
        }
        Button {
            id: btn_load
            text: "&Load"
            onClicked: parent.parent.state == "screen_2" ? save() : load()
        }
        Button {
            id: btn_prev
            text: "&Prev"
            opacity: 0
            enabled: false
            onClicked: prev()
        }
        Button {
            id: btn_next
            text: "&Next"
            opacity: 0
            enabled: false
            onClicked: next()
        }
    }

    ColumnLayout {
        anchors { right: parent.right; rightMargin: 10 }
        spacing: 0

        Label {
            text: "<a href=\"http://chessplanet.ru/pages/game-zone/rules/kratkie-pravila-igry-v-shahmaty\">"
                  + qsTr("Online help") + "</a>"
            onLinkActivated: Qt.openUrlExternally(link)
        }

        Label {
            text: "Press <Ctrl+Q> to exit"
        }
    }

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

    states: [
        State {
            name: "screen_2"
            PropertyChanges { target: btn_start; text: "&Stop" }
            PropertyChanges { target: btn_load; text: "Sa&ve" }
            PropertyChanges { target: btn_prev; opacity: 0; enabled: false }
            PropertyChanges { target: btn_next; opacity: 0; enabled: false }
        },
        State {
            name: "screen_3"
            PropertyChanges { target: btn_start; text: "&Start" }
            PropertyChanges { target: btn_load; text: "&Load" }
            PropertyChanges { target: btn_prev; opacity: 1.0; enabled: true }
            PropertyChanges { target: btn_next; opacity: 1.0; enabled: true }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { properties: "opacity"; duration: 500; }
        }
    ]

    function updateUI(screenId) {
        switch (screenId) {
        case Game.Screen_1:
            state = "";
            break;
        case Game.Screen_2:
            state = "screen_2";
            break;
        case Game.Screen_3:
            state = "screen_3";
            break;
        }
    }
}
