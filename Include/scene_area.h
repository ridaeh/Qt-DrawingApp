#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEffect>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>
#include <QPolygonF>
#include "enums.h"

class SceneArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
   SceneArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
   void clearScene();
//   PaintArea(QWidget *parent = 0);
  public slots:
    void setCurrentTool(int);

  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent* );
    void mouseMoveEvent(QGraphicsSceneMouseEvent* );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* );
  private :
   int _currentTool;
   QPointF  _startPoint,_endPoint, _offset;
   QGraphicsItem * _item;
   QPolygon _polygon;
};
#endif

