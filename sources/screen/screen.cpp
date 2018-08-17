// screen.cpp

#include "screen/screen.hpp"
#include "abstractGame/abstractGame.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include "screen/pix.hpp"
#include <QBoxLayout>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>

brick_game::screen::screen(::QWidget *parent)
    : ::QWidget{parent}, cur_game_{nullptr}, is_running_{false} {
  auto general_layout = new ::QHBoxLayout;
  {
    auto rhs_layout = new ::QVBoxLayout;
    {
      auto level_lbl = new ::QLabel{"LEVEL"};
      auto level_display = new ::QLCDNumber;
      level_display->setDigitCount(LEVEL_DIGIN_COUNT);
      connect(this, SIGNAL(set_level(int)), level_display, SLOT(display(int)));
      level_lbl->setBuddy(level_display);

      auto score_lbl = new ::QLabel{"SCORE"};
      auto score_display = new ::QLCDNumber;
      score_display->setDigitCount(SCORE_DIGIN_COUNT);
      connect(this, SIGNAL(set_score(int)), score_display, SLOT(display(int)));
      score_lbl->setBuddy(score_display);

      rhs_layout->addWidget(create_field(MINI_FIELD_SIZE, MINI_SCR_BGN));
      rhs_layout->addWidget(level_lbl);
      rhs_layout->addWidget(level_display);
      rhs_layout->addWidget(score_lbl);
      rhs_layout->addWidget(score_display);
    }
    general_layout->addWidget(create_field(FIELD_SIZE));
    general_layout->addLayout(rhs_layout);
  }
  this->setLayout(general_layout);
}

void brick_game::screen::set_game(brick_game::abstractGame *game) {
  cur_game_ = game;
  this->clear_field(FIELD_SIZE);
  this->clear_field(MINI_FIELD_SIZE, MINI_SCR_BGN);
  if (!cur_game_) {
    return;
  }
  connect(game, SIGNAL(changed(::QPoint, Value)), this,
          SIGNAL(reciver(::QPoint, Value)));
  connect(game, SIGNAL(send_level(int)), this, SIGNAL(set_level(int)));
  connect(game, SIGNAL(send_score(int)), this, SIGNAL(set_score(int)));

  connect(game, SIGNAL(end_game_signal()), this, SLOT());

  connect(this, SIGNAL(start_game_signal()), game, SLOT(start_game_slot()));
  connect(this, SIGNAL(finish_game_signal()), game, SLOT(finish_game_slot()));
}

void brick_game::screen::clear_field(::QSize size, ::QPoint pos) const {
  for (int i = 0; i < size.height(); ++i) {
    for (int j = 0; j < size.width(); ++j) {
      emit reciver(pos + ::QPoint{j, i}, Value::NONE);
    }
  }
}

void brick_game::screen::keyPressEvent(::QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Up:
    if (cur_game_ != nullptr && is_running_) {
      directionEvent event{Direction::UP};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Down:
    if (cur_game_ != nullptr && is_running_) {
      directionEvent event{Direction::DOWN};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Right:
    if (cur_game_ != nullptr && is_running_) {
      directionEvent event{Direction::RIGHT};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Left:
    if (cur_game_ != nullptr && is_running_) {
      directionEvent event{Direction::LEFT};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Space:
    if (cur_game_ != nullptr && is_running_) {
      pauseEvent event;
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Escape:
    if (cur_game_ != nullptr) {
      is_running_ = false;
      emit finish_game_signal();
      this->clear_field(FIELD_SIZE);
      this->clear_field(MINI_FIELD_SIZE, MINI_SCR_BGN);
    }
    break;
  case Qt::Key_Execute:
  case Qt::Key_Eject:
  case Qt::Key_Enter:
  case Qt::Key_E:
    if (cur_game_ != nullptr) {
      if (is_running_) {
        emit finish_game_signal();
      }
      is_running_ = true;
      this->clear_field(FIELD_SIZE);
      this->clear_field(MINI_FIELD_SIZE, MINI_SCR_BGN);
      emit start_game_signal();
    }
    break;
  default:
    break;
  }
}

::QWidget *brick_game::screen::create_field(::QSize size, ::QPoint pos) const {
  auto field_layout = new ::QGridLayout;
  field_layout->setSpacing(0);
  field_layout->setContentsMargins(0, 0, 0, 0);
  for (int i = 0; i < size.height(); ++i) {
    for (int j = 0; j < size.width(); ++j) {
      auto pix = new brick_game::pix{pos + ::QPoint{j, i}};
      connect(this, SIGNAL(reciver(::QPoint, Value)), pix,
              SLOT(change(::QPoint, Value)));
      field_layout->addWidget(pix, i, j);
    }
  }
  auto retval = new ::QWidget;
  retval->setLayout(field_layout);
  return retval;
}
