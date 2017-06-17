#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QtGui>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QWidget *parent = 0);
    ~SystemTray();
    void setParentWidget(QWidget *parent);
    void setMiddleClickText(const QString &tips);
    void setHideText(const QString &text);
    void setToolTips(const QString &tips);
    void startHideTips();

private:
    void createActions();

private slots:
    void slotActivated(QSystemTrayIcon::ActivationReason reason);
    void slotHelpAction();
    void showParentWidget();

private:
    QMenu *trayIconMenu;
    //QAction *showAction;
    QAction *helpAction;
    QAction *quitAction;
    QWidget *parentWidget;
    QString middleText;
    QString toolTils;
    QString hideText;
    QMenu *funMenu;
    QWidget *topWidget;
    //QWidgetAction *topWidgetAction;
    QPushButton *showButton;
    QPushButton *hideButton;
};

#endif // SYSTEMTRAY_H
