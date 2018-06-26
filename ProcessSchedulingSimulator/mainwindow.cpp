#include "mainwindow.h"
#include "ui_mainwindow.h"

bool operator <(const Process& l,const Process& r){
  return l.createdTime<r.createdTime;
}
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //init layout
//  setFixedSize(560, 580);
  ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  QStringList dataHeader;
  ui->dataTable->horizontalHeader()->setStretchLastSection(true);
  dataHeader<<tr("进程名")<<tr("创建时间")<<tr("服务时间");
  ui->dataTable->setHorizontalHeaderLabels(dataHeader);
  QStringList resultHeader;
  ui->resultTable->horizontalHeader()->setStretchLastSection(true);
  resultHeader<<tr("进程名")<<tr("完成时间")<<tr("周转时间")<<tr("带权周转时间");
  ui->resultTable->setHorizontalHeaderLabels(resultHeader);
  //设置验证器，Qlinetext只能输入数字
  QRegExp regx1("[0-9]+$");
  QValidator *validator1 = new QRegExpValidator(regx1, ui->createdTime );
  QRegExp regx2("[1-9][0-9]*$");
  QValidator *validator2 = new QRegExpValidator(regx2, ui->serveTime );
  ui->createdTime->setValidator(validator1);
  ui->serveTime->setValidator(validator2);
  initLayout();
  connect(this,SIGNAL(sendDarwData(vector<QString>,vector<RunMsg>)),ui->widget,SLOT(getDarwData(vector<QString>,vector<RunMsg>)));

  //set up graphics elements
  //set up graphicsView
  view=ui->graphicsView;
  scene=new QGraphicsScene(this);
  scene->setSceneRect(0,0,view->width()-2,view->height()-2);
  view->setScene(scene);
  scene->setBackgroundBrush(QBrush(QColor(131,186,201)));
  TruckItem* truck=new TruckItem("hello",2);
  truck->setPos(100,100);
//  scene->addItem(truck);

  cpu=new QGraphicsPixmapItem(QPixmap(":/image/CPU.png"));
  cpu->setPos(140,340);
  cpu->setZValue(100);
  scene->addItem(cpu);

  parkinglotIcon=new QGraphicsPixmapItem(QPixmap(":/image/parkinglot.jpg"));
  parkinglotIcon->setPos(160,0);
  scene->addItem(parkinglotIcon);

  banner=new QGraphicsPixmapItem(QPixmap(":/image/banner.png"));
  banner->setPos(250,0);
  scene->addItem(banner);

  QPen linePen;
  linePen.setWidth(5);
  for(int i=0;i<6;++i){
      scene->addLine(5+30,60*i,130+30,60*i,linePen);
    }
  scene->addLine(130+30,0,130+30,60*5,linePen);

  //添加默认测试用例
  tasks.push_back(Process("A",0,3));
  addProcessToTable("A","0","3");
  tasks.push_back(Process("B",2,6));
  addProcessToTable("B","2","6");
  tasks.push_back(Process("C",4,4));
  addProcessToTable("C","4","4");
  tasks.push_back(Process("D",6,5));
  addProcessToTable("D","6","5");
  tasks.push_back(Process("E",8,2));
  addProcessToTable("E","8","2");
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::initLayout(){
  ui->FCFS->setGeometry(465,260,60,20);
  ui->RR->setGeometry(465,285,42,20);
  ui->slice->setGeometry(465+40,285,50,25);
  ui->SJF->setGeometry(465,315,42,20);
  ui->HRN->setGeometry(465,345,50,20);
  ui->run->setGeometry(470,370,80,20);
  ui->FCFS->setChecked(true);
}
void MainWindow::resizeEvent(QResizeEvent *e){
  if(e->size().height()<580)
    setGeometry(geometry().x(),geometry().y(),geometry().width(),580);
  else
    setGeometry(geometry().x(),geometry().y(),geometry().width(),e->size().height());
  int newHeight=(e->size().height()-10-ui->widget->geometry().y())>150?(e->size().height()-10-ui->widget->geometry().y()):150;
  ui->widget->setFixedHeight(newHeight);
}

