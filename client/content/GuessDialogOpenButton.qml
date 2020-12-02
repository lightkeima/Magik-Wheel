/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import client.guessbutton 1.0
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.12
import QtMultimedia 5.15

Button {
    anchors.horizontalCenter: parent.horizontalCenter
    SoundEffect {
           id: buttonClickSound
           source: "../game resources/audio/UI Sound Pack/MENUBBack.wav"
       }
    FontLoader {
        id: kenneyFutureNarrow;
        source: "../game resources/fonts/kenney_fontpackage/Fonts/Kenney Future Narrow.ttf" }
    id: container
    property string name: "Guess the Keyword"
    objectName: "guess_button"
    background: Rectangle {
                id: bg
                implicitWidth: 300
                implicitHeight: 37
                color: "#ecf4f3"
                border.color: "#f5b642"
                border.width: 3
                radius: 4
            }
    DropShadow {
        anchors.fill: bg
        horizontalOffset: 3
        verticalOffset: 3
        radius: 10.0
        samples: 17
        color: container.down ? "#faed00" : "#80000000";
        source: bg
    }

    Text {
        id: text
        text: name
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
    onClicked: {
        buttonClickSound.play()
        guessdialog.open()
    }
    Item{
        Dialog {
            id: guessdialog
            ColumnLayout{
                spacing: 5
                Text {
                    text: "Guess the keyword"
                    fontSizeMode: Text.FixedHeight
                    //anchors.leftMargin: 5;
                    //anchors.fill: parent
                    font.pixelSize: 25
                    color: "#1b1c1d"
                    font.family: kenneyFutureNarrow.name
                }
                TextField {
                    Layout.fillWidth: true
                    placeholderText: qsTr("Enter something")
                    maximumLength: 30
                    font.family: kenneyFutureNarrow.name
                    font.pixelSize: 20
                }
                    Button{
                        id: btnaccept
                        background: Rectangle {
                                id: bg1
                                implicitWidth: 150
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

            }
            onAccepted: console.log("Ok clicked")
            onRejected: console.log("Cancel clicked")
            background: Rectangle {
                color: "#facaca"
                border.color: "#eb3434"
                border.width: 3
                radius: 10
            }

    }

    }

}
