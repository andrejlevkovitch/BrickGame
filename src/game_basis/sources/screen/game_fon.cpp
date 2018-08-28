// game_fon.cpp

#include "screen/game_fon.hpp"
#include <QPaintEvent>
#include <QPainter>

#include <QDebug>

brick_game::game_fon::game_fon(::QWidget *parent)
    : ::QWidget{parent}, fon_{":/image/paper.png"} {
  ::qDebug() << "created fon widget";
}

void brick_game::game_fon::paintEvent(::QPaintEvent *pevent) {
  if (!fon_.isNull()) {
    ::QPainter painter{this};
    auto temp =
        fon_.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
    painter.drawImage(0, 0, temp);
  }
}
