#include "QSquare.h"

// constructor
QSquare::QSquare(){
    fence = false;
    tempFence = false;
    sheep = false;
    hero = false;
    snake = false;
}

/*** @function setFence
 * @brief sets the QSquare to be considered a fence square
 */
void QSquare::setFence(){
    fence = true;
    sheep = false;
    tempFence = false;
    hero = false;
    snake = false;
    setPixmap(QPixmap(":/pics/fence.jpg").scaled(29,29,Qt::KeepAspectRatio));
}

/** @function setSheep
 * @brief sets the QSquare to be considered a sheep square, called when sheep is added or moved
 */
void QSquare::setSheep(){
    sheep = true;
    hero = false;
    fence = false;
}

/** @function setHero
 * @brief sets the QSquare to be considered a hero square
 */
void QSquare::setHero(){
    hero = true;
    sheep = false;
    snake = false;
}

/** @function seGrass
 * @brief sets the QSquare to be considered a grass square
 */
void QSquare::setGrass(){
    fence = false;
    hero = false;
    sheep = false;
    tempFence = false;
    setPixmap(QPixmap(":/pics/grass.jpg").scaled(29,29,Qt::KeepAspectRatio));
}

/** @function setSnake
 * @brief sets the QSquare to be considered a snake square
 */
void QSquare::setSnake(){
    tempFence = false;
    hero = false;
    fence = false;
    snake = true;
    setPixmap(QPixmap(":/pics/snake.jpg").scaled(29,29,Qt::KeepAspectRatio));
}

/** @function setTempFence
 * @brief sets the QSquare to be considered a TempFence square
 */
void QSquare::setTempFence(){
    tempFence = true;
    hero = false;
    setPixmap(QPixmap(":/pics/fence.jpg").scaled(29,29,Qt::KeepAspectRatio));
}


