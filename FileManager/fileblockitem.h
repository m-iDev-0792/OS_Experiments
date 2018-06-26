#ifndef FILEBLOCKITEM_H
#define FILEBLOCKITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
class FileBlockItem : public QObject,public QGraphicsItem
{
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  Q_PROPERTY(qreal scale READ scale WRITE setScale)
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
public:
  explicit FileBlockItem(QObject *parent = nullptr);
  FileBlockItem(int _width,int _height,QString _fileName,int _index,QColor _color,QObject* parent=0);
  FileBlockItem(int _width,int _height,QString _fileName,int _index,int _fileStartBlock,QColor _color,QObject* parent=0);
  QRectF boundingRect()const;
  void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
signals:

public slots:
  void showUp();
  void disappear();
private:
  QString fileName;
  int blockIndex;
  int width;
  int height;
  int fileStartBlock;
  QPolygonF bounding;
  QPolygonF fold;
  QColor color;
};

#endif // FILEBLOCKITEM_H
