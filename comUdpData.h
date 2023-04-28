
#ifndef COMUDPDATA_H
#define COMUDPDATA_H
#include <QString>
#include <QMap>
#include <QFile>
#include <QList>
#include <QTextStream>

class comUdpData: public QObject{

    struct paramSignal;

    QMap<QString,QList<paramSignal*>> qm_comParam;

    bool parseSignals(QFile *dbcFile);

    QList<QString> warnings;

    unsigned parseLength(QString  splitedPart);
    unsigned parseStartBit(QString  splitedPart);
    double parseResolution(QString  splitedPart);
    double parseOffset(QString  splitedPart);
    double parseMaxValue(QString  splitedPart);
    double parseMinValue(QString  splitedPart);
    QString parseComment(QString splitedPart);
    QString getBetween(QString first, QString second,QString fullText);
public:
    QMap<QString,QString> qm_data;

    bool importDBC(QString qs_location);
    const QMap<QString,QList<comUdpData::paramSignal*>> * const getsignalParams();

};
struct comUdpData::paramSignal{
    QString m_name;
    unsigned m_startBit;
    unsigned m_length;
    double m_min;
    double m_max;
    double m_resolution;
    double m_offset;
};
inline bool comUdpData::parseSignals(QFile *dbcFile)
{
    QTextStream  *lines = new QTextStream(dbcFile);
    bool inlineOfMessage=false;
    bool inlineOfMessageOld=false;
    QString messageID;
//  QString messageName ;
    unsigned short  messageDLC ;
    QList<QList<QString>> msgCommentList;
    unsigned long debugcounter=0;
//  bool isExtended = 0;
    bool secLineFlagCmMes = false;
    bool secLineFlagCmSig = false;
    QString secLineContainer = "";

    while (!lines->atEnd()) {
        QString curLine = lines->readLine();

        if(curLine.contains("BO_ ") && curLine.indexOf("BO_") < 2 && !(curLine.contains("INDEPENDENT")&&curLine.contains("VECTOR"))){
            inlineOfMessage = true;
            debugcounter++;

            QStringList messageList = curLine.split(" ");

            if(messageList.at(1).toUInt()>2047){
                messageID = QString::number((messageList.at(1).toUInt())-2147483648,16).toUpper();
//              isExtended=true;
            }else{
                messageID = QString::number(messageList.at(1).toUInt(),16).toUpper();
//              isExtended=false;
            }
//Read name messageName= messageList.at(2);
//Read name messageName.remove(QChar(':'),Qt::CaseInsensitive).replace(" ","_");;
//read DLC  messageDLC = messageList.at(3).toUShort();
        }else if(inlineOfMessage && curLine.contains("SG_")){

            comUdpData::paramSignal *curSignal = new comUdpData::paramSignal;
            curSignal->m_name = getBetween("SG_",":",curLine).trimmed().replace(" ","_");
            curSignal->m_startBit = parseStartBit(getBetween(":","(",curLine));
            curSignal->m_length = parseLength(getBetween(":","(",curLine));
            curSignal->m_resolution = parseResolution(getBetween("(",")",curLine));
            curSignal->m_offset = parseOffset(getBetween("(",")",curLine));
            curSignal->m_min = parseMinValue(getBetween("[","]",curLine));
            curSignal->m_max = parseMaxValue(getBetween("[","]",curLine));

            if(qm_comParam.contains(messageID)){
                qm_comParam.value(messageID).append(curSignal);
            }else{
                QList<paramSignal*> contlist;
                contlist.append(curSignal);
                qm_comParam.insert(messageID,contlist);
            }
            qm_data.insert(curSignal->m_name,"0");
        }else{
            inlineOfMessage = false;
        }
        if (inlineOfMessageOld && !inlineOfMessage){
            // Message completed
        }
        inlineOfMessageOld = inlineOfMessage;


    }

    return true;
}

inline bool comUdpData::importDBC(QString qs_location)
{
    try {
        if (qs_location.isEmpty()){
            throw QString("Dosya konumu boş olamaz!");
        }else if(!qs_location.contains(".dbc")){
            throw QString("Lütfen \".dbc\" uzantılı bir dosya seçin!");
        }
        else{
            QFile *dbcFile = new QFile(qs_location);
            if(!dbcFile->open(QIODevice::ReadOnly | QIODevice::Text)){
                throw QString("Dosya açılamadı, lütfen konumu kontrol edin!");
            }
            else{
                if (!parseSignals(dbcFile)){
                    throw QString("Arayüzü okurken bir şeyler yanlış gitti!");
                }
            }
            dbcFile->close();
        }
    } catch (QString text) {
        this->warnings.append(text);
    }
    if(warnings.isEmpty())
        return true;
    else
        return false;
}

inline const QMap<QString,QList<comUdpData::paramSignal*>>  * const comUdpData::getsignalParams()
{
    return &qm_comParam;
}
inline unsigned comUdpData::parseLength(QString splitedPart)
{
    splitedPart.remove("@1+");
    splitedPart.remove("@1-");
    QStringList container = splitedPart.trimmed().split("|");
    return container.at(1).toUShort();
}

inline unsigned comUdpData::parseStartBit(QString  splitedPart)
{
    splitedPart.remove("@1+");
    splitedPart.remove("@1-");
    QStringList container = splitedPart.trimmed().split("|");
    return container.at(0).toUShort();
}

inline double comUdpData::parseResolution(QString  splitedPart)
{
    splitedPart.remove("(");
    splitedPart.remove(")");
    QStringList container = splitedPart.trimmed().split(",");
    return container.at(0).toDouble();
}

inline double comUdpData::parseOffset(QString  splitedPart)
{
    splitedPart.remove("(");
    splitedPart.remove(")");
    QStringList container = splitedPart.trimmed().split(",");
    return container.at(1).toDouble();
}

inline double comUdpData::parseMaxValue(QString  splitedPart)
{
    splitedPart.remove("[");
    splitedPart.remove("]");
    QStringList container = splitedPart.trimmed().split("|");
    return container.at(1).toDouble();
}

inline double comUdpData::parseMinValue(QString  splitedPart)
{
    splitedPart.remove("[");
    splitedPart.remove("]");
    QStringList container = splitedPart.trimmed().split("|");
    return container.at(0).toDouble();
}

inline QString comUdpData::parseComment(QString splitedPart)
{
    QString comment = splitedPart.mid(splitedPart.indexOf("]")+1,((splitedPart.indexOf("Vector__XXX")))-(splitedPart.indexOf("]")+1));
    comment.remove("\"");
    comment.remove("Vector__XXX");
    return comment.trimmed();
}
inline QString comUdpData::getBetween(QString first, QString second, QString fullText)
{
    if(fullText.contains(first,Qt::CaseInsensitive)){
        qsizetype indexCont1 = fullText.indexOf(first,Qt::CaseInsensitive);
        fullText= fullText.sliced(indexCont1);
        indexCont1 = fullText.indexOf(first,Qt::CaseInsensitive);
        if(fullText.contains(QString(second),Qt::CaseInsensitive)){
            qsizetype indexCont2 = fullText.indexOf(second,Qt::CaseInsensitive);
            return fullText.mid(indexCont1,(indexCont2-indexCont1)).trimmed().remove("=").remove(":").remove(first).trimmed();
        }else
            return "(*ERROR*)";
    }return "(*ERROR*)";
}
#endif // COMUDPDATA_H
