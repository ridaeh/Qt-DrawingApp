#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
 _createActions();
 _createMenus();
 _createToolbars();
 _connectActions();

  QGraphicsView *view = new QGraphicsView();
  _area= new SceneArea (0,0,600,800,this);
  QGraphicsTextItem * text= _area->addText("Tu peux me deplacer !");
  text->setPos(100,100);
  text->setVisible(true);
  view->setScene(_area);
  setCentralWidget(view);
  statusBar()->showMessage(tr("Ready"));
  _styleSigPenMapper=new QSignalMapper(this);
  _styleSigPenMapper->setMapping(_dotPenAction, DOTS_PEN);
  _styleSigPenMapper->setMapping(_solidePenAction, SOLIDE_PEN);

  _widthSigPenMapper=new QSignalMapper(this);
  _widthSigPenMapper->setMapping(_smallPenAction,SMALL_PEN);
  _widthSigPenMapper->setMapping(_mediumPenAction, MEDIUM_PEN);
  _widthSigPenMapper->setMapping(_largePenAction, LARGE_PEN);

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
  _signalMapper->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_elipseAct, TOOLS_ID_CIRCLE);
  _signalMapper->setMapping(_polygonAct, TOOLS_ID_POLYGON);
  _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);

  _brushStyleSigMapper = new QSignalMapper(this);
  _brushStyleSigMapper->setMapping(_noBrushAction, NO_BRUSH);
  _brushStyleSigMapper->setMapping(_solideBrushAction, SOLIDE_PATTERN);
  _brushStyleSigMapper->setMapping(_denseBrushAction, DENSE_PATTERN);

  _connectSignals();
}

void MainWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar();
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu("&Tool");
 _styleMenu=menubar->addMenu(tr("&Style"));
 _penMenu=_styleMenu->addMenu(tr("&Pen"));
 _penStyleMenu=_penMenu->addMenu(tr("&Style"));
 _penWidthMenu=_penMenu->addMenu(tr("&Width"));
 _brushMenu=_styleMenu->addMenu(tr("&Brush"));
 _brushStyleMenu=_brushMenu->addMenu(tr("&Style"));
  _helpMenu = menubar->addMenu( tr("&Help") );
}

void MainWindow::_createToolbars(void) {
  _toolBar = addToolBar( tr("File") );
}

