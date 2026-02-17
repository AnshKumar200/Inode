#include <QBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QWidget>
#include <filesystem>
#include <qabstractitemmodel.h>
#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qscrollarea.h>
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
    void updatePreview(const QModelIndex &index);

    std::unordered_map<std::string, QIcon> extension_icons;
    QIcon dir_icon;
    QIcon default_icon;
    void loadIcons();

    QWidget *window;
    QVBoxLayout *layout_main;
    QHBoxLayout *layout_content;
    QListView *list_view;
    QStandardItemModel *model;
    QLabel *preview_label;
    QScrollArea *preview_scroll;

    std::string current_path;
    std::vector<std::filesystem::directory_entry> cached_entries;
};
