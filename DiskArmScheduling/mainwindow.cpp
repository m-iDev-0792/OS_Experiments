#include "mainwindow.h"
#include "ui_mainwindow.h"
const QString selectedStyle("border:1px solid;background-color:#1CA4F8;border-radius:5px;width:50px");
const QString unselectedStyle("border:1px solid;background-color:white;border-radius:5px;width:50px");
qreal getOffset(int diskNum){
  return -(diskNum/500.0*75.0);
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->widget->setStyleSheet("border:1px solid black;background-color:white;");
  ui->SSTF->setChecked(true);
  QRegExp regx1("[0-9,]*$");
  QValidator *validator1 = new QRegExpValidator(regx1, ui->tasks );
  ui->tasks->setValidator(validator1);
  ui->defaultPos->setDisabled(!ui->setting->isChecked());
  ui->rightDirection->setStyleSheet(selectedStyle);
  ui->leftDirection->setStyleSheet(unselectedStyle);
  ui->rightDirection->setDisabled(true);
  ui->leftDirection->setDisabled(true);
  setFixedWidth(550);
  setFixedHeight(620);

  connect(this,SIGNAL(sendResult(vector<int>,int,int)),ui->widget,SLOT(getResult(vector<int>,int,int)));

  //set up graphicsView
  view=ui->graphicsView;
  scene=new QGraphicsScene(this);
  scene->setSceneRect(0,0,view->width()-10,view->height()-10);
  view->setScene(scene);
  QLineF topLine(scene->sceneRect().topLeft(),
                 scene->sceneRect().topRight());
  QLineF leftLine(scene->sceneRect().topLeft(),
                 scene->sceneRect().bottomLeft());
  QLineF rightLine(scene->sceneRect().topRight(),
                 scene->sceneRect().bottomRight());
  QLineF bottomLine(scene->sceneRect().bottomLeft(),
                 scene->sceneRect().bottomRight());
  QPen myPen = QPen(Qt::red);
//  scene->addLine(topLine, myPen);
//  scene->addLine(leftLine, myPen);
//  scene->addLine(rightLine, myPen);
//  scene->addLine(bottomLine, myPen);
//  scene->addRect(0,0,100,100,myPen);//Ref Rect
  //add disk item
  disk=new MyPicItem(QPixmap(":/image/disk.png"));
  disk->setPos(0,0);
  disk->setTransformOriginPoint(126,126);
  scene->addItem(disk);
  head=new MyPicItem(QPixmap(":/image/head.png"));
  head->setPos(173+75,78);//x start at 173 end at 173+75 ,you will never change y value 78
  scene->addItem(head);
  //add animation for disk
  auto rotation=new QPropertyAnimation(disk,"rotation");
  rotation->setStartValue(0);
  rotation->setEndValue(360);
  rotation->setDuration(5000);
  rotation->setLoopCount(-1);
  rotation->start();

  //add text item

  headStateText=new HeadStateItem();
  headStateText->setPos(360,0);
  scene->addItem(headStateText);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_run_clicked()
{
  //get task queue first
  QString text=ui->tasks->text();
  QStringList split=text.split(",");
  tasks.clear();
  for(int i=0;i<split.size();++i){
      if(split.at(i).isEmpty())continue;
//      qDebug()<<split.at(i)<<endl;
      if(split.at(i).toInt()>500)tasks.push_back(500);
      else tasks.push_back(split.at(i).toInt());
    }
  int defaultPos=ui->setting->isChecked()?ui->defaultPos->text().toInt():-1;
  if(defaultPos>500)defaultPos=500;
    if(ui->SSTF->isChecked()){
        getResultUsingSSTF(tasks,defaultPos);

      }else{
        //using SCAN algorithm
        getResultUsingSCAN(tasks,defaultPos,direction);
      }
    on_play_clicked();

}
void MainWindow::updateDiskTrackText(){

}

void MainWindow::on_setting_clicked()
{
    if(ui->setting->isChecked()){
        ui->defaultPos->setDisabled(false);
      }else{
        ui->defaultPos->setDisabled(true);
      }
}

void MainWindow::on_SCAN_clicked()
{
    if(ui->SCAN->isChecked()){
        ui->leftDirection->setDisabled(false);
        ui->rightDirection->setDisabled(false);
        direction=1;
        ui->rightDirection->setStyleSheet(selectedStyle);
        ui->leftDirection->setStyleSheet(unselectedStyle);
      }else{
        ui->leftDirection->setDisabled(true);
        ui->rightDirection->setDisabled(true);
      }
}

void MainWindow::on_leftDirection_clicked()
{
  direction=-1;
  ui->rightDirection->setStyleSheet(unselectedStyle);
  ui->leftDirection->setStyleSheet(selectedStyle);
}

void MainWindow::on_rightDirection_clicked()
{
  direction=1;
  ui->rightDirection->setStyleSheet(selectedStyle);
  ui->leftDirection->setStyleSheet(unselectedStyle);
}

void MainWindow::on_SSTF_clicked()
{
    on_SCAN_clicked();
}
void MainWindow::getResultUsingSSTF(vector<int> tasks,int defaultP){
  paintQueue.clear();
  if(tasks.empty()){
      return;
    }
  defaultPos=(defaultP==-1)?tasks[0]:defaultP;
  int lastVisited=(defaultP==-1)?tasks[0]:defaultP;
  int totalMovement=0;
  while(!tasks.empty()){
      int minIndex=0;
      int minDiff=100000086;
      for(int i=0;i<tasks.size();++i){
          int diff=abs(lastVisited-tasks[i]);
          if(diff<minDiff){
              minDiff=diff;
              minIndex=i;
            }
        }
      paintQueue.push_back(tasks[minIndex]);
      totalMovement+=abs(lastVisited-tasks[minIndex]);
      lastVisited=tasks[minIndex];
      tasks.erase(tasks.begin()+minIndex);
    }
  emit sendResult(paintQueue,defaultPos,totalMovement);
}
void MainWindow::getResultUsingSCAN(vector<int> tasks,int defaultP,int direction){
  paintQueue.clear();
  if(tasks.empty()){
      return;
    }
  defaultPos=(defaultP==-1)?tasks[0]:defaultP;
  int totalMovement=0;
  int lastVisited=(defaultP==-1)?tasks[0]:defaultP;
  sort(tasks.begin(),tasks.end());
  int startIndex=-1;
  if(direction==1){//startPos------------->
      //找到大于等于defaultPos的第一个下标
      for(int i=0;i<tasks.size();++i){
          if(defaultPos<=tasks[i]){
              startIndex=i;
              break;
            }
        }

    }else if(direction==-1){//<------------startPos
      //找到小于等于defaultPos的最后一个下标
      for(int i=0;i<tasks.size();++i){
          if(tasks[i]<=defaultPos)startIndex=i;
          else break;
        }
    }
  //初始方向来一趟
  int i=startIndex;
  while(i>=0&&i<tasks.size()){
      paintQueue.push_back(tasks[i]);
      totalMovement+=abs(lastVisited-tasks[i]);
      lastVisited=tasks[i];
      i+=direction;
    }
  //相反方向来一趟
  direction=-direction;
  i=startIndex+direction;
  while(i>=0&&i<tasks.size()){
      paintQueue.push_back(tasks[i]);
      totalMovement+=abs(lastVisited-tasks[i]);
      lastVisited=tasks[i];
      i+=direction;
    }
//  qDebug()<<"queue size:"<<paintQueue.size()<<endl;
  emit sendResult(paintQueue,defaultPos,totalMovement);
}

void MainWindow::on_play_clicked()
{
  if(paintQueue.empty())return;
  textIndex=0;
  QSequentialAnimationGroup* group=new QSequentialAnimationGroup(this);
  QPointF lastPos(173+75,78);
  head->setPos(QPointF(248+getOffset(defaultPos),78));
  int logicalLastPos=defaultPos;
  int totalMovement=0;
  for(int i=0;i<paintQueue.size();++i){
      int duration=abs(logicalLastPos-paintQueue[i])*10;
      QParallelAnimationGroup* singleMove=new QParallelAnimationGroup();
      QPropertyAnimation* temp=new QPropertyAnimation(head,"pos");
      temp->setStartValue(lastPos);
      lastPos=QPointF(248+getOffset(paintQueue[i]),78);
      temp->setEndValue(lastPos);
      temp->setDuration(duration);
      QPropertyAnimation* changeCurPos=new QPropertyAnimation(headStateText,"curPos");
      changeCurPos->setStartValue(logicalLastPos);
      changeCurPos->setEndValue(paintQueue[i]);
      changeCurPos->setDuration(duration);
      QPropertyAnimation* changeTotalMovement=new QPropertyAnimation(headStateText,"totalMovement");
      changeTotalMovement->setStartValue(totalMovement);
      changeTotalMovement->setEndValue(totalMovement+abs(logicalLastPos-paintQueue[i]));
      changeTotalMovement->setDuration(duration);
      singleMove->addAnimation(temp);
      singleMove->addAnimation(changeCurPos);
      singleMove->addAnimation(changeTotalMovement);

      totalMovement+=abs(logicalLastPos-paintQueue[i]);
      logicalLastPos=paintQueue[i];

      group->addAnimation(singleMove);
      group->addPause(1000);
    }
  group->start();
}

void MainWindow::on_random_clicked()
{
    default_random_engine engine(time(nullptr));
    uniform_int_distribution<> dis(0, 500);
    auto dice = bind(dis, engine);
    QString str;
    for(int i=0;i<6;++i)str+=QString("%1,").arg(dice());
    str+=QString("%1").arg(dice());
    ui->tasks->setText(str);
}
