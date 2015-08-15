#include "gameboard.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

//constructor for the gameboard object
gameboard::gameboard(QWidget *parent) :
    QWidget(parent), board_size(29), direction(1), curr_level(0), pick_char(0), move_less(0), move(false), sheep_on_fence(false), smallest_score(0), isSmart(0), score_num(0), progress(0)
{
    //sets the background to black
    setStyleSheet("background:black;");

    //creates layout for top bar
    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");

    //laying a space at the top
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    //sets lives box, score, and progress
    QLabel *live_text = new QLabel("Lives:");
    QFont font("Courier", 14);
    font.setBold(true);
    live_text->setFont(font);
    top_bar->addWidget(live_text);

    //sets default character
    hero_l_text = new QString(":/pics/black_lab.jpg");
    hero_r_text = new QString(":/pics/black_lab_2.jpg");
    hero_fence_l_text = new QString(":/pics/black_lab_fence.jpg");
    hero_fence_r_text = new QString(":/pics/black_lab_fence_2.jpg");

    lives_remaining = 3;
    lives = new QLabel*[lives_remaining];

    hero_l = new QLabel;
    hero_r = new QLabel;
    hero_fence_l = new QLabel;
    hero_fence_r = new QLabel;

    //initializes the position of the hero
    hero_pos = new QPoint(0,0);
    hero_move = 0;
    score_num = 0;

    //creates lives pictures with for loop
    for(size_t i=0; i < lives_remaining; ++i){
        lives[i] = new QLabel;
        lives[i]->setPixmap(*hero_r_text);
        lives[i]->setMinimumSize(29,29);
        lives[i]->setMaximumSize(29,29);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
    }

    QSpacerItem *space1 = new QSpacerItem(29,10);
    top_bar->addSpacerItem(space1);

    QLabel *score = new QLabel("Score:");
    score->setFont(font);
    top_bar->addWidget(score);

    QString score_str = QString::number(score_num);
    score_label = new QLabel(score_str);
    score_label->setFont(font);
    top_bar->addWidget(score_label);

    QSpacerItem *space2 = new QSpacerItem(60,10);
    top_bar->addSpacerItem(space2);

    QLabel *prog_card = new QLabel("Progress:");
    prog_card->setFont(font);
    top_bar->addWidget(prog_card);

    QString prog_str = QString::number(progress/((board_size-2)*(board_size-2)));
    prog_label = new QLabel(prog_str);
    prog_label->setFont(font);
    top_bar->addWidget(prog_label);

    // adds percent sign at the end
    QLabel *percent = new QLabel("%");
    percent->setFont(font);
    top_bar->addWidget(percent);


    //sets up member variables and QGridLayout for board
    Board = new QWidget;
    labels = new QSquare*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    //creates board using nested for loop
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){

            labels[i*board_size+j] = new QSquare();
            labels[i*board_size+j]->setMinimumSize(29,29);
            labels[i*board_size+j]->setMaximumSize(29,29);
            if(i==0 || j==0 || i==board_size-1 || j==board_size-1){
                //labels[i*board_size+j]->setPixmap(QPixmap(":/pics/fence.jpg").scaled(29,29,Qt::KeepAspectRatio));
                labels[i*board_size+j]->setFence();
            }
            else{
                //labels[i*board_size+j]->setPixmap(QPixmap(":/pics/grass.jpg").scaled(29,29,Qt::KeepAspectRatio));
                labels[i*board_size+j]->setGrass();
            }
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            SquareGrid->addWidget(labels[i*board_size+j],i,j);
        }
    }

    setFixedSize(800,800);

    //main layout that puts the top bar and board together
    QVBoxLayout *put_together = new QVBoxLayout;
    put_together->addWidget(Top,0,Qt::AlignCenter);
    put_together->addWidget(Board,0,Qt::AlignCenter);

    //level number in the corner
    level_num = new QLabel(QString::number(curr_level));
    QFont level_font("Courier",6);
    level_num->setFont(level_font);
    level_num->setStyleSheet("QLabel { background-color : black; color : white; }");

    //level_num->setFont(new QFont());
    put_together->addWidget(level_num,0,Qt::AlignRight);

    //sets the main window of the gamboard
    this->setLayout(put_together);
    this->setStyleSheet("QLabel { background-color : white; color: black; }");
    this->setWindowTitle("Herding Sheep");

}

/** @function set_lab
 * @brief this sets all the pixmaps to various black lab pictures
 */
