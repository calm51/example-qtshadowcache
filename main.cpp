#include "mainwindow.h"

#include <QApplication>
#include <QDir>

#include <qtshadowcache/qtshadowcache.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 四角圆角不同, 或许可以只创建非圆角阴影,然后通过gridlayout把阴影和内容widget重叠,阴影需要挖去四角.
    auto result = QSDC::Qtshadowcache::create(nullptr, 0, 13, QColor(140, 140, 140), Qt::white);
    QString save2 = QDir::current().absoluteFilePath("shadowcache.png");
    result.pixmap.save(save2);
    qDebug() << result.pixmap << result.width << result.margin;

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
                        .arg(save2, QString::number(qMax(result.margin, static_cast<quint16>(result.radius * 2)))
                             // QString::number(qMax(static_cast<quint16>(9), qMax(result.margin, static_cast<quint16>(result.radius * 2))))
                             ));
    qDebug() << w.styleSheet();

    w.show();


    return a.exec();
}
