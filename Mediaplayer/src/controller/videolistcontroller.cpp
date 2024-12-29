#include "videolistcontroller.h"
#include "loghelper.h"
#include <QUrl>
#include <QBuffer>
#include <QImage>
VideoListController* VideoListController::m_instance = nullptr;
VideoListModel VideoListController::m_ListVModel;
VideoListController::VideoListController(QObject *parent) : QObject(parent), m_initializedV(false)
{
    LOG_INFO;
}

VideoListController::~VideoListController()
{
    LOG_INFO;
}

VideoListController *VideoListController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new VideoListController();
    }

    return m_instance;
}

void VideoListController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initializedV;
    if(!m_initializedV)
    {
        m_initializedV = true;
        context->setContextProperty("VLIST_CTRL", this);
        context->setContextProperty("VLIST_MODEL", &m_ListVModel);
    }
}

void VideoListController::loadVideo(const QString &directoryPath)
{
    QDir directory(directoryPath);
    if (!directory.exists()) {
        qDebug() << "Directory does not exist:" << directoryPath;
        return;
    }
    QStringList filters;
    filters << "*.mp4" << "*.mkv";// << "*.avi";
    QFileInfoList fileInfoList = directory.entryInfoList(filters, QDir::Files);

    if (fileInfoList.isEmpty()) {
        qDebug() << "No music files found in directory:" << directoryPath;
        return;
    }

    foreach (const QFileInfo &fileInfo, fileInfoList) {
        addVideoToModel(fileInfo.absoluteFilePath());
    }
}

//MusicListModel *MusicListController::listModel() const
//{
//    return &m_ListModel;
//}

QVariantMap VideoListController::getMetaDataV(TagLib::FileRef &reference)
{
    QVariantMap metadata;
//    metadata.insert("time", "");
//    metadata.insert("thumbnail", "");
    metadata.insert("filePath", reference.file()->name());
    QFileInfo fileInfo(QString::fromStdString(reference.file()->name()));
    QString baseName = fileInfo.completeBaseName();
    metadata.insert("name", baseName);
    return metadata;
}

QVariantMap VideoListController::metaDataContainerV(const char *filePath)
{
    TagLib::FileRef fileRef(filePath);
    getMetaDataV(fileRef);

    QVariantMap metaData;
//    metaData.insert("time", getMetaData(fileRef).value("length"));
//    metaData.insert("thumbnail", getMetaData(fileRef).value("coverArt"));
    metaData.insert("filePath", getMetaDataV(fileRef).value("filePath"));
    metaData.insert("name", getMetaDataV(fileRef).value("name"));
    return metaData;
}

QStringList VideoListController::getVideoFilePaths() {
    loadVideo("/home/manh/Code/Mock Project/ManhNT50_QtMock_Project/Mediaplayer/data");
    QStringList filePaths;
    qDebug() << __FUNCTION__ << m_ListVModel.listVideos();
    for (const auto& video : m_ListVModel.listVideos()) {
        //qDebug() << song;
        filePaths.append(video.toMap().value("filePath").toString());
    }
    qDebug() << __FUNCTION__  << filePaths;
    return filePaths;
}
QVariantMap VideoListController::getMetaDataCurrVideo(const QString &mediaPath) const
{
    QVariantMap map;
    for (const QVariant &song : m_ListVModel.listVideos()) {
        map = song.toMap();
        if (map.value("filePath").toString() == mediaPath) {
            return map;
        }
    }
    qDebug() << __FUNCTION__ << map;
    return QVariantMap();
}
void VideoListController::addVideoToModel(const QString &filePath)
{
    TagLib::FileRef fileRef(filePath.toUtf8().constData());
    getMetaDataV(fileRef);
    m_ListVModel.addListVideos(metaDataContainerV(filePath.toStdString().c_str()));
    //MusicListModel::getInstance()->addListSongs(metaDataContainer(filePath.toStdString().c_str()));
}
