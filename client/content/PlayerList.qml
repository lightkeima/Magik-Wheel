import QtQuick 2.0

Column {
    id: playerList
    anchors.rightMargin: 15
    anchors.right: parent.right
    anchors.topMargin: 15
    anchors.top: parent.top
    spacing: 10
    property variant names: ["Weebs", "aaa", "lmao"]
    property variant points: [0, 3, 4]
    Component.onCompleted: {
        var component = Qt.createComponent("PlayerInforCard.qml");
        for (var i = 0; i < names.length; ++i) {
            var object = component.createObject(playerList);
            object.name = names[i];
            object.point = points[i];
            object.objectName = "player"+i
         }
     }
}

