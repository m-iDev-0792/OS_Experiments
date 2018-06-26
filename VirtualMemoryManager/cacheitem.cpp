#include "cacheitem.h"

CacheItem::CacheItem(QObject *parent) : QObject(parent)
{
  CacheItem(400,200);
}
CacheItem::CacheItem(QRectF _rect, QObject *parent){
  CacheItem(rect.width(),rect.height(),parent);
}
CacheItem::CacheItem(int width,int height, QObject *parent):QObject(parent){
  m_loadTime=-1;
  m_lastUsedTime=-1;
  cacheID=0;
  rect=QRect(-width/2.0,-height/2.0,width,height);
  int innerOuterGap=25;
  pinLen=6;
  chipOuterRect=QRectF(-(width-pinLen)/2.0,-(height-pinLen)/2.0,width-pinLen,height-pinLen);
  chipInnerRect=QRectF(-(width-pinLen-innerOuterGap)/2.0,-(height-pinLen-innerOuterGap)/2.0,width-pinLen-innerOuterGap,height-pinLen-innerOuterGap);
}
QRectF CacheItem::boundingRect()const{
  return rect;
}
void CacheItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  QPen boundPen(Qt::black);
  boundPen.setWidth(2);
  painter->setPen(boundPen);
  painter->fillRect(chipOuterRect,QColor(97,97,97));
  painter->fillRect(chipInnerRect,QColor(69,69,69));
  painter->drawRect(chipInnerRect);
  painter->drawRect(chipOuterRect);
  //draw edge point connect line
  painter->drawLine(chipInnerRect.bottomLeft(),chipOuterRect.bottomLeft());
  painter->drawLine(chipInnerRect.bottomRight(),chipOuterRect.bottomRight());
  painter->drawLine(chipInnerRect.topLeft(),chipOuterRect.topLeft());
  painter->drawLine(chipInnerRect.topRight(),chipOuterRect.topRight());

  //draw pins
  boundPen.setWidth(1);
  painter->setPen(boundPen);
  QBrush brush(QColor(190,190,190));
  painter->setBrush(brush);

  int horiMargin=20;
  int vertMargin=10;
  int pinWidth=15;
  QPointF tl=chipOuterRect.topLeft();
  QPointF bl=chipOuterRect.bottomLeft();
  QPointF tr=chipOuterRect.topRight();
  //handle horizonal
  int horiPinNum=6;
  float horiGap=(chipOuterRect.width()-2*horiMargin-horiPinNum*pinWidth)/(horiPinNum-1);
  horiGap+=pinWidth;
  for(int i=0;i<horiPinNum;++i){
      painter->drawRect(tl.x()+horiMargin+horiGap*i,tl.y()-pinLen,pinWidth,pinLen);
      painter->drawRect(bl.x()+horiMargin+horiGap*i,bl.y(),pinWidth,pinLen);
    }
  //handle vertical
  int vertPinNum=3;
  float vertGap=(chipOuterRect.height()-2*vertMargin-vertPinNum*pinWidth)/(vertPinNum-1);
  vertGap+=pinWidth;
  for(int i=0;i<vertPinNum;++i){
      painter->drawRect(tl.x()-pinLen,tl.y()+vertMargin+i*vertGap,pinLen,pinWidth);
      painter->drawRect(tr.x(),tr.y()+vertMargin+i*vertGap,pinLen,pinWidth);
    }
  QPen textPen(Qt::gray);
  painter->setPen(textPen);
  painter->drawText(QPointF(chipInnerRect.topLeft().x()+5,chipInnerRect.topLeft().y()+15),QString("存储器")+QString::number(cacheID));
  painter->drawText(QPointF(chipInnerRect.topLeft().x()+5,chipInnerRect.topLeft().y()+30),QString("最近访问时间:")+QString::number(m_lastUsedTime));
  painter->drawText(QPointF(chipInnerRect.topLeft().x()+5,chipInnerRect.topLeft().y()+45),QString("载入时间:")+QString::number(m_loadTime));
}
int CacheItem::loadTime()const{
  return m_loadTime;
}
int CacheItem::lastUsedTime()const{
  return m_lastUsedTime;
}
int CacheItem::ID()const{
  return cacheID;
}
void CacheItem::setLoadTime(int _loadTime){
  m_loadTime=_loadTime;
  update();
}
void CacheItem::setLastUsedTime(int _lastUsedTime){
  m_lastUsedTime=_lastUsedTime;
  update();
}
void CacheItem::setID(int id){
  cacheID=id;
}
