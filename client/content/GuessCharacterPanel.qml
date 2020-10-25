import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    FontLoader {
        id: kenneyFutureNarrow;
        source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

    id: guessPanel
    width: 535
    height: 95
    color: "#ecf4f3"
    border.color: "#51adcf"
    border.width: 3
    radius: 10
    Grid {
        anchors.left: guessPanel.left
        anchors.leftMargin: 10
        anchors.top: guessPanel.top
        anchors.topMargin: 10
        columns: 13
        spacing: 5
        Repeater {
            id: digits
            model: ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
            CharacterButton{
                source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
                angle: 180
                yAxis: 1
                character: modelData
           }
        }
    }

}
