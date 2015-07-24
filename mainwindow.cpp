#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), lowest_score(0)
{
    //creates main window
    QWidget *w = new QWidget;
    w->resize(500,550);

    //makes the main layout
    QVBoxLayout *layout = new QVBoxLayout;
    //layout->setAlignment(Qt::AlignCenter);

    //header
    QLabel *header = new QLabel("Herding Sheep");
    header->setAlignment(Qt::AlignCenter);

    //header font
    QFont header_font("Courier", 36);
    header->setFont(header_font);

    //High score title
    QLabel *scores_title = new QLabel("High Scores");
    scores_title->setAlignment(Qt::AlignCenter);
    QFont scores_font("Courier", 32);
    scores_font.setUnderline(true);
    scores_title->setFont(scores_font);

    //High Scores
    //names
    QFile file(":/high_scores/high_scores.txt");
    QTextStream in(&file);
    file.open(QFile::ReadOnly | QFile::Text);
    first_name = new QLabel(in.readLine());
    first_score = new QLabel(in.readLine());
    second_name = new QLabel(in.readLine());
    second_score = new QLabel(in.readLine());
    third_name = new QLabel(in.readLine());
    third_score = new QLabel(in.readLine());
    fourth_name = new QLabel(in.readLine());
    fourth_score = new QLabel(in.readLine());
    fifth_name = new QLabel(in.readLine());
    fifth_score = new QLabel(in.readLine());

    file.close();

    //tells gameboard what the lowest score is
    lowest_score = fifth_score->text().toInt();

    QFont hscores_font("Courier",18);
    first_name->setFont(hscores_font);
    second_name->setFont(hscores_font);
    third_name->setFont(hscores_font);
    fourth_name->setFont(hscores_font);
    fifth_name->setFont(hscores_font);
    first_score->setFont(hscores_font);
    second_score->setFont(hscores_font);
    third_score->setFont(hscores_font);
    fourth_score->setFont(hscores_font);
    fifth_score->setFont(hscores_font);

    first_name->setAlignment(Qt::AlignCenter);
    second_name->setAlignment(Qt::AlignCenter);
    third_name->setAlignment(Qt::AlignCenter);
    fourth_name->setAlignment(Qt::AlignCenter);
    fifth_name->setAlignment(Qt::AlignCenter);
    first_score->setAlignment(Qt::AlignCenter);
    second_score->setAlignment(Qt::AlignCenter);
    third_score->setAlignment(Qt::AlignCenter);
    fourth_score->setAlignment(Qt::AlignCenter);
    fifth_score->setAlignment(Qt::AlignCenter);

    QHBoxLayout *horiz_scores = new QHBoxLayout;
    QVBoxLayout *names_layout = new QVBoxLayout;
    QVBoxLayout *scores_layout = new QVBoxLayout;
    horiz_scores->addLayout(names_layout);
    horiz_scores->addLayout(scores_layout);
    names_layout->addWidget(first_name);
    names_layout->addWidget(second_name);
    names_layout->addWidget(third_name);
    names_layout->addWidget(fourth_name);
    names_layout->addWidget(fifth_name);
    scores_layout->addWidget(first_score);
    scores_layout->addWidget(second_score);
    scores_layout->addWidget(third_score);
    scores_layout->addWidget(fourth_score);
    scores_layout->addWidget(fifth_score);

    //Pick a character text
    QLabel *ask = new QLabel("Pick a character:");
    QFont ask_font("Courier",16);
    ask->setFont(ask_font);
    ask->setAlignment(Qt::AlignCenter);

    //hero pictures
    QGridLayout *char_layout = new QGridLayout;

    QLabel *char1 = new QLabel;
    char1->setMaximumSize(75,75);
    char1->setPixmap(QPixmap(":/pics/black_lab.jpg").scaled(75,75,Qt::KeepAspectRatio));
    QLabel *char2 = new QLabel;
    char2->setMaximumSize(75,75);
    char2->setPixmap(QPixmap(":/pics/german_shepherd.jpg").scaled(75,75,Qt::KeepAspectRatio));
    QLabel *char3 = new QLabel;
    char3->setMaximumSize(75,75);
    char3->setPixmap(QPixmap(":/pics/dachshund.jpg").scaled(75,75,Qt::KeepAspectRatio));
    QLabel *char4 = new QLabel;
    char4->setMaximumSize(75,75);
    char4->setPixmap(QPixmap(":/pics/wolf.jpg").scaled(75,75,Qt::KeepAspectRatio));
    char_layout->addWidget(char1,0,0);
    char_layout->addWidget(char2,0,1);
    char_layout->addWidget(char3,0,2);
    char_layout->addWidget(char4,0,3);

    char1->setAlignment(Qt::AlignCenter);
    char2->setAlignment(Qt::AlignCenter);
    char3->setAlignment(Qt::AlignCenter);
    char4->setAlignment(Qt::AlignCenter);

    //Pick hero using a radio button
    black_lab = new QRadioButton("");
    german = new QRadioButton("");
    dachshund = new QRadioButton("");
    wolf = new QRadioButton("");
    black_lab->setChecked(true);

    char_layout->addWidget(black_lab,1,0);
    char_layout->addWidget(german,1,1);
    char_layout->addWidget(dachshund,1,2);
    char_layout->addWidget(wolf,1,3);

    QLabel *bl_text = new QLabel("Black Lab");
    QLabel *gs_text = new QLabel("German Shepherd");
    QLabel *d_text = new QLabel("Dachshund");
    QLabel *w_text = new QLabel("Wolf");

    char_layout->addWidget(bl_text,2,0);
    char_layout->addWidget(gs_text,2,1);
    char_layout->addWidget(d_text,2,2);
    char_layout->addWidget(w_text,2,3);

    bl_text->setAlignment(Qt::AlignCenter);
    gs_text->setAlignment(Qt::AlignCenter);
    d_text->setAlignment(Qt::AlignCenter);
    w_text->setAlignment(Qt::AlignCenter);

    //Button to bring up instructions
    QPushButton *instruct = new QPushButton("Instructions");
    //Play Button
    QPushButton *play = new QPushButton("Play!");
    //sets so that pressing enter will activate this button
    play->setDefault(true);
    play->setFocus();

    QHBoxLayout *play_layout = new QHBoxLayout();

    play_layout->addWidget(instruct);
    play_layout->addWidget(play);


    //uses member function to set member variable to play object
    setplaybutton(play);
    setinstructbutton(instruct);

    //Adds everything to the main window
    layout->addWidget(header);
    layout->addWidget(scores_title);
    layout->addLayout(horiz_scores);
    layout->addWidget(ask);
    layout->addLayout(char_layout);
    layout->addLayout(play_layout);
    //layout->addWidget(play);

    w->setLayout(layout);
    this->setCentralWidget(w);
    this->setWindowTitle("Welcome to Herding Sheep!");
}

