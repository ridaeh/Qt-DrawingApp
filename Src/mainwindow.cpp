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

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
  _signalMapper->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_elipseAct, TOOLS_ID_CIRCLE);
  _signalMapper->setMapping(_polygonAct, TOOLS_ID_POLYGON);
  _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);
  _connectSignals();
}

void MainWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar();
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu("&Tool");
 _styleMenu=menubar->addMenu(tr("&Style"));
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

 _openAction = new QAction(tr("Open"), this);
 _openAction->setShortcut(tr("Ctrl+O"));

 _saveAction = new QAction(tr("Save"), this);
 _saveAction->setShortcut(tr("Ctrl+S"));

 _saveAsAction = new QAction(tr("Save as"), this);
 _saveAsAction->setShortcut(tr("Ctrl+D"));

 _exitAction = new QAction(tr("exit"), this);
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
  _freehandAct = new QAction(tr("&Freehand"),  this);
  _lineAct = new QAction(tr("&Line"), this);
  _rectangleAct= new QAction(tr("&Rectangle"), this);
  _elipseAct= new QAction(tr("&Elipse"), this);
  _polygonAct= new QAction(tr("&Polygon"), this);
  _textAct= new QAction(tr("&Line"), this);

  _rectangleAct->setCheckable(true);
  _elipseAct->setCheckable(true);
  _polygonAct->setCheckable(true);
  _textAct->setCheckable(true);
  _freehandAct->setCheckable(true);
  _lineAct->setCheckable(true);
}

void MainWindow::_connectActions(void) {
 _fileMenu->addAction( _newAction );
 _fileMenu->addAction( _openAction );
 _fileMenu->addAction( _saveAction );
 _fileMenu->addAction( _saveAsAction );
 _fileMenu->addAction( _exitAction );
 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);

 _toolBar->addAction(_newAction);


 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectangleAct);
 _toolsQag->addAction(_elipseAct);
 _toolsQag->addAction(_polygonAct);
 _toolsQag->addAction(_textAct);

 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectangleAct);
 _toolMenu->addAction(_elipseAct);
 _toolMenu->addAction(_polygonAct);
 _toolMenu->addAction(_textAct);
}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )) );
 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));
 
 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectangleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_elipseAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polygonAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );
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
    QString fileName(QDir::currentPath().append("//scene.xml"));
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
    for (int i =0; i< _area->items().size();i++) { 
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
                  xmlWriter.writeAttribute("xd", QString::number(x));
                  xmlWriter.writeAttribute("yd", QString::number(y));
                  xmlWriter.writeAttribute("xf", QString::number(width));
                  xmlWriter.writeAttribute("yf", QString::number(height));
                  xmlWriter.writeAttribute("style", QString::number(line->pen().style()));
                }
                 break;
              case 3 :
                  {
                  qDebug() << "Line";
                  QGraphicsRectItem *rect;
                  rect = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
                  x = rect->rect().x();
                  y = rect->rect().y();
                  width = rect->rect().width();
                  height = rect->rect().height();
                  xmlWriter.writeAttribute("xd", QString::number(x));
                  xmlWriter.writeAttribute("yd", QString::number(y));
                  xmlWriter.writeAttribute("xf", QString::number(width));
                  xmlWriter.writeAttribute("yf", QString::number(height));
                  xmlWriter.writeAttribute("style", QString::number(rect->pen().style()));
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
    QString fileReadName(QDir::currentPath().append("//scene.xml"));
    QFile fileRead(fileReadName);
    if (!fileRead.open(QIODevice::ReadOnly))
    {
            return -1;
    }
   
   QXmlStreamReader xmlReader;
   QFile fileread("scene-read.xml");
   qDebug() << "read";
   if (!fileread.open(QFile::ReadOnly | QFile::Text)) { 
     qDebug() << "Error: Cannot read file ";
   }
   xmlReader.setDevice(&fileread);
   while (!xmlReader.atEnd()) {
     if(xmlReader.isStartElement()) {
       if ( xmlReader.name()== "GraphicsItem") {  
     qDebug() << "graphics";
     qDebug() << xmlReader.attributes().value("type").toString().toInt();
     if (xmlReader.attributes().value("type").toString().toInt() == 6 ) {
       int x=xmlReader.attributes().value("x").toString().toInt();
       int y=xmlReader.attributes().value("y").toString().toInt();
       int w=xmlReader.attributes().value("w").toString().toInt();
       int h=xmlReader.attributes().value("h").toString().toInt();
       int style=xmlReader.attributes().value("style").toString().toInt();
       qDebug() << "read" << x << y<< w << h << style;
       QGraphicsLineItem *ligne = _area->addLine(x,y,w,h);
       if (style == 0) {
         ligne->pen().setStyle(Qt::DashDotDotLine);
       }

     }
       }
     }
      xmlReader.readNext();
  }
  return 0;
}
