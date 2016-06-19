#include "wood.h"

Wood::Wood(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world){
    //設定圖片並將原點設中心
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);
    //建立物體
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody; //設為動態
    bodydef.userData = this;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox; //設為方形
    bodyBox.SetAsBox(w/2,h/2); //參數為質心到邊界長
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.friction = 0;
    fixturedef.density = 0;
    fixturedef.restitution = 0;
    g_body->CreateFixture(&fixturedef);
    g_body->CreateFixture(&bodyBox,9.0f);
    g_body->SetAngularDamping(3);
    //持續更新
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);
}
