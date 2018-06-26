#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  colorList.push_back(QColor(0 ,250 ,154));
  colorList.push_back(QColor(30 ,144 ,255));
  colorList.push_back(QColor(0 ,255 ,255));
  colorList.push_back(QColor(255 ,99 ,71));
  colorList.push_back(QColor(255 ,0 ,255));
  colorList.push_back(QColor(155 ,48 ,255));

  colorList.push_back(QColor(173 ,216 ,230));
  colorList.push_back(QColor(202 ,255 ,112));
  colorList.push_back(QColor(238 ,238 ,0));
  colorList.push_back(QColor(255 ,193 ,193));
  colorList.push_back(QColor(255 ,114 ,86));
  colorList.push_back(QColor(255 ,110 ,180));
  colorList.push_back(QColor(255 ,225 ,255));
  colorIndex=0;
  QStringList dataHeader;
  ui->filelist->horizontalHeader()->setStretchLastSection(true);
  dataHeader<<tr("文件名")<<tr("大小")<<tr("起始块号")<<tr("块数");
  ui->filelist->setHorizontalHeaderLabels(dataHeader);
  ui->filelist->horizontalHeader()->resizeSection(0,80);
  ui->filelist->horizontalHeader()->resizeSection(1,40);
  ui->filelist->horizontalHeader()->resizeSection(2,60);
  ui->filelist->horizontalHeader()->resizeSection(3,40);
  ui->filelist->setSelectionBehavior(QAbstractItemView::SelectRows);
  QStringList dataHeader2;
  ui->freetableView->horizontalHeader()->setStretchLastSection(true);
  dataHeader2<<tr("起始块号")<<tr("块数");
  ui->freetableView->setHorizontalHeaderLabels(dataHeader2);

  mode=FreeTable;
  head=nullptr;
  ui->freetable->setChecked(true);
  ui->bitmapview->setVisible(false);
  setFixedWidth(960);
  isRunBtnNowReset=false;
  ui->del->setDisabled(true);
  ui->addMore->setDisabled(true);

  //set up graphics elements

  view=ui->graphicsView;
  scene=new QGraphicsScene(this);
  scene->setSceneRect(0,0,5*view->width()-2,5*view->height()-2);
  view->setScene(scene);

  drawMeshBackground();
  QMatrix matrix;
  matrix.scale(.18,0.18);
  view->setMatrix(matrix);
  view->setDragMode(QGraphicsView::ScrollHandDrag);

  lawnmower=new MyPicItem(QPixmap(":/image/lawnmower.png"));
  stamp=new MyPicItem(QPixmap(":/image/stamp.png"));
  stamp->setPos(-400,-400);
  lawnmower->setPos(-400,-400);
  lawnmowerLastX=-400;
  lawnmowerLastY=-400;
  stamp->setZValue(1000);
  lawnmower->setZValue(1000);
  scene->addItem(stamp);
  scene->addItem(lawnmower);

}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::resetAll(){
  isRunBtnNowReset=false;
  ui->run->setText(tr("创建随机文件"));
  ui->del->setDisabled(true);
  ui->addMore->setDisabled(true);

  //初始化所有条件
  freetable.clear();
  fileList.clear();
  for(int i=0;i<500;++i)bitMap[i]=false;
  if(head!=nullptr){
      listNode* temp;
      while(head!=nullptr){
          temp=head;
          head=head->next;
          delete temp;
        }
    }
  head=new listNode(500,0,nullptr);

  //Graphics scene的初始化
  scene->clear();
  fileBlocksMap.clear();
  drawMeshBackground();
  lawnmower=new MyPicItem(QPixmap(":/image/lawnmower.png"));
  stamp=new MyPicItem(QPixmap(":/image/stamp.png"));
  stamp->setPos(-400,-400);
  lawnmower->setPos(-400,-400);
  lawnmowerLastX=-400;
  lawnmowerLastY=-400;
  stamp->setZValue(1000);
  lawnmower->setZValue(1000);
  scene->addItem(stamp);
  scene->addItem(lawnmower);
  updateView();
}

