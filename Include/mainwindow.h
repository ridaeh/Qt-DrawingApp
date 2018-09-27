#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QMessageBox>
#include <QDate>
#include <QSignalMapper>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDir>
#include "enums.h"
#include "scene_area.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
  public:
   MainWindow(QWidget *parent = 0);
  private:
   SceneArea* _area; 
   void _createMenus(void);
   void _createToolbars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);
   int _saveFile(void);
   int _openFile(void);

   QMenu *_fileMenu, *_toolMenu, *_editMenu, *_helpMenu,*_styleMenu;
   QToolBar *_toolBar;
   QAction *_newAction, *_exitAction , *_saveAction,*_saveAsAction,*_openAction;
   QAction *_aboutAction, *_aboutQtAction;
   QAction *_freehandAct, *_lineAct,*_rectangleAct,*_elipseAct,*_polygonAct,*_textAct;

   QActionGroup *_toolsQag;
   QSignalMapper *_signalMapper;
  private slots :
     void _newFile();
     void _exit();
     void _about();
     void _aboutQt();
  signals:
   void toolMapped(int digit);
};
#endif
