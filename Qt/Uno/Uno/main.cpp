#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>


#include"myrect.h"

int main(int argc, char *argv[])
{
      QApplication a(argc,argv);

      //creando escena
      QGraphicsScene * scene=new QGraphicsScene();

      //Creando un elemento para escena
      MyRect * rect = new MyRect();
      rect->setRect(0,0,100,100);

     //AÃ±adiendo elemento llamado rect
     scene->addItem(rect);

     //mostrando rect
     rect->setFlag(QGraphicsItem::ItemIsFocusable);
     rect->setFocus();

      //AÃ±adiendo vista
      QGraphicsView * view= new QGraphicsView(scene);
      view->show();

      return a.exec();
}
