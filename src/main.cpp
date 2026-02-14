#include "Inode.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Inode inode;
    inode.show();

    return app.exec();
}
