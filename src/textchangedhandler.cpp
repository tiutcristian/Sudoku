#include "textchangedhandler.h"
#include "board.h"
#include <iostream>

TextChangedHandler::TextChangedHandler(QTextEdit* edit, vector<vector<int>> &board_numbers, int l, int c,
                                       Board &solution, MainWindow* main_window) :
    edit(edit),
    board_numbers(board_numbers),
    l(l),
    c(c),
    solution(solution),
    main_window(main_window)
{}

// ------------------------------- private functions -------------------------------

bool TextChangedHandler::verif(vector<vector<int>> board_numbers)
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board_numbers[l][c] && board_numbers[l][c] != solution.get(l, c))
                return false;
    return true;
}

bool TextChangedHandler::complete()
{
    Board board;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board.set(i, j, board_numbers[i][j]);
    return board.is_complete();
}

// ------------------------------- public methods -------------------------------

void TextChangedHandler::alignCenter(QTextEdit* edit)
{
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignHCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    cursor.movePosition(QTextCursor::End);
    edit->setTextCursor(cursor);
}

// ------------------------------- public slots -------------------------------

void TextChangedHandler::textEditChanged()
{
    auto str = edit->toPlainText().toStdString();

    if (str.length() == 0)
    {
        if(board_numbers[l][c] == 0)
            return;
        board_numbers[l][c] = 0;
    }
    else if (str.length() == 1 && std::isdigit(str[0]) && str[0] != '0')
    {
        if(board_numbers[l][c] == str[0] - '0')
            return;
        board_numbers[l][c] = str[0] - '0';
    }
    else if (str.length() == 2
        && std::isdigit(str[0])
        && std::isdigit(str[1])
        && str[0] != '0'
        && str[1] != '0')
    {
        if (str[0] - '0' != board_numbers[l][c])    //daca s-a adaugat la stanga
            board_numbers[l][c] = str[0]-'0';
        else                                        //daca s-a adaugat la dreapta
            board_numbers[l][c] = str[1]-'0';
        edit->setText(QString((char)(board_numbers[l][c] + '0')));
    }
    else
    {
        if (board_numbers[l][c] == 0)
            edit->setText("");
        else
            edit->setText(QString((char)(board_numbers[l][c] + '0')));
    }
    alignCenter(edit);

    if(board_numbers[l][c] != 0)
    {
        if(verif(board_numbers))
            edit->setStyleSheet("color: #6B92D7;"
                                "background-color: #212433;"
                                "border: no border");
        else
        {
            edit->setStyleSheet("color: #DA5858;"
                                "background-color: #212433;"
                                "border: no border;");
            main_window->increase_mistakes();
        }
    }
    else
        edit->setStyleSheet("background-color: #212433;"
                            "border: no border;");
    if(complete())
        main_window->is_complete();
}
