#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(960,540);
    w.setWindowTitle("憤怒鳥");
    w.show();

    return a.exec();
}
