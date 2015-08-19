import QtQuick 2.4
import QtQuick.Dialogs 1.2

FileDialog {
    nameFilters: ["Chess History (*.chh)"]
    selectedNameFilter: "Chess History (*.chh)"

    property var callback: null
    property var hasExtension: /\.chh$/

    function saveGame(cb) {
        title = qsTr("Save Game");
        selectExisting = false;
        callback = (typeof cb !== 'undefined') ? cb : null;
        open();
    }

    function loadGame(cb) {
        title = qsTr("Load Game");
        selectExisting = true;
        callback = (typeof cb !== 'undefined') ? cb : null;
        open();
    }

    onAccepted: {
        var filename = hasExtension.test(fileUrl) ? fileUrl : fileUrl + ".chh";
        if (callback) callback(filename);
    }
}
