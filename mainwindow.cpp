#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <qtshadowcache/qtshadowcache.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // layout()->setContentsMargins(0, 0, 0, 0);
    qDebug() << layout()->contentsMargins();

    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    qDebug() << ui->centralwidget->layout()->contentsMargins();

    {
        QSDC::Request request;
        request.parent = nullptr;
        request.blur_radius = 9;
        request.shadow_color = QColor(140, 140, 140);
        request.background_color = Qt::white;

        const QSDC::Result &result = QSDC::Qtshadowcache::create(request);
        result.pixmap.save(result.save2);
        qDebug() << result.pixmap << result.cached << result.save2;

        ui->widget_2->setStyleSheet(QString(R"(
QWidget#widget_2{
    border-left-width: 0px;
    border-right-width: 0px;
    border-top-width: 0px;
    border-bottom-width: %2px;
    border-style: solid;
    border-image: url(%1) %2 %2 %2 %2 stretch stretch;
}
)")
                                        .arg(result.save2, QString::number(result.margin)
                                             // .arg(save2, QString::number(qMax(result.margin, static_cast<quint16>(result.radius * 2)))
                                             // QString::number(qMax(static_cast<quint16>(9), qMax(result.margin, static_cast<quint16>(result.radius * 2))))
                                             ));
        qDebug() << ui->widget_2->styleSheet();
        auto cm = ui->widget_2->layout()->contentsMargins();
        cm.setBottom(result.margin);
        ui->widget_2->layout()->setContentsMargins(cm);


        ui->pushButton->setStyleSheet(R"(
QPushButton {
    background-color: transparent;
    color: palette(button-text);
    padding: 4px 16px;
    margin: 2px;
    border: none;
    border-radius: 0px;
}
QPushButton:hover {
    background-color: palette(button);
}
QPushButton:pressed {
    background-color: palette(midlight);
}
QPushButton:disabled {
    background-color: transparent;
    color: palette(button-text-x);
}
)");

        // ui->pushButton->setEnabled(false);
        // ui->pushButton_2->setEnabled(false);
        // ui->toolButton->setEnabled(false);

    }
}

MainWindow::~MainWindow() {
    delete ui;
}
