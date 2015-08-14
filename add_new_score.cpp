#include "add_new_score.h"
#include <QDebug>


// constructor
add_new_score::add_new_score(QWidget *parent) : QWidget(parent){

    //High Scores
    //names
    file.setFileName("high_scores.txt");
    QTextStream in(&file);
    file.open(QFile::ReadOnly | QFile::Text);

    first_name = in.readLine().split(" ")[1];
    QString *first = new QString(in.readLine());
    second_name = in.readLine().split(" ")[1];
    QString *second = new QString(in.readLine());
    third_name = in.readLine().split(" ")[1];
    QString *third = new QString(in.readLine());
    fourth_name = in.readLine().split(" ")[1];
    QString *fourth = new QString(in.readLine());
    fifth_name = in.readLine().split(" ")[1];
    QString *fifth = new QString(in.readLine());

    file.close();

    //convert scores to ints
    first_score = first->toInt();
    second_score = second->toInt();
    third_score = third->toInt();
    fourth_score = fourth->toInt();
    fifth_score = fifth->toInt();


    // creates main window
    setFixedSize(550,200);

    // takes away close, minimize, etc. buttons
    setWindowFlags(Qt::CustomizeWindowHint);

    // makes the main layout
    QVBoxLayout *layout = new QVBoxLayout;

    // header
    QLabel *header = new QLabel("New High Score!!!");
    header->setAlignment(Qt::AlignCenter);

    // header font
    QFont header_font("Courier", 36);
    header->setFont(header_font);

    // box where player can input text
    name_here = new QInputDialog();
    name_here->setOption(QInputDialog::NoButtons);
    name_here->setLabelText("Type your name below to save high score (no spaces):");

    // enter button to return to home screen
    QPushButton *confirm = new QPushButton("Confirm");
    setconfirmbutton(confirm);

    layout->addWidget(header);
    layout->addWidget(name_here);
    layout->addWidget(confirm);
    setLayout(layout);
}

/** @function setconfirmbutton
 * @brief sets the member variable to a confirm score button so that it can be called by the gameboard
 */
void add_new_score::setconfirmbutton(QPushButton* p){
    confirm = p;
}

/** @function play_button
 * @brief returns play button so that main can access it
 */
QPushButton* add_new_score::confirm_button(){
    return confirm;
}

/** @function confirm score
 * @brief when confirm button is pressed, this function will reset high score file with new high score
 */
void add_new_score::confirm_score(){

    name_text = name_here->textValue().split(" ")[0];

    //opens the file to write to
    //QFile file("high_scores.txt");
    //truncate will clear the file so it can be rewritten
    file.setFileName("high_scores.txt");

    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)){
        QTextStream out(&file);
        if (score_num > first_score){
            out << "1. " << name_text << "\n";
            out << score_num << "\n";
            out << "2. " << first_name << "\n";
            out << first_score << "\n";
            out << "3. " << second_name << "\n";
            out << second_score << "\n";
            out << "4. " << third_name << "\n";
            out << third_score << "\n";
            out << "5. " << fourth_name << "\n";
            out << fourth_score;

            fifth_name = fourth_name;
            fourth_name = third_name;
            third_name = second_name;
            second_name = first_name;
            first_name = name_text;

            fifth_score = fourth_score;
            fourth_score = third_score;
            third_score = second_score;
            second_score = first_score;
            first_score = score_num;

        }
        else if(score_num > second_score){
            out << "1. " << first_name << "\n";
            out << first_score << "\n";
            out << "2. " << name_text << "\n";
            out << score_num << "\n";
            out << "3. " << second_name << "\n";
            out << second_score << "\n";
            out << "4. " << third_name << "\n";
            out << third_score << "\n";
            out << "5. " << fourth_name << "\n";
            out << fourth_score;

            fifth_name = fourth_name;
            fourth_name = third_name;
            third_name = second_name;
            second_name = name_text;

            fifth_score = fourth_score;
            fourth_score = third_score;
            third_score = second_score;
            second_score = score_num;
        }
        else if(score_num > third_score){
            out << "1. " << first_name << "\n";
            out << first_score << "\n";
            out << "2. " << second_name << "\n";
            out << second_score << "\n";
            out << "3. " << name_text << "\n";
            out << score_num << "\n";
            out << "4. " << third_name << "\n";
            out << third_score << "\n";
            out << "5. " << fourth_name << "\n";
            out << fourth_score;

            fifth_name = fourth_name;
            fourth_name = third_name;
            third_name = name_text;

            fifth_score = fourth_score;
            fourth_score = third_score;
            third_score = score_num;
        }
        else if(score_num > fourth_score){
            out << "1. " << first_name << "\n";
            out << first_score << "\n";
            out << "2. " << second_name << "\n";
            out << second_score << "\n";
            out << "3. " << third_name << "\n";
            out << third_score << "\n";
            out << "4. " << name_text << "\n";
            out << score_num << "\n";
            out << "5. " << fourth_name << "\n";
            out << fourth_score;

            fifth_name = fourth_name;
            fourth_name = name_text;

            fifth_score = fourth_score;
            fourth_score = score_num;
        }
        else{
            out << "1. " << first_name << "\n";
            out << first_score << "\n";
            out << "2. " << second_name << "\n";
            out << second_score << "\n";
            out << "3. " << third_name << "\n";
            out << third_score << "\n";
            out << "4. " << fourth_name << "\n";
            out << fourth_score << "\n";
            out << "5. " << name_text << "\n";
            out << score_num;

            fifth_name = name_text;

            fifth_score = score_num;
        }
        file.close();
    }else{
        qDebug() << file.errorString();
    }

    // hides the new score window
    hide();
}
