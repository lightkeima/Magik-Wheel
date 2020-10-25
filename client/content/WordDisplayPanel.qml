import QtQuick 2.0

Grid {
    id: container
    objectName: "wordPanel"
    columns: 15
    spacing: 2
    anchors.horizontalCenter: parent.horizontalCenter
    /*
    Repeater{
        model: word.length
        CharacterCard{
            source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
            angle: 180
            yAxis: 1
            character: word[index]
            //character: "char" + index
            objectName: "char" + index
        }
    }*/
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char0"
        visible: true
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char1"
        visible: true
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char2"
        visible: true
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char3"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char4"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char5"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char6"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char7"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char8"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char9"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char10"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char11"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char12"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char13"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char14"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char15"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char16"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char17"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char18"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char19"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char20"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char21"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char22"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char23"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char24"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char25"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char26"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char27"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char28"
        visible: false
    }
    CharacterCard{
        source: "../game resources/graphics/uipack_fixed/PNG/green_button06.png"
        angle: 180
        yAxis: 1
        character: ""
        objectName: "char29"
        visible: false
    }
}
