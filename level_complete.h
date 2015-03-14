#ifndef LEVEL_COMPLETE_H
#define LEVEL_COMPLETE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

class level_complete : public QWidget
{
    Q_OBJECT
public slots:
    QPushButton* confirm_button();
public:
    explicit level_complete(QWidget *parent=0);
    void setconfirmbutton(QPushButton* p);

private:

    QPushButton *confirm;

};

#endif // LEVEL_COMPLETE_H

