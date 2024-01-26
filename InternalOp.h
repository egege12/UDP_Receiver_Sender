
#ifndef INTERNALOP_H
#define INTERNALOP_H
#include "qdebug.h"
#include <QString>
#include <QMap>
#include <QFile>
#include <QList>
#include <QTextStream>
/*/
 * User Screen - 1010
 *
 * Monitoring Screen - 2010
 * Test Screen - 2020
 * Com Screen - 2030
 *
 *
 *
 * */
class InternalOp : public QObject{

    Q_OBJECT
    Q_PROPERTY(unsigned long activeScreen READ activeScreen WRITE setActiveScreen NOTIFY activeScreenChanged)
    Q_PROPERTY(bool loadingProgress READ loadingProgress WRITE setLoadingProgress NOTIFY loadingProgressChanged)

public:
    InternalOp();

    unsigned long activeScreen() const;
    void setActiveScreen(unsigned long newActiveScreen);

    bool loadingProgress() const;
    void setLoadingProgress(bool newLoadingProgress);

signals:
    void activeScreenChanged();

    void loadingProgressChanged();

private:
    unsigned long m_activeScreen;
    bool m_loadingProgress;
};

inline bool InternalOp::loadingProgress() const
{
    return m_loadingProgress;
}

inline void InternalOp::setLoadingProgress(bool newLoadingProgress)
{
    if (m_loadingProgress == newLoadingProgress)
        return;
    m_loadingProgress = newLoadingProgress;
    qInfo()<<"loading changed";
    emit loadingProgressChanged();

}

inline unsigned long InternalOp::activeScreen() const
{
    return m_activeScreen;
}

inline void InternalOp::setActiveScreen(unsigned long newActiveScreen)
{
    if (m_activeScreen == newActiveScreen)
        return;
    m_activeScreen = newActiveScreen;
    setLoadingProgress(true);
    emit activeScreenChanged();

}
inline InternalOp::InternalOp(){
    m_activeScreen =1010;
    m_loadingProgress=false;
}
#endif // INTERNALOP_H




