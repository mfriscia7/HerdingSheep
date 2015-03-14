#ifndef QSQUARE
#define QSQUARE
#include <QLabel>

class QSquare : public QLabel
{
    Q_OBJECT

public:
    QSquare();
    void setFence();
    void setSheep();
    void setHero();
    void setGrass();
    void setSnake();
    void setTempFence();

    bool isFence() {return fence;}
    bool isSheep() {return sheep;}
    bool isHero() {return hero;}
    bool isSnake() {return snake;}
    bool isTempFence() {return tempFence;}

    bool isFilled() {return (fence || sheep || snake || tempFence || hero);}

    bool continue_run() {return (!fence && !tempFence && !hero);}

private:
    bool fence;
    bool hero;
    bool sheep;
    bool snake;
    bool tempFence;

};

#endif // QSQUARE
