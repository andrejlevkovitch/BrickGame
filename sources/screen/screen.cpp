// screen.cpp

#include "screen/screen.hpp"
#include "screen/pix.hpp"
#include <QBoxLayout>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>

#include <QDebug>

brick_game::screen::screen(::QWidget *parent) : ::QWidget{parent} {
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
  this->setSizePolicy(::QSizePolicy::Policy::Fixed,
                      ::QSizePolicy::Policy::Fixed);
  ::qDebug() << "created screen";
}

void brick_game::screen::restore() {
  this->clear_field(FIELD_SIZE);
  this->clear_field(MINI_FIELD_SIZE, MINI_SCR_BGN);

  ::qDebug() << "screen restored";
}

void brick_game::screen::clear_field(::QSize size, ::QPoint pos) const {
  for (int i = 0; i < size.height(); ++i) {
    for (int j = 0; j < size.width(); ++j) {
      emit reciver(pos + ::QPoint{j, i}, Value::NONE);
    }
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
