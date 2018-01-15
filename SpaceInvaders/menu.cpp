#include "menu.h"
#include <QHBoxLayout>
#include <QFont>


namespace game {
Menu::Menu(QWidget* parent, QString name, int& playerScore, QList<QPair<QString, int>> scores)
        : gameScore(playerScore) {
    // Scores could be read in the future.
    makeButtons(parent, name);
}

Menu::~Menu() {
    delete score;
    delete playerName;
    delete playerScoreLabel;
}

void Menu::makeButtons(QWidget* parent, QString name) {
    score = new QPushButton("Score", parent);
    score->setGeometry(QRect(0, 0, 100, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: red");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    playerName = new QLabel(parent);
    playerName->setGeometry(0, 30, 100, 30);
    playerName->setText(name);
    playerName->setVisible(false);
    playerName->setStyleSheet("background-color: white");

    playerScoreLabel = new QLabel(parent);
    playerScoreLabel->setGeometry(100, 30, 100, 30);
    playerScoreLabel->setText(QString::number(gameScore));
    playerScoreLabel->setVisible(false);
    playerScoreLabel->setStyleSheet("background-color: gray");

    //configure the difficulty setting menu
    QFont difficultySettingFont( "Arial", 22, QFont::Bold);
    difficultySetting = new QLabel(parent);
    difficultySetting->setGeometry((parent->width()/2)-100,parent->height()/2
                                   ,500,100);
    difficultySetting->setFont(difficultySettingFont);
    difficultySetting->setText("DIFFICULTY SETTING");
    difficultySetting->setVisible(false);
    difficultySetting->setStyleSheet("background-color: yellow");
    difficultySetting->setAlignment(Qt::AlignTop| Qt::AlignHCenter);

    //add 3 options of difficulty to the difficulty setting option
    veryEasy = new QPushButton("VERY EASY", difficultySetting);
    veryEasy->setGeometry(QRect(10,difficultySetting->height()/2,100,40));
    veryEasy->setVisible(false);
    veryEasy->setStyleSheet("background-color: #66ccff");
    QObject::connect(veryEasy, SIGNAL(released()), parent, SLOT(setVeryEasyMode()));

    easy = new QPushButton("EASY", difficultySetting);
    easy ->setGeometry(QRect(130,difficultySetting->height()/2,100,40));
    easy ->setVisible(false);
    easy ->setStyleSheet("background-color: #00b300");
    QObject::connect(easy, SIGNAL(released()), parent, SLOT(setEasyMode()));

    normal = new QPushButton("NORMAL", difficultySetting);
    normal ->setGeometry(QRect(250,difficultySetting->height()/2,100,40));
    normal ->setVisible(false);
    normal ->setStyleSheet("background-color: #ff9900");
    QObject::connect(normal, SIGNAL(released()), parent, SLOT(setNormalMode()));

    hard = new QPushButton("HARD", difficultySetting);
    hard ->setGeometry(QRect(370,difficultySetting->height()/2,100,40));
    hard ->setVisible(false);
    hard ->setStyleSheet("background-color: #ff3300");
    QObject::connect(hard, SIGNAL(released()), parent, SLOT(setHardMode()));
}

// called when game is paused or unpaused
void Menu::displayMenu(bool paused) {
    if (!paused) {
        closeButtons();
    } else {
        score->setVisible(true);
        revealPlayerScore(true);
        difficultySetting->setVisible(true);
        veryEasy->setVisible(true);
        easy->setVisible(true);
        normal->setVisible(true);
        hard->setVisible(true);
    }
}

// helper, closes all the opened menus
void Menu::closeButtons() {
    score->setVisible(false);
    revealPlayerScore(false);
    difficultySetting->setVisible(false);
    veryEasy->setVisible(false);
    easy->setVisible(false);
    normal->setVisible(false);
    hard->setVisible(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
    playerScoreLabel->setText(QString::number(gameScore));
    playerName->setVisible(open);
    playerScoreLabel->setVisible(open);
}

void Menu::openScore() {
    if (playerName->isVisible()) {
        revealPlayerScore(false);
    } else {
        revealPlayerScore(true);
    }
}
}
