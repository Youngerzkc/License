#include "license.h"
#include "success.h"
#include "error.h"

#include <QApplication>
#include <QTextCodec>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

        QString program = "zactive" ;
        QStringList arguments;
        arguments << "-c";

        QProcess *myProcess = new  QProcess();
        myProcess->start(program, arguments);
        myProcess->waitForFinished();
        QString output = myProcess->readAllStandardOutput();

        QApplication a(argc, argv);

        if(!output.contains("ok"))
        {
            license w;
            w.show();
            a.exec();
        }


        return 0;
}
