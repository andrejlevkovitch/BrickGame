// player.cpp

#include "player/player.hpp"
#include <QMediaPlayer>

#include <QDebug>

brick_game::player::player(::QObject *parent)
    : ::QObject{parent}, player_{new ::QMediaPlayer{this}}, soundless_{false} {
  ::qDebug() << "creates player";
}

void brick_game::player::set_sounds(const ::QUrl &begin_theme,
                                    const ::QUrl &activity, const ::QUrl &score,
                                    const ::QUrl &level_up) {
  begin_theme_ = begin_theme;
  activity_ = activity;
  score_ = score;
  level_up_ = level_up;
  player_->setMedia(::QUrl{""});
  ::qDebug() << "set next sounds:" << begin_theme_ << activity_ << score_
             << level_up_;
}

void brick_game::player::remove_sound() {
  if (soundless_) {
    soundless_ = false;
    ::qDebug() << "sound on";
  } else {
    soundless_ = true;
    player_->stop();
    ::qDebug() << "sound off";
  }
}

void brick_game::player::begin_theme() {
  if (!soundless_ && !begin_theme_.isEmpty()) {
    player_->stop();
    player_->setMedia(begin_theme_);
    player_->play();
  }
}

void brick_game::player::activity() {
  if (!soundless_ && !activity_.isEmpty()) {
    if (player_->state() != ::QMediaPlayer::State::PlayingState) {
      player_->stop();
      player_->setMedia(activity_);
      player_->play();
    }
  }
}

void brick_game::player::score_changed() {
  if (!soundless_ && !score_.isEmpty()) {
    if (player_->state() != ::QMediaPlayer::State::PlayingState) {
      player_->stop();
      player_->setMedia(score_);
      player_->play();
    }
  }
}

void brick_game::player::level_up() {
  if (!soundless_ && !level_up_.isEmpty()) {
    player_->stop();
    player_->setMedia(level_up_);
    player_->play();
  }
}

void brick_game::player::pause(bool status) {
  if (!status) {
    if (!soundless_ && player_->state() == ::QMediaPlayer::State::PausedState) {
      player_->play();
    }
  } else {
    player_->pause();
  }
}

void brick_game::player::stop() { player_->stop(); }
