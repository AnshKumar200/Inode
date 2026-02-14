#include "Inode.h"
#include "get_dir_names.h"

#include <QLabel>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QPushButton>
#include <QWidget>

Inode::Inode() {
    window = new QWidget;
    window->setFixedSize(800, 600);
    layout_main = new QVBoxLayout(window);
    layout_dir = new QGridLayout(window);
    layout_main->setAlignment(Qt::AlignTop);

    QPushButton *back = new QPushButton("Back", window);
    back->setFixedSize(100, 40);
    layout_main->addWidget(back);
    QObject::connect(back, &QPushButton::clicked, [this]() {
        path.pop();
        refresh();
    });

    layout_main->addLayout(layout_dir);

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
            QPushButton *item = new QPushButton(
                QString::fromStdString(dir_list[i].path().filename()), window);

            layout_dir->addWidget(item, i / 10, i % 10);

            QObject::connect(item, &QPushButton::clicked, [this, i]() {
                path.push(dir_list[i].path().filename());
                refresh();
            });
        } else {
            QLabel *item = new QLabel(window);
            item->setText(QString::fromStdString(dir_list[i].path().filename()));
            layout_dir->addWidget(item, i / 10, i % 10);
        }
    }
}
