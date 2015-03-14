#include "pausewindow.h"

// constructor
PauseWindow::PauseWindow(QWidget *parent) : QWidget(parent){

    setFixedSize(350,150);

    //Takes away close, minimize, etc. buttons
    setWindowFlags(Qt::CustomizeWindowHint);

    QVBoxLayout *v = new QVBoxLayout;

    QLabel *paused = new QLabel("Game Paused");

    QFont font("Courier", 36);
    paused->setFont(font);
    paused->setAlignment(Qt::AlignCenter);

    QPushButton *go_back = new QPushButton("Resume");
    setunpausebutton(go_back);

    v->addWidget(paused);
    v->addWidget(go_back);
    setLayout(v);
}

/* @function setunpausebutton
 * @brief sets the member variable to a pause button so that it can be called by the gameboard
 */
void PauseWindow::setunpausebutton(QPushButton* p){
    button = p;
}

/* @function unpause_button
 * @brief links the QPushButton to tghe member variable
 */
QPushButton* PauseWindow::unpause_button(){
    return button;
}
