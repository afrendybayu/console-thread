#ifndef STRUCT_H
#define STRUCT_H

#include <QString>
#include <QDateTime>

//#define JOB_DAQ         1
//#define JOB_FORMULA     2

#define MAX_CRAWLING_LOOP       3
#define MAX_THREAD_CRAWLING     3


enum JOB_TYPE {
    JOB_DAQ = 1,
    JOB_FORMULA
};

enum JOB_STATUS {
    JOB_FREE    = 0,
    JOB_WAITING,            // ketika masuk antrian
    JOB_PENDING,            // ketika masuk thread
    JOB_EXECUTING,
    JOB_DONE
};

struct stJobQueue   {
    int id;             // id tag
    QString tag;
    int nextJob = 0;        // dalam epochtime (int)
    int nextnextJob = 0;
    int lastJob = 0;
    int status = 0;         // JOB_STATUS
    int jobType;    // 1. DAQ    2. Formula
    int source;
    int periode;
    bool selalu = false;        // continue ato one shoot execute
    QString webId;
    QString kode;
    int thId;
    QString account;
    QString password;
    QString host;
    QString port;
    QString url;
    QString max_daq_request;
};

struct stRecordedDataPiWebAPi    {
    int id;
    QDateTime dt;
    int epoch;
    float value;
};


#endif // STRUCT_H
