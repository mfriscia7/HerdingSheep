#ifndef PAUSEWINDOW
#define PAUSEWINDOW

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

class PauseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PauseWindow(QWidget *parent=0);

    void setunpausebutton(QPushButton* p);
    QPushButton* unpause_button();

private:
    QPushButton* button;
    int score;
};


#endif // PAUSEWINDOW