void MainWindow::on_addTask_clicked()
{
  if(ui->taskName->text().isEmpty()||ui->createdTime->text().isEmpty()||ui->serveTime->text().isEmpty()){
      QMessageBox::warning(this,tr("提示"),tr("有项目为空白"));
      return;
    }
  for(auto &v:tasks){
      if(v.name==ui->taskName->text()){
          QMessageBox::warning(this,tr("提示"),tr("进程名已经存在"));
          return;
        }
    }
  tasks.push_back(Process(ui->taskName->text(),ui->createdTime->text().toInt(),ui->serveTime->text().toInt()));
  addProcessToTable(ui->taskName->text(),ui->createdTime->text(),ui->serveTime->text());
  ui->taskName->clear();
  ui->createdTime->clear();
  ui->serveTime->clear();
  ui->taskName->setFocus();
}
void MainWindow::addProcessToTable(QString n,QString c,QString s){
  ui->dataTable->setRowCount(ui->dataTable->rowCount()+1);
  int r=ui->dataTable->rowCount()-1;
  ui->dataTable->setItem(r,0,new QTableWidgetItem(n));
  ui->dataTable->setItem(r,1,new QTableWidgetItem(c));
  ui->dataTable->setItem(r,2,new QTableWidgetItem(s));
}

void MainWindow::on_deleteTask_clicked()
{
  int rowIndex = ui->dataTable->currentRow();
  cout<<rowIndex<<endl;
  if (rowIndex != -1)
  ui->dataTable->removeRow(rowIndex);
  tasks.erase(tasks.begin()+rowIndex);
}

void MainWindow::on_run_clicked()
{
  if(ui->FCFS->isChecked()){
      FCFS();
      createAnimation();
      updateResult();
    }
  else if(ui->SJF->isChecked()){
      SJF();
      createAnimation();
      updateResult();
    }
  else if(ui->RR->isChecked()){
      RR(ui->slice->value());
      createAnimation(ui->slice->value());
      updateResult();
    }
  else if(ui->HRN->isChecked()){
      HRN();
      createAnimation();
      updateResult();
    }

}
void MainWindow::FCFS(){
  if(tasks.empty())return;
  runResults.clear();
  runMsgs.clear();
  sort(tasks.begin(),tasks.end());
  int lastCompleteTime=0;
  for(int i=0;i<tasks.size();++i){

      int startTime=(tasks[i].createdTime>lastCompleteTime?tasks[i].createdTime:lastCompleteTime);
      int finishTime=startTime+tasks[i].serveTime;
      int turnaroundTime=finishTime-tasks[i].createdTime;

      runResults.push_back(RunResult(tasks[i].name,finishTime,//完成时间
          turnaroundTime,//周转时间
          (float)(turnaroundTime)/tasks[i].serveTime));//带权周转时间
      runMsgs.push_back(RunMsg(tasks[i].name,startTime,finishTime));
     lastCompleteTime=finishTime;
    }
}
void MainWindow::SJF(){
  if(tasks.empty())return;
  runResults.clear();
  runMsgs.clear();
  sort(tasks.begin(),tasks.end());
  int lastCompleteTime=0;
  auto tasksBackup=tasks;
  while(!tasksBackup.empty()){
          //查看有没有进程在等待，没有的话最新执行时间设置为第一个任务的创建时间
          int newestTime;
          if(lastCompleteTime>=tasksBackup[0].createdTime)newestTime=lastCompleteTime;
          else newestTime=tasksBackup[0].createdTime;
          int minServeTime=1000000;
          int minIndex=0;
          for(int i=0;i<tasksBackup.size();++i){
              if(tasksBackup[i].createdTime>newestTime)break;//创建时间比当前最新时间晚直接退出
              if(minServeTime>tasksBackup[i].serveTime){
                  minIndex=i;
                  minServeTime=tasksBackup[i].serveTime;
                }
            }
          runResults.push_back(RunResult(tasksBackup[minIndex].name,
                                         newestTime+tasksBackup[minIndex].serveTime,//完成时间
                                         newestTime+tasksBackup[minIndex].serveTime-tasksBackup[minIndex].createdTime,//周转时间
                                         (float)(newestTime+tasksBackup[minIndex].serveTime-tasksBackup[minIndex].createdTime)/tasksBackup[minIndex].serveTime));//带权周转时间
          runMsgs.push_back(RunMsg(tasksBackup[minIndex].name,newestTime,newestTime+tasksBackup[minIndex].serveTime));
          lastCompleteTime=newestTime+tasksBackup[minIndex].serveTime;

          //删除操作放在最后
          tasksBackup.erase(tasksBackup.begin()+minIndex);

    }
}
void MainWindow::RR(int slice){
  if(tasks.empty())return;
  runResults.clear();
  runMsgs.clear();
  sort(tasks.begin(),tasks.end());
  int lastCompleteTime=0;//上一个进程的完成时间（最新完成时间）
  map<QString,int> name2ServeTime;
  queue<Process> q;
  queue<Process> processList;
  for(auto& t:tasks){
      processList.push(t);
      name2ServeTime[t.name]=t.serveTime;
    }
  //首先初始化队列
  q.push(processList.front());
  processList.pop();
  while(!(processList.empty()&&q.empty())){
      if(slice>=q.front().serveTime){//有一个家伙要出队列了
          //添加runMsgs信息
          runMsgs.push_back(RunMsg(q.front().name,lastCompleteTime,lastCompleteTime+q.front().serveTime));
          lastCompleteTime+=q.front().serveTime;
          //添加runResult信息
          runResults.push_back(RunResult(q.front().name,
                                         lastCompleteTime,//完成时间
                                         lastCompleteTime-q.front().createdTime,
                                         (float)(lastCompleteTime-q.front().createdTime)/name2ServeTime[q.front().name]));
          q.pop();//走之

          //把在执行过程中 又新来的进程加进去
          while(!processList.empty()&&lastCompleteTime>=processList.front().createdTime){
              q.push(processList.front());
              processList.pop();
            }
          //如果执行过程中没有新的而且原来的队列已经执行完了，边空了，那么再加一个 “未来” 的进程进去
          if(q.empty()&&!processList.empty()){//如果队列还是空的
              q.push(processList.front());
              lastCompleteTime=processList.front().createdTime;
              processList.pop();
            }

        }else{
          //添加runMsgs信息
          runMsgs.push_back(RunMsg(q.front().name,lastCompleteTime,lastCompleteTime+slice));
          lastCompleteTime+=slice;
          q.front().serveTime-=slice;
          while(!processList.empty()&&lastCompleteTime>=processList.front().createdTime){
              q.push(processList.front());
              processList.pop();
            }
          auto front=q.front();
          q.pop();
          q.push(front);
        }
    }
}
void MainWindow::HRN(){
  if(tasks.empty())return;
  runResults.clear();
  runMsgs.clear();
  sort(tasks.begin(),tasks.end());
  int lastCompleteTime=0;
  queue<Process> processList;
  for(auto &t:tasks){
      processList.push(t);
    }
  vector<HRNNode> q;
  //don't forget to init priority_queue q!!!
  q.push_back(HRNNode(processList.front(),
                 (float)(lastCompleteTime-processList.front().createdTime+processList.front().serveTime)/processList.front().serveTime));
  processList.pop();
  while(!(q.empty()&&processList.empty())){
      auto &top=*q.begin();
      if(lastCompleteTime<top.p.createdTime){
          lastCompleteTime=top.p.createdTime;
        }
      // name finishTime turnaroundTime weightedTurnaroundTime
      runResults.push_back(RunResult(top.p.name,
                                     lastCompleteTime+top.p.serveTime,
                                     lastCompleteTime+top.p.serveTime-top.p.createdTime,
                                     (float)(lastCompleteTime+top.p.serveTime-top.p.createdTime)/top.p.serveTime));
      //name startTime endTime
      runMsgs.push_back(RunMsg(top.p.name,lastCompleteTime,lastCompleteTime+top.p.serveTime));
      lastCompleteTime+=top.p.serveTime;
      q.erase(q.begin());
      while(!processList.empty()&&processList.front().createdTime<=lastCompleteTime){
          q.push_back(HRNNode(processList.front(),0));//暂时不赋优先级，等最后统一更新在赋值
          processList.pop();
        }
      //统一更新优先级
      for(auto &node:q){
          node.priority=(float)(lastCompleteTime-node.p.createdTime+node.p.serveTime)/node.p.serveTime;
        }
      sort(q.begin(),q.end());
    }


}

