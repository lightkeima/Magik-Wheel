import QtQuick 2.0

Rectangle {
    FontLoader {
        id: kenneyFutureNarrow;
        source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

    id: guessPanel
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.topMargin: 10
    property string hint: "is a mostly derogatory slang term for a Western person who is obsessed with Japanese culture, especially anime, often regarding it as superior to all other cultures."
    width: 770
    height: 130
    color: "#ecf4f3"
    border.color: "#51adcf"
    border.width: 3
    radius: 10
    Text {
        id: text
        text: hint
        fontSizeMode: Text.FixedHeight
        anchors.leftMargin: 10
        anchors.left: parent.left
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.bottomMargin: 10
        anchors.bottom: parent.bottom
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 20
        minimumPixelSize: 10
        color: "#1b1c1d"
        font.family: kenneyFutureNarrow.name
    }
}
