#include "mypicitem.h"


MyPicItem::MyPicItem(QObject *parent) : QObject(parent){
}
MyPicItem::MyPicItem(const QPixmap &pic,QObject* parent):QObject(parent),QGraphicsPixmapItem(pic){
}
