#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QDebug>
#include <unistd.h>
#include <sys/syscall.h>

#include <iostream>
#define LOG_INFO qDebug().nospace() << "[Thread #" << syscall(SYS_gettid) << "]" << Q_FUNC_INFO << " "
#endif // LOGHELPER_H
