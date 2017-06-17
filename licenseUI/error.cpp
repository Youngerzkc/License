#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    //QWidget *widget = new QWidget;
   setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(192,253,123));
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/new/prefix1/image/error.png")));
   setPalette(palette);

   move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
}

void error::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}

void error::mouseMoveEvent(QMouseEvent *event)
{
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void error::mouseReleaseEvent()
{
    m_Drag = false;
}

error::~error()
{
    delete ui;
}




void error::on_pushButton_clicked()
{

    close();
}
