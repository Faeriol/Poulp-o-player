#include "playerwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QSystemTrayIcon tray;
    //tray.show();
    QMediaPlayer player;
    player.setVolume(100);
    QMediaPlaylist myList;
    player.setPlaylist(&myList);
    PlayerWindow w(0, &player);
    w.show();


    return a.exec();
}
