#include "mainwindow.h"
#include "gameboard.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //creates the quit widget to be used throughout
    QuitWidget *qwidget = new QuitWidget;

    //creates the main menu, gameboard, and instruction windows
    MainWindow *mm = new MainWindow;
    gameboard *g = new gameboard;

    //creates end windows and pause window
    add_new_score *score_window = new add_new_score();
    no_new_score *game_over_window = new no_new_score();
    PauseWindow *p_window = new PauseWindow();
    level_complete* level_window = new level_complete();

    //puts instruction text in QLabel
    QFile inst_file(":/instructions/Instruct.txt");
    QTextStream in(&inst_file);
    inst_file.open(QFile::ReadOnly | QFile::Text);
    QLabel *instruction = new QLabel(in.readAll());

    //sets the look of the Instruction window
    instruction->setFixedSize(400,500);
    instruction->setWordWrap(true);
    instruction->setMargin(5);
    instruction->setWindowTitle("Instructions");
    instruction->hide();

    //sets the quit widget to call for the main menu window
    mm->setQuitWidget(qwidget);

    //sets the main window and gameboard objects
    //as member variables in each other
    mm->setgameboard(g);
    g->setMainWindow(mm);
    g->setnewscorewindow(score_window);
    g->setgameoverwindow(game_over_window);
    g->setpausewindow(p_window);
    g->setlevelwindow(level_window);

    //connects character pushbuttons
    mm->connect_hero();

    //shows Main Menu
    mm->show();

    //connects windows so that when play is clicked,
    //mm closes and gameboard is made
    QObject::connect(mm->play_button(), SIGNAL(clicked()), g, SLOT(play_game()));
    QObject::connect(mm->play_button(), SIGNAL(clicked()), mm, SLOT(hide()));
    QObject::connect(mm->instruct_button(), SIGNAL(clicked()), instruction, SLOT(show()));

    //connects the quit widget with the quit whole application
    QObject::connect(qwidget->quit_ok, SIGNAL(clicked()), &a, SLOT(quit()));

    //connects buttons for score pages at the end
    QObject::connect(score_window->confirm_button(), SIGNAL(clicked()), score_window, SLOT(confirm_score()));
    QObject::connect(score_window->confirm_button(), SIGNAL(clicked()), mm, SLOT(show()));
    QObject::connect(score_window->confirm_button(), SIGNAL(clicked()), mm, SLOT(update_high_scores()));
    QObject::connect(game_over_window->no_button(), SIGNAL(clicked()), mm, SLOT(show()));
    QObject::connect(game_over_window->no_button(), SIGNAL(clicked()), game_over_window, SLOT(hide()));

    //connects buttons for pause button
    QObject::connect(p_window->unpause_button(), SIGNAL(clicked()), g, SLOT(unpause()));

    // connects to the next level button
    QObject::connect(level_window->confirm_button(), SIGNAL(clicked()), g, SLOT(next_level()));

    QTimer *timer = new QTimer(g);
    QObject::connect(timer, SIGNAL(timeout()), g, SLOT(next_move()));
    timer->start(100);

    return a.exec();
}
