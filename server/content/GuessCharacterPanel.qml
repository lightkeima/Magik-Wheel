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
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "a"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "b"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "c"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "d"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "e"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "f"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "g"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "h"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "i"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "j"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "k"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "l"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "m"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "n"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "o"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "p"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "q"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "r"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "s"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "t"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "u"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "v"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "w"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "x"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "y"
        }
        CharacterButton{
            source: "../game resources/graphics/uipack_fixed/PNG/blue_button06.png"
            angle: 180
            yAxis: 1
            character: "z"
        }
    }

}
