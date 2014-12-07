#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QMediaPlaylist>
#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QWidget *parent, QMediaPlayer *player) :
    QMainWindow(parent), ui(new Ui::PlayerWindow),
    player(player), max(100000)
{

    ui->setupUi(this);

    ui->progressSlider->setMaximum(max);
    ui->volume->setValue(player->volume());
    player->setNotifyInterval(500);

    // Connect ALL the things
    connect(ui->actionQuit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(ui->actionAbout, SIGNAL(triggered()),  this, SLOT(showAbout()));

    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(posChange(qint64)));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(pStatusChange(QMediaPlayer::State)));

    connect(player->playlist(), SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(mediaChanged(QMediaContent)));

    connect(this, SIGNAL(posChanged(int)), ui->progressSlider, SLOT(setValue(int)));
    connect(ui->progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderPosChange(int)));

    connect(ui->songList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemActivated(QListWidgetItem*)));

    connect(ui->volume, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
    connect(player, SIGNAL(volumeChanged(int)), ui->volume, SLOT(setValue(int)));

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playPressed()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()) );
    connect(ui->mpickButton, SIGNAL(clicked()), this, SLOT(pickFiles()));
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}

void PlayerWindow::posChange(qint64 x)
{
    int e = (((qreal)x/(qreal)player->duration())*max);
    emit posChanged(e);
}

void PlayerWindow::showAbout()
{
    QMessageBox::about(this, "About", "Poulp-o-player... 'Cause fuck heavy weight music players");
}

void PlayerWindow::pickFiles()
{
    QList<QUrl> ret = QFileDialog::getOpenFileUrls(this, "Select Files");
    if(ret.isEmpty()) return;
    for(QUrl q : ret){
        player->playlist()->addMedia(q);
        ui->songList->addItem(q.fileName());
    }
    if(player->media().isNull()){ //Actually useless with playlist?
        player->setMedia(ret.at(0));
        player->play();
    }
    if(player->state()==QMediaPlayer::StoppedState){
        player->play();
    }
}

void PlayerWindow::itemActivated(QListWidgetItem*)
{
    player->playlist()->setCurrentIndex(ui->songList->currentRow());
    player->play();
}

void PlayerWindow::mediaChanged(QMediaContent m)
{
    setWindowTitle("Poulp-o-player - " +m.canonicalUrl().fileName());
    ui->songList->setCurrentRow(player->playlist()->currentIndex());
}

void PlayerWindow::stop()
{ // May actually be useless now! Used to have more stuff in here!!
    player->stop();
}

void PlayerWindow::playPressed()
{
    if(player->state()==QMediaPlayer::PlayingState){
        player->pause();
    } else if(player->state()==QMediaPlayer::PausedState){
        player->play();
    } else if(player->state()==QMediaPlayer::StoppedState){
        if(!player->media().isNull()){
            player->play();
        }
    }
}

void PlayerWindow::sliderPosChange(int x)
{
    if(player->state()==QMediaPlayer::StoppedState){
        ui->progressSlider->setValue(0);
        return;
    }
    qint64 currentPost = ((qreal)x/(qreal)max)*player->duration();
    player->setPosition(currentPost);
}

void PlayerWindow::pStatusChange(QMediaPlayer::State s)
{
    if(s==QMediaPlayer::PlayingState) {
        ui->playButton->setText("Pause");
    } else if (s==QMediaPlayer::PausedState) {
        ui->playButton->setText("Play");
    } else if (s==QMediaPlayer::StoppedState) {
        ui->playButton->setText("Play");
        ui->progressSlider->setValue(0);
    }
}
