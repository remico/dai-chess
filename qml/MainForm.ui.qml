import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1

    RowLayout {
        id: buttons
        anchors.centerIn: parent

        Button {
            id: button1
            text: qsTr("Press Me 1")
        }

        Button {
            id: button2
            text: qsTr("Press Me 2")
        }

        Button {
            id: button3
            text: qsTr("Press Me 3")
        }
    }

    ProgressBar {
        id: progressBar1
        anchors.top: buttons.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        maximumValue: 100
        minimumValue: 0
    }

    states: [
        State {
            name: "full"
//            when: button1.pressed
            PropertyChanges { target: progressBar1; value: 100 }
        }
    ]
}

//    MainForm {
//        id: mf
//        anchors.fill: parent
////        button1.onClicked: messageDialog.show(qsTr("Button 1 pressed"))
////        button2.onClicked: messageDialog.show(qsTr("Button 2 pressed"))
//        button3.onClicked: messageDialog.show(qsTr("Button 3 pressed"))
//        button1.onClicked: mf.state == "" ? mf.state = "full" : mf.state = ""

//        transitions: [
//            Transition {
//                from: ""; to: "full";
//                reversible: true
//                NumberAnimation { properties: "value"; duration: 500; easing.type: Easing.OutQuad }
//            }
//        ]
//    }



