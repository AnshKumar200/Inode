#include <QBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include <filesystem>
#include <qicon.h>
#include <qwidget.h>
#include <stack>
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
    QGridLayout *layout_dir;

    QScrollArea *scroll_dir;
    QWidget *scroll_dir_wid;

    QIcon dir_icon;

    std::string current_path;
    std::vector<std::filesystem::directory_entry> cached_entries;
};
