#ifndef MYPICITEM_H
#define MYPICITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
class MyPicItem : public QObject,public QGraphicsPixmapItem
{
  Q_OBJECT
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  explicit MyPicItem(QObject *parent = nullptr);
  MyPicItem(const QPixmap &pic,QObject* parent=0);
signals:

public slots:
};

#endif // MYPICITEM_H
