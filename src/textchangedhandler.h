#ifndef TEXTCHANGEDHANDLER_H
#define TEXTCHANGEDHANDLER_H

#include "board.h"
#include "mainwindow.h"
#include "qtextedit.h"
#include <vector>

using namespace std;

class TextChangedHandler : public QObject
{
    Q_OBJECT

private:
    //variables
    QTextEdit *edit;
    vector<vector<int>> &board_numbers;
    int l, c;
    Board &solution;
    MainWindow* main_window;

    //functions
    bool verif(vector<vector<int>> board_numbers);
    bool complete();

public:
    TextChangedHandler(QTextEdit* edit, vector<vector<int>> &board_numbers,int l, int c,
                       Board &solution, MainWindow* main_window);
    //methods
    static void alignCenter(QTextEdit* edit);

public slots:
    void textEditChanged();
};

#endif // TEXTCHANGEDHANDLER_H
