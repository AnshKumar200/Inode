#include "Inode.h"
#include "get_dir_names.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>
#include <QWidget>
#include <filesystem>
#include <qabstractitemmodel.h>
#include <qicon.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstandarditemmodel.h>
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

    list_view = new QListView;
    list_view->setViewMode(QListView::IconMode);
    list_view->setGridSize(QSize(100, 60));
    list_view->setIconSize(QSize(32, 32));
    list_view->setWrapping(true);
    list_view->setResizeMode(QListView::Adjust);
    list_view->setSpacing(10);
    list_view->setUniformItemSizes(true);
    //    list_view->setFlowDirection(QListView::LeftToRight);

    model = new QStandardItemModel;
    list_view->setModel(model);
    layout_main->addWidget(list_view);

    refresh();
}

void Inode::loadIcons() { dir_icon = QIcon("../icons/dir.png"); }

void Inode::show() {
    window->setLayout(layout_main);
    window->setWindowTitle("Inode");
    window->show();
}

void Inode::refresh() {
    model->clear();

    cached_entries.clear();
    cached_entries = get_names(current_path);

    for (const auto &entry : cached_entries) {
        QString file_name =
            QString::fromStdString(entry.path().filename().string());
        QStandardItem *item = new QStandardItem(file_name);

        if (entry.is_directory()) {
            item->setIcon(dir_icon);
            item->setData(QString::fromStdString(entry.path().string()),
                          Qt::UserRole);
        } else {
            item->setIcon(dir_icon);
        }
        item->setTextAlignment(Qt::AlignCenter);
        model->appendRow(item);
    }
    QObject::disconnect(list_view, nullptr, nullptr, nullptr);
    QObject::connect(
        list_view, &QListView::doubleClicked, [this](const QModelIndex &index) {
            QString path =
                model->item(index.row())->data(Qt::UserRole).toString();
            if (!path.isEmpty()) {
                current_path = path.toStdString();
                refresh();
            }
        });
}
