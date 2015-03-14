#ifndef ADD_NEW_SCORE
#define ADD_NEW_SCORE

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPushButton>

class add_new_score : public QWidget
{
    Q_OBJECT
public slots:
    void confirm_score();
public:
    explicit add_new_score(QWidget *parent=0);

    void setconfirmbutton(QPushButton* p);
    QPushButton* confirm_button();

    int score_num;

private:
    QString name_text;

    QFile file;

    int first_score;
    int second_score;
    int third_score;
    int fourth_score;
    int fifth_score;

    QString *first_name;
    QString *second_name;
    QString *third_name;
    QString *fourth_name;
    QString *fifth_name;

    QPushButton *confirm;

};

#endif // ADD_NEW_SCORE

