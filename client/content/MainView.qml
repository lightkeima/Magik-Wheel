import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import "MessagePanel.qml"
import "WordDisplayPanel.qml"
import "GuessDialogOpenButton.qml"
import "GuessCharacterPanel.qml"
import "PlayerList.qml"

Item{
    id: mainView
    Column{
        objectName: "mainColumn"
        anchors.fill: parent
        spacing: 5
        MessagePanel{}
        WordDisplayPanel{}
        GuessDialogOpenButton{}
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
