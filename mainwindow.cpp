#include "mainwindow.h"
#include "qtextedit.h"
#include "textchangedhandler.h"
#include "ui_mainwindow.h"
#include "generator.h"
#include "solver.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <QFont>
#include <QMessageBox>
#include <QFileDialog>
#include <QPropertyAnimation>
#include "help.h"


// --------------------------------------- private methods ---------------------------------------

void MainWindow::update_ui_board(Board &board)
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            board_numbers[i][j] = board.get(i, j);
            std::string str = board_numbers[i][j] == 0 ? "" : std::to_string(board_numbers[i][j]);
            board_inputs[i][j]->setText(str.c_str());
            TextChangedHandler::alignCenter(board_inputs[i][j]);
        }
}

void MainWindow::expand_tools_menu()
{
    auto anim1 = new QPropertyAnimation(ui->openButton, "geometry");
    anim1->setDuration(300);
    anim1->setStartValue(ui->openButton->geometry());

    auto anim2 = new QPropertyAnimation(ui->saveButton, "geometry");
    anim2->setDuration(300);
    anim2->setStartValue(ui->saveButton->geometry());

    auto anim3 = new QPropertyAnimation(ui->resetButton, "geometry");
    anim3->setDuration(300);
    anim3->setStartValue(ui->resetButton->geometry());

    auto anim4 = new QPropertyAnimation(ui->quitButton, "geometry");
    anim4->setDuration(300);
    anim4->setStartValue(ui->quitButton->geometry());

    auto anim5 = new QPropertyAnimation(ui->helpButton, "geometry");
    anim5->setDuration(300);
    anim5->setStartValue(ui->helpButton->geometry());

    menuButtonSelected = 1;
    anim1->setEndValue(QRect(70, 10, 50, 50));
    anim2->setEndValue(QRect(125, 10, 50, 50));
    anim3->setEndValue(QRect(180, 10, 50, 50));
    anim4->setEndValue(QRect(235, 10, 50, 50));
    anim5->setEndValue(QRect(290, 10, 50, 50));

    anim1->start();
    anim2->start();
    anim3->start();
    anim4->start();
    anim5->start();
}

void MainWindow::shrink_tools_menu()
{
    auto anim1 = new QPropertyAnimation(ui->openButton, "geometry");
    anim1->setDuration(300);
    anim1->setStartValue(ui->openButton->geometry());

    auto anim2 = new QPropertyAnimation(ui->saveButton, "geometry");
    anim2->setDuration(300);
    anim2->setStartValue(ui->saveButton->geometry());

    auto anim3 = new QPropertyAnimation(ui->resetButton, "geometry");
    anim3->setDuration(300);
    anim3->setStartValue(ui->resetButton->geometry());

    auto anim4 = new QPropertyAnimation(ui->quitButton, "geometry");
    anim4->setDuration(300);
    anim4->setStartValue(ui->quitButton->geometry());

    auto anim5 = new QPropertyAnimation(ui->helpButton, "geometry");
    anim5->setDuration(300);
    anim5->setStartValue(ui->helpButton->geometry());

    menuButtonSelected = 0;
    anim1->setEndValue(QRect(15, 10, 50, 50));
    anim2->setEndValue(QRect(15, 10, 50, 50));
    anim3->setEndValue(QRect(15, 10, 50, 50));
    anim4->setEndValue(QRect(15, 10, 50, 50));
    anim5->setEndValue(QRect(15, 10, 50, 50));

    anim1->start();
    anim2->start();
    anim3->start();
    anim4->start();
    anim5->start();
}

void MainWindow::expand_generate_menu()
{
    auto anim1 = new QPropertyAnimation(ui->easyButton, "geometry");
    anim1->setDuration(300);
    anim1->setStartValue(ui->easyButton->geometry());

    auto anim2 = new QPropertyAnimation(ui->mediumButton, "geometry");
    anim2->setDuration(300);
    anim2->setStartValue(ui->mediumButton->geometry());

    auto anim3 = new QPropertyAnimation(ui->hardButton, "geometry");
    anim3->setDuration(300);
    anim3->setStartValue(ui->hardButton->geometry());

    auto anim4 = new QPropertyAnimation(ui->extremeButton, "geometry");
    anim4->setDuration(300);
    anim4->setStartValue(ui->extremeButton->geometry());

    generateButtonSelected = 1;
    anim1->setEndValue(QRect(130, 560, 80, 50));
    anim2->setEndValue(QRect(215, 560, 90, 50));
    anim3->setEndValue(QRect(310, 560, 80, 50));
    anim4->setEndValue(QRect(395, 560, 90, 50));

    anim1->start();
    anim2->start();
    anim3->start();
    anim4->start();
}

