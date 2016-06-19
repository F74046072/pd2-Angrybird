#ifndef ENEMY_H
#define ENEMY_H

#include <gameitem.h>
#include <QGraphicsScene>

class Enemy : public GameItem
{
public:
    Enemy(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // ENEMY_H
