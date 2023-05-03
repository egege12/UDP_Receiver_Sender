import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property string x_E_Psng2_AC_Cosu_kWh
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

    Rectangle{
        id:rec1
        anchors.alignWhenCentered: parent
        width : name1.implicitWidth;
        height: name1.implicitHeight;
        border.width: 2
        border.color : "black"
        Text{

            id: name1
            text: qsTr(x_E_Psng2_AC_Cosu_kWh)
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
    Rectangle{
        id: rec2
        anchors.top: rec1.bottom
        anchors.topMargin: 15
        width : name2.implicitWidth;
        height: name2.implicitHeight;
        border.width: 2
        border.color : "black"
        Text{

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
    }Rectangle{
        id:rec3
        anchors.top: rec2.bottom
        anchors.topMargin: 15
        width : name3.implicitWidth;
        height: name3.implicitHeight;
        border.width: 2
        border.color : "black"
        Text{

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
    Rectangle{
            id:rec4
            anchors.top: rec3.bottom
            anchors.topMargin: 15
            width : name4.implicitWidth;
            height: name4.implicitHeight;
            border.width: 2
            border.color : "black"
            Text{

                id: name4
                text: qsTr(x_ESS_SW_Ver_MAJ)
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
    }
    Connections{
        target:udpReceive
        onDataChanged: {
            x_E_Psng2_AC_Cosu_kWh = "X_E_Psng2_AC_Cosu_kWh : " +udpReceive.getValue("X_E_Psng2_AC_Cosu_kWh");
            x_Avg_Cosu_Daily= "X_E_Psng1_AC_Cosu_kWh : " +udpReceive.getValue("X_E_Psng1_AC_Cosu_kWh");
            x_Avg_Cosu_Trp= "X_E_Drv_24V_Cosu_kWh : " + udpReceive.getValue("X_E_Drv_24V_Cosu_kWh");
            x_ESS_SW_Ver_MAJ= " X_ESS_SW_Ver_MAJ : " + udpReceive.getValue("X_ESS_SW_Ver_MAJ");
            x_ESS_SW_Ver_MIN= " X_ESS_SW_Ver_MIN: " + udpReceive.getValue("X_ESS_SW_Ver_MIN");
            x_ESS_SW_Ver_REV= " X_ESS_SW_Ver_REV: " + udpReceive.getValue("X_ESS_SW_Ver_REV");
            x_ESS_SW_Ver_DEV= " X_ESS_SW_Ver_DEV: " + udpReceive.getValue("X_ESS_SW_Ver_DEV");
        }
    }
}
