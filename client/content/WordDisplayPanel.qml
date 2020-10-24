import QtQuick 2.0

Grid {
    id: container
    columns: 15
    spacing: 2
    property int numberOfCharacter: 0
    property string word: "Weebs";
    anchors.horizontalCenter: parent.horizontalCenter
    Component.onCompleted: {
            var component = Qt.createComponent("CharacterCard.qml");
            for (var i = 0; i < word.length; ++i) {
                var object = component.createObject(container);
                object.source = "../game resources/graphics/uipack_fixed/PNG/green_button06.png";
                object.angle = 180;
                object.yAxis = 1;
                object.character = word[i];
            }
        }
}
