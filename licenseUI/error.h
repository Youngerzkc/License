#ifndef ERROR_H
#define ERROR_H

#include <QWidget>
#include <QToolButton>
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class error;
}

class error : public QWidget
{
    Q_OBJECT
    
public:
    explicit error(QWidget *parent = 0);
    ~error();
    
private:
    Ui::error *ui;
    QPoint m_DragPosition;
    bool m_Drag;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent();
private slots:
    void on_pushButton_clicked();
};

#endif // ERROR_H
