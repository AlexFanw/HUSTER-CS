#include "global.h"

Global::Global()
{

}

pthread_mutex_t Global::sMutex=PTHREAD_MUTEX_INITIALIZER;

QStandardItemModel* Global::model=new QStandardItemModel();

QStringList Global::tableTitleLabels = QObject::trUtf8("IP,File,Status Code,Time").simplified().split(",");

QStandardItem* Global::item=0;

int Global::i=0;