void MainWindow::on_run_clicked()
{
  if(isRunBtnNowReset){
      resetAll();
    }else{
  fileList.clear();
  int freeblock=0;
  std::default_random_engine engine(time(nullptr));
  std::uniform_int_distribution<> dis(2, 10);
  auto dice = std::bind(dis,engine);
  ui->filelist->clearContents();
  freetable.push_back(freetableNode(0,500));
  QSequentialAnimationGroup* runAnimation=new QSequentialAnimationGroup();
  for(int i=0;i<randomFileNum;++i){
      int size=dice();
      int blockNum=ceil((float)size/blocksize);
      //cout<<"size:"<<size<<"blockNum"<<blockNum<<"start"<<freeblock<<endl;
      file temp;
      if(mode==FreeTable){
          temp=createFileUsingFreetable(QString::number(i+1)+QString(".txt"),size);
        }else if(mode==FreeLinkList){
          temp=createFileUsingFreelinklist(QString::number(i+1)+QString(".txt"),size);

        }else if(mode==BitMap){
          temp=createFileUsingBitMap(QString::number(i+1)+QString(".txt"),size);
        }
      if(temp.startBlock>=0)
        fileList.push_back(temp);
      runAnimation->addAnimation(createFileShowUpAnimation(QString::number(i+1)+QString(".txt")));
      freeblock+=blockNum;
    }

  updateView();
  isRunBtnNowReset=true;
  ui->run->setText(tr("重置"));
  ui->del->setDisabled(false);
  runAnimation->start();
    }
}
//-----------------------------空闲表法--------------------------------------
file MainWindow::createFileUsingFreetable(QString filename,float filesize){
  int candidate=-1;
  for(int i=0;i<freetable.size();++i){
      if(freetable[i].blockNum*blocksize>=filesize){
          candidate=i;
          break;
        }
    }
  if(candidate==-1){
      return file(QString("none"),0,-1,0);//找不到合适的空间
    }
  int blockNum=ceil(filesize/blocksize);
  if(freetable[candidate].blockNum==blockNum){//如果大小刚好合适

      int startBlock=freetable[candidate].startBlock;
      freetable.erase(freetable.begin()+candidate);
      addFileBlockItem(filename,startBlock,blockNum,filesize);
      return file(filename,filesize,startBlock,blockNum);
    }else{//this block still have some free space
      int startBlock=freetable[candidate].startBlock;
      freetable[candidate].startBlock=startBlock+blockNum;
      freetable[candidate].blockNum-=blockNum;
      //重新排序
      sort(freetable.begin(),freetable.end());
      addFileBlockItem(filename,startBlock,blockNum,filesize);
      return file(filename,filesize,startBlock,blockNum);
    }
}
void MainWindow::delFileUsingFreetable(QString delFilename){
  int index=-1;
  for(int i=0;i<fileList.size();++i){
      if(fileList[i].fileName==delFilename){
          index=i;
          break;
        }
    }
  if(index==-1)return;
  for(int i=0;i<freetable.size();++i){
      //看看有没有连续的空间可以合并的
      if(freetable[i].startBlock==fileList[index].startBlock+fileList[index].blockNum){
          freetable[i].startBlock=fileList[index].startBlock;
          freetable[i].blockNum+=fileList[index].blockNum;
          fileList.erase(fileList.begin()+index);
          sort(freetable.begin(),freetable.end());
          return;
        }
    }
  freetable.push_back(freetableNode(fileList[index].startBlock,fileList[index].blockNum));
  fileList.erase(fileList.begin()+index);
  sort(freetable.begin(),freetable.end());
}

//--------------------------------------------------------------------------


//-------------------------位示图法------------------------------------------
file MainWindow::createFileUsingBitMap(QString filename, float filesize){
  int blockNum=ceil(filesize/blocksize);
  for(int i=0;i<500;++i){
      int ok=true;
      if(bitMap[i])continue;
      for(int j=0;j<blockNum;++j){
          if(i+j>=500){
              ok=false;
              break;
            }
          if(bitMap[i+j]){
            ok=false;
            break;
            }
        }
      if(ok){
          for(int k=0;k<blockNum;++k){
              bitMap[i+k]=true;
            }
          addFileBlockItem(filename,i,blockNum,filesize);
          return file(filename,filesize,i,blockNum);
        }
    }
  return file(filename,filesize,-1,0);
}
void MainWindow::delFileUsingBitMap(QString delFilename){
  int index=-1;
  for(int i=0;i<fileList.size();++i){
      if(fileList[i].fileName==delFilename){
          index=i;
          break;
        }
    }
  if(index==-1)return;
  for(int i=0;i<fileList[index].blockNum;++i){
      bitMap[fileList[index].startBlock+i]=false;
    }
  fileList.erase(fileList.begin()+index);
}