//destructor
MainWindow::~MainWindow()
{

}

/** @function setgameboard
 * @brief sets the board member variable to the parameter passed in
 */
void MainWindow::setgameboard(gameboard* game_board){
    board = game_board;
}

/** @function closeEvent
 * @brief stops window from closing and opens a Quit Widget instead
 */
void MainWindow::closeEvent(QCloseEvent *e) {
    e->ignore();
    qwidget->show();
}

/** @function setQuitWidget
 * @brief sets the qwidget member variable to a quit widget
 */
void MainWindow::setQuitWidget(QuitWidget* quit_widget) {
    qwidget = quit_widget;
}

/** @function setplaybutton
 * @brief sets the play button so that we can access it from a connect in main
 */
void MainWindow::setplaybutton(QPushButton* p){
    play = p;
}

/** @function play_button
 * @brief returns play button so that main can access it
 */
QPushButton* MainWindow::play_button(){
    return play;
}

/** @function setinstruct
 * @brief sets the instruct button so that we can access it from a connect in main
 */
void MainWindow::setinstructbutton(QPushButton* inst){
    instruct = inst;
}

/** @function instruct
 * @brief returns instruction button so that
 * instructions will be shown on click
 */
QPushButton* MainWindow::instruct_button(){
    return instruct;
}

/** @function clear_gameboard
 * @brief creates a new gameboard object to start a new game
 */
void MainWindow::clear_gameboard(){

    board->clear_board();
}

/** @function connect_hero
 * @brief connects the hero choice buttons to the hero pixmaps to change heros picture
 */
void MainWindow::connect_hero(){
    QObject::connect(black_lab, SIGNAL(clicked()), board, SLOT(set_lab()));
    QObject::connect(german, SIGNAL(clicked()), board, SLOT(set_german()));
    QObject::connect(dachshund, SIGNAL(clicked()), board, SLOT(set_dach()));
    QObject::connect(wolf, SIGNAL(clicked()), board, SLOT(set_wolf()));
}

/** @function update_high_scores
 * @brief changes the high scores shown in the main window when a game ends, in case a new score is added
 */
void MainWindow::update_high_scores(){

    // gets all the names and high scores in QStrings
    QFile file(":/high_scores/high_scores.txt");
    QTextStream in(&file);
    file.open(QFile::ReadOnly | QFile::Text);

    QString *first_name1 = new QString(in.readLine());
    QString *first_score1 = new QString(in.readLine());
    QString *second_name1 = new QString(in.readLine());
    QString *second_score1 = new QString(in.readLine());
    QString *third_name1 = new QString(in.readLine());
    QString *third_score1 = new QString(in.readLine());
    QString *fourth_name1 = new QString(in.readLine());
    QString *fourth_score1 = new QString(in.readLine());
    QString *fifth_name1 = new QString(in.readLine());
    QString *fifth_score1 = new QString(in.readLine());

    // resets the text of the mainwindow variables
    first_name->setText(*first_name1);
    first_score->setText(*first_score1);
    second_name->setText(*second_name1);
    second_score->setText(*second_score1);
    third_name->setText(*third_name1);
    third_score->setText(*third_score1);
    fourth_name->setText(*fourth_name1);
    fourth_score->setText(*fourth_score1);
    fifth_name->setText(*fifth_name1);
    fifth_score->setText(*fifth_score1);

    // closes file
    file.close();
}
