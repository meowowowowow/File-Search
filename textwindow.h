#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QWidget>
#include<QTextEdit>
class TextWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TextWindow(QString path);
    QTextEdit text;
signals:

};

#endif // TEXTWINDOW_H
