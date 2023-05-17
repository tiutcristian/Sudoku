#include "help.h"
#include "ui_help.h"
#include <QVBoxLayout>

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(ui->rulesTitle);
    layout->addWidget(ui->rules);
    layout->addWidget(ui->useTitle);
    layout->addWidget(ui->use);
    ui->scrollWidget->setLayout(layout);
}

Help::~Help()
{
    delete ui;
}
