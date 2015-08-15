#include "level_complete.h"


// constructor
level_complete::level_complete(QWidget *parent) : QWidget(parent){

    // sets a fixed size
    setFixedSize(300,150);

    // takes away close, minimize, etc. buttons
    setWindowFlags(Qt::CustomizeWindowHint);

    // makes the main layout
    QVBoxLayout *layout = new QVBoxLayout;

    // creates label for the window text
    QLabel *text = new QLabel("Level Complete!");
    text->setAlignment(Qt::AlignCenter);

    // sets font for text
    QFont font = text->font();
    font.setPointSize(24);
    text->setFont(font);

    // enter button to go to next level
    QPushButton *confirm = new QPushButton("Next Level");
    setconfirmbutton(confirm);

    // puts everything together
    layout->addWidget(text);
    layout->addWidget(confirm);
    setLayout(layout);
}

/** @function setconfirmbutton
 * @brief sets the member variable to a confirm button so that it can be called by the gameboard
 */
void level_complete::setconfirmbutton(QPushButton* p){
    confirm = p;
}

/** @function play_button
 * @brief returns play button so that main can access it
 */
QPushButton* level_complete::confirm_button(){
    return confirm;
}
