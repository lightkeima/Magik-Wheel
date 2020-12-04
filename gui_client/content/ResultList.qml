import QtQuick 2.0

Column {
    id: res
    spacing: 10
    anchors.centerIn: parent
    FontLoader {
        id: kenneyFutureNarrow;
        source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

    Text {
        id: text
        text: "Top 3 players"
        font.pixelSize: 30
        minimumPixelSize: 10
        color: "#08c71e"
        font.family: kenneyFutureNarrow.name
    }
    PlayerInforCard{
        name: "Player 0"
        border.width: 3
        border.color: "#08c71e"
        point: 0
        objectName: "top1"
        visible : true
        width: 250
        height: 60
    }
    PlayerInforCard{
        name: "Player 1"
        border.width: 3
        border.color: "#ffc803"
        point: 0
        objectName: "top2"
        visible : true
        width: 230
        height:  60
    }
    PlayerInforCard{
        name: "Player 2"
        border.width: 3
        border.color: "#d90b00"
        point: 0
        objectName: "top3"
        visible : true
        width: 210
        height: 60
    }
}

