#ifndef LICENSE_H
#define LICENSE_H

#include <QWidget>
#include <QToolButton>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include<signal.h>

#include "systemtray.h"
#include "success.h"
#include "error.h"

namespace Ui {
class license;
}

class license : public QWidget
{
    Q_OBJECT
    
public:
    explicit license(QWidget *parent = 0);
    ~license();
    
private slots:
    void on_delete_button_clicked();
    void on_export_button_clicked();
    void on_import_button_clicked();
    void on_active_button_clicked();

private:
    Ui::license *ui;
    SystemTray *systemTray;
    QPoint m_DragPosition;
    bool m_Drag;
    QString auth_path;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent();
     void closeEvent(QCloseEvent *event);
};

#endif // LICENSE_H
