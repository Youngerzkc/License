#include "license.h"
#include "ui_license.h"


license::license(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::license)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    //QWidget *widget = new QWidget;
   setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(192,253,123));
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/new/prefix1/image/noactive.png")));
   setPalette(palette);

   systemTray = new SystemTray(this);
   systemTray->setMiddleClickText(tr("系统托盘"));
   systemTray->setToolTips(tr("系统激活"));
   systemTray->setHideText(tr("应用程序隐藏在系统托盘"));
   systemTray->show();

   move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);


}

license::~license()
{
    delete ui;
}

void license::closeEvent(QCloseEvent *event)
{
    if (systemTray->isVisible()) {
        systemTray->startHideTips();
        hide();
        event->ignore();
    }
}


void license::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}

void license::mouseMoveEvent(QMouseEvent *event)
{
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void license::mouseReleaseEvent()
{
    m_Drag = false;
}

void license::on_delete_button_clicked()
{
    close();
}

void license::on_export_button_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("导出注册文件"));
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory("/");
    //fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));

    QString file_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if(file_path.isEmpty())
    {
        return;
    }else{
        file_path = file_path + "/keyfile";
        QString program = "zactive" ;
        QStringList arguments;
        arguments << "--getfile" << file_path ;

        QProcess *myProcess = new  QProcess();
        myProcess->start(program, arguments);
        myProcess->waitForFinished();
        QByteArray output = myProcess->readAllStandardOutput();
        qDebug() << output;
        QMessageBox::information(NULL, tr("提示"), tr("你已经成功生成注册文件：") +  file_path);

        close();
    }
}

void license::on_import_button_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("导入授权文件"));
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory("/");
    //fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));
    if(fileDialog->exec() == QDialog::Accepted) {
            auth_path = fileDialog->selectedFiles()[0];
            QMessageBox::information(NULL, tr("提示"), tr("You selected ") + auth_path);

    } else {
            //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));

    }
}

void license::on_active_button_clicked()
{

    QString program = "zactive" ;
    QStringList arguments;
    arguments << "--putfile" << auth_path ;

    QProcess *myProcess = new  QProcess();
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    QString output = myProcess->readAllStandardOutput();

    qDebug() << "info"  << output;
    if(output.contains("TEMP"))
    {
        //QMessageBox::information(NULL, tr("提示"), tr("你已经完成临时授权 ") + auth_path);
        success* my_succ = new success();
        my_succ->show();
        close();
    }
    else if(output.contains("PERMIT"))
    {
        //QMessageBox::information(NULL, tr("提示"), tr("你已经完成永久授权 ") + auth_path);
        success* my_succ = new success();
        my_succ->show();
        close();
    }
    else
    {
        error* my_err = new error();
        my_err->show();
    }


}