void gameboard::set_lab(){
    *hero_l_text = ":/pics/black_lab.jpg";
    *hero_r_text = ":/pics/black_lab_2.jpg";
    *hero_fence_l_text = ":/pics/black_lab_fence.jpg";
    *hero_fence_r_text = ":/pics/black_lab_fence_2.jpg";

    hero_l->setPixmap(QPixmap(*hero_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_r->setPixmap(QPixmap(*hero_r_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_l->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_r->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
    lives[0]->setPixmap(QPixmap(*hero_r_text));
    lives[1]->setPixmap(QPixmap(*hero_r_text));
    lives[2]->setPixmap(QPixmap(*hero_r_text));
}

/** @function set_german
 * @brief this sets all the pixmaps to various german shepherd pictures
 */
void gameboard::set_german(){
    *hero_l_text = ":/pics/german_shepherd.jpg";
    *hero_r_text = ":/pics/german_shepherd_2.jpg";
    *hero_fence_l_text = ":/pics/german_shepherd_fence.jpg";
    *hero_fence_r_text = ":/pics/german_shepherd_fence_2.jpg";

    hero_l->setPixmap(QPixmap(*hero_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_r->setPixmap(QPixmap(*hero_r_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_l->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_r->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
    lives[0]->setPixmap(QPixmap(*hero_r_text));
    lives[1]->setPixmap(QPixmap(*hero_r_text));
    lives[2]->setPixmap(QPixmap(*hero_r_text));
}

/** @function set_dach
 * @brief this sets all the pixmaps to various dachshund pictures
 */
void gameboard::set_dach(){
    *hero_l_text = ":/pics/dachshund.jpg";
    *hero_r_text = ":/pics/dachshund_2.jpg";
    *hero_fence_l_text = ":/pics/dachshund_fence.jpg";
    *hero_fence_r_text = ":/pics/dachshund_fence_2.jpg";

    hero_l->setPixmap(QPixmap(*hero_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_r->setPixmap(QPixmap(*hero_r_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_l->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_r->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
    lives[0]->setPixmap(QPixmap(*hero_r_text));
    lives[1]->setPixmap(QPixmap(*hero_r_text));
    lives[2]->setPixmap(QPixmap(*hero_r_text));
}

/** @function set_wolf
 * @brief this sets all the pixmaps to various wolf pictures
 */
void gameboard::set_wolf(){
    *hero_l_text = ":/pics/wolf.jpg";
    *hero_r_text = ":/pics/wolf_2.jpg";
    *hero_fence_l_text = ":/pics/wolf_fence.jpg";
    *hero_fence_r_text = ":/pics/wolf_fence_2.jpg";

    hero_l->setPixmap(QPixmap(*hero_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_r->setPixmap(QPixmap(*hero_r_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_l->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
    hero_fence_r->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
    lives[0]->setPixmap(QPixmap(*hero_r_text));
    lives[1]->setPixmap(QPixmap(*hero_r_text));
    lives[2]->setPixmap(QPixmap(*hero_r_text));
}

/** @function setsmallestscore
 * @brief sets the lowest score to check if new high score is reached at the end of the game
 */
void gameboard::setsmallestscore(){
    smallest_score = mw->getsmallestscore();
}

/** @function close event
 * @brief hides game window, resets scores and returns to main menu window
 */
void gameboard::closeEvent(QCloseEvent *e) {

    e->ignore();
    mw->show();
    hide();

    //resets gameboard
    mw->clear_gameboard();
}

/** @function setMainWindow
 * @brief sets the mw member object of gameboard to a MainWindow parameter
 */
void gameboard::setMainWindow(MainWindow* main_window) {
    mw = main_window;
    //sets the smallest high score as well
    setsmallestscore();
}

/** @function clear_board
 * @brief resets all member variables that affect what is shown in the gameboard
 */
void gameboard::clear_board(){

    // resets all the values of the board
    direction = 1;
    curr_level = 0;
    level_num->setText(QString::number(curr_level));
    pick_char = 0;
    move_less = 0;
    move = false;
    sheep_on_fence = false;
    smallest_score = 0;
    isSmart = 0;
    progress = 0;
    score_num = 0;

    //resets lives counter
    lives_remaining = 3;
    for(size_t i=0; i < lives_remaining; ++i)
        lives[i]->setPixmap(*hero_r_text);

    //resets the values of the QSquares
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){

            if(i==0 || j==0 || i==board_size-1 || j==board_size-1)
                labels[i*board_size+j]->setFence();
            else
                labels[i*board_size+j]->setGrass();
        }
    }


    // resets top_bar
    update_nums();

    // checks if level is comlete
    check_progress();
}

/** @function setnewscorewindow
 * @brief sets the member variable to a score window so that it can be called by the gameboard
 */
void gameboard::setnewscorewindow(add_new_score *add){
    new_score_window = add;
}

/** @function setgameoverwindow
 * @brief sets the member variable to a pause window so that it can be called by the gameboard
 */
void gameboard::setgameoverwindow(no_new_score *no){
    no_score_window = no;
}

/** @function setpausewindow
 * @brief sets the member variable to a pause window so that it can be called by the gameboard
 */
void gameboard::setpausewindow(PauseWindow *p){
    pause_window = p;
}

/** @function setlevelwindow
 * @brief sets the member variable to a level complete window so that it can be called by the gameboard
 */
void gameboard::setlevelwindow(level_complete *l){
    level_win = l;
}

/** @function initialize_board
 * @brief initializes board to begin a new game, resets lives, movement, etc.
 * @param curr_level determines which level is set up in the gameboard
 */
void gameboard::initialize_board(){

    // stops movemenets
    move = false;

    //resets direction
    direction = 1;

    //resets the values of the QSquares
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){

            if(i==0 || j==0 || i==board_size-1 || j==board_size-1)
                labels[i*board_size+j]->setFence();
            else
                labels[i*board_size+j]->setGrass();
        }
    }

    //resets vectors
    sheep_direction.clear();
    sheep_pos.clear();
    current_fence.clear();
    snake_pos.clear();

    hero_move = 0;

    //sets hero in starting position
    hero_pos = new QPoint(0,0);
    labels[0]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));



    // this part sets parameters depending on the level

    if (curr_level == 1){

        add_sheep();
    }
    else if (curr_level == 2){

        add_sheep();
        add_sheep();
        add_sheep();
    }
    else if (curr_level == 3){

        add_sheep();
        add_sheep();
        add_sheep();

        add_snake();
        isSmart = false;
    }
    else if (curr_level == 4){

        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();

        add_snake();
        add_snake();
        isSmart = false;
    }
    else if (curr_level == 5){

        add_sheep();
        add_sheep();

        add_snake();
        isSmart = true;
    }
    else if (curr_level == 6){

        add_sheep();
        add_sheep();
        add_sheep();

        add_snake();
        add_snake();
        isSmart = true;
    }
    else if (curr_level == 7){

        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();

        add_snake();
        add_snake();
        add_snake();
        isSmart = true;
    }
    else if (curr_level == 8){
        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();
        add_sheep();

        add_snake();
        add_snake();
        add_snake();
        add_snake();
        isSmart = true;
    }
    // keeps levels going on for a while
    else{

        for (int i=0;i<(curr_level-2);++i)
            add_sheep();
        for (int j=0;j<(curr_level/2);++j)
            add_snake();
        isSmart = true;
    }
}

/** @function keyPressEvent
 * @brief gets user input from keyboard to determine where to move hero or to pause the game
 */
void gameboard::keyPressEvent(QKeyEvent *event){

    int fence_place, hero_place;

    //only checks last fence spot if there is one
    if (!current_fence.empty()){
        // doesn't allow hero to move backwards when making a fence
        QPoint last_fence = current_fence[current_fence.size()-1];
        fence_place = (last_fence.ry()*board_size) + last_fence.rx();
        hero_place = (hero_pos->ry()*board_size) + hero_pos->rx();
    }
    else{
        fence_place = -1;
        hero_place = 1000;
    }

    //hero_move values correspond to number pad again
    switch (event->key()){
    case Qt::Key_Up:
        move = true;
        if(hero_pos->ry() != 0)
            //can't turn around if making a new fence
            if (hero_move != 8 || fence_place != hero_place - board_size)
                hero_move = 2;
        break;
    case Qt::Key_Down:
        move = true;
        if(hero_pos->ry() !=board_size-1)
            //can't turn around if making a new fence
            if (hero_move != 2 || fence_place != hero_place + board_size)
                hero_move = 8;
        break;
    case Qt::Key_Left:
        move = true;
        if(hero_pos->rx() != 0)
            //can't turn around if making a new fence
            if (hero_move != 6 || fence_place != hero_place - 1)
                hero_move = 4;
        break;
    case Qt::Key_Right:
        move = true;
        if(hero_pos->rx() != board_size-1)
            //can't turn around if making a new fence
            if (hero_move != 4 || fence_place != hero_place + 1)
                hero_move = 6;
        break;
    case Qt::Key_P:
        pause_game();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

/** @function update_hero
 * @brief this serves as a sort of translator that converts commands from keyPressEvent
 * into movements of the hero. Also takes into account if a tempFence or enemy is hit
 */
void gameboard::update_hero(int x, int y, int nx, int ny){
    // only change position if hero is not trying to go past the edge of the board
    if(nx >= 0 && ny >= 0 && nx < board_size && ny < board_size){

        // check first to make sure not hitting a tempFence (where hero is currently making fence)
        // if you hit a fence you are currently making, you die
        if (labels[ny*board_size+nx]->isTempFence()){
            you_died("sheep");
            return;
        }
        // then checks if hitting sheep
        else if (labels[ny*board_size+nx]->isSheep()){

            // first check if hero is a wolf
            if (*hero_l_text == ":/pics/wolf.jpg"){
                std::uniform_int_distribution<int> board_dist(0,board_size-1);

                // find the index in sheep_pos of which sheep was hit
                int index;

                for (size_t i = 0; i < sheep_pos.size();++i){
                    if (sheep_pos[i]->rx() == nx && sheep_pos[i]->ry() == ny)
                        index = i;
                }
                int new_x, new_y;

                // randomly find a new open position for this sheep
                do{
                    new_x = board_dist(generator);
                    new_y = board_dist(generator);

                } while(labels[new_y*board_size + new_x]->isFilled());

                // sets the new position of the sheep
                labels[new_y*board_size+new_x]->setSheep();
                labels[sheep_pos[index]->ry()*board_size+sheep_pos[index]->rx()]->setGrass();
                labels[new_y*board_size+new_x]->setPixmap(QPixmap(":/pics/sheep.jpg").scaled(29,29,Qt::KeepAspectRatio));
                labels[sheep_pos[index]->ry()*board_size+sheep_pos[index]->rx()]->setPixmap(QPixmap(":/pics/grass.jpg").scaled(29,29,Qt::KeepAspectRatio));
                sheep_pos[index]->setX(new_x);
                sheep_pos[index]->setY(new_y);
                return;
            }

            // find the index in sheep_pos of which sheep was hit

            int ind;

            for (size_t i = 0; i < sheep_pos.size();++i){
                if (sheep_pos[i]->rx() == nx && sheep_pos[i]->ry() == ny)
                    ind = i;
            }
            sheep_hit_hero(ind);
            return;
        }
        // else if a snake is hit
        else if (labels[ny*board_size+nx]->isSnake()){
            snake_hit_hero();
            return;
        }

        // if hero moving onto fence from a non-fence spot
        if(labels[ny*board_size+nx]->isFence() && !labels[y*board_size+x]->isFence()){

            //set where the end point of the fence is
            curr_fence_end.setX(nx);
            curr_fence_end.setY(ny);

            //if going left
            if (nx < x){
                labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
                direction = -1;
                fence_end_direc = 4;
                labels[y*board_size+x]->setTempFence();
                current_fence.push_back(QPoint(x,y));
                finish_fence(x,y-1,x,y+1);
            }
            //going right
            else if (nx > x){
                labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
                direction = 1;
                fence_end_direc = 6;
                labels[y*board_size+x]->setTempFence();
                current_fence.push_back(QPoint(x,y));
                finish_fence(x,y-1,x,y+1);
            }
            //going up or down, keeps same direction as before the move
            else{
                if (current_fence.size() > 0)
                    finish_fence(x-1,y,x+1,y);
                if(direction == -1){
                    labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
                    labels[y*board_size+x]->setTempFence();
                    current_fence.push_back(QPoint(x,y));
                    if (ny>y)
                        fence_end_direc = 8;
                    else
                        fence_end_direc = 2;
                    finish_fence(x-1,y,x+1,y);
                }
                else{
                    labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
                    labels[y*board_size+x]->setTempFence();
                    current_fence.push_back(QPoint(x,y));
                    if (ny>y)
                        fence_end_direc = 8;
                    else
                        fence_end_direc = 2;
                    finish_fence(x-1,y,x+1,y);
                }


            }
            hero_pos->setX(nx);
            hero_pos->setY(ny);
            labels[ny*board_size+nx]->setHero();
        }
        //else if not finishing a fence
        else{

            if (!labels[y*board_size+x]->isFence()){
                labels[y*board_size+x]->setTempFence();
                current_fence.push_back(QPoint(x,y));
            }
            // if going left
            if (nx < x){
                labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));
                direction = -1;
                fence_start_direc = 4;
            }
            //going right
            else if (nx > x){
                labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
                direction = 1;
                fence_start_direc = 6;
            }
            else{
                if (direction == 1)
                    labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
                else
                    labels[ny*board_size+nx]->setPixmap(QPixmap(*hero_fence_l_text).scaled(29,29,Qt::KeepAspectRatio));

                if (ny>y)
                    fence_start_direc = 8;
                else
                    fence_start_direc = 2;
            }
            hero_pos->setX(nx);
            hero_pos->setY(ny);
            labels[ny*board_size+nx]->setHero();


            // if current fence is empty, we are just starting a fence
            if (current_fence.size() == 0){
                curr_fence_start.setX(x);
                curr_fence_start.setY(y);
            }
        }
        //if moving from a fence
        if(labels[y*board_size+x]->isFence()){
            //erases hero to be true
            labels[y*board_size+x]->setFence();
            hero_pos->setX(nx);
            hero_pos->setY(ny);
            labels[ny*board_size+nx]->setHero();
        }

    }
}

/** @function pause_game
 * @brief stops all movements on the gameboard, opens pause window
 */
void gameboard::pause_game(){

    //stops movements
    move = false;

    pause_window->show();

    //hides gameboard
    hide();
}

/** @function execute_move
 * @brief this uses the timer that is setup in main to determine when hero and enemies move positions
 */
void gameboard::execute_move(int hero_move){

    if (move){
        if (hero_move != 0){
            int x = hero_pos->rx();
            int y = hero_pos->ry();

            //hero movements
            if (hero_move == 2){
                //move up

                update_hero(x,y,x,y-1);
            }
            else if (hero_move == 8){
                //move down
                update_hero(x,y,x,y+1);
            }
            else if (hero_move == 4){
                //move left
                update_hero(x,y,x-1,y);
            }
            else if (hero_move == 6){
                //move right
                update_hero(x,y,x+1,y);
            }
        }
    }
}

/** @function you_died
 * @brief when called, hero will lose a life or game will end if there are zero lives remaining
 * @param attacker will do different things depending on which enemy is hit
 * determines which hero power up can be used
 */
void gameboard::you_died(QString attacker){

    //stop movements of hero
    hero_move = 0;

    if (lives_remaining == 1){
        //opens game over window
        //will let you submit name if new high score is reached
        if (score_num > smallest_score){
            new_score_window->score_num = score_num;
            new_score_window->show();
        }
        //else it will open the Game Over window
        else{
            no_score_window->show();
        }
        //hides the gameboard window and exits function
        hide();
        return;
    }

    //if lives is not 0
    //change number of lives in top bar
    QPixmap* black_lives = new QPixmap;
    black_lives->fill(Qt::black);
    lives[--lives_remaining]->setPixmap(*black_lives);

    int old_h_x = hero_pos->rx();
    int old_h_y = hero_pos->ry();

    //move hero back to original
    if (attacker == "snake")
        labels[old_h_y*board_size+old_h_x]->setFence();
    else
        labels[old_h_y*board_size+old_h_x]->setGrass();

    //clear any temporary fence blocks
    if (current_fence.size() > 0){
        int x,y;

        for(auto i: current_fence){
            x = i.rx();
            y = i.ry();

            labels[y*board_size+x]->setGrass();
            labels[y*board_size+x]->setPixmap(QPixmap(":/pics/grass.jpg").scaled(29,29,Qt::KeepAspectRatio));
        }
        current_fence.clear();
    }

    //resets hero to first square and resets his direction
    hero_pos->setX(0);
    hero_pos->setY(0);
    direction = 1;

    labels[0]->setPixmap(QPixmap(*hero_fence_r_text).scaled(29,29,Qt::KeepAspectRatio));
    labels[0]->setHero();
}

/** @function add_sheep
 * @brief adds a new sheep character to a random position on the board
 */
void gameboard::add_sheep(){
    //random numbers
    std::uniform_int_distribution<int> distribution(1,board_size-2);

    int x, y;

    do{
        x = distribution(generator);
        y = distribution(generator);
    //loop continues until (x,y) not on an edge and as long as a sheep is not already there
    }while((x==0 || y==0 || x==board_size-1 || y==board_size-1) && labels[y*board_size+x]->isSheep());

    // facing is which direction it is facing
    // d is which direction the sheep will initially go
    int d = distribution(generator) % 2;
    int facing = distribution(generator) % 2;

    //stores the new sheep position
    sheep_pos.push_back(new QPoint(x,y));
    labels[y*board_size+x]->setSheep();

    //sets sheep direction and direction pic
    //if sheep going in left direction
    if(facing == 1){
        labels[y*board_size+x]->setPixmap(QPixmap(":/pics/sheep.jpg").scaled(29,29,Qt::KeepAspectRatio));
        //randomizes the direction of the sheep
        if(d == 0)
            sheep_direction.push_back(new QPoint(1,1));
        else
            sheep_direction.push_back(new QPoint(1,-1));
    }
    else{
        labels[y*board_size+x]->setPixmap(QPixmap(":/pics/sheep_2.jpg").scaled(29,29,Qt::KeepAspectRatio));
        if(d == 0)
            sheep_direction.push_back(new QPoint(-1,1));
        else
            sheep_direction.push_back(new QPoint(-1,-1));
    }
}

/** @function add_snake
 * @brief adds a new snake to a random position on the board
 */
void gameboard::add_snake(){
    //random numbers
    std::uniform_int_distribution<int> distribution(0,board_size-1);

    int x,y, dist_from_start, pick_edge;

    do{
        dist_from_start = distribution(generator);
        pick_edge = distribution(generator) % 4;

    // while loop to make sure the snake doesn't start too close to the hero
    }while(pick_edge < 2 && dist_from_start <= 5);

    // place snake on left edge
    if (pick_edge == 0){
        x = 0;
        y = dist_from_start;
    }
    // place snake on top edge
    else if (pick_edge == 1){
        y = 0;
        x = dist_from_start;
    }
    // place snake on right edge
    else if (pick_edge == 2){
        x = board_size - 1;
        y = dist_from_start;
    }
    // place snake on bottom edge
    else if (pick_edge == 3){
        x = dist_from_start;
        y = board_size - 1;
    }

    //add snake to snake vector and to gameboard
    snake_pos.push_back(new QPoint(x,y));
    labels[y*board_size+x]->setSnake();
}

/** @function move_snake
 * @brief moves the snake in a direction on the board where there is fence
 * @param isSmart if true, snake will be smart and move towards the hero
 */
void gameboard::move_snake(){
    std::uniform_int_distribution<int> distribution(0,board_size);

    size_t size = snake_pos.size();

    //for loop moves one spot for each snake
    for(size_t i = 0; i < size; ++i){

        //original position
        int x = snake_pos[i]->rx();
        int y = snake_pos[i]->ry();

        int x_direc, y_direc;

        if (isSmart){

            // finds which way to go first in x direction, then in y direction
            // default is set at not moving
            x_direc = 0;
            y_direc = 0;

            // if snake is to the right of hero
            if (x - hero_pos->rx() > 0){
                // if snake is below hero
                if (y - hero_pos->ry() > 0){
                    if (y-1 >= 0 && x-1 >= 0 && labels[(y-1)*board_size+(x-1)]->isFence()){
                        x_direc = -1;
                        y_direc = -1;
                    }
                    else if (y-1 >= 0 && labels[(y-1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = -1;
                    }
                    else if (x-1 >= 0 && labels[y*board_size+(x-1)]->isFence()){
                            x_direc = -1;
                            y_direc = 0;
                    }
                }
                // else if snake is above hero
                else if (y - hero_pos->ry() < 0){
                    if (y+1 <= board_size-1 && x-1 >= 0 && labels[(y+1)*board_size+(x-1)]->isFence()){
                        x_direc = -1;
                        y_direc = 1;
                    }
                    else if (y+1 <= board_size-1 && labels[(y+1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = 1;
                    }
                    else if (x-1 >= 0 && labels[y*board_size+(x-1)]->isFence()){
                        x_direc = -1;
                        y_direc = 0;
                    }
                }
                // else if they are in the same row
                else if (y - hero_pos->ry() == 0){
                    if (x-1 >=0 && labels[y*board_size+(x-1)]->isFence()){
                        x_direc = -1;
                        y_direc = 0;
                    }
                }
            }
            // if snake is to the left
            else if (x - hero_pos->rx() < 0){
                // if snake is below hero
                if (y - hero_pos->ry() > 0){
                    if (y-1 >= 0 && x+1 <= board_size-1 && labels[(y-1)*board_size+(x+1)]->isFence()){
                        x_direc = 1;
                        y_direc = -1;
                    }
                    else if (y-1 >= 0 && labels[(y-1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = -1;
                    }
                    else if (x+1 <= board_size-1 && labels[y*board_size+(x+1)]->isFence()){
                        x_direc = 1;
                        y_direc = 0;
                    }
                }
                // else if snake is above hero
                else if (y - hero_pos->ry() < 0){
                    if (y+1 <= board_size-1 && x+1 <= board_size-1 && labels[(y+1)*board_size+(x+1)]->isFence()){
                        x_direc = 1;
                        y_direc = 1;
                    }
                    else if (y+1 <= board_size-1 && labels[(y+1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = 1;
                    }
                    else if (x+1 <= board_size-1 && labels[y*board_size+(x+1)]->isFence()){
                        x_direc = 1;
                        y_direc = 0;
                    }
                }
                // else if they are in the same row
                else if (y - hero_pos->ry() == 0){
                    if (x+1 <= board_size-1 && labels[y*board_size+(x+1)]->isFence()){
                        x_direc = 1;
                        y_direc = 0;
                    }
                }
            }
            // else if they are in the same column
            else if (x - hero_pos->rx() == 0){
                // if snake is below
                if (y - hero_pos->ry() > 0){
                    if (y-1 >=0 && labels[(y-1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = -1;
                    }
                }
                // if snake is above
                if (y - hero_pos->ry() < 0){
                    if (y+1 <= board_size-1 && labels[(y+1)*board_size+x]->isFence()){
                        x_direc = 0;
                        y_direc = 1;
                    }
                }
            }
        }
        // else random movement is performed
        else{
            // pick random direction until a fence spot is chosen in a non-diagonal direction
            do{
                // if snake at left or right edge
                if (!x)
                    // direc can be 0 or 1
                    x_direc = distribution(generator) % 2;
                else if (x == board_size-1)
                    // direc can be -1 or 0
                    x_direc = (distribution(generator) % 2) - 1;
                else
                    // can be -1, 0, or 1
                    x_direc = (distribution(generator) % 3) - 1;



                // if snake at top or bottom edge
                if (!y)
                    // direc can be 0 or 1
                    y_direc = distribution(generator) % 2;
                else if (y == board_size-1)
                    // direc can be 0 or -1
                    y_direc = (distribution(generator) % 2) - 1;
                else
                    // can be -1, 0, or 1
                    y_direc = (distribution(generator) % 3) - 1;

            }while ((!labels[(y+y_direc)*board_size+(x+x_direc)]->isFence()) || abs(x_direc + y_direc) == 2);
        }

        // changes squares on board
        labels[y*board_size+x]->setFence();

        // see if hit hero
        if (labels[(y+y_direc)*board_size+(x+x_direc)]->isHero()){
            you_died("snake");
        }

        labels[(y+y_direc)*board_size+(x+x_direc)]->setSnake();


        //make changes to the actual snake position
        snake_pos[i]->setX(x+x_direc);
        snake_pos[i]->setY(y+y_direc);

        // first check if snake is hitting hero or another snake
        if (labels[(y+y_direc)*board_size+(x+x_direc)]->isHero()){
            snake_hit_hero();
        }
    }
}

/** @function move_sheep
 * @brief moves sheep in the direction it is headed to an open grass spot, also will bounce off fence
 */
void gameboard::move_sheep(){

    size_t size = sheep_pos.size();

    //for loop moves one spot for each sheep
    for(size_t i = 0; i < size; ++i){

        //original position
        int x = sheep_pos[i]->rx();
        int y = sheep_pos[i]->ry();

        //gets direction
        int x_direc = sheep_direction[i]->rx();
        int y_direc = sheep_direction[i]->ry();

        //first check if sheep hits a not finished fence
        if (labels[(y+y_direc)*board_size+(x+x_direc)]->isTempFence()){
            sheep_on_fence = true;
            sheep_hit_x = x+x_direc;
            sheep_hit_y = y+y_direc;
            sheep_hit_fence();
        }
        // then checks if the sheep is hitting the hero
        if (labels[(y+y_direc)*board_size + (x+x_direc)]->isHero() && (y+y_direc != 0 && y+y_direc != board_size-1 && x+x_direc != 0 && x+x_direc != board_size-1))
            sheep_hit_hero(i);

        //checks if it is moving into an taken spot
        if(labels[(y+y_direc)*board_size+(x+x_direc)]->isFilled()){

            int next_spot = (y+y_direc)*board_size+(x+x_direc);

            //phone dialpad style of referencing
            //all squares around sheep
            int one = (y-1)*board_size+(x-1);
            int two = (y-1)*board_size+x;
            int three = (y-1)*board_size+(x+1);
            int four = y*board_size+(x-1);
            int six = y*board_size+(x+1);
            int seven = (y+1)*board_size+(x-1);
            int eight = (y+1)*board_size+x;
            int nine = (y+1)*board_size+(x+1);

            if(next_spot == one){
                //if corner
                if(labels[two]->isFilled() && labels[four]->isFilled()){
                    x_direc = 1;
                    y_direc = 1;
                }
                //if fence is top
                else if(labels[two]->isFilled())
                    y_direc = 1;
                //if fence is on left
                else if(labels[four]->isFilled())
                    x_direc = 1;
                //else bounce in opposite way
                else{
                    x_direc = 1;
                    y_direc = 1;
                }
            }
            else if(next_spot == three){
                //if corner
                if(labels[two]->isFilled() && labels[six]->isFilled()){
                    x_direc = -1;
                    y_direc = 1;
                }
                //if fence is on top
                else if(labels[two]->isFilled())
                    y_direc = 1;
                //if fence is on right
                else if(labels[six]->isFilled())
                    x_direc = -1;
                //else bounce in opposite way
                else{
                    x_direc = -1;
                    y_direc = 1;
                }
            }
            else if(next_spot == seven){
                //if corner
                if(labels[four]->isFilled() && labels[eight]->isFilled()){
                    x_direc = 1;
                    y_direc = -1;
                }
                //if hits bottom
                else if(labels[eight]->isFilled())
                    y_direc = -1;
                //if hits left
                else if(labels[four]->isFilled())
                    x_direc = 1;
                //else bounce in opposite way
                else{
                    x_direc = 1;
                    y_direc = -1;
                }
            }

            else if(next_spot == nine){
                //if corner
                if(labels[six]->isFilled() && labels[eight]->isFilled()){
                    x_direc = -1;
                    y_direc = -1;
                }
                //if fence is on bottom
                else if(labels[eight]->isFilled())
                    y_direc = -1;
                //if fence is on right
                else if(labels[six]->isFilled())
                    x_direc = -1;
                //else bounce in opposite way
                else{
                    x_direc = -1;
                    y_direc = -1;
                }
            }
        }

            //changes state of QSquare
            labels[y*board_size+x]->setGrass();
            labels[(y+y_direc)*board_size+(x+x_direc)]->setSheep();

            if(x_direc == 1)
                labels[(y+y_direc)*board_size+(x+x_direc)]->setPixmap(QPixmap(":/pics/sheep_2.jpg").scaled(29,29,Qt::KeepAspectRatio));
            else
                labels[(y+y_direc)*board_size+(x+x_direc)]->setPixmap(QPixmap(":/pics/sheep.jpg").scaled(29,29,Qt::KeepAspectRatio));

            //make changes to the actual sheep position
            sheep_pos[i]->setX(x+x_direc);
            sheep_pos[i]->setY(y+y_direc);

            //changes the direction of the sheep
            sheep_direction[i]->setX(x_direc);
            sheep_direction[i]->setY(y_direc);
    }
}

/** @function next_move
 * @brief determines the speed of movements of all moving parts on the gameboard
 */
void gameboard::next_move(){

    if(move != 0){
        // set speeds of sheep and snake CHANGE WHEN LEVELS SET
        sheep_speed = 4;
        snake_speed = 4;

        // move sheep
        if(move_less % sheep_speed == 0)
            move_sheep();

        // check if there are any snakes in the level
        if(snake_pos.size() > 0)
            if(move_less % snake_speed == 0)
                move_snake();

        // move hero
        if (hero_move != 0)
            execute_move(hero_move);


        // this occurs if sheep_hit_fence is called
        if (sheep_on_fence && move_less){

            // finds index of where sheep hit
            for (size_t i = 1; i < current_fence.size(); ++i){
                if ( current_fence[i].rx() == sheep_hit_x && current_fence[i].ry() == sheep_hit_y){
                    right_half = i;
                    left_half = i;
                }
            }

            if (right_half >= 0 && right_half < current_fence.size() && left_half >= 0 && left_half < current_fence.size())
                sheep_hit_fence();
            else
                sheep_on_fence = false;

        }

        ++move_less;
    }
}

/** @function finish_fence
 * @brief when a tempFence is completec by landing back on a fence, the tempfence is turned into regualar fence
 * @param: first x and y corresponds to the starting point of the first fill in, second x and y for the second
 */
void gameboard::finish_fence(int first_x, int first_y, int second_x, int second_y){

    int size = current_fence.size();

    // first checks where to have the anchor
    // where there is grass on either side of a tempfence spot
    // so that it can fill in best
    if (labels[first_y*board_size+first_x]->isAnyFence() || labels[second_y*board_size+second_x]->isAnyFence()){

        //find the spot in the tempFence where there is grass on two sides
        for (size_t i=0; i < current_fence.size();++i){
            int _x = current_fence[i].rx();
            int _y = current_fence[i].ry();

            if (!labels[(_y+1)*board_size+_x]->isAnyFence() && !labels[(_y-1)*board_size+_x]->isAnyFence()){
                first_y = _y+1;
                second_y = _y-1;
                first_x = _x;
                second_x = _x;
                break;
            }
            else if (!labels[_y*board_size+(_x+1)]->isAnyFence() && !labels[_y*board_size+(_x-1)]->isAnyFence()){
                first_y = _y;
                second_y = _y;
                first_x = _x+1;
                second_x = _x-1;
                break;
            }
        }
    }


    // only set to true in check if fill fence
    sheep_or_snake = false;
    animal_in_pool1 = false;
    animal_in_pool2 = false;

    //changes all tempFences to normal fence
    //removes all tempFences from vector
    for(auto i : current_fence)
        labels[i.ry()*board_size+(i.rx())]->setFence();
    current_fence.clear();

    // check which is inside and which is outside
    // true and false refers to which vector to place points in
    if (size > 0){
        check_if_fill(first_x, first_y, true);
        check_if_fill(second_x, second_y, false);
    }

    // check which pool will be used
    if (first_pool.size() < second_pool.size())
        sheep_or_snake = animal_in_pool1;
    else
        sheep_or_snake = animal_in_pool2;

    if (!sheep_or_snake){
        // fills fence according to which is smaller: pool_1 or pool_2
        // 175 max so that can't fill up too much in one fence
        if (first_pool.size() <= 175 || second_pool.size() <= 175){

            // first check if both sides are small enough to fill both and no animals in either side
            if  (first_pool.size() <= 20 && second_pool.size() <= 20 && !animal_in_pool1 && !animal_in_pool2){
                fill_fence(first_pool);
                fill_fence(second_pool);
                size += (first_pool.size() + second_pool.size());
            }
            // normal fill in routine, only filling smaller of two pools
            else{
                if (first_pool.size() < second_pool.size()){
                    fill_fence(first_pool);
                    size += first_pool.size();
                }
                else{
                    fill_fence(second_pool);
                    size += second_pool.size();
                }
            }
        }
    }

    // empty the vectors once done
    first_pool.clear();
    second_pool.clear();

    // clears all labels of flag
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            labels[i*board_size+j]->reset_flag();
        }
    }

    // change the progress and score
    progress += size;
    score_num += size;

    // changes the values of the score and progress in the window
    update_nums();

    // checks to see if progress reached
    check_progress();
}

/** @function check_if_fill
 * @brief this takes an x and a y coordinate as input, adds this point to
 *  a queue. Then runs through queue and adds to the pool vector to be filled
 *  if it is not already a pool. Adds spots to queue in while loop
 */
void gameboard::check_if_fill(int x, int y, bool is_first){

    int n_x, n_y;

    if (is_first){

        // first make sure that the queue is empty
        if (!first_queue.isEmpty())
            first_queue.clear();

        if (!labels[y*board_size+x]->isFilled())
            first_queue.enqueue(QPoint(x,y));

        while(!first_queue.isEmpty()){

            // take first off of the queue
            QPoint next_spot = first_queue.dequeue();
            n_x = next_spot.rx();
            n_y = next_spot.ry();

            // flags the spot as checked by this method
            labels[y*board_size+x]->flag_for_fill();

            // add the processed QPoint to the vector to be filled
            first_pool.push_back(QPoint(n_x,n_y));

            // check left
            if ((n_x-1) >= 0 && labels[n_y*board_size+(n_x-1)]->notFillorFlagged()){
                first_queue.enqueue(QPoint(n_x-1,n_y));
                // flags the spot as checked by this method
                labels[n_y*board_size+(n_x-1)]->flag_for_fill();

                if (labels[n_y*board_size+(n_x-1)]->isAnimal())
                    animal_in_pool1 = true;
            }

            // check down
            if ((n_y+1) < board_size && labels[(n_y+1)*board_size+n_x]->notFillorFlagged()){
                first_queue.enqueue(QPoint(n_x,n_y+1));
                // flags the spot as checked by this method
                labels[(n_y+1)*board_size+n_x]->flag_for_fill();

                if (labels[(n_y+1)*board_size+n_x]->isAnimal())
                    animal_in_pool1 = true;
            }

            // check right
            if ((n_x+1) < board_size && labels[n_y*board_size+(n_x+1)]->notFillorFlagged()){
                first_queue.enqueue(QPoint(n_x+1,n_y));
                // flags the spot as checked by this method
                labels[n_y*board_size+(n_x+1)]->flag_for_fill();

                if (labels[n_y*board_size+(n_x+1)]->isAnimal())
                    animal_in_pool1 = true;
            }

            // check up
            if ((n_y-1) >= 0 && labels[(n_y-1)*board_size+n_x]->notFillorFlagged()){
                first_queue.enqueue(QPoint(n_x,n_y-1));
                // flags the spot as checked by this method
                labels[(n_y-1)*board_size+n_x]->flag_for_fill();

                if (labels[(n_y-1)*board_size+n_x]->isAnimal())
                    animal_in_pool1 = true;
            }
        }
    }
    else{
        // first make sure the queue is empty
        if (!second_queue.isEmpty())
            second_queue.clear();

        if (!labels[y*board_size+x]->isFilled())
            second_queue.enqueue(QPoint(x,y));

        while (!second_queue.isEmpty()){

            //take first off of the queue
            QPoint next_spot = second_queue.dequeue();
            n_x = next_spot.rx();
            n_y = next_spot.ry();

            // flags the spot as checked by this method
            labels[y*board_size+x]->flag_for_fill();

            // add the processed QPoint to the vector to be filled
            second_pool.push_back(QPoint(n_x,n_y));

            // check left
            if (n_x > 1 && labels[n_y*board_size+(n_x-1)]->notFillorFlagged()){
                second_queue.enqueue(QPoint(n_x-1,n_y));
                // flags the spot as checked by this method
                labels[n_y*board_size+(n_x-1)]->flag_for_fill();

                if (labels[n_y*board_size+(n_x-1)]->isAnimal())
                    animal_in_pool2 = true;
            }

            // check down
            if (n_y+1 < board_size && labels[(n_y+1)*board_size+n_x]->notFillorFlagged()){
                second_queue.enqueue(QPoint(n_x,n_y+1));
                // flags the spot as checked by this method
                labels[(n_y+1)*board_size+n_x]->flag_for_fill();

                if (labels[(n_y+1)*board_size+n_x]->isAnimal())
                    animal_in_pool2 = true;
            }

            // check right
            if (n_x < board_size && labels[n_y*board_size+(n_x+1)]->notFillorFlagged()){
                second_queue.enqueue(QPoint(n_x+1,n_y));
                // flags the spot as checked by this method
                labels[n_y*board_size+(n_x+1)]->flag_for_fill();

                if (labels[n_y*board_size+(n_x+1)]->isAnimal())
                    animal_in_pool2 = true;
            }

            // check up
            if (n_y > 1 && labels[(n_y-1)*board_size+n_x]->notFillorFlagged()){
                second_queue.enqueue(QPoint(n_x,n_y-1));
                // flags the spot as checked by this method
                labels[(n_y-1)*board_size+n_x]->flag_for_fill();

                if (labels[(n_y-1)*board_size+n_x]->isAnimal())
                    animal_in_pool2 = true;
            }
        }
    }
}

/** @function fill_fence
 * @brief this funciton takes a vector of QPoint's as input and sets each QPoint to a fence type
 */
void gameboard::fill_fence(std::vector<QPoint> fill_v){

    // fills fence in spots in the vector
    for(auto i : fill_v){
        if (!labels[i.ry()*board_size+(i.rx())]->isSnake())
            labels[i.ry()*board_size+(i.rx())]->setFence();
    }

    // updates the progress and the score
    update_nums();
}

/** @function sheep_hit_hero
 * @brief will call the you_died function unless a hero superpower is used
 */
void gameboard::sheep_hit_hero(int index){
    std::uniform_int_distribution<int> distribution(0,2);
    std::uniform_int_distribution<int> board_dist(0,board_size-1);

    // 1/3 chance of escape for german shepherd
    int chance = distribution(generator);

    // if wolf, it will "eat" the sheep and move it to a random open position on the board
    if (*hero_l_text == ":/pics/wolf.jpg"){

        int new_x, new_y;

        // randomly find a new open position for this sheep
        do{
            new_x = board_dist(generator);
            new_y = board_dist(generator);

        } while(labels[new_y*board_size + new_x]->isFilled());

        // sets the new position of the sheep
        labels[new_y*board_size+new_x]->setSheep();
        labels[sheep_pos[index]->ry()*board_size+sheep_pos[index]->rx()]->setGrass();
        labels[new_y*board_size+new_x]->setPixmap(QPixmap(":/pics/sheep.jpg").scaled(29,29,Qt::KeepAspectRatio));
        labels[sheep_pos[index]->ry()*board_size+sheep_pos[index]->rx()]->setPixmap(QPixmap(":/pics/grass.jpg").scaled(29,29,Qt::KeepAspectRatio));
        sheep_pos[index]->setX(new_x);
        sheep_pos[index]->setY(new_y);
    }
    // else if hero is a german shepherd, there is a 1/3 chance that the character will evade the sheep
    else if (*hero_l_text == ":/pics/german_shepherd.jpg" && chance == 0){
        // do nothing
    }
    else
        you_died("sheep");
}

/** @function sheep_hit_fence
 * @brief calls the you_died fucntion and destroys the tempfence unless a hero superpower is used
 */
void gameboard::sheep_hit_fence(){
    // sets random generation
    std::uniform_int_distribution<int> distribution(0,2);
    int chance = distribution(generator);

    if (*hero_l_text == ":pics/black_lab.jpg" && chance == 0){
        // do nothing
        return;
    }

    you_died("sheep");
}

/** @function snake_hit_hero
 * @brief calls you_died function unless a hero superpower is used
 */
void gameboard::snake_hit_hero(){
    std::uniform_int_distribution<int> distribution(0,2);

    // 1/3 chance for dachshund
    int chance = distribution(generator);

    // if hero is a dach, there is a 1/3 chance that the dach will evade the snake
    if (*hero_l_text == ":/pics/dachshund.jpg" && chance == 0){
        // labels[(y + y_direc)*board_size + (x + x_direc)]->setSnake();
        // labels[y*board_size + x]->setFence();
    }
    else
        you_died("snake");
}

/** @function update_nums
 * @brief updates the QLabels in the gameboard corresponding to the score and the level progress
 */
void gameboard::update_nums(){

    // changes the score in the score_label
    QString new_score_str = QString::number(score_num);
    score_label->setText(new_score_str);

    // changes the value in the prog_label
    QString new_prog_str = QString::number((100*progress)/((board_size-2)*(board_size-2)));
    //QString new_prog_str = QString::number(progress);
    prog_label->setText(new_prog_str);
}

/** @function unpause
 * @brief resumes the game, is called when the unpause button is presssed
 */
void gameboard::unpause(){

    move = true;
    pause_window->hide();
    show();
}

/** @function check_progress
 * @brief does nothing unless progress of 75% is reached, then calls level complete
 */
void gameboard::check_progress(){

    // checks player has reached 75% progress
    if ((100*progress)/((board_size-2)*(board_size-2)) >= 75){
        level_win->show();
        move = 0;
        hide();
    }
}

/** @function next_level
 * @brief sets up the gameboard to be ready for the next level in the game
 */
void gameboard::next_level(){

    // increments the level number
    ++curr_level;
    level_num->setText(QString::number(curr_level));

    // resets the progress on the level but not the score
    progress = 0;
    update_nums();

    initialize_board();
    show();
    level_win->hide();


    // if the player reaches over 75%, next level is called
    if (progress > (75 / (board_size*board_size))){
        next_level();
    }
}

/** @function play_game
 * @brief called when new game is started. sets up first level of the game
 */
void gameboard::play_game(){

    curr_level = 0;
    level_num->setText(QString::number(curr_level));

    // increments curr_level and initializes board with this number
    next_level();

    show();
}
