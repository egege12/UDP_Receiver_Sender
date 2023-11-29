import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    id: root
    width: 1024
    height: 768
    visible: true
    property bool fullscreen
    property bool iconSize
    property bool darkmode:false
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint  // to hide windows window and still show minimized icon
    title: qsTr("Charger UI")
    color:"transparent"

    property string varTextComType : ""
    Rectangle{
        id:mainRectangle
        anchors.fill:parent
        color:"transparent"
        Rectangle{
            id:topBar
            anchors.top:parent.top
            anchors.right:parent.right
            anchors.left:parent.left
            height:25
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#0ba360"
                }

                GradientStop {
                    position: 0.47945
                    color: "#525252"
                }

                GradientStop {
                    position: 0.52511
                    color: "#525252"
                }

                GradientStop {
                    position: 1
                    color: "#545454"
                }


                orientation: Gradient.Horizontal
            }
            z:5
            Text{
                id : textVersion
                text: qsTr("Charger UI v0.0.013")
                width :80
                height:20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.pixelSize: 13
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
                z:3
            }
            Switch {
                id: switch1
                anchors.right: windowButtonBar.left
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("DarkMode")
                checked: root.darkmode
                onCheckedChanged: {
                    root.darkmode = switch1.checked
                }
            }
            ButtonBar{
                id:windowButtonBar
                anchors.verticalCenter: parent.verticalCenter
                anchors.right:parent.right
                onFullScreenClicked:{
                    if(fullscreen === true){
                        root.showNormal()
                    }else{
                        root.showFullScreen()
                    }
                    fullscreen= !fullscreen}
                onIconSizeClicked: {
                    if(iconSize === true){
                        root.showNormal()
                    }else{
                        root.showMinimized()
                    }
                    iconSize= !iconSize}
                onEscapeClicked: Qt.quit()

            }

        }
        Rectangle{
            id:stackAreaRectangle
            anchors.top:topBar.bottom
            anchors.bottom:parent.bottom
            anchors.right:parent.right
            anchors.left:parent.left
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: (root.darkmode === true) ? "#000000" : "#FFFFFF"
                }

                GradientStop {
                    position: (root.darkmode === true) ?  0.84018 : 0.42466
                    color: (root.darkmode === true) ? "#000000" : "#949494"
                }

                GradientStop {
                    position: 1
                    color: "#262727"
                }
                orientation: Gradient.Vertical
            }
            z:4
            StackView {
                id: stack
                anchors.fill:parent
                initialItem: "qrc:/Sc01_Main.qml"
                z:2
            }
            Rectangle {
                id: navigationBar
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height * .8
                width: 612
                height: 97
                radius: 25
                border.color: "#ffffff"
                z:3
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
                    text: qsTr("Egemen Türker")
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
                    id : monitoringButton
                    width: 120
                    buttonImageSource : "qrc:/img/800_800_MonitoringIcon.png"
                    clip: false
                    visible: true
                    anchors.left:maintenanceGuyPic.right
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter

                }
                TouchButton{
                    id : testButton
                    width: 120
                    buttonImageSource : "qrc:/img/540_540_TestIcon.png"
                    clip: false
                    visible: true
                    anchors.left:monitoringButton.right
                    anchors.verticalCenter: parent.verticalCenter

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
                        stack.push("qrc:/ComInterface.qml")
                    }
                }
            }
        }

        Popup{
            id:popupWindow
            spacing :5
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            focus: true
            modal:true
            anchors.centerIn: parent

            PopupWindow{
                id:windowElement
                onButtonClicked:popupWindow.close();
                onEscapedClicked: popupWindow.close();
            }

        }
        DragHandler {
            onActiveChanged: if(active) startSystemMove();
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton
            z:1
            property int edges: 2;
            property int edgeOffest: 5;

            function setEdges(x, y) {
                edges = 0;
                if(x < edgeOffest) edges |= Qt.LeftEdge;
                if(x > (width - edgeOffest))  edges |= Qt.RightEdge;
                if(y < edgeOffest) edges |= Qt.TopEdge;
                if(y > (height - edgeOffest)) edges |= Qt.BottomEdge;
            }

            cursorShape: {
                return !containsMouse ? Qt.ArrowCursor:
                                        edges == 3 || edges == 12 ? Qt.SizeFDiagCursor :
                                                                    edges == 5 || edges == 10 ? Qt.SizeBDiagCursor :
                                                                                                edges & 9 ? Qt.SizeVerCursor :
                                                                                                            edges & 6 ? Qt.SizeHorCursor : Qt.ArrowCursor;
            }

            onPositionChanged: setEdges(mouseX, mouseY);
            onPressed: {
                setEdges(mouseX, mouseY);
                if(edges && containsMouse) {
                    startSystemResize(edges);
                }
            }
        }
    }
}