void MainWindow::_createActions(void) {
  // Create File Action
 _newAction = new QAction( QIcon(":/Images/new.png"), tr("&New..."), this );
 _newAction->setShortcut( tr("Ctrl+N") );
 _newAction->setToolTip( tr("New Tooltip") );
 _newAction->setStatusTip( tr("New Status") );
 _newAction->setData(QVariant("New data to process"));

 _openAction = new QAction(QIcon(":/Images/open.png"),tr("&Open"), this);
 _openAction->setShortcut(tr("Ctrl+O"));
 _openAction->setToolTip( tr("Open existing Tooltip") );
 _openAction->setStatusTip( tr("Open Status") );
 _openAction->setData(QVariant("Existing data to process"));

 _saveAction = new QAction(QIcon(":/Images/save.png"),tr("Save"), this);
 _saveAction->setShortcut(tr("Ctrl+S"));
 _saveAction->setToolTip( tr("Save Tooltip") );
 _saveAction->setStatusTip( tr("Save Status") );
 _saveAction->setData(QVariant("Saving data to process"));

 _saveAsAction = new QAction(tr("Save as"), this);
 _saveAsAction->setShortcut(tr("Ctrl+D"));

 _exitAction = new QAction(tr("Exit"), this);
 _exitAction->setShortcut(tr("Ctrl+Q"));

 //Create Help Action

 _aboutAction = new QAction(tr("About"), this);
 _aboutAction->setShortcut(tr("Ctrl+A"));
 _aboutAction->setStatusTip(tr("It' a beautiful work"));
 _aboutQtAction = new QAction(tr("About Qt"), this);
 _aboutAction->setShortcut(tr("Ctrl+Q"));
 _aboutQtAction->setStatusTip(tr("Thank's a lot, you're so cute !"));

 //create tool actions
  _toolsQag = new QActionGroup( this );
  _penStyleQag=new QActionGroup( this );
  _penWidthQag=new QActionGroup( this );
  _brushStyleQag=new QActionGroup( this );

  _freehandAct = new QAction(tr("&Freehand"),  this);
  _lineAct = new QAction(tr("&Line"), this);
  _rectangleAct= new QAction(tr("&Rectangle"), this);
  _elipseAct= new QAction(tr("&Elipse"), this);
  _polygonAct= new QAction(tr("&Polygon"), this);
  _textAct= new QAction(tr("&Text"), this);

  _brushColorAction=new QAction(tr("&Color"),this);
  _noBrushAction= new QAction(tr("&No Brush"), this);
  _solideBrushAction= new QAction(tr("&Solide Brush"), this);
  _denseBrushAction= new QAction(tr("&Dense Brush"), this);

  _rectangleAct->setCheckable(true);
  _elipseAct->setCheckable(true);
  _polygonAct->setCheckable(true);
  _textAct->setCheckable(true);
  _freehandAct->setCheckable(true);
  _lineAct->setCheckable(true);
  _lineAct->setChecked(true);


  _noBrushAction->setCheckable(true);
  _noBrushAction->setChecked(true);
  _solideBrushAction->setCheckable(true);
  _denseBrushAction->setCheckable(true);
  _eraseAction=new QAction(tr("&Erase"),this);
  //----------------------------------------------------------------//

  _colorPenAction=new QAction(tr("&Color"),this);
  _smallPenAction=new QAction(tr("&Small Pen"),this);
  _mediumPenAction=new QAction(tr("&Medium Pen"),this);
  _largePenAction=new QAction(tr("&Large Pen"),this);
  _solidePenAction=new QAction(tr("&Solide Line"),this);
  _dotPenAction=new QAction(tr("&Dot Line"),this);

  _smallPenAction->setCheckable(true);
  _smallPenAction->setChecked(true);
  _mediumPenAction->setCheckable(true);
  _largePenAction->setCheckable(true);
  _solidePenAction->setCheckable(true);
  _solidePenAction->setChecked(true);
  _dotPenAction->setCheckable(true);
}

void MainWindow::_connectActions(void) {
 _fileMenu->addAction( _newAction );
 _fileMenu->addAction( _openAction );
 _fileMenu->addAction( _saveAction );
// _fileMenu->addAction( _saveAsAction );
 _fileMenu->addAction( _exitAction );
 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);

 _toolBar->addAction(_newAction);
  _toolBar->addAction(_openAction);
   _toolBar->addAction(_saveAction);


 //_toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectangleAct);
 _toolsQag->addAction(_elipseAct);
// _toolsQag->addAction(_polygonAct);
 _toolsQag->addAction(_textAct);

// _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectangleAct);
 _toolMenu->addAction(_elipseAct);
 //_toolMenu->addAction(_polygonAct);
 _toolMenu->addAction(_textAct);

 _penMenu->addAction(_colorPenAction);
 _penWidthMenu->addAction(_smallPenAction);
 _penWidthMenu->addAction(_mediumPenAction);
 _penWidthMenu->addAction(_largePenAction);

 _penStyleMenu->addAction(_solidePenAction);
  _penStyleMenu->addAction(_dotPenAction);


 _penWidthQag->addAction(_smallPenAction);
 _penWidthQag->addAction(_mediumPenAction);
 _penWidthQag->addAction(_largePenAction);

 _penStyleQag->addAction(_dotPenAction);
 _penStyleQag->addAction(_solidePenAction);

  _brushMenu->addAction(_brushColorAction);
  _brushStyleMenu->addAction(_noBrushAction);
  _brushStyleMenu->addAction(_solideBrushAction);
  _brushStyleMenu->addAction(_denseBrushAction);

 _brushStyleQag->addAction(_noBrushAction);
 _brushStyleQag->addAction(_solideBrushAction);
 _brushStyleQag->addAction(_denseBrushAction);
}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )) );
 connect( _saveAction, SIGNAL(triggered( )), this, SLOT(_saveFile( )) );
 connect( _openAction, SIGNAL(triggered( )), this, SLOT(_openFile( )) );
 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));
