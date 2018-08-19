// general_window.cpp

#include "general/general_window.hpp"
#include "abstractGame/abstractGame.hpp"
#include "abstractGame/simplExempl.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include "logs/endDialog.hpp"
#include "logs/pauseLog.hpp"
#include "player/player.hpp"
#include "recordTable/recordTable.hpp"
#include "screen/screen.hpp"
#include "tetramino/tetramino.hpp"
#include <QAction>
#include <QBoxLayout>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <QDebug>
#include <QtGlobal>

brick_game::general_window::general_window(::QWidget *parent)
    : ::QWidget{parent}, screen_{nullptr}, cur_game_{nullptr},
      record_table_{nullptr}, player_{nullptr} {
  player_ = new brick_game::player{this};
  screen_ = new brick_game::screen;
  record_table_ = new brick_game::recordTable{this};

  pause_log_ = new brick_game::pauseLog{this};
  end_dialog_ = new brick_game::endDialog{this};
  end_dialog_->setRecordTable(record_table_);

  connect(this, SIGNAL(set_game_signal(brick_game::abstractGame *)), this,
          SLOT(set_game_slot(brick_game::abstractGame *)));

  auto general_layout = new ::QVBoxLayout;
  {
    auto status_bar = new ::QStatusBar;
    {
      connect(this, &brick_game::general_window::set_game_signal, status_bar,
              [=](abstractGame *game) {
                Q_CHECK_PTR(game);
                status_bar->showMessage(game->game_name());
                ::qDebug() << "game name: " + game->game_name();
              });
    }
    auto menu_bar = new ::QMenuBar;
    {
      auto game_menu = new ::QMenu{"Games"};
      {
        auto simpl_exempl_action = new ::QAction{"simplExempl", game_menu};
        {
          connect(simpl_exempl_action, &::QAction::triggered, this, [=]() {
            player_->stop();
            player_->set_sounds(::QUrl{}, ::QUrl{"qrc:/audio/activity.mp3"},
                                ::QUrl{}, ::QUrl{});
            emit set_game_signal(new brick_game::simplExempl);
          });
        }
        auto tetramino_action = new ::QAction{"tetramino", game_menu};
        {
          connect(tetramino_action, &::QAction::triggered, this, [=]() {
            player_->stop();
            player_->set_sounds(::QUrl{"qrc:/audio/tetramino_theme.mp3"},
                                ::QUrl{"qrc:/audio/activity.mp3"},
                                ::QUrl{"qrc:/audio/score.mp3"},
                                ::QUrl{"qrc:/audio/level_up.mp3"});
            emit set_game_signal(new brick_game::tetramino);
          });
        }
        game_menu->addAction(simpl_exempl_action);
        game_menu->addAction(tetramino_action);
      }
      auto sound_action =
          new ::QAction{::QPixmap{":/image/sound.png"}, "sound", menu_bar};
      {
        connect(sound_action, SIGNAL(triggered()), player_,
                SLOT(remove_sound()));
      }
      auto record_table_action = new ::QAction{::QPixmap{":/image/list.png"},
                                               "Record Table", menu_bar};
      {
        connect(record_table_action, &::QAction::triggered, this, [=]() {
          endDialog end_dialog;
          end_dialog.setRecordTable(record_table_);
          ::qDebug() << "open record table";
          end_dialog.exec();
        });
      }
      menu_bar->addMenu(game_menu);
      menu_bar->addAction(sound_action);
      menu_bar->addAction(record_table_action);
    }
    general_layout->addWidget(menu_bar);
    general_layout->addWidget(screen_);
    general_layout->addWidget(status_bar);
  }
  this->setLayout(general_layout);

  ::qDebug() << "created general_window";
}

brick_game::general_window::~general_window() {
  if (cur_game_) {
    delete cur_game_;
  }
}

void brick_game::general_window::keyPressEvent(::QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_W:
  case Qt::Key_K:
  case Qt::Key_Up:
    if (cur_game_ != nullptr) {
      directionEvent event{Direction::UP};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_S:
  case Qt::Key_J:
  case Qt::Key_Down:
    if (cur_game_ != nullptr) {
      directionEvent event{Direction::DOWN};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_D:
  case Qt::Key_L:
  case Qt::Key_Right:
    if (cur_game_ != nullptr) {
      directionEvent event{Direction::RIGHT};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_A:
  case Qt::Key_H:
  case Qt::Key_Left:
    if (cur_game_ != nullptr) {
      directionEvent event{Direction::LEFT};
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Space:
    if (cur_game_ != nullptr) {
      pauseEvent event;
      ::QCoreApplication::sendEvent(cur_game_, &event);
    }
    break;
  case Qt::Key_Escape:
    if (cur_game_ != nullptr) {
      ::qDebug() << "emit finish game signal";
      emit finish_game_signal();
      screen_->restore();
    }
    break;
  case Qt::Key_Enter:
  case Qt::Key_Return:
  case Qt::Key_E:
    if (cur_game_ != nullptr) {
      screen_->restore();
      ::qDebug() << "emit start game signal";
      emit start_game_signal();
    }
    break;
  default:
    break;
  }
}

void brick_game::general_window::set_game_slot(abstractGame *game) {
  Q_CHECK_PTR(game);
  ::qDebug() << "begin connecting game";
  if (cur_game_) {
    delete cur_game_;
    cur_game_ = nullptr;
  }
  cur_game_ = game;
  screen_->restore();
  if (record_table_) {
    record_table_->set_file_name(::QString{"/."} + cur_game_->game_name() +
                                 ::QString{"_record_table.xml"});
  }

  connect(this, SIGNAL(start_game_signal()), cur_game_,
          SLOT(start_game_slot()));
  connect(this, SIGNAL(finish_game_signal()), cur_game_,
          SLOT(finish_game_slot()));

  connect(this, SIGNAL(start_game_signal()), player_, SLOT(begin_theme()));
  connect(cur_game_, SIGNAL(end_game_signal()), player_, SLOT(stop()));
  connect(cur_game_, SIGNAL(send_level(int)), player_, SLOT(level_up()));
  connect(cur_game_, SIGNAL(send_score(int)), player_, SLOT(score_changed()));
  connect(cur_game_, SIGNAL(pause_signal(bool)), player_, SLOT(pause(bool)));
  connect(cur_game_, SIGNAL(activity()), player_, SLOT(activity()));

  connect(cur_game_, SIGNAL(changed(::QPoint, Value)), screen_,
          SIGNAL(reciver(::QPoint, Value)));
  connect(cur_game_, SIGNAL(send_level(int)), screen_, SIGNAL(set_level(int)));
  connect(cur_game_, SIGNAL(send_score(int)), screen_, SIGNAL(set_score(int)));

  connect(cur_game_, &brick_game::abstractGame::pause_signal, pause_log_,
          [=](bool status) {
            if (status) {
              ::qDebug() << "open pauseLog";
              pause_log_->exec();
            }
          });
  connect(cur_game_, &brick_game::abstractGame::end_game_signal, end_dialog_,
          [=](unsigned short level, unsigned score) {
            end_dialog_->setDate(level, score);
            ::qDebug() << "open endDialog";
            end_dialog_->exec();
          });

  ::qDebug() << "end connecting game";
}
