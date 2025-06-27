#include "widget.h"
#include "ui_widget.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QList>
#include <QUrl>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

Widget::~Widget() {
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        // qDebug() << "event url is " << event->mimeData()->urls()[0];
        // 事件接收文件拖拽接收的动作
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Widget::dropEvent(QDropEvent *event) {
    const QMimeData* mimeData = event->mimeData();
    // 判断是否包含url
    if (mimeData->hasUrls()) {
        QList<QUrl> listUrl = mimeData->urls();
        QString strFileName = listUrl[0].toLocalFile();
        if (!strFileName.isEmpty()) {
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            QFile file(strFileName);
            if (!file.open(QIODevice::ReadOnly)) {
                return;
            }
            QTextCodec::setCodecForLocale(codec);
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
    } else {
        event->ignore();
    }
}

