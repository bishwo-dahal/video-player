#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMainWindow>
#include<QtMultimedia/QMediaPlayer>
#include<QVideoWidget>
#include<QFile>
#include<QFileDialog>
#include<QUrl>
#include<QMessageBox>
#include<QDebug>
#include<QVBoxLayout>
#include<QDrag>
#include<QDragEnterEvent>
#include<QMimeData>



QT_BEGIN_NAMESPACE
namespace Ui { class musicPlayer; }
QT_END_NAMESPACE

class musicPlayer : public QMainWindow
{
    Q_OBJECT

public:
    musicPlayer(QWidget *parent = nullptr);
    ~musicPlayer();
    void setFile(QString file);

private slots:
    void on_actionOpen_triggered();

    void on_volume_valueChanged(int value);
    void on_slider_valueChanged(int value);

    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void on_play_clicked();

    void on_pause_clicked();

    void on_fullScreen_clicked();

    void on_videoFullScreen_clicked();
    void dragEnterEvent(QDragEnterEvent *event)override;

private:
    Ui::musicPlayer *ui;
    QMediaPlayer *player;
    bool isPaused;
    QVideoWidget *video;
};
#endif // MUSICPLAYER_H
