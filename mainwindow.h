#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"form.h"
#include<QWidget>
#include<QTextEdit>
#include <QPainter>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QProcess>
#include <QWidget>
#include <QGroupBox>
#include <QScrollBar>
#include <QVBoxLayout>
#include<QTextDocument>
#include <QTextCursor>
#include<fstream>
#include<iostream>
#include<QSettings>
#include<Qdebug>
#include<QTextCodec>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString itemindex=NULL;
    int cindex=0;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void clear();
    void head_location();
    QWidget* wdw(QString *str);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void readconfigfile();
    bool createconfigfile();

    void on_comboBox_currentIndexChanged(int index);

//protected:
//    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
