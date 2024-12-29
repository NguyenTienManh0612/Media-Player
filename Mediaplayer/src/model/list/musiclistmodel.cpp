#include "musiclistmodel.h"
#include <QDebug>

//MusicListModel *MusicListModel::m_instance = nullptr;
MusicListModel::MusicListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int MusicListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listSongs.count();
}

QVariant MusicListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();

    const QVariantMap map = m_listSongs.at(row).toMap();

    switch (role) {
    case Artist:
        return map.value("artist");
    case Title:
        return map.value("title");
    case CoverArt:
        return map.value("coverArt");
    case Time:
        return map.value("time");
    case Album:
        return map.value("album");
    case FilePath:
        return map.value("filePath");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MusicListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Artist] = "artist";
    roles[Title] = "title";
    roles[CoverArt] = "coverArt";
    roles[Time] = "time";
    roles[Album] = "album";
    roles[FilePath] = "filePath";
    return roles;
}

void MusicListModel::addListSongs(const QVariantMap &data)
{
    beginInsertRows(QModelIndex(), m_listSongs.size(), m_listSongs.size());
    m_listSongs.append(data);
    endInsertRows();
    //qDebug() << m_listSongs << '\n';
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

QVariantList MusicListModel::listSongs() const
{
    //qDebug() << __FUNCTION__ << m_listSongs;
    //qDebug() << __FUNCTION__ << m_listSongs.indexOf(2);
    return m_listSongs;
}

