#ifndef MUSICLISTCONTROLLER_H
#define MUSICLISTCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "musiclistmodel.h"
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

// this class will handle read all .mp3 file in a directory then it push to model
// save xuong json gi gi do
class MusicListController : public QObject
{
    Q_OBJECT
private:
    explicit MusicListController(QObject *parent = nullptr);

public:
    ~MusicListController();

    // singleton pattern
    static MusicListController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    // load music from a directory
    void loadMusic(const QString &directoryPath);
    // push data to playlist
    QStringList getMusicFilePaths();
    // get metadata to display current song
    QVariantMap getMetaDataCurrSong(const QString &mediaPath) const;
    void addMusicToModel(const QString &filePath);
    // get meta-data of a song
    QVariantMap getMetaData(TagLib::FileRef &reference);
    QVariantMap metaDataContainer(const char* filePath);
//    MusicListModel getListModel() const;
//    void setListModel(const MusicListModel &ListModel);
    static MusicListModel m_ListModel;

private:
    static MusicListController *m_instance;
    bool m_initialized;
    //MusicListModel m_ListModel;
};

#endif // MUSICLISTCONTROLLER_H
