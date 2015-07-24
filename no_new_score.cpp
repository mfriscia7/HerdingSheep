#include "no_new_score.h"

// constructor
no_new_score::no_new_score(QWidget *parent) : QWidget(parent){

    //resizes main window
    setFixedSize(400,200);

    //Takes away close, minimize, etc. buttons
    setWindowFlags(Qt::CustomizeWindowHint);

    //makes the main layout
    QVBoxLayout *layout = new QVBoxLayout;
    //layout->setAlignment(Qt::AlignCenter);

    //header
    QLabel *header = new QLabel("Game Over...");
    header->setAlignment(Qt::AlignCenter);

    //header font
    QFont header_font("Courier", 36);
    header->setFont(header_font);

    //Enter button to return to home screen
    QPushButton *p = new QPushButton("Go Back");
    setnobutton(p);

    layout->addWidget(header);
    layout->addWidget(p);
    setLayout(layout);
}

/** @function setnobutton
 * @brief sets the member variable to a button so that it can be called by the gameboard
 */
void no_new_score::setnobutton(QPushButton* p){
    button = p;
}

/** @function play_button
 * @brief returns play button so that main can access it
 */
QPushButton* no_new_score::no_button(){
    return button;
}
