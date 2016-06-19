#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <iostream>
#include <math.h>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <wood.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    void quitGame();
private slots:
    void startgame();
    void clear();
    void setBird();
    void setWood();
    void setPig();
    void tick();
    void setReady();
    void newBird();
    void isAllDone();

    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer; 
    QMediaPlayer *music;
    QMediaPlayer *hit;
    //鳥的準備位置
    float init_x = 3.8, init_y = 7.7;
    Land *land;
    Bird *bird[4];
    Pig *pig[5];
    Wood *wood[9];
    //判斷發射時資料
    bool isPressed = false;
    bool isFired = false;
    bool skillUsed = false;
    bool done = false;
    bool alldone = false;
    int birdnum = 0;
    float dx, dy;
    //判斷擊中時資料
    int score=0;
    bool isReady = false;
    bool die0 = false;
    bool die1 = false;
    bool die2 = false;
    bool die3 = false;
    bool die4 = false;
    b2Vec2 v0,v1,v2,v3,v4;
};

#endif // MAINWINDOW_H
