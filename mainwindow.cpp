#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("C:/Users/Me/Downloads/笔记");
    ui->textEdit->setVisible(false);
    this->setFixedSize(519,710);
    readconfigfile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this,"选择目录",QDir::homePath()));
    createconfigfile();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"提示","选择目录不能为空");
        return;
    }
    QDir d(ui->lineEdit->text());
    QStringList fs=d.entryList(QDir::Files);

    foreach(QString filename,fs){
        QString fn;
        QFile file(ui->lineEdit->text()+"//"+filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            in.setCodec("UTF-8");
            while(!in.atEnd()){
                if(in.readLine().contains(ui->lineEdit_2->text())){
                    fn=filename;
                }
            }
        }
        if(!fn.isEmpty()){
            ui->listWidget->addItem(fn);
        }
        file.close();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"警告","没有选择文件！");
        return;
    }

    QListWidgetItem *item=ui->listWidget->currentItem();
    QStringList argv;
    argv<<ui->lineEdit->text()+"//"+item->text();

    QProcess *p;
    if(ui->comboBox->currentIndex()==0){
        p->startDetached("subl.exe",argv);
    }
    if(ui->comboBox->currentIndex()==1){
        p->startDetached("typora.exe",argv);
    }
    delete p;
    free(p);
}

void MainWindow::clear()
{
    QScrollBar *bar=ui->textEdit->verticalScrollBar();
    bar->setValue(bar->minimum());
    ui->textEdit->clear();
}

void MainWindow::head_location()
{
    QScrollBar *bar=ui->textEdit->verticalScrollBar();
    bar->setValue(bar->minimum());
}

QWidget* MainWindow::wdw(QString *str)
{
    QWidget *wdw=new QWidget();
    QVBoxLayout *y=new QVBoxLayout(wdw);
    QTextEdit *tx=new QTextEdit();
    wdw->setMinimumSize(1500,800);
    wdw->setMaximumSize(1920,1080);
    tx->setFontFamily("黑体");
    tx->setFontPointSize(15);
    y->addWidget(tx);
    tx->setText(*str);
    wdw->show();

    return 0;
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(itemindex!=item->text()){
        clear();

        QFile file(ui->lineEdit->text()+"//"+item->text());
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            in.setCodec("UTF-8");

            while(!in.atEnd()){
                ui->textEdit->append(in.readLine());
            }
        }
        file.close();
        itemindex=item->text();
    }
    QString str=ui->textEdit->toPlainText();
    wdw(&str);
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"提示","没有选择目录！");
        return;
    }
    QString newfilename;
    if(!ui->lineEdit_3->text().isEmpty()){
        newfilename=ui->lineEdit_3->text().toUtf8();
    }else{
        newfilename="all.md";
    }

    QString newfilepath=ui->lineEdit->text()+"//"+newfilename;
    QFile mkfile(newfilepath);
    mkfile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream o(&mkfile);
        o.setCodec("UTF-8");

    QDir d(ui->lineEdit->text());
    QStringList fs=d.entryList(QDir::Files);

    foreach(QString filename,fs){
        QFile file(ui->lineEdit->text()+"//"+filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            in.setCodec("UTF-8");

            while(!in.atEnd()){
                QString line=in.readLine();
                o<<line<<"\n";
            }
        file.close();
        }
        else
        {
            QMessageBox::warning(this,"提示","无法打开文件"+file.fileName());
        }
    }
    mkfile.close();
    QMessageBox::warning(this,"提示","成功将所有文件合并到 "+ui->lineEdit->text()+" 下的 "+newfilename+" 中！");
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(itemindex!=item->text()){
        clear();
        itemindex=item->text();
        QFile file(ui->lineEdit->text()+"//"+item->text());
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
             QTextStream in(&file);
              in.setCodec("UTF-8");

              while(!in.atEnd()){
                  ui->textEdit->append(in.readLine());
              }
         }
        file.close();

        this->setFixedSize(1500,710);
        ui->textEdit->setVisible(true);
        head_location();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    itemindex="";
    this->setFixedSize(520,710);
}

void MainWindow::on_pushButton_6_clicked()
{
       QString st=ui->s_text->text();
       int foundIndex=ui->textEdit->toPlainText().indexOf(st);

       if(foundIndex!=-1){
           QTextCursor cursor=ui->textEdit->textCursor();
           cursor.setPosition(foundIndex);
           //设置光标
       }else{
           QTextCursor cursor=ui->textEdit->textCursor();
           ui->textEdit->setTextCursor(cursor);
           QMessageBox::information(this,"提示","未找到文本！");
       }
}

void MainWindow::readconfigfile()
{
    if (QFile::exists("coindex.conf")) {
            // 文件存在，可以进行读取操作
            QSettings s("coindex.conf",QSettings::IniFormat); //按照INI格式读取配置文件，INI格式：key=value
            qDebug() << s.value("index").toUInt();
            ui->comboBox->setCurrentIndex(s.value("index").toInt());

//            QSettings d("coindex.conf",QSettings::IniFormat);
//            d.setIniCodec(QTextCodec::codecForName("UTF-8"));
//            qDebug() << d.value("ddir");
//            ui->lineEdit->setText(d.value("ddir").toString());
        } else {
            createconfigfile();
            qDebug() << "文件不存在，已创建！";
      }

}

bool MainWindow::createconfigfile()
{
    QFile file("coindex.conf");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<"index=";
        out<<ui->comboBox->currentIndex()<<Qt::endl;  //写入combox索引

//        out<<"ddir=";
//        out<<ui->lineEdit->text();

        file.close();
        return true;
    }
    else{
        return false;
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox->currentIndex();
    createconfigfile();
}
//void MainWindow::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(255,255,255,100));
//}