void MainWindow::shrink_generate_menu()
{
    auto anim1 = new QPropertyAnimation(ui->easyButton, "geometry");
    anim1->setDuration(300);
    anim1->setStartValue(ui->easyButton->geometry());

    auto anim2 = new QPropertyAnimation(ui->mediumButton, "geometry");
    anim2->setDuration(300);
    anim2->setStartValue(ui->mediumButton->geometry());

    auto anim3 = new QPropertyAnimation(ui->hardButton, "geometry");
    anim3->setDuration(300);
    anim3->setStartValue(ui->hardButton->geometry());

    auto anim4 = new QPropertyAnimation(ui->extremeButton, "geometry");
    anim4->setDuration(300);
    anim4->setStartValue(ui->extremeButton->geometry());

    generateButtonSelected = 0;
    anim1->setEndValue(QRect(15, 560, 80, 50));
    anim2->setEndValue(QRect(15, 560, 90, 50));
    anim3->setEndValue(QRect(15, 560, 80, 50));
    anim4->setEndValue(QRect(15, 560, 90, 50));

    anim1->start();
    anim2->start();
    anim3->start();
    anim4->start();
}

void MainWindow::connect_components()
{
    for(int l = 0; l < 9; l++)
        for(int c = 0; c < 9; c++)
        {
            TextChangedHandler *handler = new TextChangedHandler(board_inputs[l][c], board_numbers, l, c,
                                                                 solution, this);
            connect(board_inputs[l][c], SIGNAL(textChanged()), handler, SLOT(textEditChanged()));
        }

    connect(ui->toolsMenuButton, SIGNAL( pressed() ), this, SLOT(toolsMenuPressed()));
    connect(ui->openButton, SIGNAL( pressed() ), this, SLOT(openPressed()));
    connect(ui->saveButton, SIGNAL ( pressed() ), this, SLOT(savePressed()));
    connect(ui->resetButton, SIGNAL( pressed() ), this, SLOT(resetPressed()));
    connect(ui->quitButton, SIGNAL ( pressed() ), this, SLOT(quitPressed()));

    connect(ui->generateButton, SIGNAL( pressed() ), this, SLOT(generatePressed()));
    connect(ui->easyButton, SIGNAL( pressed() ), this, SLOT(easyPressed()));
    connect(ui->mediumButton, SIGNAL ( pressed() ), this, SLOT(mediumPressed()));
    connect(ui->hardButton, SIGNAL( pressed() ), this, SLOT(hardPressed()));
    connect(ui->extremeButton, SIGNAL ( pressed() ), this, SLOT(extremePressed()));
}


// ----------------------------------- private style methods -----------------------------------

void MainWindow::solved_style()
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            board_inputs[i][j]->setStyleSheet("border: no border;"
                                              "background-color: #212433;"
                                              "color: #ACADB1;");
            board_inputs[i][j]->setReadOnly(true);
            board_inputs[i][j]->setDisabled(true);
        }
}

void MainWindow::disabled_style()
{

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            board_inputs[i][j]->setReadOnly(true);
            board_inputs[i][j]->setDisabled(true);
            board_inputs[i][j]->setStyleSheet("background-color: #202332;"
                                              "border: no border;");
        }
}

void MainWindow::initial_style()
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board_numbers[i][j] == 0)
            {
                board_inputs[i][j]->setStyleSheet("background-color: #202332;"
                                                  "border: no border;");
                board_inputs[i][j]->setReadOnly(false);
                board_inputs[i][j]->setDisabled(false);
            }
            else
            {
                board_inputs[i][j]->setStyleSheet("color: #ADADAF;"
                                                  "background-color: #202332;"
                                                  "border: no border;");
                board_inputs[i][j]->setReadOnly(true);
                board_inputs[i][j]->setDisabled(true);
            }
}

void MainWindow::board_style()
{
    ui->boardWidget->setStyleSheet("background-color: #000000;"); //darkgray
    board_inputs.resize(9, vector<QTextEdit *>(9));
    board_numbers.resize(9, vector<int> (9, 0));

    ui->board->setSpacing(5);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            auto grid = new QGridLayout(this);
            ui->board->addLayout(grid, i, j);
            grid->setSpacing(2);
            for(int k = 0; k < 3; k++)
            {
                for(int l = 0; l < 3; l++)
                {
                    auto edit = new QTextEdit();
                    grid->addWidget(edit, k, l);
                    edit->setAlignment(Qt::AlignHCenter);
                    edit->setFont(QFont("Segoe UI", 23));
                    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    board_inputs[i*3+k][j*3+l] = edit;
                }
            }
        }
    }
}

void MainWindow::tools_menu_style()
{
    auto cursor = new QCursor;
    cursor->setShape(Qt::PointingHandCursor);

    ui->toolsMenuButton->setCursor(*cursor);
    ui->openButton->setCursor(*cursor);
    ui->saveButton->setCursor(*cursor);
    ui->resetButton->setCursor(*cursor);
    ui->quitButton->setCursor(*cursor);
    ui->helpButton->setCursor(*cursor);

    ui->toolsMenuButton->setIcon(QIcon(":/icons/menuicon.png"));
    ui->openButton->setIcon(QIcon(":/icons/openicon.png"));
    ui->saveButton->setIcon(QIcon(":/icons/saveicon.png"));
    ui->resetButton->setIcon(QIcon(":/icons/reseticon.png"));
    ui->quitButton->setIcon(QIcon(":/icons/quiticon.png"));
}