void MainWindow::updateResult(){
  ui->resultTable->clearContents();
  ui->resultTable->setRowCount(runResults.size());
  int i=0;
  for(auto &r:runResults){
      ui->resultTable->setItem(i,0,new QTableWidgetItem(r.name));
      ui->resultTable->setItem(i,1,new QTableWidgetItem(QString::number(r.finishedTime)));
      ui->resultTable->setItem(i,2,new QTableWidgetItem(QString::number(r.turnaroundTime)));
      ui->resultTable->setItem(i,3,new QTableWidgetItem(QString("%1").arg(r.weightedTurnaroundTime)));
      ++i;
    }

  //更新调度图
  vector<QString> taskNames;
  for(auto& t:tasks){
      taskNames.push_back(t.name);
    }
  emit sendDarwData(taskNames,runMsgs);

}
int MainWindow::allocParkingSpace(){
  for(int i=0;i<5;++i){
      if(parkingSpaceState[i]==0){
          parkingSpaceState[i]=1;
//          qDebug()<<"分配位置"<<i;
          return i;
        }
    }
  return 0;
}
void MainWindow::releaseParkingSpace(int pos){
  parkingSpaceState[pos]=0;
}

void MainWindow::createAnimation(int slice){
  for(int i=0;i<6;++i)parkingSpaceState[i]=0;
  map<QString,TruckItem*> truckMap;
  map<QString,int> truckParkingPos;//-1=没有停车位，-2=我都走了还停个屁 >0我已经有停车位了，而且还赖着没走
  map<QString,int> truckQuantity;
  int parkingSpaceCount=0;
  QSequentialAnimationGroup* group=new QSequentialAnimationGroup();
  for(auto& t:tasks){
      TruckItem* item=new TruckItem(t.name,t.serveTime);
      item->setPos(-400,-400);
      truckMap[t.name]=item;
      truckParkingPos[t.name]=-1;
      truckQuantity[t.name]=t.serveTime;
      scene->addItem(item);
    }
  int index=-1;
  for(auto& msg:runMsgs){
      ++index;//for convenient use
      if(truckParkingPos[msg.name]==-1){
          //直接开到开始位置

        }else{
          //创建一个从停车位开到开始位置的动画
          QPropertyAnimation* gotoStartPos=new QPropertyAnimation(truckMap[msg.name],"pos");
          gotoStartPos->setStartValue(QPointF(50,truckParkingPos[msg.name]*60));
          gotoStartPos->setEndValue(QPointF(-50,truckParkingPos[msg.name]*60));
          gotoStartPos->setDuration(1000);
          group->addAnimation(gotoStartPos);

          //让出停车位
          releaseParkingSpace(truckParkingPos[msg.name]);
          truckParkingPos[msg.name]=-1;
//          qDebug()<<msg.name<<"让出位置"<<truckParkingPos[msg.name];
        }

      //创建开到CPU的动画
      QPropertyAnimation* gotoCPU=new QPropertyAnimation(truckMap[msg.name],"pos");
      gotoCPU->setStartValue(QPointF(400,360));
      gotoCPU->setEndValue(QPointF(160,360));
      gotoCPU->setDuration(3000);
      group->addAnimation(gotoCPU);
      //update quantity
      QPropertyAnimation* changeQuantity=new QPropertyAnimation(truckMap[msg.name],"quantity");
      changeQuantity->setStartValue(truckQuantity[msg.name]);
      changeQuantity->setEndValue((truckQuantity[msg.name]-slice)>0?(truckQuantity[msg.name]-slice):0);
      changeQuantity->setDuration(3000);

      QPropertyAnimation* leaveCPU=new QPropertyAnimation(truckMap[msg.name],"pos");
      leaveCPU->setStartValue(QPointF(160,360));
      leaveCPU->setEndValue(QPointF(-150,360));
      leaveCPU->setDuration(3000);

      //看看这期间有没有新车进来
      int endTime=msg.end;
      QParallelAnimationGroup* newTruckComeIn=new QParallelAnimationGroup();
      for(auto& t:tasks){
          if(t.createdTime<=endTime&&truckParkingPos[t.name]==-1&&t.name!=msg.name){
              //分配新的停车场位置
              truckParkingPos[t.name]=allocParkingSpace();
              QPropertyAnimation* gotoParkingLot=new QPropertyAnimation(truckMap[t.name],"pos");
              gotoParkingLot->setStartValue(QPointF(-50,truckParkingPos[t.name]*60));
              gotoParkingLot->setEndValue(QPointF(50,truckParkingPos[t.name]*60));
              gotoParkingLot->setDuration(2000);
              newTruckComeIn->addAnimation(gotoParkingLot);
            }
        }
      newTruckComeIn->addAnimation(changeQuantity);
      group->addAnimation(newTruckComeIn);
      group->addAnimation(leaveCPU);

      truckQuantity[msg.name]-=slice;
      if(truckQuantity[msg.name]<=0){//车子空了，直接开走
          if(truckParkingPos[msg.name]>0)releaseParkingSpace(truckParkingPos[msg.name]);
          truckParkingPos[msg.name]=-2;
//          qDebug()<<msg.name<<"让出位置"<<truckParkingPos[msg.name];
        }else{
          //车子没有空，还有货
          if(truckParkingPos[msg.name]==-1){
          //还有东西到停车场里停一下,但是没有停车位，分配一个
              truckParkingPos[msg.name]=allocParkingSpace();
            }
          //创建停到停车场里的动画
          QPropertyAnimation* gotoParkingLot=new QPropertyAnimation(truckMap[msg.name],"pos");
          gotoParkingLot->setStartValue(QPointF(-50,truckParkingPos[msg.name]*60));
          gotoParkingLot->setEndValue(QPointF(50,truckParkingPos[msg.name]*60));
          gotoParkingLot->setDuration(2000);
          group->addAnimation(gotoParkingLot);
        }

    }
  group->start();
}
