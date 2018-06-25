#ifndef     DEFINES_HPP
#define    DEFINES_HPP

#include <QMessageLogContext>
#include <QSettings>
#include <QString>
#include <stdlib.h>

#define APP_NAME    QStringLiteral("DAQScada")
#define ORG_DOMAIN  QStringLiteral("DaunBiru")
#define VERSION     QStringLiteral("0.0.0.1")

int     myKill(pid_t pid, int signal);
void    installMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void    init(QSettings &set);
bool    isLoggedIn(void);

#endif