//--------------------------------------------------------------------------
//------------------------空闲链表法------------------------------------------
file MainWindow::createFileUsingFreelinklist(QString filename, float filesize){
  int blockNum=ceil(filesize/blocksize);
  listNode* ptr=head;
  listNode* ptrLast=head;
//  qDebug()<<"head data:"<<head->startBlock<<" blockNum"<<head->blockNum<<endl;
  while(ptr!=nullptr){
      if(ptr->blockNum>blockNum){//一个块的空间还有的多
          //不会删除任何节点
          file newFile(filename,filesize,ptr->startBlock,blockNum);
          addFileBlockItem(filename,ptr->startBlock,blockNum,filesize);
          ptr->startBlock+=blockNum;
          ptr->blockNum-=blockNum;
          return newFile;
        }else if(ptr->blockNum==blockNum){//一个块的空间刚好，则这个块要被删除了
          if(ptr==head){
              head=ptr->next;
            }else{
              ptrLast->next=ptr->next;
            }
          file newFile(filename,filesize,ptr->startBlock,blockNum);
          addFileBlockItem(filename,ptr->startBlock,blockNum,filesize);
          delete ptr;
          return newFile;
        }
      ptrLast=ptr;
      ptr=ptr->next;
    }
  return file(QString("none"),0,-1,0);//找不到合适的空间
}
void MainWindow::delFileUsingFreelinklist(QString delFilename){
  int index=-1;
  for(int i=0;i<fileList.size();++i){
      if(fileList[i].fileName==delFilename){
          index=i;
          break;
        }
    }
  if(index==-1)return;

  if(head==nullptr){
      head=new listNode(fileList[index].startBlock,fileList[index].blockNum,nullptr);
      fileList.erase(fileList.begin()+index);
      return;
    }
  listNode *ptrLast=head;
  listNode *ptr=head;
  while(ptr!=nullptr){
      if(ptr->startBlock==fileList[index].startBlock+fileList[index].blockNum){
          ptr->startBlock=fileList[index].startBlock;
          ptr->blockNum+=fileList[index].blockNum;
          fileList.erase(fileList.begin()+index);
          return;
        }else if(ptr->startBlock>fileList[index].startBlock+fileList[index].blockNum){
          listNode *newNode=new listNode(fileList[index].blockNum,fileList[index].startBlock,nullptr);
          if(ptr==head){
              head=newNode;
              newNode->next=ptr;
            }else{
              ptrLast->next=newNode;
              newNode->next=ptr;
            }
          fileList.erase(fileList.begin()+index);
          return;
        }else{
          ptrLast=ptr;
          ptr=ptr->next;
        }
    }
}

//--------------------------------------------------------------------------
void MainWindow::updateView(){
  ui->filelist->setRowCount(0);
  for(auto& f:fileList){
        ui->filelist->setRowCount(ui->filelist->rowCount()+1);
        int r=ui->filelist->rowCount()-1;
        ui->filelist->setItem(r,0,new QTableWidgetItem(f.fileName));
        ui->filelist->setItem(r,1,new QTableWidgetItem(QString("%1").arg(f.size)));
        ui->filelist->setItem(r,2,new QTableWidgetItem(QString::number(f.startBlock)));
        ui->filelist->setItem(r,3,new QTableWidgetItem(QString::number(f.blockNum)));
      }

  if(mode==FreeTable){
      ui->freetableView->setRowCount(0);
      for(auto& ftn:freetable){
          ui->freetableView->setRowCount(ui->freetableView->rowCount()+1);
          int r=ui->freetableView->rowCount()-1;
          ui->freetableView->setItem(r,0,new QTableWidgetItem(QString::number(ftn.startBlock)));
          ui->freetableView->setItem(r,1,new QTableWidgetItem(QString::number(ftn.blockNum)));
        }
    }
  else if(mode==FreeLinkList){
      listNode* v;
      v=head;
      ui->freetableView->setRowCount(0);
      while(v!=nullptr){
          ui->freetableView->setRowCount(ui->freetableView->rowCount()+1);
          int r=ui->freetableView->rowCount()-1;
          ui->freetableView->setItem(r,0,new QTableWidgetItem(QString::number(v->startBlock)));
          ui->freetableView->setItem(r,1,new QTableWidgetItem(QString::number(v->blockNum)));
          v=v->next;
        }
    }
  else if(mode==BitMap){
      ui->bitmapview->clear();
      QString m;
      for(int i=0;i<500;++i)
        m.append(bitMap[i]?QChar('1'):QChar('0'));
      ui->bitmapview->setText(m);
    }

}

