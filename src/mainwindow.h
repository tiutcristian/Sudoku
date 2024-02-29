#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "qtextedit.h"
#include <QMainWindow>
#include "board.h"
#include "ui_mainwindow.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //variables
    Ui::MainWindow *ui;
    vector<vector<QTextEdit *>> board_inputs;
    vector<vector<int>> board_numbers;
    Board solution;
    int mistakes = 0;
    bool menuButtonSelected = 0;
    bool generateButtonSelected = 0;

    //methods
    void update_ui_board(Board &board);
    void update_mistakes_label(){ ui->mistakesLabel->setText(("Mistakes: " + to_string(mistakes) + "/3").c_str()); }
    void expand_tools_menu();
    void shrink_tools_menu();
    void expand_generate_menu();
    void shrink_generate_menu();
    void connect_components();

    //style methods
    void solved_style();
    void disabled_style();
    void initial_style();
    void board_style();
    void tools_menu_style();
    void generate_menu_style();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //methods
    void increase_mistakes();
    void is_complete();

public slots:
    //tools menu slots
    void toolsMenuPressed();
    void openPressed();
    void savePressed();
    void resetPressed();
    void quitPressed();

    //generate menu slots
    void generatePressed();
    void easyPressed();
    void mediumPressed();
    void hardPressed();
    void extremePressed();
private slots:
    void on_helpButton_clicked();
};
#endif // MAINWINDOW_H
