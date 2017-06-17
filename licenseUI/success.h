#ifndef SUCCESS_H
#define SUCCESS_H

#include <QWidget>
#include <QToolButton>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QSystemTrayIcon>

namespace Ui {
class success;
}

class success : public QWidget
{
    Q_OBJECT
    
public:
    explicit success(QWidget *parent = 0);
    ~success();
    
private:
    Ui::success *ui;
    //QSystemTrayIcon * myTray; //自定义系统托盘
    QPoint m_DragPosition;
    bool m_Drag;



protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent();
private slots:
    void on_close_button_clicked();
};

#endif // SUCCESS_H
