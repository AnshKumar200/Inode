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
#include <unordered_map>
#include <vector>

class Inode {
  public:
    Inode();
    void show();

  private:
    void refresh();

    std::unordered_map<std::string, QIcon> extension_icons;
    QIcon dir_icon;
    QIcon default_icon;
    void loadIcons();

    QWidget *window;
    QVBoxLayout *layout_main;
    QListView *list_view;
    QStandardItemModel *model;

    std::string current_path;
    std::vector<std::filesystem::directory_entry> cached_entries;
};
