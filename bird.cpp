#include "bird.h"
#include "pig.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world){
    //設定圖片並將原點設中心
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);
    //建立物體
    b2BodyDef bodydef;
    bodydef.type = b2_staticBody; //設為靜止
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape; //設為圓形
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    //持續更新
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);
}

void Bird::setDynamic(){
    g_body->SetType(b2_dynamicBody);
}

void Bird::setVelocity(float x, float y){
    g_body->SetLinearVelocity(b2Vec2(x,y));
}

b2Vec2 Bird::getVelocity(){
    return g_body->GetLinearVelocity();
}

void Bird::setPos(float x, float y){
    g_body->SetTransform(b2Vec2(x,y),0);
}

b2Vec2 Bird::getPos(){
    return g_body->GetPosition();
}

void Bird::rotate(int rad){
    g_body->SetAngularVelocity(rad);
}
