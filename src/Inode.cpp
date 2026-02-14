#include "Inode.h"
#include "get_dir_names.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>
#include <QWidget>
#include <qicon.h>
#include <qnamespace.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qwidget.h>

Inode::Inode() {
    window = new QWidget;
    window->setFixedSize(1100, 600);
    layout_main = new QVBoxLayout(window);
    layout_main->setAlignment(Qt::AlignTop);

    QPushButton *back = new QPushButton("Back", window);
    back->setFixedSize(100, 40);
    layout_main->addWidget(back);
    QObject::connect(back, &QPushButton::clicked, [this]() {
        path.pop();
        refresh();
    });

    scroll_dir = new QScrollArea;
    scroll_dir_wid = new QWidget;

    scroll_dir->setWidget(scroll_dir_wid);
    scroll_dir->setWidgetResizable(true);
    scroll_dir->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout_dir = new QGridLayout(scroll_dir_wid);
    layout_dir->setAlignment(Qt::AlignTop);
    layout_main->addWidget(scroll_dir);

    path.push("/home");

    refresh();
}

void Inode::show() {
    window->setLayout(layout_main);
    window->setWindowTitle("Inode");
    window->show();
}

void Inode::refresh() {
    QLayoutItem *child;
    while ((child = layout_dir->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    dir_list = get_names(path);

    for (int i = 0; i < dir_list.size(); i++) {
        if (dir_list[i].is_directory()) {
            QPushButton *dir_item = new QPushButton(scroll_dir_wid);
            dir_item->setIcon(QIcon("../icons/dir.png"));
            dir_item->setIconSize(QSize(32, 32));
            dir_item->setText(
                QString::fromStdString(dir_list[i].path().filename()));
            dir_item->setFixedSize(100, 40);

            layout_dir->addWidget(dir_item, i / 10, i % 10);

            QObject::connect(dir_item, &QPushButton::clicked, [this, i]() {
                path.push(dir_list[i].path().filename());
                refresh();
            });
        } else {
            QLabel *item = new QLabel(window);
            item->setText(
                QString::fromStdString(dir_list[i].path().filename()));
            item->setFixedSize(100, 40);
            layout_dir->addWidget(item, i / 10, i % 10);
        }
    }
}
