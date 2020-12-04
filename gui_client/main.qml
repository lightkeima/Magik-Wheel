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
    title: qsTr("Chiếc nón mlem")
    visible: true
    Item{
        id: datastorage
        visible: false
        objectName: "dataStorage"
        property string guessCharacter: ''
        property bool accpeted: false
        property string  guessKeyword: ""
    }
    FontLoader {
        id: kenneyFutureNarrow;
        source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }

    Image {
        anchors.fill: parent
        source: "../game resources/graphics/7977fbcd22e6155b23421b58340ed2c3.png"
    }
    SoundEffect {
           id: buttonClickSound
           source: "../game resources/audio/UI Sound Pack/MENUBBack.wav"
       }

    Rectangle{
        anchors.centerIn: parent
        width: 290
        height: 190
        color: "#ecf4f3"
        border.color: "#ecf4f3"
        border.width: 10
        radius: 10
        id: joinmenu
            Column{
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: "Your name"
                    fontSizeMode: Text.FixedHeight
                    //anchors.leftMargin: 5;
                    //anchors.fill: parent
                    font.pixelSize: 25
                    color: "#1b1c1d"
                    font.family: kenneyFutureNarrow.name
                }

                TextField {
                    objectName: "tfusername"
                    placeholderText: qsTr("Enter name")
                    font.pixelSize: 25
                    text: ""
                    font.family: kenneyFutureNarrow.name
                }


                Button{
                    objectName: "buttonAccept"
                    property bool accepted: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: btnaccept

                    onClicked: {
                        buttonClickSound.play()
                        btnaccept.state = "accept"
                        stack.push(mainView)
                    }
                    states: State {
                            name: "accept"
                            PropertyChanges { target: btnaccept; accepted: true }
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
                        anchors.horizontalCenter: parent.horizontalCenter
                        id: btnext
                        onClicked: {
                            buttonClickSound.play()
                            Qt.callLater(Qt.quit)}
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
        }
        Row{
            anchors.leftMargin: 15
            anchors.left: parent.left
            anchors.bottomMargin: 15
            anchors.bottom: parent.bottom
            GuessCharacterPanel{}
        }
        //PlayerList{}
    }
    Rectangle{
        anchors.centerIn: parent
        id: resultPanel
        objectName: "resultlist"
        visible: false
        ResultList{}
    }
    Text {
            anchors.centerIn: parent
            objectName: "waitPanel"
            text: "CONNECT TO SERVER"
            //anchors.leftMargin: 5;
            //anchors.fill: parent
            font.pixelSize: 60
            color: "#ff8800"
            font.family: kenneyFutureNarrow.name
     }
    Rectangle {
        id:guesspanel
        objectName: "guesspanel"
        visible: false
        anchors.centerIn: parent
        height: 170
        width: 250
        color: "#ecf4f3"
        border.color: "#00b30c"
        border.width: 2
        radius: 3
        Column{
        Text {
            text: " Guess keyword?"
                //anchors.leftMargin: 5;
                //anchors.fill: parent
            font.pixelSize: 25
            color: "#1b1c1d"
            font.family: kenneyFutureNarrow.name
         }
        Rectangle{
          id:tfrec
          width: 250
          height: 45
         TextField {
            anchors.fill: tfrec
            objectName: "tfguess"
            placeholderText: qsTr("Enter keyword")
            font.pixelSize: 25
            font.family: kenneyFutureNarrow.name
            maximumLength: 30
         }
        }

         Button{
             objectName: "buttonGuessAccept"
             property bool accepted: false
             anchors.horizontalCenter: parent.horizontalCenter
             id: btnguessaccept

             onClicked: {
                 buttonClickSound.play()
                 btnguessaccept.accepted=true
                 guesspanel.visible=false
                 }

             background: Rectangle {
                 id: bg3
                 implicitWidth: 160
                 implicitHeight: 37
                 color: "#ecf4f3"
                 border.color: "#00b30c"
                 border.width: 3
                 radius: 4
                 }
              DropShadow {
                 anchors.fill: bg3
                 horizontalOffset: 3
                 verticalOffset: 3
                 radius: 10.0
                 samples: 17
                 color: btnaccept.down ? "#7fff3b" : "#80000000";
                 source: bg3
                 }
              Text {
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
             anchors.horizontalCenter: parent.horizontalCenter
             id: btnguessexit
             onClicked: {
                 buttonClickSound.play()
                 guesspanel.visible=false
                 }
             background: Rectangle {
                 id: bg4
                 implicitWidth: 160
                 implicitHeight: 37
                 color: "#ecf4f3"
                 border.color: "#fc3d03"
                 border.width: 3
                 radius: 4
                 }
             DropShadow {
                 anchors.fill: bg4
                 horizontalOffset: 3
                 verticalOffset: 3
                 radius: 10.0
                 samples: 17
                 color: btnext.down ? "#ff3c2e" : "#80000000";
                 source: bg4
             }

             Text {
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
}

