#include "scene_area.h"

SceneArea::SceneArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "Scene::Scene(void)";

  _startPoint = _endPoint = _offset = QPointF(0,0);
_currentTool=TOOLS_ID_LINE;
  addRect(QRectF(150,150,200,400));
  pen=QPen();
  brush=QBrush();
   pen.setWidth(1);
  text="";
/*
  _polygon << QPointF(10, 10) << QPointF(100, 10) <<  QPointF(100, 100) << QPointF(10, 100);
  addPolygon(_polygon);
*/
  _item=NULL;
  _itemToDelete=NULL;
  connect(this,SIGNAL(showContextMenu()),parent,SLOT(_showContextMenu()));
  _createItem=false;
  _isCreationFinished=true;
}

void SceneArea::mousePressEvent(QGraphicsSceneMouseEvent* evt) {

  qDebug() << "Scene::mousePressEvent(void)";
  qDebug() <<  "evt->pos() : " << evt->pos();
  qDebug() <<  "evt->scenePos() : " <<  evt->scenePos();
  if(evt->button()==Qt::RightButton){
    _createItem=false;
   	_isCreationFinished=true;
    _itemToDelete=itemAt(evt->scenePos());
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
  else{	_createItem=true;_isCreationFinished=true;
    if(_currentTool==TOOLS_ID_TEXT){
     text="Entre your text";
     QGraphicsTextItem * textItem= addText(text);
     textItem->setPos(_startPoint.x(), _startPoint.y());
     textItem->setVisible(true);
     textItem->setFlag(QGraphicsItem::ItemIsMovable);
     text="";
     qDebug() << "Text";
     _createItem=false;
      _isCreationFinished=false;
    }
}




}

void SceneArea::mouseMoveEvent(QGraphicsSceneMouseEvent* evt)
{
 // qDebug() << "Scene::mouseMoveEvent(void)";
  if (_item) {

     _item->setPos(evt->scenePos() - _offset);
  }
  _endPoint = evt->scenePos();
  if(_createItem){
			  if (_startPoint != _endPoint) {
		//    addLine( _startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y() );
			switch (_currentTool) {
			  case TOOLS_ID_RECTANGLE :{

				QGraphicsRectItem *rect = addRect(_startPoint.x(), _startPoint.y(),
				 _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y(),pen,brush);
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
				 _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y(),pen,brush);
				elipse->setFlag(QGraphicsItem::ItemIsMovable);
				 qDebug() << "Elipse";
				 break;
			  }



			};
			_createItem=false;
			_isCreationFinished=false;
			update();
		 }
 }
 else if(!_isCreationFinished){
	 switch (_currentTool) {
			  case TOOLS_ID_RECTANGLE :{

				QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(items().value(0));
        rect->setRect(_startPoint.x(), _startPoint.y(),
				 _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());

				break;
			  }
			  case TOOLS_ID_LINE :{
					QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(items().value(0));
          line->setLine( _startPoint.x(), _startPoint.y(),
				 _endPoint.x(), _endPoint.y());
				 break;
				 }
			  case TOOLS_ID_CIRCLE:{

				QGraphicsEllipseItem *  elipse=qgraphicsitem_cast<QGraphicsEllipseItem*>(items().value(0));
        elipse->setRect (_startPoint.x(), _startPoint.y(),
				 _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());


				 break;
			  }


			};
			update();
	 }

}

void SceneArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* evt)
{
  qDebug() << "Scene::mouseReleaseEvent(void)";
  if (_item) {
    _item->setPos(evt->scenePos() - _offset);
    _item->ungrabMouse();
    _item=NULL;
  }
  if(_currentTool!=TOOLS_ID_TEXT){
   _createItem=false;
	 _isCreationFinished=true;
  }


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
void SceneArea::setCurrentBrushColor(QColor color) {
  qDebug() << "Scene::setCurrentBrushColor(QColor color)";
  brush.setColor(color);
}

void SceneArea::setCurrentBrushStyle(int style) {
  qDebug() << "Scene::setCurrentPenStyle(int style)";
  qDebug () << style;
  switch(style){
    case NO_BRUSH : brush.setStyle(Qt::NoBrush); break;
    case SOLIDE_PATTERN :brush.setStyle(Qt::SolidPattern); break;
    case DENSE_PATTERN :brush.setStyle(Qt::Dense3Pattern); break;
  };

}

void SceneArea::clearScene(){
  qDebug()<< "Clear";
  for (QGraphicsItem * item : items() ){
    removeItem(item);

  }
}
void SceneArea::keyPressEvent(QKeyEvent* event){

  if(!_isCreationFinished && _currentTool== TOOLS_ID_TEXT){
    qDebug()<<"KeyPressed";

    if(event->key()==Qt::Key_Enter|| event->key()==Qt::Key_Return ){
       _createItem=false;
  	   _isCreationFinished=true;
      return;
    }
    text = text + event->text();
    qDebug()<< "Text :" <<text;
    if(event->key()==Qt::Key_Backspace){
      qDebug()<< "delet " ;
      text.remove(text.length()-2,text.length()-1);
    }

    QGraphicsTextItem *txt = qgraphicsitem_cast<QGraphicsTextItem*>(items().value(0));
    txt->setPlainText(text);
    update();
  }

}
void SceneArea::eraseItem(){
  if(_itemToDelete){
    removeItem(_itemToDelete);
    qDebug()<<"de";
    _itemToDelete=NULL;
    update();
  }
}
