import QtQuick 6.2

Rectangle {

    property string accountMaintenance
    property bool naviDownsize: false

    radius: 25
    border.color: "#ffffff"
    anchors.horizontalCenter: parent.horizontalCenter
    y:-120
    width: 712
    height: 97
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#858585"
        }

        GradientStop {
            position: 1
            color: "#00000000"
        }
        orientation: Gradient.Vertical
    }
    Text{
        id : maintenanceGuyName
        text: accountMaintenance
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right:maintenanceGuyPic.left
        font.pixelSize: 18
        antialiasing: true
        font.hintingPreference: Font.PreferNoHinting
        style: Text.Normal
        focus: false
        font.weight: Font.Medium
        font.family: "Verdana"
        color: "white"
        wrapMode: Text.Wrap
        elide: Text.ElideNone
    }
    Image{
        id:maintenanceGuyPic
        anchors.left:parent.left
        anchors.leftMargin:100
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        antialiasing: true
        source:"qrc:/img/500_500_Worker.png"
        fillMode:Image.PreserveAspectFit
    }
    TouchButton{
        id : userButton
        width: 120
        buttonImageSource : "qrc:/img/800_800_MonitoringIcon.png"
        clip: false
        visible: true
        anchors.left:maintenanceGuyPic.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        disableButtonClick: false
        onButtonClicked: {
            internalOp.activeScreen= 1010
        }
    }
    TouchButton{
        id : monitoringButton
        width: 120
        buttonImageSource : "qrc:/img/800_800_MonitoringIcon.png"
        clip: false
        visible: true
        anchors.left:userButton.right
        anchors.verticalCenter: parent.verticalCenter
        disableButtonClick: true
        onButtonClicked: {
            internalOp.activeScreen= 2010
        }
    }
    TouchButton{
        id : testButton
        width: 120
        buttonImageSource : "qrc:/img/540_540_TestIcon.png"
        clip: false
        visible: true
        anchors.left:monitoringButton.right
        anchors.verticalCenter: parent.verticalCenter
        disableButtonClick: true
        onButtonClicked: {
            internalOp.activeScreen= 2020
        }
    }
    TouchButton{
        id : comButton
        width: 120
        buttonImageSource : "qrc:/img/512_512_ComInterface.png"
        clip: false
        visible: true
        anchors.left:testButton.right
        anchors.verticalCenter: parent.verticalCenter
        onButtonClicked: {
            internalOp.activeScreen= 2030
        }


    }

}