void MainWindow::generate_menu_style()
{
    auto cursor = new QCursor;
    cursor->setShape(Qt::PointingHandCursor);
    ui->generateButton->setCursor(*cursor);
    ui->easyButton->setCursor(*cursor);
    ui->mediumButton->setCursor(*cursor);
    ui->hardButton->setCursor(*cursor);
    ui->extremeButton->setCursor(*cursor);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board_style();
    disabled_style();
    tools_menu_style();
    generate_menu_style();
    ui->mistakesLabel->setText("Mistakes: /3");
    connect_components(); 
}

MainWindow::~MainWindow()
{
    delete ui;
}


// --------------------------------------- public methods ---------------------------------------

void MainWindow::increase_mistakes()
{
    mistakes++;
    update_mistakes_label();
    if(mistakes >= 3)
    {
        resetPressed();
        QMessageBox box(QMessageBox::Icon::Critical, "TOO MANY MISTAKES", "You have made too many mistakes! Game over", QMessageBox::Ok, this);
        box.exec();
    }
}

void MainWindow::is_complete()
{
    QMessageBox box(QMessageBox::Icon::Information, "CONGRATS", "Congratulations! You have completed the board. Do you want to clear the board?", QMessageBox::Yes | QMessageBox::No, this);
    if(box.exec() == QMessageBox::Yes)
        resetPressed();
}


// --------------------------------------- SLOTS ---------------------------------------


// ------------------------------------ tools menu -------------------------------------

void MainWindow::toolsMenuPressed()
{
    shrink_generate_menu();
    if(!menuButtonSelected)
        expand_tools_menu();
    else
        shrink_tools_menu();
}

void MainWindow::openPressed()
{
    shrink_tools_menu();
    QFileDialog dialog(this, "Open file", QDir::homePath());
    if(dialog.exec())
    {
        auto files = dialog.selectedFiles();
        if(files.count() != 1)
            return;
        std::ifstream fin(files[0].toUtf8());

        Board board;
        bool ok = true;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
            {
                int nr;
                fin >> nr;
                if(board.is_posib(i, j, nr))
                    board.set(i, j, nr);
                else
                    ok = false;
            }
        if(ok)
        {
            Board copy;
            copy = board;
            auto result = solve(copy);
            if(result == solver_result::IMPOSIBIL)
            {
                QMessageBox box(QMessageBox::Icon::Critical, "IMPOSSIBILE", "The board has no solution", QMessageBox::Close, this);
                box.exec();
            }
            else if(result == solver_result::NEDETERMINAT)
            {
                QMessageBox box(QMessageBox::Icon::Critical, "OPEN FAILED", "The board has no unique solution", QMessageBox::Close, this);
                box.exec();
            }
            else
            {
                solution = copy;
                update_ui_board(board);
                initial_style();
                mistakes = 0;
                update_mistakes_label();
            }
        }
        else
        {
            QMessageBox box(QMessageBox::Icon::Critical, "IMPOSSIBILE", "The board has no solution", QMessageBox::Close, this);
            box.exec();
        }

        fin.close();
    }
}

void MainWindow::savePressed()
{
    shrink_tools_menu();
    QFileDialog dialog(this, tr("Save file"), QDir::homePath(), tr("Text files(*.txt)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix(".txt");

    if(dialog.exec())
    {
        auto files = dialog.selectedFiles();
        string path = files[0].toStdString();
        std::ofstream fout(path);

        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                fout << board_numbers[i][j] << " ";
            fout << "\n";
        }

        fout.close();
    }
}

void MainWindow::resetPressed()
{
    shrink_tools_menu();
    Board board;
    update_ui_board(board);
    disabled_style();
    mistakes = 0;
    ui->mistakesLabel->setText("Mistakes: /3");
}

void MainWindow::quitPressed()
{
    QApplication::exit(0);
}


// ---------------------------------- generate menu -----------------------------------

void MainWindow::generatePressed()
{
    shrink_tools_menu();
    if(!generateButtonSelected)
        expand_generate_menu();
    else
        shrink_generate_menu();
}

void MainWindow::easyPressed()
{
    shrink_generate_menu();
    Board board;
    board = generate(35);
    solution = board;
    solve(solution);
    update_ui_board(board);
    initial_style();
    mistakes = 0;
    update_mistakes_label();
}

void MainWindow::mediumPressed()
{
    shrink_generate_menu();
    Board board;
    board = generate(30);
    solution = board;
    solve(solution);
    update_ui_board(board);
    initial_style();
    mistakes = 0;
    update_mistakes_label();
}

void MainWindow::hardPressed()
{
    shrink_generate_menu();
    Board board;
    board = generate(25);
    solution = board;
    solve(solution);
    update_ui_board(board);
    initial_style();
    mistakes = 0;
    update_mistakes_label();
}

void MainWindow::extremePressed()
{
    shrink_generate_menu();
    Board board;
    board = generate_extreme();
    solution = board;
    solve(solution);
    update_ui_board(board);
    initial_style();
    mistakes = 0;
    update_mistakes_label();
}

void MainWindow::on_helpButton_clicked()
{
    shrink_tools_menu();
    Help help;
    help.setModal(true);
    help.exec();
}
