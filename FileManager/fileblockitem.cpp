#include "fileblockitem.h"

FileBlockItem::FileBlockItem(QObject *parent) : QObject(parent)
{

}
FileBlockItem::FileBlockItem(int _width, int _height, QString _fileName, int _index, QColor _color,QObject *parent):QObject(parent){
  width=_width;
  height=_height;
  fileName=_fileName;
  blockIndex=_index;
  color=_color;

}
FileBlockItem::FileBlockItem(int _width,int _height,QString _fileName,int _index,int _fileStartBlock,QColor _color,QObject* parent){
  width=_width;
  height=_height;
  fileName=_fileName;
  blockIndex=_index;
  fileStartBlock=_fileStartBlock;
  color=_color;
  bounding<<QPoint(0,0)<<QPointF(_width*0.7,0)<<QPointF(_width,_width*0.3)<<QPointF(_width,_height)<<QPointF(0,_height);
  fold<<QPointF(_width*0.7,0)<<QPointF(_width,_width*0.3)<<QPointF(_width*0.7,_width*0.3);
}

QRectF FileBlockItem::boundingRect()const{
  return QRectF(0,0,width,height);
}
void FileBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//  painter->fillRect(boundingRect(),color);
  painter->save();
  QPen linePen;
  linePen.setWidth(3);
  painter->setBrush(QBrush(color));
  painter->drawPolygon(bounding);
  int gap=15;
  for(int i=2;i<=7;++i){
      if(gap*i>height)break;
      painter->drawLine(10,gap*i,width-10,gap*i);
  }
  painter->restore();
  painter->drawText(10,57,QString("文件")+fileName);
  painter->drawText(10,43,QString("第")+QString::number(blockIndex)+QString("块of"));
  painter->drawText(10,28,QString("块号:")+QString::number(fileStartBlock+blockIndex));
  painter->setBrush(QBrush(Qt::gray));
  painter->drawPolygon(fold);

}
void FileBlockItem::showUp(){
  setVisible(true);
}
void FileBlockItem::disappear(){
  setVisible(false);
}