connect(_exitAction, SIGNAL(triggered()), this, SLOT(_exit()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectangleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_elipseAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polygonAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );

 connect(_smallPenAction,SIGNAL(triggered()),_widthSigPenMapper, SLOT(map()));
 connect(_largePenAction,SIGNAL(triggered()),_widthSigPenMapper, SLOT(map()));
 connect(_mediumPenAction,SIGNAL(triggered()),_widthSigPenMapper, SLOT(map()));

 connect(_dotPenAction,SIGNAL(triggered()),_styleSigPenMapper, SLOT(map()));
 connect(_solidePenAction,SIGNAL(triggered()),_styleSigPenMapper, SLOT(map()));

 connect(_widthSigPenMapper,SIGNAL(mapped(int)), this, SIGNAL(penStyleMapped(int)));
 connect(this, SIGNAL(penStyleMapped(int)), _area, SLOT(setCurrentPenStyle(int)) );
 connect(_widthSigPenMapper,SIGNAL(mapped(int)), this, SIGNAL(penWidthMapped(int)));
 connect(this, SIGNAL(penWidthMapped(int)), _area, SLOT(setCurrentPenWidth(int)) );

 connect(_colorPenAction, SIGNAL(triggered()), this, SLOT(_selectPenColor()));
 connect(this, SIGNAL(setPenColor(QColor)), _area, SLOT(setCurrentPenColor(QColor)));

 connect(_brushColorAction, SIGNAL(triggered()), this, SLOT(_selectBrushColor()));
 connect(this, SIGNAL(setBrushColor(QColor)), _area, SLOT(setCurrentBrushColor(QColor)));

 connect(_brushStyleSigMapper,SIGNAL(mapped(int)), this, SIGNAL(brushStyleMapped(int)));
 connect(this, SIGNAL(brushStyleMapped(int)), _area, SLOT(setCurrentBrushStyle(int)) );

 connect(_noBrushAction,SIGNAL(triggered()),_brushStyleSigMapper, SLOT(map()));
 connect(_solideBrushAction,SIGNAL(triggered()),_brushStyleSigMapper, SLOT(map()));
 connect(_denseBrushAction,SIGNAL(triggered()),_brushStyleSigMapper, SLOT(map()));

 connect(_eraseAction,SIGNAL(triggered()),_area, SLOT(eraseItem()));
}

void MainWindow::_newFile(void) {
   int ret = QMessageBox::warning(this, tr("New File"),
                                tr("The document has been modified.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel,
                                QMessageBox::Save);

 switch (ret) {
   case QMessageBox::Save:
       if(_saveFile()!=-1)
          _area->clearScene();

       break;
   case QMessageBox::Discard:{
       qDebug() << "MainWindow::newFile(void)";
       qDebug() << "Date : " << QDate::currentDate();
       QString str = _newAction->data().toString();
       qDebug() << str ;
       statusBar()->showMessage(str);

       for (int i =0; i< _area->items().size();i++) {
           qDebug() <<  "scene.items() :" <<_area->items().value(i)->type();
           qDebug() << _area->items().value(i)->x();
           qDebug() << _area->items().value(i)->pos();
           qDebug() << _area->items().value(i)->scenePos();
      //     qDebug() << _area->mapToScene(_area->items().value(i)->pos());
         }

          _area->clearScene();

       break;
       }
   case QMessageBox::Cancel:

       break;

  }

}

void MainWindow::_exit(void) {
qDebug()<< "MainWindow::_exit(void)" ;
 int ret = QMessageBox::warning(this, tr("Exit"),
                                tr("The document has been modified.\n"
                                   "Do you want to save your changes?"),
                                 QMessageBox::Cancel |QMessageBox::Save
                                | QMessageBox::Close,
                                QMessageBox::Cancel);
 switch (ret) {
   case QMessageBox::Save:
       if(_saveFile()!=-1)
         exit(0);

       break;
   case QMessageBox::Close:{
       exit(0);

       break;
       }
   case QMessageBox::Cancel:

       break;

  }

}


void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1",
                           "ENIB module CAI 2, Copyright Automne 2018 : \n HAMDANI Ridae",
                           "Go back to work !");
}