void MainWindow::on_del_clicked()
{

  QSequentialAnimationGroup* delFileAnimation=new QSequentialAnimationGroup();

  if(mode==FreeTable){
      for(int i=0;i<randomFileNum/2;++i){
          delFileUsingFreetable(QString::number(i*2+1)+QString(".txt"));
          delFileAnimation->addAnimation(createFileDisappearAnimation(QString::number(i*2+1)+QString(".txt")));
        }
    }
  else if(mode==FreeLinkList){
      for(int i=0;i<randomFileNum/2;++i){
          delFileUsingFreelinklist(QString::number(i*2+1)+QString(".txt"));
          delFileAnimation->addAnimation(createFileDisappearAnimation(QString::number(i*2+1)+QString(".txt")));
        }
    }
  else if(mode==BitMap){
      for(int i=0;i<randomFileNum/2;++i){
          delFileUsingBitMap(QString::number(i*2+1)+QString(".txt"));
          delFileAnimation->addAnimation(createFileDisappearAnimation(QString::number(i*2+1)+QString(".txt")));
        }
    }
  //create lawnmower goes away animation
  QPropertyAnimation* goAway=new QPropertyAnimation(lawnmower,"pos");
  goAway->setStartValue(QPointF(lawnmowerLastX,lawnmowerLastY));
  goAway->setEndValue(QPointF(lawnmowerLastX+1000,lawnmowerLastY));
  goAway->setDuration(200);
  delFileAnimation->addAnimation(goAway);
    updateView();
    ui->addMore->setDisabled(false);
    ui->del->setDisabled(true);
    connect(delFileAnimation,SIGNAL(finished()),this,SLOT(resetLawnmowerStatus()));
    delFileAnimation->start();
}

void MainWindow::on_addMore_clicked()
{

  QSequentialAnimationGroup* runAnimation=new QSequentialAnimationGroup();
  ui->addMore->setDisabled(true);
  if(mode==FreeTable){
      fileList.push_back(createFileUsingFreetable(tr("A.txt"),7));
      fileList.push_back(createFileUsingFreetable(tr("B.txt"),5));
      fileList.push_back(createFileUsingFreetable(tr("C.txt"),2));
      fileList.push_back(createFileUsingFreetable(tr("D.txt"),9));
      fileList.push_back(createFileUsingFreetable(tr("E.txt"),3.50));
    }
  else if(mode==FreeLinkList){
      fileList.push_back(createFileUsingFreelinklist(tr("A.txt"),7));
      fileList.push_back(createFileUsingFreelinklist(tr("B.txt"),5));
      fileList.push_back(createFileUsingFreelinklist(tr("C.txt"),2));
      fileList.push_back(createFileUsingFreelinklist(tr("D.txt"),9));
      fileList.push_back(createFileUsingFreelinklist(tr("E.txt"),3.50));
    }
  else if(mode==BitMap){
      fileList.push_back(createFileUsingBitMap(tr("A.txt"),7));
      fileList.push_back(createFileUsingBitMap(tr("B.txt"),5));
      fileList.push_back(createFileUsingBitMap(tr("C.txt"),2));
      fileList.push_back(createFileUsingBitMap(tr("D.txt"),9));
      fileList.push_back(createFileUsingBitMap(tr("E.txt"),3.50));
    }
  runAnimation->addAnimation(createFileShowUpAnimation(QString("A.txt")));
  runAnimation->addAnimation(createFileShowUpAnimation(QString("B.txt")));
  runAnimation->addAnimation(createFileShowUpAnimation(QString("C.txt")));
  runAnimation->addAnimation(createFileShowUpAnimation(QString("D.txt")));
  runAnimation->addAnimation(createFileShowUpAnimation(QString("E.txt")));
  runAnimation->start();
  updateView();
}

void MainWindow::on_freetable_clicked()
{
  if(mode==FreeTable)return;
    mode=FreeTable;
    ui->viewtype->setText(tr("空闲表"));
    ui->bitmapview->setVisible(false);
    ui->freetableView->setVisible(true);
    setFixedWidth(960);
    resetAll();
    updateView();
}

