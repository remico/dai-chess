import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import SimpleChess 1.0

ApplicationWindow {
    id: mainwnd
    title: qsTr("Simple Chess")
    visible: true
    width: 600
    height: chessboard.height + buttons.height
    minimumWidth: 600
    minimumHeight: chessboard.height + buttons.height

    property bool dirty: false

    Action {
        shortcut: "Ctrl+Q"
        onTriggered: close()
    }

    onClosing: {
        close.accepted = !dirty
        if (dirty) saveDialog.askSave(qsTr("Quit"), mainwnd.close)
    }

    Game {
        id: game
        objectName: "Game"
        onScreenIdChanged: {
            dirty = Game.Screen_2 === screenId;
            buttons.updateUI(screenId);
        }
    }

    ColumnLayout {
        ButtonBar {
            id: buttons
            onStart: game.start()
            onStop:  {
                if (dirty) saveDialog.askSave(qsTr("Unsaved Game"), game.stop);
                else game.stop();
            }
            onLoad:  historyDialog.loadGame(game.load)
            onSave:  historyDialog.saveGame(function(filepath) {
                                                game.save(filepath);
                                                dirty = false;
                                            });
            onPrev: game.prev()
            onNext: game.next()
        }

        ChessBoard {
            id: chessboard
            objectName: "chessboard"
            width: 600
        }
    }

    HistoryDialog { id: historyDialog }

    MessageDialog {
        id: saveDialog
        standardButtons: StandardButton.Yes|StandardButton.No|StandardButton.Cancel
        text: qsTr("Do you want to save the Game?")

        property var callback: null

        onYes: {
            historyDialog.saveGame(function(filepath) {
                                      game.save(filepath);
                                      dirty = false;
                                      if (callback) callback();
                                   });
        }

        onNo: {
            dirty = false;
            if (callback) callback();
        }

        function askSave(title, cb) {
            saveDialog.title = title;
            saveDialog.callback = (typeof cb !== 'undefined') ? cb : null;
            saveDialog.open();
        }
    }
}
