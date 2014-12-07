#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QtGui>
#include <QListWidget>

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = 0, QMediaPlayer *player = 0);
    ~PlayerWindow();

signals:
    void posChanged(int);

private:
    Ui::PlayerWindow *ui;
    QMediaPlayer *player;
    int max;
private slots:
    void posChange(qint64);
    void showAbout();
    void pickFiles();
    void itemActivated(QListWidgetItem*);
    void pStatusChange(QMediaPlayer::State);
    void mediaChanged(QMediaContent);
    void stop();
    void playPressed();
    void sliderPosChange(int);
};

#endif // PLAYERWINDOW_H
