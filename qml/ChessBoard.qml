import QtQuick 2.4

Item {
    height: width

    property int cellSize: width / 8
    property var chessPieces: []

    Grid {
        id: chessgrid
        columns: 8
        rows: 8
        anchors.fill: parent

        Repeater {
            model: 64
            Rectangle {
                width: cellSize
                height: cellSize
                color: ((Math.floor(index / 8) % 2) === 0) ?
                       (index % 2  === 1 ? "#D18B47" : "#FFCE9E") : // light brown
                       (index % 2  === 0 ? "#D18B47" : "#FFCE9E")   // dark brown
            }
        }
    }

    Component.onCompleted: createChessPieces(this);

    function createChessPieces(board) {
        var component = Qt.createComponent("qrc:/qml/ChessPiece.qml");
        if (component.status != Component.Ready) {
            console.warn("Error loading ChessPiece.qml: " + component.errorString());
            return;
        };

        var type;
        var counter = 0;

        for (var row = 0; row < 8; ++row) {
            for (var col = 0; col < 8; ++col) {
                counter++;

                switch (row) {
                case 1: case 6:
                    type = "pawn";
                    break;
                case 0: case 7:
                    switch (col) {
                    case 0: case 7:
                        type = "rook";
                        break;
                    case 1: case 6:
                        type = "knight";
                        break;
                    case 2: case 5:
                        type = "bishop";
                        break;
                    case 3:
                        type = "queen";
                        break;
                    case 4:
                        type = "king";
                        break;
                    }
                break;
                default:
                    continue;
                }

                var chessPiece = component.createObject(board);
                var color = row < 4 ? "black" : "white";
                chessPiece.width = cellSize;
                chessPiece.source = "qrc:/rc/chessimg/" + color + "_" + type + ".svg";
                chessPiece.initPoint.x = col * cellSize;
                chessPiece.initPoint.y = row * cellSize;
                chessPiece.idx = counter;
                chessPiece.objectName = "chesspiece" + counter;
                chessPieces[counter] = chessPiece;
            }
        }
    }

    function init(draggable) {
        for (var idx in chessPieces) {
            chessPieces[idx].visible = true;
            chessPieces[idx].draggable = draggable;
            chessPieces[idx].init();
        }
    }

    function clear() {
        for (var idx in chessPieces) {
            chessPieces[idx].visible = false;
        }
    }
}
