#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //啟用事件管理
    qApp->installEventFilter(this);
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/doggy.mp3"));
    hit = new QMediaPlayer();
    hit->setMedia(QUrl("qrc:/hit.mp3"));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showEvent(QShowEvent *){
    //初始化
    startgame();
    //計時器
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(10);
}

bool MainWindow::eventFilter(QObject *, QEvent *event){
    QMouseEvent *mouseEvent = (QMouseEvent*) event;
    if(event->type() == QEvent::MouseButtonPress){
        if(mouseEvent->pos().x()<300){ //滑鼠位在此範圍才算準備發射
            isPressed = true;
            if(isFired==true&&skillUsed==false&&done==false&&birdnum<4) //收到發射後使用技能
                skillUsed = true;
            if(done==true) //已使用技能
                done=false;
        }
        //按下重玩
        if(mouseEvent->pos().x()>=550&&mouseEvent->pos().x()<650&&mouseEvent->pos().y()>=30&&mouseEvent->pos().y()<130){
            clear();
            startgame();
        }
        //按下離開
        if(mouseEvent->pos().x()>=800&&mouseEvent->pos().x()<900&&mouseEvent->pos().y()>=30&&mouseEvent->pos().y()<130){
            close();
        }
    }
    if(event->type() == QEvent::MouseMove){
        if(isPressed==true&&isFired==false&&skillUsed==false&&done==false){
            float x = mouseEvent->pos().x();
            float y = mouseEvent->pos().y();
            float yy = height() - mouseEvent->pos().y() + 30; //y需顛倒
            bird[birdnum]->setPos(x/30.0,yy/30.0);
            dx = x-init_x*30; //轉成像素相減
            dy = -(y-(height()-init_y*30)); //最後再顛倒
        }
    }
    if(event->type() == QEvent::MouseButtonRelease){
        if(isPressed==true&&isFired==false&&skillUsed==false&&done==false&&birdnum<4){ //發射
            //根據與準備位置的相對距離決定速度
            float vx=-(dx/7.0);
            float vy=-(dy/10.0);
            bird[birdnum]->setDynamic(); //設為動態
            bird[birdnum]->setVelocity(vx,vy);
            isPressed = false;
            isFired = true;
            if(birdnum<3) //尚未到最後一隻鳥，0.3秒後將下一隻鳥移到準備位置
                QTimer::singleShot(300,this,SLOT(newBird()));
            std::cout<<"shoot"<<std::endl;
        }

        if(isFired==true&&skillUsed==true&&birdnum<4){ //收到使用技能
            if(birdnum==0&&done==false){ //技能：無
                done=true;
                birdnum++;
                isFired=false;
                skillUsed=false;
                std::cout<<"0 skillused"<<std::endl;
            }
            if(birdnum==1&&done==false){ //技能：轉成當前反向速度的10倍
                float vx = bird[birdnum]->getVelocity().x;
                float vy = bird[birdnum]->getVelocity().x;
                bird[birdnum]->setVelocity(-vx*10,-vy*10);
                done=true;
                birdnum++;
                isFired=false;
                skillUsed=false;
                std::cout<<"1 skillused"<<std::endl;
            }
            if(birdnum==2&&done==false){ //技能：直線衝刺
                bird[birdnum]->setVelocity(100,0);
                done=true;
                birdnum++;
                isFired=false;
                skillUsed=false;
                std::cout<<"2 skillused"<<std::endl;
            }
            if(birdnum==3&&done==false){ //技能：快速旋轉與墜落
                bird[birdnum]->rotate(200);
                bird[birdnum]->setVelocity(0,-50);
                done=true;
                isFired=false;
                skillUsed=false;
                QTimer::singleShot(1000,this,SLOT(isAllDone()));
                std::cout<<"3 skillused"<<std::endl;
            }
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *){
    emit quitGame();
}

void MainWindow::startgame(){
    //設定視窗
    scene = new QGraphicsScene(0,0,width(),height());
    scene->setBackgroundBrush(QPixmap(":/bg.jpg").scaled(width(),height()));
    ui->graphicsView->setGeometry(0,0,960,540);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //環境設定，g=-9.8，1像素=30公尺
    world = new b2World(b2Vec2(0.0, -9.8));
    GameItem::setGlobalSize(QSizeF(32,18),size());
    //設定場景
    land = new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene);
    ui->shooter->setGeometry(100,330,50,125);
    ui->score->setGeometry(50,30,150,80);
    ui->nowscore->setGeometry(200,30,150,80);
    ui->nowscore->setText(QString::number(score));
    ui->restart->setGeometry(550,30,100,100);
    ui->exit->setGeometry(800,30,100,100);
    ui->win->setGeometry((width()/2)-150,(height()/2)-150,300,300);
    ui->win->setPixmap(QPixmap(":/win.png").scaled(300,300));
    ui->win->hide();
    ui->lose->setGeometry((width()/2)-150,(height()/2)-150,300,300);
    ui->lose->setPixmap(QPixmap(":/lose.png").scaled(300,300));
    ui->lose->hide();
    setBird();
    setWood();
    setPig();
    QTimer::singleShot(1000,this,SLOT(setReady())); //1秒後可進行計分
    music->stop();
    music->play();
    //設定資料
    isPressed = false;
    isFired = false;
    skillUsed = false;
    done = false;
    alldone = false;
    isReady = false;
    birdnum = 0;
    score = 0;
    die0 = false;
    die1 = false;
    die2 = false;
    die3 = false;
    die4 = false;

    std::cout<<"gamestart"<<std::endl;
}

void MainWindow::clear(){ //清除iTemList的物件
    itemList.clear();
}

void MainWindow::setBird(){ //初始化鳥
    bird[0] = new Bird(init_x,init_y,0.8,&timer,QPixmap(":/red.png"),world,scene);
    bird[1] = new Bird(2.5,3.8,0.8,&timer,QPixmap(":/black.png"),world,scene);
    bird[2] = new Bird(1.5,3.8,0.8,&timer,QPixmap(":/yellow.png"),world,scene);
    bird[3] = new Bird(0.2,3.8,0.8,&timer,QPixmap(":/white.png"),world,scene);
}

void MainWindow::setWood(){ //初始化木條
    //直向木條
    wood[0] = new Wood(13,5,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    wood[1] = new Wood(17,5,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    wood[2] = new Wood(21,5,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    wood[3] = new Wood(25,5,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    wood[4] = new Wood(19,11,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    wood[5] = new Wood(24,11,0.66,3.33,&timer,QPixmap(":/wood3.png").scaled(20,100),world,scene);
    //橫向木條
    wood[6] = new Wood(15,8,4,0.66,&timer,QPixmap(":/wood2.png").scaled(120,20),world,scene);
    wood[7] = new Wood(19,8,4,0.66,&timer,QPixmap(":/wood2.png").scaled(120,20),world,scene);
    wood[8] = new Wood(23,8,4,0.66,&timer,QPixmap(":/wood2.png").scaled(120,20),world,scene);
}

void MainWindow::setPig(){ //初始化豬
    pig[0] = new Pig(15,4,1,&timer,QPixmap(":/pig.png"),world,scene);
    pig[1] = new Pig(19,4,1.1,&timer,QPixmap(":/pig.png"),world,scene);
    pig[2] = new Pig(23,4,1.1,&timer,QPixmap(":/pig.png"),world,scene);
    pig[3] = new Pig(16,10,1.1,&timer,QPixmap(":/pig.png"),world,scene);
    pig[4] = new Pig(22,10,1.1,&timer,QPixmap(":/pig.png"),world,scene);
}

void MainWindow::tick(){ //持續更新
    world->Step(1.0/60.0,6,2);
    scene->update();
    if(isReady == true){ //可進行計分
        if(die0 == false){ //尚未擊中
            v0 = pig[0]->getVelocity(); //取得豬當下速度
            if (abs(v0.x)>1.5||abs(v0.y)>1.5){ //得分條件為豬當下任一速度>1.5
                die0 = true; //已擊中
                score += 1000;
                pig[0]->changePic(QPixmap(":/hit.png")); //換圖
                hit->play();
                //pig[0]->~GameItem();
            }
        }
        if(die1 == false){
            v1 = pig[1]->getVelocity();
            if(abs(v1.x)>1.5||abs(v1.y)>1.5){
                die1 = true;
                score += 1000;
                pig[1]->changePic(QPixmap(":/hit.png"));
                hit->play();
                //pig[1]->~GameItem();
            }
        }
        if(die2 == false){
            v2 = pig[2]->getVelocity();
            if(abs(v2.x)>1.5||abs(v2.y)>1.5){
                die2 = true;
                score += 1000;
                pig[2]->changePic(QPixmap(":/hit.png"));
                hit->play();
                //pig[2]->~GameItem();
            }
        }
        if(die3 == false){
            v3 = pig[3]->getVelocity();
            if(abs(v3.x)>1.5||abs(v3.y)>1.5){
                die3 = true;
                score += 1000;
                pig[3]->changePic(QPixmap(":/hit.png"));
                hit->play();
                //pig[3]->~GameItem();
            }
        }
        if(die4 == false){
            v4 = pig[4]->getVelocity();
            if(abs(v4.x)>1.5||abs(v4.y)>1.5){
                die4 = true;
                score += 1000;
                pig[4]->changePic(QPixmap(":/hit.png"));
                hit->play();
                //pig[4]->~GameItem();
            }
        }
        if(score == 5000){ //全部擊中則直接獲勝
            ui->win->show();
        }
        if(birdnum==3&&alldone==true&&score<5000){ //須等第四隻鳥用完技能後才可判斷
            ui->lose->show();
        }
    }
    ui->nowscore->setText(QString::number(score));
}

void MainWindow::setReady(){ //1秒後設為可計分
    isReady = true;
}

void MainWindow::newBird(){ //0.3秒後將下隻鳥移到準備位置
    bird[birdnum+1]->setPos(init_x,init_y);
}

void MainWindow::isAllDone(){ //全部鳥已發射且使用技能
    alldone = true;
}

void MainWindow::QUITSLOT(){ //結束信號
    music->stop();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
