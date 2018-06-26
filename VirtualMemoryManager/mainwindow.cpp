#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setFixedHeight(560);
  QStringList dataHeader;
  ui->history->horizontalHeader()->setStretchLastSection(true);
  dataHeader<<tr("访问页面")<<tr("访问结果");
  ui->history->setHorizontalHeaderLabels(dataHeader);
  ui->FIFO->setChecked(true);
  ui->history->horizontalHeader()->resizeSection(0,50);
  QRegExp regx1("[1-9][0-9]*$");
  QValidator *validator1 = new QRegExpValidator(regx1, ui->wantedPage );
  ui->wantedPage->setValidator(validator1);
  requestNum=pageNum=0;

  lastVisitedMemory.id=0;
  lastVisitedMemory.lastUsedTime=-1;
  lastVisitedMemory.loadTime=-1;
  //set up graphicsView
  view=ui->graphicsView;
  scene=new QGraphicsScene(this);
  scene->setSceneRect(0,0,view->width()-10,view->height()-10);
  QBrush bgBrush(QPixmap(":/image/chip.png"));
  scene->setBackgroundBrush(bgBrush);
  view->setBackgroundBrush(bgBrush);
  view->setScene(scene);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_setPageNum_clicked()
{
  memories.clear();
  ui->history->setRowCount(0);
  pageNum=ui->pageNum->value();
  for(int i=0;i<pageNum;++i){
      memories.push_back(Memory(i,-1,-1,-1));
    }

  scene->clear();
  caches.clear();
  hand=new MyPicItem(QPixmap(":/image/hand.png"));
  kick=new MyPicItem(QPixmap(":/image/kick.png"));
  arrow=new MyPicItem(QPixmap(":/image/arrow.png"));
  float gap=(view->height()-pageNum*chipHeight)/(pageNum+1.0);
  QParallelAnimationGroup* group=new QParallelAnimationGroup(scene);
  //add cache to graphcisView
  for(int i=0;i<pageNum;++i){
      CacheItem* temp=new CacheItem(chipWidth,chipHeight,scene);
      temp->setPos(view->width()/2.0,gap+chipHeight/2.0+(gap+chipHeight)*i);
      temp->setID(i);
      temp->setCacheMode(QGraphicsItem::ItemCoordinateCache);
      scene->addItem(temp);
      caches.push_back(temp);
      storedPageTexts.push_back(nullptr);
      QPropertyAnimation* animation=new QPropertyAnimation(temp,"pos");
      animation->setStartValue(QPointF(view->width()/2.0,-50));
      animation->setEndValue(QPointF(view->width()/2.0,gap+chipHeight/2.0+(gap+chipHeight)*i));
      animation->setDuration((i+1)*250);
      animation->setEasingCurve(QEasingCurve::OutCubic);
      group->addAnimation(animation);
    }
  group->start();
  kick->setTransformOriginPoint(QPointF(82,0));
  hand->setPos(-100,-100);
  kick->setPos(-100,-100);
  arrow->setPos(-100,-100);
  scene->addItem(hand);
  scene->addItem(kick);
  scene->addItem(arrow);
}
void MainWindow::FIFO(int page){
  for(int i=0;i<memories.size();++i){
      if(memories[i].storedPage==page){
          memories[i].lastUsedTime=++requestNum;
          ui->history->setRowCount(ui->history->rowCount()+1);
          int r=ui->history->rowCount()-1;
          ui->history->setItem(r,0,new QTableWidgetItem(QString::number(page)));
          ui->history->setItem(r,1,new QTableWidgetItem(tr("命中,在存储器%1中找到").arg(memories[i].id)));
          lastVisitedMemory.id=i;
          lastVisitedMemory.lastUsedTime=requestNum;
          lastVisitedMemory.loadTime=memories[i].loadTime;
          shootAt(i);
          return;
        }
    }
  //没有命中,寻找载入时间最长的cache
  int oldest=0;
  int oldestTime=1000000;
  for(int i=0;i<memories.size();++i){
      if(memories[i].loadTime<oldestTime){
          oldestTime=memories[i].loadTime;
          oldest=i;
        }
    }
  int originalPage=memories[oldest].storedPage;
  memories[oldest].storedPage=page;
  memories[oldest].loadTime=++requestNum;
  memories[oldest].lastUsedTime=requestNum;

  lastVisitedMemory.id=oldest;
  lastVisitedMemory.lastUsedTime=requestNum;
  lastVisitedMemory.loadTime=requestNum;
  if(originalPage==-1){
      //仅仅载入送值的动画
      playLoadPageAnimation(oldest,page,requestNum,requestNum);
    }else{
      //载入踢走值的动画和送值的动画
      playLoadPageAnimation(oldest,page,requestNum,requestNum,true);
    }
  ui->history->setRowCount(ui->history->rowCount()+1);
  int r=ui->history->rowCount()-1;
  ui->history->setItem(r,0,new QTableWidgetItem(QString::number(page)));
  ui->history->setItem(r,1,new QTableWidgetItem(tr("未命中,替换存储器%1").arg(memories[oldest].id)));

}
void MainWindow::LRU(int page){
  for(int i=0;i<memories.size();++i){
      if(memories[i].storedPage==page){
          memories[i].lastUsedTime=++requestNum;
          ui->history->setRowCount(ui->history->rowCount()+1);
          int r=ui->history->rowCount()-1;
          ui->history->setItem(r,0,new QTableWidgetItem(QString::number(page)));
          ui->history->setItem(r,1,new QTableWidgetItem(tr("命中,在存储器%1中找到").arg(memories[i].id)));
          lastVisitedMemory.id=i;
          lastVisitedMemory.lastUsedTime=requestNum;
          lastVisitedMemory.loadTime=memories[i].loadTime;
          shootAt(i);
          return;
        }
    }
  //没有命中,寻找最久没有使用的cache进行替换
  int least=0;
  int leastTime=1000000;
  for(int i=0;i<memories.size();++i){
      if(memories[i].lastUsedTime<leastTime){
          leastTime=memories[i].lastUsedTime;
          least=i;
        }
    }
  int originalPage=memories[least].storedPage;
  memories[least].storedPage=page;
  memories[least].loadTime=++requestNum;
  memories[least].lastUsedTime=requestNum;
  lastVisitedMemory.id=least;
  lastVisitedMemory.lastUsedTime=requestNum;
  lastVisitedMemory.loadTime=requestNum;
  if(originalPage==-1){
      //仅仅载入送值的动画
      playLoadPageAnimation(least,page,requestNum,requestNum);
    }else{
      //载入踢走值的动画和送值的动画
      playLoadPageAnimation(least,page,requestNum,requestNum,true);
    }
  //找到了要被替换的页面，更新历史信息
  ui->history->setRowCount(ui->history->rowCount()+1);
  int r=ui->history->rowCount()-1;
  ui->history->setItem(r,0,new QTableWidgetItem(QString::number(page)));
  ui->history->setItem(r,1,new QTableWidgetItem(tr("未命中,替换页面%1").arg(memories[least].id)));
}

