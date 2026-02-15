#include <QBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QWidget>
#include <filesystem>
#include <qicon.h>
#include <qwidget.h>
#include <string>
#include <vector>

class Inode {
  public:
    Inode();
    void show();

  private:
    void refresh();
    void loadIcons();

    QWidget *window;
    QVBoxLayout *layout_main;
    QListView *list_view;
    QStandardItemModel *model;

    QIcon dir_icon;

    std::string current_path;
    std::vector<std::filesystem::directory_entry> cached_entries;
};
