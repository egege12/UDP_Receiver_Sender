
#ifndef COMDATATABLEMODEL_H
#define COMDATATABLEMODEL_H
#include <qqml.h>
#include <QAbstractTableModel>
#include <QMap>
class comDataTAbleModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
        QML_ADDED_IN_MINOR_VERSION(1)
        private:
                  enum TableRoles{
                      TableDataRole = Qt::UserRole+1,
                      HeadingRole,
                      MessageId
                  };

            QList<QList<QString>> tableData;
            QMap<QString,QList<QList<QString>>> dataMap;
            const QList<QString> headings{"Signal Name","Değer"};

        public:
    comDataTAbleModel();

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int setSignals();
    int updateSignalValue(const QString *signalName);

};

inline int comDataTAbleModel::rowCount(const QModelIndex &) const
{
    return 200;
}

inline int comDataTAbleModel::columnCount(const QModelIndex &) const
{
    return 200;
}

inline QVariant comDataTAbleModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case HeadingRole:
    {
        if((index.row()==0) && (index.column()==0)){
            return headings.at(0);
        }else if ((index.row()==0) && (index.column()==1)){
            return headings.at(1);
        }else{
            return false;
        }
    }
    case TableDataRole:
    {
        if(index.row()!=0){
        return tableData.at(index.row()).at(index.column());
       }else
        return false;
    }
    default:
        break;
    }

    return QVariant();
}

inline QHash<int, QByteArray> comDataTAbleModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[HeadingRole] = "heading";
    roles[TableDataRole]= "tabledata";
    roles[MessageId] = "messageid";
    return roles;
}

#endif // COMDATATABLEMODEL_H


inline comDataTAbleModel::comDataTAbleModel() : QAbstractTableModel(parent())
{

}