void MainWindow::on_requestPage_clicked()
{
  if(ui->wantedPage->text().isEmpty())return;
  int page=ui->wantedPage->text().toInt();
  if(ui->FIFO->isChecked()){
      FIFO(page);
    }else{
      LRU(page);
    }
  ui->requestNum->setText(tr("已访问次数:")+QString::number(requestNum));

}

void MainWindow::on_resetHistory_clicked()
{
  requestNum=0;
  ui->requestNum->setText(tr("已访问次数:")+QString::number(requestNum));
  ui->history->setRowCount(0);
  for(auto& t:memories){
      t.loadTime=-1;
      t.lastUsedTime=-1;
      t.storedPage=-1;
    }
  //update view
}

void MainWindow::playLoadPageAnimation(int index, int loadPageNum,int loadTime,int lastUsedTime,bool needKick){

  arrow->setPos(-100,-100);
  QSequentialAnimationGroup* sendGroup=new QSequentialAnimationGroup();
  if(needKick){//加入踢腿动画
      QPointF legPoint=caches.at(index)->pos();
      legPoint=QPointF(legPoint.x()+160,legPoint.y()-60);
      kick->setPos(legPoint);

      QPointF textPoint=storedPageTexts.at(index)->pos();


      QPropertyAnimation* rotation=new QPropertyAnimation(kick,"rotation");
      rotation->setStartValue(-45);
      rotation->setEndValue(45);
      rotation->setDuration(250);
      QPropertyAnimation* rotationBack=new QPropertyAnimation(kick,"rotation");
      rotationBack->setStartValue(45);
      rotationBack->setEndValue(-45);
      rotationBack->setDuration(250);

      QParallelAnimationGroup* textGroup=new QParallelAnimationGroup();
      QPropertyAnimation* textRotation=new QPropertyAnimation(storedPageTexts.at(index),"rotation");
      textRotation->setStartValue(0);
      textRotation->setEndValue(360);
      textRotation->setLoopCount(4);
      textRotation->setDuration(250);
      QPropertyAnimation* textFlyOut=new QPropertyAnimation(storedPageTexts.at(index),"pos");
      textFlyOut->setStartValue(textPoint);
      textFlyOut->setEndValue(QPointF(textPoint.x()-400,textPoint.y()-100));
      textFlyOut->setDuration(1000);
      textGroup->addAnimation(textRotation);
      textGroup->addAnimation(textFlyOut);
      textGroup->addAnimation(rotationBack);
      //add kick animation
      sendGroup->addAnimation(rotation);
      sendGroup->addAnimation(textGroup);
      storedPageTexts.at(index)=nullptr;
    }
  QPointF cachePos=caches.at(index)->pos();
  QString t=QString("逻辑页面:")+QString::number(loadPageNum);
  QGraphicsTextItem* newText=new QGraphicsTextItem(t);
  newText->setPos(-100,-100);
  scene->addItem(newText);
  storedPageTexts.at(index)=newText;
  QPropertyAnimation* handIn=new QPropertyAnimation(hand,"pos");
  handIn->setStartValue(QPoint(cachePos.x()+250,cachePos.y()+20));
  handIn->setEndValue(QPoint(cachePos.x()+20,cachePos.y()+20));
  handIn->setDuration(1000);
  handIn->setEasingCurve(QEasingCurve::OutCubic);
  QPropertyAnimation* textIn=new QPropertyAnimation(newText,"pos");
  textIn->setStartValue(QPoint(cachePos.x()+250,cachePos.y()));
  textIn->setEndValue(QPoint(cachePos.x()+30,cachePos.y()));
  textIn->setDuration(1000);
  textIn->setEasingCurve(QEasingCurve::OutCubic);
  QPropertyAnimation* handOut=new QPropertyAnimation(hand,"pos");
  handOut->setStartValue(QPoint(cachePos.x()+20,cachePos.y()+20));
  handOut->setEndValue(QPoint(cachePos.x()+250,cachePos.y()+20));
  handOut->setDuration(1000);
  handOut->setEasingCurve(QEasingCurve::InCubic);
  QParallelAnimationGroup* in=new QParallelAnimationGroup();
  in->addAnimation(handIn);
  in->addAnimation(textIn);
  sendGroup->addAnimation(in);
  sendGroup->addAnimation(handOut);
  connect(sendGroup,SIGNAL(finished()),this,SLOT(updateMemoryInfo()));
  sendGroup->start();

}
void MainWindow::makeKickUnvisible(){
  kick->setPos(-400,-400);
}
void MainWindow::shootAt(int index){
  arrow->setPos(-100,-100);
  QPointF target=caches.at(index)->pos();
  target=QPointF(target.x()+80,target.y()-80);
  QPropertyAnimation* shootAnimation=new QPropertyAnimation(arrow,"pos");
  shootAnimation->setStartValue(QPointF(view->width(),0));
  shootAnimation->setEndValue(target);
  shootAnimation->setDuration(100);
  connect(shootAnimation,SIGNAL(finished()),this,SLOT(updateMemoryInfo()));
  shootAnimation->start();

}

void MainWindow::updateMemoryInfo(){
  CacheItem* item=caches.at(lastVisitedMemory.id);
  item->setLastUsedTime(lastVisitedMemory.lastUsedTime);
  item->setLoadTime(lastVisitedMemory.loadTime);
}
