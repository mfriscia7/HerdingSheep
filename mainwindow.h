#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboard.h"

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QRadioButton>
#include <QPushButton>
#include <QFile>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QBrush>
#include <QTextStream>
#include <QLineEdit>
#include <QRadioButton>

class gameboard;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void update_high_scores();
public:
    explicit MainWindow(QWidget *parent = 0);

    void setgameboard(gameboard* game_board);
    void clear_gameboard();
    void connect_hero();

    void setQuitWidget(QuitWidget *quit_widget);
    void closeEvent(QCloseEvent *e);
    void setplaybutton(QPushButton* p);
    void setinstructbutton(QPushButton* inst);
    QPushButton* play_button();
    QPushButton* instruct_button();

    int getsmallestscore(){return lowest_score;}

    ~MainWindow();

private:
    gameboard* board;
    QuitWidget* qwidget;

    QPushButton* play;
    QPushButton* instruct;

    QRadioButton* black_lab;
    QRadioButton* german;
    QRadioButton* dachshund;
    QRadioButton* wolf;

    // labels for high scores
    QLabel *first_name;
    QLabel *first_score;
    QLabel *second_name;
    QLabel *second_score;
    QLabel *third_name;
    QLabel *third_score;
    QLabel *fourth_name;
    QLabel *fourth_score;
    QLabel *fifth_name;
    QLabel *fifth_score;

    int lowest_score;
};

#endif // MAINWINDOW_H
