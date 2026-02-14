#include <QBoxLayout>
#include <QGridLayout>
#include <filesystem>
#include <QScrollArea>
#include <QWidget>
#include <qwidget.h>
#include <stack>
#include <vector>

class Inode {
  public:
    Inode();
    void show();

  private:
    void refresh();

    QWidget *window;
    QVBoxLayout *layout_main;
    QGridLayout *layout_dir;

    QScrollArea *scroll_dir;
    QWidget *scroll_dir_wid;

    std::stack<std::string> path;
    std::vector<std::filesystem::directory_entry> dir_list;
};
