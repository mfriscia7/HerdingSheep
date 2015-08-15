#ifndef GAMEBOARD
#define GAMEBOARD

#include <QWidget>
#include "quitwidget.h"
#include "mainwindow.h"
#include "QSquare.h"
#include "add_new_score.h"
#include "no_new_score.h"
#include "pausewindow.h"
#include "level_complete.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFile>
#include <QString>
#include <QLabel>
#include <QCloseEvent>
#include <QFont>
#include <QPixmap>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QPoint>
#include <QString>

#include <QTimer>
#include <random>
#include <chrono>

#include <QQueue>

class MainWindow;

class gameboard : public QWidget
{
    Q_OBJECT

public slots:
    //this runs the whole game
    void play_game();

    //unpauses game
    void unpause();

    void next_level();

    //runs once every timer
    void next_move();

    //this changes the state of the board for each move
    //void execute_move(int hero_move);
    void set_lab();
    void set_german();
    void set_dach();
    void set_wolf();
    void clear_board_slot(){
        clear_board();
    }

public:
    explicit gameboard(QWidget *parent = 0);

    void setMainWindow(MainWindow* main_window);
    void setnewscorewindow(add_new_score *add);
    void setgameoverwindow(no_new_score *no);
    void setpausewindow(PauseWindow *p);
    void setlevelwindow(level_complete *l);
    void closeEvent(QCloseEvent *e);

    void initialize_board();
    void update_nums();
    void check_progress();

    void finish_fence(int first_x, int first_y, int second_x, int second_y);
    void fill_fence(std::vector<QPoint> fill_v);
    void check_if_fill(int x, int y, bool is_first);

    void snake_hit_hero();
    void sheep_hit_hero(int index);
    void sheep_hit_fence();

    void you_died(QString attacker);

    //enemies!
    void add_sheep();
    void add_snake();

    //move enemies!
    void move_sheep();
    void move_snake();

    //movement functions
    void keyPressEvent(QKeyEvent *e);
    void update_hero(int x, int y, int nx, int ny);
    void execute_move(int hero_move);

    void setsmallestscore();

    void pause_game();
    void clear_board();


private:
    QWidget *Top;
    int board_size;

    QWidget *Board;
    QSquare** labels;
    int* values;
    int score_num;
    unsigned int lives_remaining;
    QLabel** lives;

    // QLabels for scores and progress
    QLabel *score_label;
    QLabel *prog_label;

    //positions of characters
    QPoint *hero_pos;
    int direction;
    int pick_char;

    //movement variables
    bool move;
    int hero_move;

    //hero file location text
    QString *hero_l_text;
    QString *hero_r_text;
    QString *hero_fence_l_text;
    QString *hero_fence_r_text;

    //hero pic objects
    QLabel *hero_l;
    QLabel *hero_r;
    QLabel *hero_fence_l;
    QLabel *hero_fence_r;

    //enemies
    std::vector<QPoint*> sheep_direction;
    std::vector<QPoint*> snake_direction;
    std::vector<QPoint*> sheep_pos;
    std::vector<QPoint*> snake_pos;
    int move_less;
    int sheep_speed;
    int snake_speed;
    bool isSmart;

    bool sheep_on_fence;
    int sheep_hit_x;
    int sheep_hit_y;

    bool sheep_or_snake;
    bool animal_in_pool1;
    bool animal_in_pool2;

    std::vector<QPoint> current_fence;
    std::vector<QPoint> first_pool;
    std::vector<QPoint> second_pool;

    // used for keeping track of current_fence index when sheep hits fence
    int right_half;
    int left_half;

    int progress;
    int curr_level;
    QLabel* level_num;

    // vectors to help fill in completed fence areas
    std::vector<int> inside;
    QPoint curr_fence_start;
    QPoint curr_fence_end;
    int fence_start_direc;
    int fence_end_direc;

    MainWindow* mw;

    add_new_score *new_score_window;
    no_new_score  *no_score_window;
    PauseWindow *pause_window;
    level_complete *level_win;

    int smallest_score;

    //queues for implementing the flood fill algorithm
    QQueue<QPoint> first_queue;
    QQueue<QPoint> second_queue;
};

#endif // GAMEBOARD
