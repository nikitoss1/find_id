#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <set>
#include <QString>

using namespace std;



bool search_word_in_keywords(const string &str);

QString convert_in_QString(std::string &str);

vector<QString> search_id(const string &str);

vector<string> vector_append(vector<string> arr1, vector<string> arr2);

set<QString> create_set(vector<QString> code);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void on_execute_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