void MainWindow::on_freelinklist_clicked()
{
  if(mode==FreeLinkList)return;
    mode=FreeLinkList;
    ui->viewtype->setText(tr("空闲链表"));
    ui->bitmapview->setVisible(false);
    ui->freetableView->setVisible(true);
//    if(head!=nullptr){
//        listNode* temp;

//        while(head!=nullptr){
//            temp=head;
//            head=head->next;
//            delete temp;
//          }
//      }
//    head=new listNode(500,0,nullptr);
    resetAll();
    updateView();
}

void MainWindow::on_bitmap_clicked()
{
  if(mode==BitMap)return;
    mode=BitMap;
    ui->viewtype->setText(tr("位示图"));
    for(int i=0;i<500;++i)bitMap[i]=false;
    ui->bitmapview->setVisible(true);
    ui->freetableView->setVisible(false);
    setFixedWidth(960);
    resetAll();
    updateView();
}
void MainWindow::paintEvent(QPaintEvent *e){
}
void MainWindow::drawMeshBackground(){
  float horiGap=scene->width()/20.0;
  float vertGap=scene->height()/25.0;
  for(int i=1;i<20;++i){
      scene->addLine(horiGap*i,0,horiGap*i,scene->height());
    }
  for(int i=1;i<25;++i){
      scene->addLine(0,vertGap*i,scene->width(),vertGap*i);
    }
  QLineF topLine(scene->sceneRect().topLeft(),scene->sceneRect().topRight());
  QLineF leftLine(scene->sceneRect().topLeft(),scene->sceneRect().bottomLeft());
  QLineF rightLine(scene->sceneRect().topRight(),scene->sceneRect().bottomRight());
  QLineF bottomLine(scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());
  scene->addLine(topLine);
  scene->addLine(leftLine);
  scene->addLine(rightLine);
  scene->addLine(bottomLine);
//  scene->setBackgroundBrush(QBrush(QColor(188,133,97)));
}
void MainWindow::addFileBlockItem(QString filename, int startBlock, int blockNum, float size){
  vector<FileBlockItem*> temp;
  QColor color=colorList.at(colorIndex++%colorList.size());
  for(int i=0;i<blockNum;++i){
      float realBlockSize=size<blocksize?size:blocksize;
      size-=blocksize;
      float w=scene->width()/20.0;
      float h=scene->height()/25.0*realBlockSize/blocksize;

      FileBlockItem* item=new FileBlockItem(w,h,filename,i,startBlock,color);
      item->setPos(((startBlock+i)%20)*scene->width()/20.0,((startBlock+i)/20)*scene->height()/25.0);
      scene->addItem(item);
      item->setVisible(false);
      temp.push_back(item);
    }
  fileBlocksMap[filename]=temp;
}

