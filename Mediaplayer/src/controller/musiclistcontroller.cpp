#include "musiclistcontroller.h"
#include "loghelper.h"
#include <QUrl>
#include <QBuffer>
#include <QImage>
MusicListController* MusicListController::m_instance = nullptr;
MusicListModel MusicListController::m_ListModel;
MusicListController::MusicListController(QObject *parent)
    :QObject(parent), m_initialized(false)
{

}

MusicListController::~MusicListController()
{
    LOG_INFO;
}

MusicListController *MusicListController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new MusicListController();
    }

    return m_instance;
}

void MusicListController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("MLIST_CTRL", this);
        context->setContextProperty("MLIST_MODEL", &m_ListModel);
    }
}

void MusicListController::loadMusic(const QString &directoryPath)
{
    QDir directory(directoryPath);
    if (!directory.exists()) {
        qDebug() << "Directory does not exist:" << directoryPath;
        return;
    }
    QStringList filters;
    filters << "*.mp3" << "*.flac" << "*.m4a" << "*.wav";// << "*.ape";
    QFileInfoList fileInfoList = directory.entryInfoList(filters, QDir::Files);

    if (fileInfoList.isEmpty()) {
        qDebug() << "No music files found in directory:" << directoryPath;
        return;
    }

    foreach (const QFileInfo &fileInfo, fileInfoList) {
        addMusicToModel(fileInfo.absoluteFilePath());
    }
}

QVariantMap MusicListController::getMetaData(TagLib::FileRef &reference)
{
    QVariantMap metadata;
    metadata.insert("title", QVariant::fromValue(TStringToQString(reference.tag()->title())));
    metadata.insert("artist", QVariant::fromValue(TStringToQString(reference.tag()->artist())));
    metadata.insert("album", QVariant::fromValue(TStringToQString(reference.tag()->album())));
    //    metadata.insert("year", QVariant::fromValue(reference.tag()->year()));
    //    metadata.insert("comment", QVariant::fromValue(TStringToQString(reference.tag()->comment())));
    //    metadata.insert("track", QVariant::fromValue(reference.tag()->track()));
    //    metadata.insert("genre", QVariant::fromValue(TStringToQString(reference.tag()->genre())));
    metadata.insert("filePath", reference.file()->name());

    TagLib::AudioProperties *properties = reference.audioProperties();
    int seconds = properties->lengthInSeconds() % 60;
    int minutes = (properties->lengthInSeconds() - seconds) / 60;
    // get covert art
        TagLib::MPEG::File mpegFile(reference.file()->name());
        //TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
        TagLib::ID3v2::FrameList frameList;
        //TagLib::ID3v2::AttachedPictureFrame *picFrame;
        QString coverArt;
        if (mpegFile.isValid()) {
            TagLib::ID3v2::Tag *id3v2Tag = mpegFile.ID3v2Tag();
            if (id3v2Tag) {
                frameList = id3v2Tag->frameListMap()["APIC"];
                if (!frameList.isEmpty()) {
                    TagLib::ID3v2::AttachedPictureFrame *coverFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

                    QImage coverImage;

                    coverImage.loadFromData(reinterpret_cast<const uchar *>(coverFrame->picture().data()), coverFrame->picture().size());
                    QByteArray byteArray;
                    QBuffer buffer(&byteArray);
                    coverImage.save(&buffer, "jpeg"); // Save cover art as jpeg in byte array
                    coverArt = "data:image/jpeg;base64," + QString::fromLatin1(byteArray.toBase64().data());
                    //qDebug() << coverArt;
                    metadata.insert("coverArt", QUrl(coverArt).toString());
                }
            }

        }
//    // get covert art
//    TagLib::MPEG::File mpegFile(reference.file()->name());
//    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
//    TagLib::ID3v2::FrameList frame ;
//    TagLib::ID3v2::AttachedPictureFrame *picFrame ;
//    void *srcImage ;
//    unsigned long Size ;
//    QString outputFilePath;
//    if ( id3v2tag )
//    {
//        // picture frame
//        frame = id3v2tag->frameListMap()["APIC"] ;
//        if (!frame.isEmpty() )
//        {
//            for(TagLib::ID3v2::FrameList::ConstIterator it = frame.begin(); it != frame.end(); ++it)
//            {
//                picFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;
//                {
//                    // extract image (in it’s compressed form)
//                    Size = picFrame->picture().size() ;
//                    srcImage = malloc ( Size ) ;
//                    if ( srcImage )
//                    {
//                        memcpy ( srcImage, picFrame->picture().data(), Size ) ;

//                        // Specify the output file path
//                        QFileInfo fileInfo(QString::fromStdString(reference.file()->name()));
//                        QString baseName = fileInfo.completeBaseName();
//                        outputFilePath = QDir::currentPath() + QString("/%1_cover.jpg").arg(baseName);
//                        QFile file(outputFilePath);
//                        if (file.open(QIODevice::WriteOnly)) {
//                            file.write((const char*)srcImage, Size);
//                            file.close();
//                            qDebug() << "Cover art saved to:" << outputFilePath;
//                        } else {
//                            qDebug() << "Failed to save cover art to file:" << outputFilePath;
//                        }
//                        free( srcImage ) ;
//                    }
//                    //qDebug() << outputFilePath;
//                    metadata.insert("coverArt", outputFilePath);
//                }
//            }
//            coverArtFound = true;
//            qDebug() << __FUNCTION__ << metadata;
//        } else {
//            //qDebug()<<"Not include coverart";
//        }
//    } else {
//        // qDebug()<<"Not include coverart";
//    }
//    if (!coverArtFound) {
//        // Use default cover art
//        QString defaultCoverArtPath = "qrc:/images/default-coverArt.png"; // Path to your default cover art
//        if (QFile::exists(defaultCoverArtPath)) {
//            metadata.insert("coverArt", QUrl(defaultCoverArtPath).toString());
//        }
//    }

    QString lengthSec = seconds < 10 ? ("0" + QString::number(seconds)) : QString::number(seconds);
    QString lengthMin = minutes < 10 ? ("0" + QString::number(minutes)) : QString::number(minutes);
    metadata.insert("length", QVariant::fromValue(lengthMin + ":" + lengthSec));
    return metadata;
}

