// pauseLog.cpp

#include "logs/pauseLog.hpp"
#include <QBoxLayout>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLabel>

brick_game::pauseLog::pauseLog(::QWidget *parent)
    : ::QDialog{parent, Qt::FramelessWindowHint}, parent_{parent} {
  auto general_layout = new ::QVBoxLayout;
  {
    auto pause_lbl = new ::QLabel{"PAUSE"};
    pause_lbl->setObjectName("pauseLog");
    general_layout->addWidget(pause_lbl);
  }
  this->setLayout(general_layout);
}

void brick_game::pauseLog::keyPressEvent(::QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    ::QCoreApplication::sendEvent(parent_, event);
    this->accept();
  }
}
