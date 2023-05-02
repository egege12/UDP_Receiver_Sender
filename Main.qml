import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property string x_e_Chrg
    property string x_Avg_Cosu_Daily
    property string x_Avg_Cosu_Trp
    property string x_E_Genr_Daily_Wh
    property string x_E_Cosu_Daily_Wh
    property string x_ESS_SW_Ver_MAJ
    property string x_ESS_SW_Ver_MIN
    property string x_ESS_SW_Ver_REV
    property string x_ESS_SW_Ver_DEV
    property string x_M_Max_Mot_1
    property string x_Req_Trq_Mot
    property string x_M_Min_Mot_1
    property string x_Acc_Pdl_Pos
    property string x_Stat_Ret
    property string x_Brk_Pdl_Pos
    property string x_M_Max_Avl
    property string x_Spd_Lim_Der
    property string x_ACU_Trq_Der
    property string x_M_Rls


    Rectangle{
        anchors.fill: parent


        Text{
            anchors.alignWhenCentered: parent
            id: name1
            text: qsTr(x_e_Chrg)
            width :80
            font.pixelSize: 18
            antialiasing: true
            font.hintingPreference: Font.PreferNoHinting
            style: Text.Normal
            focus: false
            font.weight: Font.Medium
            font.family: "Verdana"
        }
        Text{
            anchors.left: name1
            anchors.leftMargin: 15
            id: name2
            text: qsTr(x_Avg_Cosu_Daily)
            width :80
            font.pixelSize: 18
            antialiasing: true
            font.hintingPreference: Font.PreferNoHinting
            style: Text.Normal
            focus: false
            font.weight: Font.Medium
            font.family: "Verdana"
        }
        Text{
            anchors.left: name2
            anchors.leftMargin: 15
            id: name3
            text: qsTr(x_Avg_Cosu_Trp)
            width :80
            font.pixelSize: 18
            antialiasing: true
            font.hintingPreference: Font.PreferNoHinting
            style: Text.Normal
            focus: false
            font.weight: Font.Medium
            font.family: "Verdana"
        }
    }
    Connections{
        target:udpReceive
        onDataChanged: {
            x_e_Chrg = udpReceive.getValue("X_E_Chrg");
            x_Avg_Cosu_Daily=udpReceive.getValue("X_Avg_Cosu_Daily");
            x_Avg_Cosu_Trp=udpReceive.getValue("X_Avg_Cosu_Trp");
        }
    }
}
