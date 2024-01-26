import QtQuick 6.2
import QtQuick.Controls 6.2
Rectangle {
    id:buttonRectangle
    signal buttonClicked()
    signal buttonReleased()
    signal buttonEntered()
    signal buttonExited()
    property string buttonImageSource: ""
    property bool disableButtonClick
    property real buttonOpacity : 1
    property color disabledColor : "#9e9b9b"
    property color pressedColor : "#575757"
    property color releasedColor : "#707070"
    property color hoveredColor : "#4A4A4A"
    property real imageRatio : 0.9
    height: width
    radius: width
    opacity : buttonRectangle.buttonOpacity
    onDisableButtonClickChanged: disableButtonClick ? disabledColor : releasedColor
    color :disableButtonClick ? disabledColor : releasedColor
    Image{
        id:image
        width: parent.width*imageRatio
        height: parent.height*imageRatio
        anchors.centerIn: parent
        antialiasing: true
        source: parent.buttonImageSource
        opacity: parent.disableButtonClick ? 0.4 : 1.0
        fillMode:Image.PreserveAspectFit
        z:1
    }


    MouseArea{
        id:mouseArea
        anchors.fill: parent
        onPressed: parent.color = parent.disableButtonClick ? parent.disabledColor : parent.pressedColor
        onReleased: {
            parent.color = parent.disableButtonClick ? parent.disabledColor : parent.releasedColor
            parent.disableButtonClick ? undefined : parent.buttonReleased()
        }
        onClicked: {parent.disableButtonClick ? undefined: parent.buttonClicked()}
        hoverEnabled: true
        onEntered: {
            if(parent.disableButtonClick === false){parent.color = parent.hoveredColor; parent.buttonEntered()}}
        onExited: {if(parent.disableButtonClick === false) { parent.color = parent.releasedColor; parent.buttonExited()}}
        z:2
    }

}

