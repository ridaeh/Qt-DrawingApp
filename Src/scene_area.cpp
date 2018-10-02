#include "scene_area.h"

SceneArea::SceneArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "Scene::Scene(void)";

  _startPoint = _endPoint = _offset = QPointF(0,0);
_currentTool=TOOLS_ID_LINE;
  addRect(QRectF(150,150,200,400));
  pen=QPen();
/*
  _polygon << QPointF(10, 10) << QPointF(100, 10) <<  QPointF(100, 100) << QPointF(10, 100);
  addPolygon(_polygon);
*/
  _item=NULL;
  connect(this,SIGNAL(showContextMenu()),parent,SLOT(_showContextMenu()));
}

void SceneArea::mousePressEvent(QGraphicsSceneMouseEvent* evt) {
  qDebug() << "Scene::mousePressEvent(void)";
  qDebug() <<  "evt->pos() : " << evt->pos();
  qDebug() <<  "evt->scenePos() : " <<  evt->scenePos();
  if(evt->button()==Qt::RightButton){
    emit showContextMenu();
    return;
  }
 for (int i =0; i<items().size();i++) {
    items().value(i)->show();
    qDebug() << "item number : " << i;
    qDebug() << "items().value(i)->scenePos() : " << items().value(i)->scenePos();
    qDebug() << "items().value(i)->pos()  : " << items().value(i)->mapToScene(items().value(i)->pos());
  }

  _startPoint = _endPoint = evt->scenePos();
  _item=itemAt(_startPoint);
  if (_item) {
    QList<QGraphicsItem *>   items = collidingItems(_item);
    for (int i =0; i< items.size();i++) {
    qDebug() << "colliding item number : " << i;
     items.value(i)->hide();
    }
    _offset =  _startPoint - _item->pos();
//    _item->setPos(_startPoint - _offset );
//    _item->setPos( _item->pos());
    _item->grabMouse();
  }

}

void SceneArea::mouseMoveEvent(QGraphicsSceneMouseEvent* evt)
{
//  qDebug() << "Scene::mouseMoveEvent(void)";
  if (_item) {
     _item->setPos(evt->scenePos() - _offset);
  }
  _endPoint = evt->scenePos();
}

void SceneArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* evt)
{
  qDebug() << "Scene::mouseReleaseEvent(void)";
  if (_item) {
    _item->setPos(evt->scenePos() - _offset);
    _item->ungrabMouse();
    _item=NULL;
  }
  else if (_startPoint != _endPoint) {
//    addLine( _startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y() );
    switch (_currentTool) {
      case TOOLS_ID_RECTANGLE :{
        QGraphicsRectItem *rect = addRect(_startPoint.x(), _startPoint.y(),
         _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y(),pen);
        rect->setFlag(QGraphicsItem::ItemIsMovable);
        break;
      }
      case TOOLS_ID_LINE :{
        QGraphicsLineItem *line = addLine( _startPoint.x(), _startPoint.y(),
         _endPoint.x(), _endPoint.y(),pen);
        line->setFlag(QGraphicsItem::ItemIsMovable);
         qDebug() << "Line";

         break;
         }
      case TOOLS_ID_CIRCLE:{

        QGraphicsEllipseItem *  elipse=addEllipse (_startPoint.x(), _startPoint.y(),
         _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y(),pen);
        elipse->setFlag(QGraphicsItem::ItemIsMovable);
         qDebug() << "Elipse";
         break;
      }

    };
    update();

 }
 _endPoint = evt->scenePos();
  qDebug() << items().size();
}

void SceneArea::setCurrentTool(int tool) {
  qDebug() << "Scene::setCurrentTool(int tool)";
  _currentTool = tool;
  qDebug () << _currentTool;
}
void SceneArea::setCurrentPenStyle(int style) {
  qDebug() << "Scene::setCurrentPenStyle(int style)";
  qDebug () << style;
  switch(style){
    case DOTS_PEN : pen.setStyle(Qt::SolidLine); break;
    case SOLIDE_PEN :pen.setStyle(Qt::DotLine); break;
  };

}
void SceneArea::setCurrentPenWidth(int width) {
  qDebug() << "Scene::setCurrentPenWidth(int width)";
  qDebug () << width;
  switch(width){
    case SMALL_PEN : pen.setWidth(1); break;
    case MEDIUM_PEN : pen.setWidth(5); break;
    case LARGE_PEN : pen.setWidth(10); break;
  };
}
void SceneArea::setCurrentPenColor(QColor color) {
  qDebug() << "Scene::setCurrentPenColor(QColor color)";
  pen.setColor(color);
}
void SceneArea::clearScene(){
  qDebug()<< "Clear";
  for (QGraphicsItem * item : items() ){
    removeItem(item);

  }

}
