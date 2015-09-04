#ifndef NO_NEW_SCORE
#define NO_NEW_SCORE

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

class no_new_score : public QWidget
{
    Q_OBJECT

public:
    explicit no_new_score(QWidget *parent=0);
    ~no_new_score();

    void setnobutton(QPushButton* p);
    QPushButton* no_button();

private:
    QPushButton *button;
};

#endif // NO_NEW_SCORE

