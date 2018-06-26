#include "diskview.h"

DiskView::DiskView(QWidget *parent) : QWidget(parent)
{
  colorList.push_back(QColor(0 ,250 ,154));
  colorList.push_back(QColor(30 ,144 ,255));
  colorList.push_back(QColor(0 ,255 ,255));
  colorList.push_back(QColor(255 ,99 ,71));
  colorList.push_back(QColor(255 ,0 ,255));
  colorList.push_back(QColor(155 ,48 ,255));
  mode=0;

}
void DiskView::paintEvent(QPaintEvent *e){
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

  horiGap=width()/20.0;//change to 20
  vertGap=height()/25.0;//change to 25
  //18.5 17.64
  int colorIndex=0;
  for(auto &f:fileList){
      if(f.startBlock<0)continue;
      int x=horiGap*(f.startBlock%20);//change to 20
      int y=vertGap*(f.startBlock/20);//change to 20
      int w=((float)f.size/blocksize)*horiGap;
      p.fillRect(x,y,w,vertGap,colorList[colorIndex%colorList.size()]);
      w=w+x-width();
      while(w>0){
          y+=vertGap;
          p.fillRect(0,y,w,vertGap,colorList[colorIndex%colorList.size()]);
          w-=width();
        }
      ++colorIndex;
    }
  QPen dotline(Qt::gray);
  dotline.setStyle(Qt::DotLine);
  p.setPen(dotline);

  for(int i=1;i<20;++i){//change to 20
      p.drawLine(horiGap*i,0,horiGap*i,height());
    }
  for(int i=1;i<25;++i){//change to 25
      p.drawLine(0,vertGap*i,width(),vertGap*i);
    }
  QPen solidline(Qt::black);
  solidline.setWidth(2);
  p.setPen(solidline);
  p.drawLine(0,0,width(),0);
  p.drawLine(0,height(),width(),height());
  p.drawLine(0,0,0,height());
  p.drawLine(width(),0,width(),height());
  if(mode==1){
      QPen solidline2(Qt::black);
      solidline2.setWidth(1);
      p.setPen(solidline2);
      p.setRenderHint(QPainter::Antialiasing, true);
      if(head==nullptr){
          qDebug()<<"head is null"<<endl;
          return;
        }
      QPoint points[2];
      int index=0;
      listNode const* temp;
      temp=head;
      while(temp!=nullptr){
          int x,y;
          if(!index){//tail point
              x=horiGap*((temp->startBlock+temp->blockNum-1)%20)+horiGap/2;
              y=vertGap*((temp->startBlock+temp->blockNum-1)/20)+vertGap/2;
            }else{//head point
              x=horiGap*(temp->startBlock%20)+horiGap/2;
              y=vertGap*(temp->startBlock/20)+vertGap/2;

            }

          points[index].setX(x);
          points[index].setY(y);
          ++index;
          if(index>1){
              index=0;
              p.drawLine(points[0],points[1]);
              p.drawEllipse(points[0],2,2);
              p.drawEllipse(points[1],2,2);
              continue;
            }
          temp=temp->next;
        }
    }
}
void DiskView::getFileList(vector<file> &newFileList){
  fileList=newFileList;
  repaint();
}
void DiskView::drawConnectLine(QPainter& painter){

}
