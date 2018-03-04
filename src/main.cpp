#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QSplashScreen>
#include <QSound>

#include "circletower.h"
#include "squaretower.h"
#include "triangletower.h"
#include "gun.h"
#include "circlebomb.h"
#include "trianglebomb.h"
#include "squarebomb.h"
#include "myview.h"

int main(int argc, char ** argv) {

    QApplication app(argc, argv);

    QSound * sound = new QSound(":/sound/sound/backsound1.wav");
    sound->play();
    sound->setLoops(-1);

    MyView view;
    QPixmap pix(":/pic/back/init.jpg");
    QSplashScreen splash(pix);

    splash.resize(pix.size());
    splash.show();
    splash.finish(&view);
    app.processEvents();

    view.show();

    return app.exec();
}
