import QtQuick 2.0

Column {
    id: playerList
    objectName: "playerList"
    anchors.rightMargin: 15
    anchors.right: parent.right
    anchors.topMargin: 15
    anchors.top: parent.top
    spacing: 10
    PlayerInforCard{
        name: "Player 0"
        point: 0
        objectName: "player0"
        visible : true
    }
    PlayerInforCard{
        name: "Player 1"
        point: 0
        objectName: "player1"
        visible : true
    }
    PlayerInforCard{
        name: "Player 2"
        point: 0
        objectName: "player2"
        visible : true
    }
    PlayerInforCard{
        name: "Player 3"
        point: 0
        objectName: "player3"
        visible : true
    }
    PlayerInforCard{
        name: "Player 4"
        point: 0
        objectName: "player4"
        visible : false
    }
    PlayerInforCard{
        name: "Player 5"
        point: 0
        objectName: "player5"
        visible : false
    }
    PlayerInforCard{
        name: "Player 6"
        point: 0
        objectName: "player6"
        visible : false
    }
    PlayerInforCard{
        name: "Player 7"
        point: 0
        objectName: "player7"
        visible : false
    }
    PlayerInforCard{
        name: "Player 8"
        point: 0
        objectName: "player8"
        visible : false
    }
    PlayerInforCard{
        name: "Player 9"
        point: 0
        objectName: "player9"
        visible : false
    }

}

