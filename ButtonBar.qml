import QtQuick 2.15
import QtQuick.Controls 6.3
import QtQuick.Layouts 1.0
Item {
    id: item
    signal iconSizeClicked()
    signal escapeClicked()
    signal fullScreenClicked()
    property int buttonRadius : 1
    property real buttonOpacity : 0.4

        width: 105
        height: parent.height
    MouseArea{
            width:parent.width
            height:parent.height
            anchors.fill:parent
            hoverEnabled: true
            onEntered: item.buttonOpacity = 1
            onExited: item.buttonOpacity = 0.4

            MenuButton {
                id : buttonIconSize
                width: parent.width/3
                height: parent.height
                buttonImageSource : "qrc:/img/iconIconSizeButton.png"
                clip: false
                buttonOpacity: item.buttonOpacity
                visible: true
                radius: item.buttonRadius
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                hoveredColor:"#d6d4d4"
                pressedColor: "#4f4e4e"
                releasedColor: "#878686"
                onButtonClicked: item.iconSizeClicked()

            }

            MenuButton {
                id : buttonFullscreen
                width: parent.width/3
                height: parent.height
                buttonImageSource : "qrc:/img/iconFullscreenButton.png"
                clip: false
                buttonOpacity: item.buttonOpacity
                visible: true
                radius: item.buttonRadius
                anchors.left: buttonIconSize.right
                anchors.verticalCenter: parent.verticalCenter
                hoveredColor:"#d6d4d4"
                pressedColor: "#4f4e4e"
                releasedColor: "#878686"
                onButtonClicked: item.fullScreenClicked()

            }
            MenuButton {
                id : escapeButton
                width: parent.width/3
                height: parent.height
                buttonImageSource : "qrc:/img/iconEscapeButton.png"
                clip: false
                buttonOpacity: item.buttonOpacity
                visible: true
                radius: item.buttonRadius
                anchors.left: buttonFullscreen.right
                anchors.verticalCenter: parent.verticalCenter
                hoveredColor:"#f00505"
                pressedColor: "#969595"
                releasedColor: "#a80303"
                onButtonClicked: item.escapeClicked()

            }

        }


}
