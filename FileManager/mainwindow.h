#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diskview.h"
#include <cmath>
#include <random>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPixmap>
#include <map>
#include "fileblockitem.h"
#include "mypicitem.h"
namespace Ui {
  class MainWindow;
}

struct freetableNode{
  int startBlock;
  int blockNum;
  freetableNode(int start,int num):startBlock(start),blockNum(num){}
  bool operator <(const freetableNode& fn)const{
    return blockNum<fn.blockNum;
  }
};
enum ModeType{
  FreeTable,
  FreeLinkList,
  BitMap
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void updateView();
  //-----------------空闲表法------------------
  file createFileUsingFreetable(QString filename,float filesize);
  void delFileUsingFreetable(QString delFilename);
  //------------------------------------------

  //-----------------位示图法------------------
  file createFileUsingBitMap(QString filename,float filesize);
  void delFileUsingBitMap(QString delFilename);
  //------------------------------------------

  //-----------------空闲链表法------------------
  file createFileUsingFreelinklist(QString filename,float filesize);
  void delFileUsingFreelinklist(QString delFilename);
  //------------------------------------------


private:
  Ui::MainWindow *ui;
  vector<file> fileList;
  void drawMeshBackground();
  const int blocksize=2;
  vector<QColor> colorList;
  int colorIndex=0;

  //following are important elements,use them carefully!
  //---------空闲表---------------
  vector<freetableNode> freetable;
  //-----------------------------

  //---------位示图---------------
  bool bitMap[500];
  //-----------------------------

  //---------空闲链表法-----------
  listNode* head;
  //----------------------------

  int mode;

  bool isRunBtnNowReset;
  QGraphicsView* view;
  QGraphicsScene* scene;
  MyPicItem* lawnmower;
  MyPicItem* stamp;
  map<QString,vector<FileBlockItem*>> fileBlocksMap;
  void addFileBlockItem(QString filename,int startBlock,int blockNum,float size);
  QSequentialAnimationGroup* createFileShowUpAnimation(QString filename);
  QSequentialAnimationGroup* createFileDisappearAnimation(QString filename);
  void resetAll();
  float lawnmowerLastX;
  float lawnmowerLastY;
  const int randomFileNum=50;

signals:
  void sendNewFileList(vector<file> &filelist);
private slots:
  void on_run_clicked();
  void on_del_clicked();
  void on_addMore_clicked();
  void on_freetable_clicked();
  void on_freelinklist_clicked();
  void on_bitmap_clicked();
  void resetStampStatus();
  void resetLawnmowerStatus();

  void on_zoomScale_valueChanged(int value);

protected:
  virtual void paintEvent(QPaintEvent* e);
};

#endif // MAINWINDOW_H
