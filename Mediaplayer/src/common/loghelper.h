#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QDebug>
#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>
#include <iomanip>
#define LOG_INFO std::cout << "[Thread #" << syscall(SYS_gettid) << "]" << Q_FUNC_INFO << " "<<std::endl

#endif // LOGHELPER_H
