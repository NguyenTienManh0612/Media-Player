#ifndef MUSICLISTMODEL_H
#define MUSICLISTMODEL_H

#include <QAbstractListModel>

// handle list data model for display music list screen
class MusicListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MusicListModel(QObject *parent = nullptr);
    enum SongRoles {
        Album = Qt::UserRole + 1,
        Artist,
        CoverArt,
        Time,
        Title,
        FilePath
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addListSongs(const QVariantMap &data);
    QVariantList listSongs() const;
//    QVariantMap getMetaData(const QString &mediaPath) const;
//    static MusicListModel *getInstance();
private:
    QVariantList m_listSongs;
    //static MusicListModel *m_instance;
};

#endif // MUSICLISTMODEL_H
