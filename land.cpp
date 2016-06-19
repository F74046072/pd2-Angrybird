#include "land.h"

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world){
    //設定圖片並將原點設中心
    g_pixmap.setPixmap(pixmap);
    g_size = QSizeF(w,h);
    //建立物體
    b2BodyDef bodydef;
    bodydef.userData = this;
    bodydef.position.Set(x,y);
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox; //設為方形
    bodyBox.SetAsBox(w/2,h/2); //參數為質心到邊界長
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}