void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");

}

int MainWindow::_saveFile(){
   QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save File"),"", tr("XML Files (*.xml);;All Files (*)"));

     if (!fileName.endsWith(".xml"))
         fileName += ".xml";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
            return -1;
    }
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Scene");
    xmlWriter.writeAttribute("version", "v1.0");
    xmlWriter.writeStartElement("GraphicsItemList");
    qreal width, height, x, y;
    for (int i =_area->items().size()-1; i>=0 ;i--) {
            xmlWriter.writeStartElement("GraphicsItem");
            int number=_area->items().value(i)->type();
            xmlWriter.writeAttribute("type", QString::number(number));
            switch(number) {
              case 6 :
               {
                  qDebug() << "Line";
                  QGraphicsLineItem *line;
                  line = qgraphicsitem_cast<QGraphicsLineItem*>(_area->items().value(i));
                  x = line->line().x1();
                  y = line->line().y1();
                  width = line->line().x2();
                  height = line->line().y2();
                  xmlWriter.writeAttribute("x", QString::number(x));
                  xmlWriter.writeAttribute("y", QString::number(y));
                  xmlWriter.writeAttribute("w", QString::number(width));
                  xmlWriter.writeAttribute("h", QString::number(height));
                  xmlWriter.writeAttribute("pStyle", QString::number(line->pen().style()));
                  xmlWriter.writeAttribute("pWidth", QString::number(line->pen().width()));
                  xmlWriter.writeAttribute("pColor", line->pen().color().name());

                }
                 break;
              case 3 :
                  {
                  qDebug() << "Rectangle";
                  QGraphicsRectItem *rect;
                  rect = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
                  x = rect->rect().x();
                  y = rect->rect().y();
                  width = rect->rect().width();
                  height = rect->rect().height();
                  xmlWriter.writeAttribute("x", QString::number(x));
                  xmlWriter.writeAttribute("y", QString::number(y));
                  xmlWriter.writeAttribute("w", QString::number(width));
                  xmlWriter.writeAttribute("h", QString::number(height));
                  xmlWriter.writeAttribute("pStyle", QString::number(rect->pen().style()));
                  xmlWriter.writeAttribute("pWidth", QString::number(rect->pen().widthF()));
                  xmlWriter.writeAttribute("pColor", rect->pen().color().name());
                  xmlWriter.writeAttribute("bColor", rect->brush().color().name());
                  xmlWriter.writeAttribute("bStyle", QString::number(rect->brush().style()));
                }
                 break;
              case 8:{
                qDebug() << "Text";
                QGraphicsTextItem *text;
                text = qgraphicsitem_cast<QGraphicsTextItem*>(_area->items().value(i));
                x = text->x();
                y = text->y();
                QString txt=text->toPlainText();
                xmlWriter.writeAttribute("x", QString::number(x));
                xmlWriter.writeAttribute("y", QString::number(y));
                xmlWriter.writeAttribute("txt", txt);


              }
              break;
              case 4:{
                qDebug() << "Ellipse";
                QGraphicsEllipseItem *ellipse;
                ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(_area->items().value(i));
                x = ellipse->rect().x();
                y = ellipse->rect().y();
                width = ellipse->rect().width();
                height = ellipse->rect().height();
                xmlWriter.writeAttribute("x", QString::number(x));
                xmlWriter.writeAttribute("y", QString::number(y));
                xmlWriter.writeAttribute("w", QString::number(width));
                xmlWriter.writeAttribute("h", QString::number(height));
                xmlWriter.writeAttribute("pStyle", QString::number(ellipse->pen().style()));
                  xmlWriter.writeAttribute("pWidth", QString::number(ellipse->pen().widthF()));
                  xmlWriter.writeAttribute("pColor", ellipse->pen().color().name());
                  xmlWriter.writeAttribute("bColor", ellipse->brush().color().name());
                  xmlWriter.writeAttribute("bStyle", QString::number(ellipse->brush().style()));

              }
              break;
      }
            xmlWriter.writeEndElement(); // GraphicsItem
    }
   xmlWriter.writeEndElement(); // GraphicsItemList
   xmlWriter.writeEndElement(); // Scene
   file.close();
   return 1;
}

