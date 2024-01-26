import QtQuick 6.2
import QtQuick.Window 2.15
import QtQuick.Controls 6.2

Window {
    id: root
    width: 1024
    height: 768
    visible: true
    property bool fullscreen
    property bool iconSize
    property bool darkmode:false
    property bool naviBarActive:false

    //CONSTANTS
    //-------------------------------------
    property var naviAreaHeight : 30 ;


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
            anchors.bottomMargin:naviAreaHeight
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
            z:3
            StackView {
                id: stack
                anchors.fill:parent
                initialItem: "qrc:/Sc1010_Main.qml"
                z:2

            }

        }
        Rectangle{
            id:naviArea
            anchors.bottom:parent.bottom
            height : naviAreaHeight
            anchors.right: parent.right
            anchors.left:parent.left
            clip: false
            z:4
            NavigationBar{
                id: navigationBar
                accountMaintenance:"Egemen Turker"

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
    Connections{
        target:internalOp
        onActiveScreenChanged:{
            if(internalOp.activeScreen === 1010){
                stack.pop()
                stack.push("qrc:/Sc1010_Main.qml")
            }else if(internalOp.activeScreen === 2010){

            }else if(internalOp.activeScreen === 2020){

            }else if(internalOp.activeScreen === 2030){
                stack.pop()
                stack.push("qrc:/Sc2030_ComMon.qml")
            }
        }
    }

}