QVariantMap MusicListController::metaDataContainer(const char *filePath)
{
    TagLib::FileRef fileRef(filePath);
    getMetaData(fileRef);

    QVariantMap metaData;
    metaData.insert("artist", getMetaData(fileRef).value("artist"));
    metaData.insert("title", getMetaData(fileRef).value("title"));
    metaData.insert("time", getMetaData(fileRef).value("length"));
    metaData.insert("album", getMetaData(fileRef).value("album"));
    metaData.insert("coverArt", getMetaData(fileRef).value("coverArt"));
    metaData.insert("filePath", getMetaData(fileRef).value("filePath"));
    return metaData;
}

QStringList MusicListController::getMusicFilePaths() {
    loadMusic("/home/manh/Code/Mock Project/ManhNT50_QtMock_Project/Mediaplayer/data");
    QStringList filePaths;
    //qDebug() << __FUNCTION__ << m_ListModel.listSongs();
    for (const auto& song : m_ListModel.listSongs()) {
        //qDebug() << song;
        filePaths.append(song.toMap().value("filePath").toString());
    }
    qDebug() << __FUNCTION__  << filePaths;
    return filePaths;
}
QVariantMap MusicListController::getMetaDataCurrSong(const QString &mediaPath) const
{
    QVariantMap map;
    for (const QVariant &song : m_ListModel.listSongs()) {
        map = song.toMap();
        if (map.value("filePath").toString() == mediaPath) {
            return map;
        }
    }
    qDebug() << __FUNCTION__ << map;
    return QVariantMap();
}
void MusicListController::addMusicToModel(const QString &filePath)
{
    TagLib::FileRef fileRef(filePath.toUtf8().constData());
    getMetaData(fileRef);
    m_ListModel.addListSongs(metaDataContainer(filePath.toStdString().c_str()));
    //MusicListModel::getInstance()->addListSongs(metaDataContainer(filePath.toStdString().c_str()));
}
