import QtQuick 2.0
import QtQuick.Controls 2.15

Dialog {
    id: guessdialog
    title: "Title"
    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked")

    TextField {
        placeholderText: qsTr("Enter name")
    }

}
