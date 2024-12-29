QT += quick
CONFIG += c++17
QT += multimedia dbus
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += MEDIADATAPATH= $$PWD/data

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INCLUDEPATH += $$PWD/../ThirdParty/Taglib/header
LIBS += -L$$PWD/../ThirdParty/Taglib/ -ltag -lz
INCLUDEPATH += \
    ./src \
    ./src/common \
    ./src/controller \
    ./src/model \
    ./src/model/playback \
    ./src/model/list \
    ./src/service

HEADERS += \
    src/common/appdefines.h \
    src/common/loghelper.h \
    src/controller/musiclistcontroller.h \
    src/controller/translatorcontroller.h \
    src/controller/videolistcontroller.h \
    src/controller/screencontroller.h \
    src/model/list/musiclistmodel.h \
    src/appengine.h \
    src/controller/baseplayercontroller.h \
    src/controller/videoplayercontroller.h \
    src/controller/musicplayercontroller.h \
    src/model/list/videolistmodel.h \
    src/model/playback/baseplaybackmodel.h \
    src/model/playback/videoplaybackmodel.h \
    src/model/playback/musicplaybackmodel.h \
    src/model/screenmodel.h \
    src/model/translatormodel.h

SOURCES += \
    src/controller/musiclistcontroller.cpp \
    src/controller/translatorcontroller.cpp \
    src/controller/videolistcontroller.cpp \
    src/controller/screencontroller.cpp \
    src/model/list/musiclistmodel.cpp \
    src/appengine.cpp \
    src/main.cpp \
    src/controller/baseplayercontroller.cpp \
    src/controller/videoplayercontroller.cpp \
    src/controller/musicplayercontroller.cpp \
    src/model/list/videolistmodel.cpp \
    src/model/playback/baseplaybackmodel.cpp \
    src/model/playback/videoplaybackmodel.cpp \
    src/model/playback/musicplaybackmodel.cpp \
    src/model/screenmodel.cpp \
    src/model/translatormodel.cpp

RESOURCES += \
    images.qrc \
    localization.qrc \
    qml.qrc

TRANSLATIONS += \
    localization/AppLanguage_en.ts \
    localization/AppLanguage_vi.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../ThirdParty/ -ltag -lz

INCLUDEPATH += $$PWD/../ThirdParty
DEPENDPATH += $$PWD/../ThirdParty

unix:!macx: PRE_TARGETDEPS += $$PWD/../ThirdParty/libtag.a -lz
