#include <filesystem>
#include <QBoxLayout>
#include <QGridLayout>
#include <QWidget>
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

    std::stack<std::string> path;
    std::vector<std::filesystem::directory_entry> dir_list;
};
