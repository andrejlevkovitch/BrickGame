// screen.cpp

#include "screen/screen.hpp"
#include "screen/game_fon.hpp"
#include "screen/pix.hpp"
#include <QBoxLayout>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>

#include <QDebug>

int brick_game::screen::LEVEL_DIGIN_COUNT() { return 2; }

int brick_game::screen::SCORE_DIGIN_COUNT() { return 6; }

brick_game::screen::screen(::QWidget *parent)
    : ::QWidget{parent}, general_pixarr_(FIELD_SIZE.height(),
                                         decltype(general_pixarr_)::value_type(
                                             FIELD_SIZE.width(), nullptr)),
      dop_pixarr_(MINI_FIELD_SIZE.height(),
                  decltype(general_pixarr_)::value_type(MINI_FIELD_SIZE.width(),
                                                        nullptr)) {
  auto general_layout = new ::QHBoxLayout;
  {
    auto rhs_layout = new ::QVBoxLayout;
    {
      auto level_lbl = new ::QLabel{"LEVEL"};
      level_lbl->setObjectName("level_lbl");
      auto level_display = new ::QLCDNumber;
      level_display->setDigitCount(LEVEL_DIGIN_COUNT());
      connect(this, SIGNAL(set_level(int)), level_display, SLOT(display(int)));
      level_lbl->setBuddy(level_display);

      auto score_lbl = new ::QLabel{"SCORE"};
      score_lbl->setObjectName("score_lbl");
      auto score_display = new ::QLCDNumber;
      score_display->setDigitCount(SCORE_DIGIN_COUNT());
      connect(this, SIGNAL(set_score(int)), score_display, SLOT(display(int)));
      score_lbl->setBuddy(score_display);

      auto mini_field = create_dop_field();
      mini_field->setSizePolicy(::QSizePolicy::Policy::Fixed,
                                ::QSizePolicy::Policy::Fixed);

      rhs_layout->addWidget(mini_field);
      rhs_layout->addWidget(level_lbl);
      rhs_layout->addWidget(level_display);
      rhs_layout->addWidget(score_lbl);
      rhs_layout->addWidget(score_display);
    }
    general_layout->addWidget(create_general_field());
    general_layout->addLayout(rhs_layout);
  }
  this->setLayout(general_layout);
  ::qDebug() << "created screen";
}

::QWidget *brick_game::screen::create_general_field() {
  auto field_layout = new ::QGridLayout;
  field_layout->setSpacing(0);
  field_layout->setContentsMargins(0, 0, 0, 0);
  for (int i = 0; i < FIELD_SIZE.height(); ++i) {
    for (int j = 0; j < FIELD_SIZE.width(); ++j) {
      general_pixarr_[i][j] = new brick_game::pix;
      connect(this, &screen::clear_all, general_pixarr_[i][j], &pix::change);
      field_layout->addWidget(general_pixarr_[i][j], i, j);
    }
  }
  auto retval = new brick_game::game_fon;
  retval->setLayout(field_layout);
  return retval;
}

::QWidget *brick_game::screen::create_dop_field() {
  auto field_layout = new ::QGridLayout;
  field_layout->setSpacing(0);
  field_layout->setContentsMargins(0, 0, 0, 0);
  for (int i = 0; i < MINI_FIELD_SIZE.height(); ++i) {
    for (int j = 0; j < MINI_FIELD_SIZE.width(); ++j) {
      dop_pixarr_[i][j] = new brick_game::pix;
      connect(this, &screen::clear_all, dop_pixarr_[i][j], &pix::change);
      field_layout->addWidget(dop_pixarr_[i][j], i, j);
    }
  }
  auto retval = new ::QWidget;
  retval->setLayout(field_layout);
  retval->setObjectName("miniField");
  retval->setFixedSize(retval->sizeHint());
  return retval;
}
