#ifndef VIDEOLISTMODEL_H
#define VIDEOLISTMODEL_H

#include <QAbstractListModel>

// handle list data model for video
class VideoListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    VideoListModel(QObject *parent = nullptr);
    enum VideoRoles {
        FilePath = Qt::UserRole + 1,
        Name,
//        Time,
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addListVideos(const QVariantMap &data);
    QVariantList listVideos() const;
private:
    QVariantList m_listVideos;
};

#endif // VIDEOLISTMODEL_H
