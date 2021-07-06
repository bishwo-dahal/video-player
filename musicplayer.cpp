#include "musicplayer.h"
#include "ui_musicplayer.h"

musicPlayer::musicPlayer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::musicPlayer)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::durationChanged, this, &musicPlayer::onDurationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &musicPlayer::onPositionChanged);
    video = new QVideoWidget(ui->media);
    QVBoxLayout *layout = new QVBoxLayout(ui->media);
    layout->addWidget(video);
    layout->setMargin(0);
    ui->media->setLayout(layout);
    player->setVideoOutput(video);
    setAcceptDrops(true);
}

musicPlayer::~musicPlayer()
{
    delete ui;
}

void musicPlayer::on_actionOpen_triggered()
{
    QUrl fileName = QFileDialog::getOpenFileUrl(this, "Select media here", QUrl(""), "Audio/Video files (*.mp4 *.mp3)");
    setFile(fileName.toString());
}

void musicPlayer::on_volume_valueChanged(int value)
{
    player->setVolume(value);
    ui->volumeLabel->setText("Volume: " + QString::number(value) + "%");
}

void musicPlayer::on_slider_valueChanged(int value)
{
    player->setPosition(value);
}

void musicPlayer::onDurationChanged(qint64 duration)
{
    ui->slider->setMaximum(duration);
}

void musicPlayer::onPositionChanged(qint64 position)
{
    ui->slider->setValue(position);
    ui->media->showFullScreen();
}
//D:\Projects\projects 2021-7-3\QT\music-player



void musicPlayer::on_play_clicked()
{
    player->play();
}

void musicPlayer::on_pause_clicked()
{
    player->pause();
}

void musicPlayer::on_fullScreen_clicked()
{
    if(!musicPlayer::isFullScreen()){
        showFullScreen();
    }else{
        showNormal();
    }

}

void musicPlayer::on_videoFullScreen_clicked()
{
    if(!ui->media->isFullScreen()){
        ui->media->showFullScreen();
    }else{
        ui->media->showNormal();
    }
}

void musicPlayer::dragEnterEvent(QDragEnterEvent *event){
    qDebug()<<event->mimeData()->urls().front().toString();
    setFile(event->mimeData()->urls().front().toString());
}

void musicPlayer::setFile(QString file)
{
    if (file.isEmpty())
    {
        QMessageBox::warning(this, "Could not open file", "Please provide valid url");
    }
    else
    {
        ui->currentMedia->setText(file);
        player->setMedia(QUrl(file));
        player->play();
        ui->volume->setValue(50);
        player->setVolume(50);
    }
}
