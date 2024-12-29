#include "videolistmodel.h"
#include <QDebug>
VideoListModel::VideoListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int VideoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listVideos.count();
}

QVariant VideoListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();

    const QVariantMap map = m_listVideos.at(row).toMap();

    switch (role) {
//    case Time:
//        return map.value("time");
    case Name:
        return map.value("name");
    case FilePath:
        return map.value("filePath");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> VideoListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[FilePath] = "filePath";
    roles[Name] = "name";
//    roles[Time] = "time";

    return roles;
}

void VideoListModel::addListVideos(const QVariantMap &data)
{
    beginInsertRows(QModelIndex(), m_listVideos.size(), m_listVideos.size());
    m_listVideos.append(data);
    endInsertRows();
    qDebug() << __FUNCTION__ << m_listVideos << '\n';
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

QVariantList VideoListModel::listVideos() const
{
    return m_listVideos;
}


