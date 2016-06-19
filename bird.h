#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
//設定物理條件
#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setDynamic(); //設為動態
    void setVelocity(float x, float y); //設定速度
    b2Vec2 getVelocity(); //取得速度
    void setPos(float x, float y); //設定位置
    b2Vec2 getPos(); //取得位置
    void rotate(int rad); //設定旋轉速度
};

#endif // BIRD_H
