import QtQuick 2.0
Rectangle{
    id: container
    width:180
    height: 45
    property string name: "<Undefine>"
    property int point: 100
    objectName: "id"
    color: "#ecf4f3"
    border.color: "#51adcf"
    border.width: 2
    radius: 10
    Row {
        id: row
        FontLoader {
            id: kenneyFutureNarrow;
            source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

        function randomNumber() {
            return parseInt(Math.random() * 30 + 1);
        }
        function getRandomAvatar() {
            return "../game resources/graphics/kenney_animalpackredux/PNG/Round without details (outline)/avatar (" + randomNumber() + ").png";
        }
        spacing: 10
        //anchors.fill: parent

        Image{
           source: row.getRandomAvatar()
           width: 45
           height: 45

        }
        Column{
            spacing: 3
            Text {
                id: text_name
                text: container.name
                fontSizeMode: Text.FixedHeight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 17
                minimumPixelSize: 10
                color: "#07689f"
                font.family: kenneyFutureNarrow.name
            }
            Text {
                id: text_point
                text: container.point
                fontSizeMode: Text.FixedHeight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 15
                minimumPixelSize: 10
                color: "#ffc93c"
                font.family: kenneyFutureNarrow.name
            }
        }
    }
}
