#include "mainwindow.h"

#include <QApplication>
#include <QDir>

#include <qtshadowcache/qtshadowcache.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSDC::Request request;
    request.parent = nullptr;
    request.blur_radius = 13;
    request.shadow_color = QColor(140, 140, 140);
    request.background_color = Qt::white;

    const QSDC::Result &result = QSDC::Qtshadowcache::create(request);
    const QString &save2 = QDir::current().absoluteFilePath(result.name);
    result.pixmap.save(save2);
    qDebug() << result.pixmap << result.cached << result.name;


    // result.margin /= 2;
    // result.radius /= 2;

    MainWindow w;
    // w.setStyleSheet("*{background-color: rgb(255,255,255);}"); // border: 1px solid rgb(0,0,255);


    w.setWindowFlag(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground);

    w.setStyleSheet(QString(R"(
QWidget#widget{
    border-width: %2px;
    border-style: solid;
    border-image: url(%1) %2 %2 %2 %2 stretch stretch;
}
)")
                        .arg(save2, QString::number(result.margin)
                             // .arg(save2, QString::number(qMax(result.margin, static_cast<quint16>(result.radius * 2)))
                             // QString::number(qMax(static_cast<quint16>(9), qMax(result.margin, static_cast<quint16>(result.radius * 2))))
                             ));
    qDebug() << w.styleSheet();

    w.show();


    return a.exec();
}
