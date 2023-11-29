import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
Rectangle {
    anchors.fill:parent

    color:"transparent"
    Rectangle{
        id:transmitSignals
        width:parent.width/2
        anchors.top: parent.top
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        color:"transparent"

        ScrollView{
            id:scrollViewTxObject
            anchors.fill: parent
            clip: true
            ScrollBar.vertical.interactive: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Grid{
                id:gridTx
                columns: 1
                spacing: 5

                property var createdBoxes: [] // Kutu nesnelerini tutacak dizi

                function createBox(text) {
                    var rectWidth =350;
                    var rectHeight = 18;
                    var rect = Qt.createQmlObject(
                                "import QtQuick 2.15; Rectangle { width: " + rectWidth + "; height: " + rectHeight + "; color: 'grey'; opacity: 0.6;}",
                                gridTx // Add the Rectangle as a child of the Column
                                );
                    var rectValWidth =100;
                    var rectVal = Qt.createQmlObject(
                                "import QtQuick 2.15; Rectangle { width: " + rectValWidth + "; height: " + rectHeight + "; color: 'darkgrey'; opacity: 0.6; }",
                                rect
                                );
                    rectVal.anchors.right = rect.right;
                    var textItem = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: '" + text + "'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rect
                                );
                    textItem.anchors.left = rect.left;
                    textItem.anchors.stop = rect.top;
                    textItem.anchors.leftMargin = 5;
                    textItem.anchors.horizontalCenter= rect.horizontalCenter;
                    var textDot = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: ':'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rect
                                );
                    textDot.anchors.right = rectVal.left;
                    var textVal = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: '--'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rectVal
                                );
                    textVal.anchors.left = rectVal.left;
                    textVal.anchors.leftMargin=5;
                    textVal.anchors.verticalCenter = rectVal.verticalCenter;
                    udpSend.dataChanged.connect(function(){
                        textVal.text= udpSend.getValue(textItem.text)
                    });

                    createdBoxes.push(rect);
                }

                function createBoxes() {

                    var linesArray =  udpSend.getDataList();
                    for (var j = 0; j < linesArray.length; j++) {
                        createBox(linesArray[j])
                    }

                }
                function clearBoxes() {
                    for (var i = 0; i < createdBoxes.length; i++) {
                        createdBoxes[i].destroy() // Oluşturulmuş kutuları yok et
                    }
                    createdBoxes = [] // Diziyi boşalt
                }
            }
        }
    }
    Rectangle{
        id:receiveSignals
        width:parent.width/2
        anchors.top: parent.top
        anchors.bottom:parent.bottom
        anchors.right:parent.right
        color:"transparent"

        ScrollView{
            id:scrollViewRxObject
            anchors.fill: parent
            clip: true
            ScrollBar.vertical.interactive: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Grid{
                id:gridRx
                columns: 1
                spacing: 5

                property var createdBoxes: [] // Kutu nesnelerini tutacak dizi

                function createBox(text) {
                    var rectWidth =350;
                    var rectHeight = 18;
                    var rect = Qt.createQmlObject(
                                "import QtQuick 2.15; Rectangle { width: " + rectWidth + "; height: " + rectHeight + "; color: 'grey'; opacity: 0.6;}",
                                gridRx // Add the Rectangle as a child of the Column
                                );
                    var rectValWidth =100;
                    var rectVal = Qt.createQmlObject(
                                "import QtQuick 2.15; Rectangle { width: " + rectValWidth + "; height: " + rectHeight + "; color: 'darkgrey'; opacity: 0.6; }",
                                rect
                                );
                    rectVal.anchors.right = rect.right;
                    var textItem = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: '" + text + "'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rect
                                );
                    textItem.anchors.left = rect.left;
                    textItem.anchors.stop = rect.top;
                    textItem.anchors.leftMargin = 5;
                    textItem.anchors.horizontalCenter= rect.horizontalCenter;
                    var textDot = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: ':'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rect
                                );
                    textDot.anchors.right = rectVal.left;
                    var textVal = Qt.createQmlObject(
                                "import QtQuick 2.15; Text { text: '--'; color: 'black'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                                rectVal
                                );
                    textVal.anchors.left = rectVal.left;
                    textVal.anchors.leftMargin=5;
                    textVal.anchors.verticalCenter = rectVal.verticalCenter;
                    udpReceive.dataChanged.connect(function(){
                        textVal.text= udpReceive.getValue(textItem.text)
                    });

                    createdBoxes.push(rect);
                }

                function createBoxes() {

                    var linesArray =  udpReceive.getDataList();
                    for (var j = 0; j < linesArray.length; j++) {
                        createBox(linesArray[j])
                    }

                }
                function clearBoxes() {
                    for (var i = 0; i < createdBoxes.length; i++) {
                        createdBoxes[i].destroy() // Oluşturulmuş kutuları yok et
                    }
                    createdBoxes = [] // Diziyi boşalt
                }
            }
        }
    }
    Component.onCompleted: {
        console.log("ComInterface.qml loaded.")
        gridRx.createBoxes();
        gridTx.createBoxes();
    }
    Component.onDestruction: {
        console.log("ComInterface.qml destructed.")
        gridRx.clearBoxes();
        gridTx.clearBoxes();
    }

}
