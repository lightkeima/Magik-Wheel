import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtMultimedia 5.15

import "content"
Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Chiếc nón mlem")
    SoundEffect {
           id: buttonClickSound
           source: "../game resources/audio/UI Sound Pack/MENUBBack.wav"
       }
    Image {
        anchors.centerIn: parent
        source: "../game resources/graphics/7977fbcd22e6155b23421b58340ed2c3.png"
    }
    Rectangle{
        anchors.centerIn: parent
        width: 400
        height: 270
        color: "#ecf4f3"
        border.color: "#ecf4f3"
        border.width: 10
        radius: 10
        id: joinmenu
        objectName: "joinmenu"
        FontLoader {
            id: kenneyFutureNarrow;
            source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

            Column{
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: "Server IP"
                    fontSizeMode: Text.FixedHeight
                    //anchors.leftMargin: 5;
                    //anchors.fill: parent
                    font.pixelSize: 25
                    color: "#1b1c1d"
                    font.family: kenneyFutureNarrow.name
                }
                Rectangle{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200
                    height: 37
                TextField {
                    objectName: "server_ip"
                    anchors.fill: parent
                    placeholderText: qsTr("Enter IP")
                    maximumLength: 30
                    font.family: kenneyFutureNarrow.name
                    font.pixelSize: 20
                }
                }
                Text {
                    text: "Player name"
                    fontSizeMode: Text.FixedHeight
                    //anchors.leftMargin: 5;
                    //anchors.fill: parent
                    font.pixelSize: 25
                    color: "#1b1c1d"
                    font.family: kenneyFutureNarrow.name
                }
                Rectangle{

                    width: 200
                    height: 37
                TextField {
                    objectName: "playername"
                    anchors.fill: parent
                    placeholderText: qsTr("Your name")
                    maximumLength: 10
                    font.family: kenneyFutureNarrow.name
                    font.pixelSize: 20
                }
                }
                Button{
                    id: btnaccept
                    onClicked: {
                        buttonClickSound.play()
                        stack.push(mainView)
                    }
                    background: Rectangle {
                        id: bg1
                        implicitWidth: 160
                        implicitHeight: 37
                        color: "#ecf4f3"
                        border.color: "#00b30c"
                        border.width: 3
                        radius: 4
                        }
                     DropShadow {
                        anchors.fill: bg1
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 10.0
                        samples: 17
                        color: btnaccept.down ? "#7fff3b" : "#80000000";
                        source: bg1
                        }
                     Text {

                        id: text1
                        text: "Accept"
                        fontSizeMode: Text.FixedHeight
                        anchors.leftMargin: 5;
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 25
                        minimumPixelSize: 10
                        color: "#1b1c1d"
                        font.family: kenneyFutureNarrow.name
                        }
                    }
                    Button{
                        id: btnext
                        onClicked: {
                            buttonClickSound.play()
                            Qt.callLater(Qt.quit)
                        }
                        background: Rectangle {
                            id: bg2
                            implicitWidth: 160
                            implicitHeight: 37
                            color: "#ecf4f3"
                            border.color: "#fc3d03"
                            border.width: 3
                            radius: 4
                            }
                        DropShadow {
                            anchors.fill: bg2
                            horizontalOffset: 3
                            verticalOffset: 3
                            radius: 10.0
                            samples: 17
                            color: btnext.down ? "#ff3c2e" : "#80000000";
                            source: bg2
                        }

                        Text {
                            id: text2
                            text: "Exit"
                            fontSizeMode: Text.FixedHeight
                            anchors.leftMargin: 5;
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 25
                            minimumPixelSize: 10
                            color: "#1b1c1d"
                            font.family: kenneyFutureNarrow.name
                            }
                        }

        }

    }
    StackView {
        id: stack
        initialItem: joinmenu
        anchors.fill: parent
    }

    Item{
        id: mainView
        visible: false
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

}

