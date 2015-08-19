import QtQuick 2.4
import "functions.js" as Funcs

Image {
    height: width
    visible: false
    x: parent.width / 2 - width / 2
    y: parent.width / 2 - width / 2
    z: ma.drag.active ? 1 : 0       // active item should cover any other items

    property int idx
    property point initPoint: Qt.point(x, y)
    property alias draggable: ma.enabled
    property var validator

    MouseArea {
        id: ma
        anchors.fill: parent
        drag.target: parent

        property point startPoint

        onPressed: {
            startPoint = Qt.point(parent.x, parent.y);
        }

        onReleased: {
            var currentX = parent.x + mouseX;
            var currentY = parent.y + mouseY;
            var sCell = Funcs.cellByPosition(startPoint.x, startPoint.y);
            var dCell = Funcs.cellByPosition(currentX, currentY);

            if (currentX < 0 || currentX >= parent.width * 8 ||
                    currentY < 0 || currentY >= parent.height * 8 ||
                    sCell == dCell) {   // paranoid mode is ON:)
                moveToCell(sCell);
            }
            else {
                if (validator && !validator.isMoveValid(idx, sCell, dCell))
                    moveToCell(sCell);
                else
                    moveToCell(game.move(idx, sCell, dCell) ? dCell : sCell);
            }
        }
    }

    Behavior on x { PropertyAnimation { duration: 100 } }
    Behavior on y { PropertyAnimation { duration: 100 } }

    function init() { x = initPoint.x; y = initPoint.y; }

    function moveToCell(cell) {
        x = Funcs.columnByCell(cell) * width;
        y = Funcs.rowByCell(cell) * height;
    }
}

