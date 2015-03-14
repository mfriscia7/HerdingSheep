#include "quitwidget.h"
#include <QHBoxLayout>
#include <QCoreApplication>

// constructor
QuitWidget::QuitWidget(QWidget *parent) :
    QWidget(parent)
{
    //sets labels and text
    this->setWindowTitle("Quit");
    quit_label = new QLabel("Are you sure?");
    quit_label->setAlignment(Qt::AlignCenter);
    quit_cancel = new QPushButton("Cancel");
    quit_ok = new QPushButton("Ok");

    //sets layout
    QHBoxLayout* quit_hlayout = new QHBoxLayout;
    quit_hlayout->addWidget(quit_cancel);
    quit_hlayout->addWidget(quit_ok);

    //sets whole window layout
    QVBoxLayout* quit_vlayout = new QVBoxLayout;
    quit_vlayout->addWidget(quit_label);
    quit_vlayout->addLayout(quit_hlayout);

    this->setLayout(quit_vlayout);

    //connects the pushbuttons to slots
    QObject::connect(quit_cancel, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(quit_ok, SIGNAL(clicked()), qApp, SLOT(quit()));

}

//destructor
QuitWidget::~QuitWidget()
{ }
