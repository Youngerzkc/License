#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include "systemtray.h"

SystemTray::SystemTray(QWidget *parent)
    : QSystemTrayIcon(parent)
    , middleText("")
    , toolTils("")
    , hideText("")
{
    parentWidget = parent;
    createActions();
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showParentWidget()));
    timer->start(5000);
}

SystemTray::~SystemTray()
{

}

void SystemTray::setParentWidget(QWidget *parent)
{
    parentWidget = parent;
}

void SystemTray::setMiddleClickText(const QString &tips)
{
    middleText = tips;
}

void SystemTray::setHideText(const QString &text)
{
    hideText = text;
}

void SystemTray::setToolTips(const QString &tips)
{
    this->setToolTip(tips);
}

void SystemTray::startHideTips()
{
    this->showMessage(tr("提示信息："), hideText, QSystemTrayIcon::Information, 2000);
}

void SystemTray::createActions()
{
    this->setIcon(QIcon(":/new/prefix1/image/lock.png"));
    trayIconMenu = new QMenu();

    helpAction = new QAction(this);
    helpAction->setIcon(QIcon(":/help.png"));
    helpAction->setText(tr("帮助"));


    //trayIconMenu->addAction(topWidgetAction);
    //trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(helpAction);
    trayIconMenu->addSeparator();

    this->setContextMenu(trayIconMenu);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(slotHelpAction()));
}

void SystemTray::slotActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (parentWidget) {
        switch (reason) {
            case QSystemTrayIcon::Trigger:
            case QSystemTrayIcon::DoubleClick: {
                if (parentWidget->isHidden() || parentWidget->windowState() == Qt::WindowMinimized) {
                    //showNormal(),showMinimized(),showMaxmized(),showFullScreen()
                    parentWidget->showNormal();
                    parentWidget->raise();
                    parentWidget->activateWindow();
                }
                else {
                    parentWidget->hide();
                    startHideTips();
                }
                break;
            }
            case QSystemTrayIcon::MiddleClick: {
                if (!middleText.isEmpty()) {
                    this->showMessage(tr("提示信息："), middleText, QSystemTrayIcon::Information, 3000);
                }
                break;
            }
            default:
                break;
        }
    }
}

void SystemTray::slotHelpAction()
{
    const QUrl AuthorUrl("http://zblxsoft.gotoip1.com/");
    //qDebug() << AuthorUrl.scheme();
    //qDebug() << AuthorUrl.port();
    QDesktopServices::openUrl(AuthorUrl);
}

void SystemTray::showParentWidget()
{

    QString program = "zactive" ;
    QStringList arguments;
    arguments << "-c";

    QProcess *myProcess = new  QProcess();
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    QString output = myProcess->readAllStandardOutput();

    if(output.contains("failed"))
    {
        parentWidget->showNormal();
        parentWidget->raise();
        parentWidget->activateWindow();
    }

}
