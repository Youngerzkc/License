#include "success.h"
#include "ui_success.h"

success::success(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::success)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    //QWidget *widget = new QWidget;
   setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(192,253,123));
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/new/prefix1/image/success.png")));
   setPalette(palette);

   move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);

}


void success::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}

void success::mouseMoveEvent(QMouseEvent *event)
{
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void success::mouseReleaseEvent()
{
    m_Drag = false;
}

success::~success()
{
    delete ui;
}

void success::on_close_button_clicked()
{
    close();
}