QSequentialAnimationGroup* MainWindow::createFileShowUpAnimation(QString filename){
  vector<FileBlockItem*> v=fileBlocksMap[filename];
  QSequentialAnimationGroup* fileShowUp=new QSequentialAnimationGroup();
  if(v.empty()){
//      qDebug()<<filename<<" is empty!"<<endl;
      return fileShowUp;
    }
  //create first block show up animation

  QPropertyAnimation* firstStampFall=new QPropertyAnimation(stamp,"pos");
  firstStampFall->setStartValue(QPointF(v[0]->x()-25,v[0]->y()-200));
  firstStampFall->setEndValue(QPointF(v[0]->x()-25,v[0]->y()-100));
  firstStampFall->setDuration(300);
  firstStampFall->setEasingCurve(QEasingCurve::OutCubic);
  fileShowUp->addAnimation(firstStampFall);
  connect(firstStampFall,SIGNAL(finished()),v[0],SLOT(showUp()));
  for(int i=1;i<v.size();++i){
      //从上一个文件块移走的动画
      QPropertyAnimation* stampBack=new QPropertyAnimation(stamp,"pos");
      stampBack->setStartValue(QPointF(v[i-1]->x()-25,v[i-1]->y()-100));
      stampBack->setEndValue(QPointF(v[i-1]->x()+67.65,v[i-1]->y()-200));
      stampBack->setDuration(300);
      QPropertyAnimation* stampRotation=new QPropertyAnimation(stamp,"rotation");
      stampRotation->setStartValue(0);
      stampRotation->setKeyValueAt(0.3,15);
      stampRotation->setKeyValueAt(0.7,15);
      stampRotation->setEndValue(0);
      stampRotation->setDuration(300);
      QParallelAnimationGroup* backPara=new QParallelAnimationGroup();
      backPara->addAnimation(stampBack);
      backPara->addAnimation(stampRotation);

      //落到当前块的动画
      QPropertyAnimation* stampFall=new QPropertyAnimation(stamp,"pos");
      stampFall->setStartValue(QPointF(v[i]->x()-25,v[i]->y()-200));
      stampFall->setEndValue(QPointF(v[i]->x()-25,v[i]->y()-100));
      stampFall->setDuration(300);
      fileShowUp->addAnimation(backPara);
      fileShowUp->addAnimation(stampFall);
      connect(stampFall,SIGNAL(finished()),v[i],SLOT(showUp()));
    }
  QPropertyAnimation* lastStampBack=new QPropertyAnimation(stamp,"pos");
  lastStampBack->setStartValue(QPointF(v[v.size()-1]->x()-25,v[v.size()-1]->y()-100));
  lastStampBack->setEndValue(QPointF(v[v.size()-1]->x()+67.65,v[v.size()-1]->y()-200));
  lastStampBack->setDuration(300);
  fileShowUp->addAnimation(lastStampBack);
  connect(fileShowUp,SIGNAL(finished()),this,SLOT(resetStampStatus()));
  return fileShowUp;
}
QSequentialAnimationGroup* MainWindow::createFileDisappearAnimation(QString filename){
  vector<FileBlockItem*> v=fileBlocksMap[filename];
  fileBlocksMap.erase(fileBlocksMap.find(filename));
  QSequentialAnimationGroup* fileDisappear=new QSequentialAnimationGroup();
  if(v.empty()){
      qDebug()<<"v is empty!"<<endl;
      return fileDisappear;
    }
  int xOffset=-150;
  //create transition animation first
  if(abs(lawnmowerLastY-(v[0]->y()-50))<1){
      QPropertyAnimation* transition=new QPropertyAnimation(lawnmower,"pos");
      transition->setStartValue(QPointF(lawnmowerLastX,lawnmowerLastY));
      transition->setEndValue(QPointF(v[0]->x()+xOffset,v[0]->y()-50));
      transition->setDuration(abs(lawnmowerLastY-(v[0]->y()-50)+5e-7)*200000000);
      transition->setEasingCurve(QEasingCurve::OutCirc);
      fileDisappear->addAnimation(transition);
    }
  //create moveIn animation
  for(int i=0;i<v.size();++i){
      QPropertyAnimation* lawnmowerMoveIn=new QPropertyAnimation(lawnmower,"pos");
      lawnmowerMoveIn->setStartValue(QPointF(v[i]->x()+xOffset,v[i]->y()-50));
      lawnmowerMoveIn->setEndValue(QPointF(v[i]->x()+xOffset+92.65,v[i]->y()-50));
      lawnmowerMoveIn->setDuration(500);
      fileDisappear->addAnimation(lawnmowerMoveIn);
      connect(lawnmowerMoveIn,SIGNAL(finished()),v[i],SLOT(disappear()));
    }
  lawnmowerLastX=v[v.size()-1]->x()+xOffset+92.65;
  lawnmowerLastY=v[v.size()-1]->y()-50;
  QPropertyAnimation* lawnmowerMoveOut=new QPropertyAnimation(lawnmower,"pos");
  lawnmowerMoveOut->setStartValue(QPointF(v[v.size()-1]->x()+xOffset+92.65,v[v.size()-1]->y()-50));
  lawnmowerMoveOut->setEndValue(QPointF(v[v.size()-1]->x()+50,v[v.size()-1]->y()-50));
  lawnmowerMoveOut->setDuration(500);
//  fileDisappear->addAnimation(lawnmowerMoveOut);
  return fileDisappear;
}
void MainWindow::resetStampStatus(){
  stamp->setRotation(0);
  stamp->setPos(-400,-400);
}

void MainWindow::resetLawnmowerStatus(){
  lawnmower->setPos(-400,-400);
  lawnmowerLastX=-400;
  lawnmowerLastY=-400;
}

void MainWindow::on_zoomScale_valueChanged(int value)
{
  QMatrix matrix;
  matrix.scale(value*0.0082+0.18,value*0.0082+0.18);
  view->setMatrix(matrix);

}
