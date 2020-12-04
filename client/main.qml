import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import "content"
Window {
    id: window
    width: 1280
    height: 600
    visible: true
    title: qsTr("Chiếc nón mlem")
    Column{
        objectName: "mainColumn"
        anchors.fill: parent
        spacing: 5
        MessagePanel{}
        WordDisplayPanel{}
    }

    Row{
        anchors.leftMargin: 15
        anchors.left: parent.left
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        GuessCharacterPanel{}
    }
    PlayerList{}
}

