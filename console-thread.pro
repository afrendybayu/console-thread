QT -= gui
QT += sql network
QT += core
QT += script

CONFIG += c++11 console
CONFIG -= app_bundle

#TARGET = app
#win32: TARGET = ../../../../../Program Files (x86)/Daun Biru/daq/daqscadamits.exe
win32: TARGET = daqscadamits
unix:  TARGET = DAQScadaMITs

DEFINES += CONSOLE

include(libs/qtservice/src/qtservice.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    model/activetagmodel.cpp \
    model/piwebapicrawler.cpp \
    model/serverconfigmodel.cpp \
    model/sourcemodel.cpp \
    model/tagtmmsdetailmodel.cpp \
    model/activeformulamodel.cpp \
    utils/sqldb.cpp \
    utils/utilsutils.cpp \
    controller/maincontrollero.cpp \
    model/piwebapimodel.cpp

#    model/piwebapicrawler.cpp
#    controller/maincontrollerthread.cpp \

HEADERS += \
    model/activetagmodel.h \
    model/piwebapicrawler.h \
    model/serverconfigmodel.h \
    model/sourcemodel.h \
    model/tagtmmsdetailmodel.h \
    model/activeformulamodel.h  \
    utils/sqldb.h \
    utils/struct.h \
    utils/utilsutils.h \
    controller/maincontrollero.h \
    model/piwebapimodel.h

#    model/piwebapicrawler.h
#    controller/maincontrollerthread.h \
#    release/moc_predefs.h \

win32:RC_ICONS          =   resources/favicon.ico