int MainWindow::_openFile(void){
    QString fileReadName = QFileDialog::getOpenFileName(this,
    tr("Open File"),"", tr("XML Files (*.xml);;All Files (*)"));

    QFile fileRead(fileReadName);
    if (!fileRead.open(QIODevice::ReadOnly))
    {
            return -1;
    }
    _area->clearScene();
   QXmlStreamReader xmlReader;
   xmlReader.setDevice(&fileRead);
   while (!xmlReader.atEnd()) {
     if(xmlReader.isStartElement()) {
       if ( xmlReader.name()== "GraphicsItem") {
           qDebug() << "graphics";


             int x=xmlReader.attributes().value("x").toString().toInt();
             int y=xmlReader.attributes().value("y").toString().toInt();
             int w=xmlReader.attributes().value("w").toString().toInt();
             int h=xmlReader.attributes().value("h").toString().toInt();
             int pstyle=xmlReader.attributes().value("pStyle").toString().toInt();
             int pWidth=xmlReader.attributes().value("pWidth").toString().toInt();
             QString pColor=xmlReader.attributes().value("pColor").toString();
             int bStyle=xmlReader.attributes().value("bStyle").toString().toInt();
             QString bColor=xmlReader.attributes().value("bColor").toString();


             switch (xmlReader.attributes().value("type").toString().toInt()) {
                 case 6:{
                     QPen pen=QPen();
                     if (pstyle == 1) {
                       pen.setStyle(Qt::SolidLine);
                     }else pen.setStyle(Qt::DotLine);
                     pen.setWidth(pWidth);

                     pen.setColor(QColor(pColor));
                     _area->addLine(x,y,w,h,pen);
                    }
                    break;
                  case 3:
                  {
                     QPen pen=QPen();
                     if (pstyle == 1) {
                       pen.setStyle(Qt::SolidLine);
                     }else pen.setStyle(Qt::DotLine);
                     pen.setWidth(pWidth);
                     QBrush brush=QBrush();
                     pen.setColor(QColor(pColor));
                     brush.setColor(QColor(bColor));
                     if (bStyle == 1) {
                       brush.setStyle(Qt::SolidPattern);
                     }else if (bStyle == 4)
                       brush.setStyle(Qt::Dense3Pattern);
                      else
                        brush.setStyle(Qt::NoBrush);
                      _area->addRect(x,y,w,h,pen,brush);

                  }
                  break;
                  case 8:{
                    QGraphicsTextItem * text= _area->addText(xmlReader.attributes().value("txt").toString());
                    text->setPos(x,y);
                    text->setVisible(true);
                  }break;
                  case 4:{
                      QPen pen=QPen();
                     if (pstyle == 1) {
                       pen.setStyle(Qt::SolidLine);
                     }else pen.setStyle(Qt::DotLine);
                     pen.setWidth(pWidth);
                     QBrush brush=QBrush();
                     pen.setColor(QColor(pColor));
                     brush.setColor(QColor(bColor));
                     if (bStyle == 1) {
                       brush.setStyle(Qt::SolidPattern);
                     }else if (bStyle == 4)
                       brush.setStyle(Qt::Dense3Pattern);
                      else
                        brush.setStyle(Qt::NoBrush);
                     _area->addEllipse(x,y,w,h,pen,brush);

                  }break;
             }


           }
       }
     _area->update();
      xmlReader.readNext();
  }
  fileRead.close();
  return 0;
}
void MainWindow::_selectPenColor(){
  emit setPenColor(QColorDialog::getColor());
}
void MainWindow::_selectBrushColor(){
  emit setBrushColor(QColorDialog::getColor());
}
void MainWindow::_showContextMenu()
{
    QMenu menu(this);
    menu.addMenu(_toolMenu);
    menu.addMenu(_styleMenu);
    menu.addSeparator();
    menu.addAction(_eraseAction);
    menu.exec(QCursor::pos());
}
