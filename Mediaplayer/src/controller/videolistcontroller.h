#ifndef MUSICLISTCONTROLLER_H
#define MUSICLISTCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "videolistmodel.h"
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <cstdio>
#include <QDebug>
#include <QDir>
#include <taglib/fileref.h>
#include <taglib/tag.h>

// this class will handle read all .mp4 file in a directory then it push to model
class VideoListController : public QObject
{
    Q_OBJECT
private:
    explicit VideoListController(QObject *parent = nullptr);

public:
    ~VideoListController();

    // singleton pattern
    static VideoListController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    // load music from a directory
    void loadVideo(const QString &directoryPath);
    // push data to playlist
    QStringList getVideoFilePaths();
    // get metadata to display current video
    QVariantMap getMetaDataCurrVideo(const QString &mediaPath) const;
    void addVideoToModel(const QString &filePath);
    // get meta-data of a video
    QVariantMap getMetaDataV(TagLib::FileRef &reference);
    QVariantMap metaDataContainerV(const char* filePath);
    static VideoListModel m_ListVModel;
private:
    static VideoListController *m_instance;
    bool m_initializedV;
};

#endif // MUSICLISTCONTROLLER_H
