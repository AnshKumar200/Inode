#include "Inode.h"
#include "get_dir_names.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>
#include <QWidget>
#include <filesystem>
#include <qicon.h>
#include <qnamespace.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qwidget.h>

Inode::Inode() {
    current_path = "/home";
    loadIcons();

    window = new QWidget;
    window->setFixedSize(1100, 600);
    layout_main = new QVBoxLayout(window);
    layout_main->setAlignment(Qt::AlignTop);

    QPushButton *back = new QPushButton("Back", window);
    back->setFixedSize(100, 40);
    layout_main->addWidget(back);
    QObject::connect(back, &QPushButton::clicked, [this]() {
        std::filesystem::path current(current_path);
        std::filesystem::path parent = current.parent_path();

        if (parent != current) {
            current_path = parent.string();
            refresh();
        }
    });

    scroll_dir = new QScrollArea;
    scroll_dir_wid = new QWidget;

    scroll_dir->setWidget(scroll_dir_wid);
    scroll_dir->setWidgetResizable(true);
    scroll_dir->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout_dir = new QGridLayout(scroll_dir_wid);
    layout_dir->setAlignment(Qt::AlignTop);
    layout_main->addWidget(scroll_dir);

    refresh();
}

void Inode::loadIcons() {
    dir_icon = QIcon("../icons/dir.png");
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

    cached_entries.clear();
    cached_entries = get_names(current_path);

    for (int i = 0; i < cached_entries.size(); i++) {
        const auto &entry = cached_entries[i];
        const std::string file_name = entry.path().filename().string();

        if (entry.is_directory()) {
            QPushButton *dir_item = new QPushButton(
                QString::fromStdString(file_name), scroll_dir_wid);
            dir_item->setIcon(dir_icon);
            dir_item->setIconSize(QSize(32, 32));
            dir_item->setFixedSize(100, 40);
            layout_dir->addWidget(dir_item, i / 10, i % 10);

            QObject::connect(dir_item, &QPushButton::clicked,
                             [this, path = entry.path().string()]() {
                                 current_path = path;
                                 refresh();
                             });
        } else {
            QLabel *item =
                new QLabel(QString::fromStdString(file_name), scroll_dir_wid);
            item->setFixedSize(100, 40);
            layout_dir->addWidget(item, i / 10, i % 10);
        }
    }
}
