// general_window.cpp

#include "general_window.hpp"
#include "abstractGame/abstractGame.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include "logs/endDialog.hpp"
#include "logs/pauseLog.hpp"
#include "player/player.hpp"
#include "recordTable/recordTable.hpp"
#include "screen/pix.hpp"
#include "screen/screen.hpp"
#include <QAction>
#include <QBoxLayout>
#include <QCoreApplication>
#include <QDir>
#include <QKeyEvent>
#include <QMenu>
#include <QToolBar>
#include <QPluginLoader>
#include <QStatusBar>
#include <QMenuBar>

#include <config.h>

#include <QDebug>

brick_game::general_window::general_window(::QWidget *parent)
    : ::QWidget{parent}, screen_{nullptr}, cur_game_{nullptr},
      record_table_{nullptr}, player_{nullptr}, status_bar_{nullptr} {
  player_ = new brick_game::player{this};
  screen_ = new brick_game::screen;
  record_table_ = new brick_game::recordTable{this};

  pause_log_ = new brick_game::pauseLog{this};
  end_dialog_ = new brick_game::endDialog{this};
  end_dialog_->setRecordTable(record_table_);

  auto general_layout = new ::QVBoxLayout;
  {
    status_bar_ = new ::QStatusBar;
    auto menu_bar = new ::QMenuBar;
    {
      game_menu_ = new ::QMenu{"&Games"};
      menu_bar->addMenu(game_menu_);
    }
    auto tool_bar = new ::QToolBar;
    {
      auto sound_action =
          new ::QAction{::QPixmap{":/image/sound.png"}, "sound", tool_bar};
      sound_action->setWhatsThis("switch sound");
      {
        connect(sound_action, SIGNAL(triggered()), player_,
                SLOT(remove_sound()));
      }
      auto record_table_action = new ::QAction{::QPixmap{":/image/list.png"},
                                               "Record Table", tool_bar};
      record_table_action->setWhatsThis("Record Table");
      {
        connect(record_table_action, &::QAction::triggered, this, [=]() {
          endDialog end_dialog;
          end_dialog.setRecordTable(record_table_);
          ::qDebug() << "open record table";
          end_dialog.exec();
        });
      }
      tool_bar->addAction(sound_action);
      tool_bar->addAction(record_table_action);
    }
    general_layout->addWidget(menu_bar);
    general_layout->addWidget(tool_bar);
    general_layout->addWidget(screen_);
    general_layout->addWidget(status_bar_);
  }
  this->setLayout(general_layout);

  loadPlugins();

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
      emit screen_->clear_all();
    }
    break;
  case Qt::Key_Enter:
  case Qt::Key_Return:
  case Qt::Key_E:
    if (cur_game_ != nullptr) {
      emit screen_->clear_all();
      ::qDebug() << "emit start game signal";
      emit start_game_signal();
    }
    break;
  default:
    break;
  }
}

void brick_game::general_window::loadPlugins() {
  ::qDebug() << "start loading plugins";
  ::QDir dir{CMAKE_LIBRARY_OUTPUT_DIRECTORY};
  if (!dir.isEmpty()) {
    for (auto &i : dir.entryList(::QDir::Files)) {
      ::QPluginLoader loader(dir.absoluteFilePath(i));
      addToMenu(qobject_cast<::QObject *>(loader.instance()));
    }
  }
  ::qDebug() << "finish loading plugins";
}

void brick_game::general_window::addToMenu(::QObject *plugin) {
  if (plugin) {
    auto game = qobject_cast<brick_game::abstractGame *>(plugin);
    if (game) {
      auto game_action = new ::QAction{::QPixmap{game->icon_}, game->game_name(), plugin};
      game_menu_->addAction(game_action);
      connect(game_action, &::QAction::triggered, this,
              [=]() { set_game(game); });
    }
  }
}

void brick_game::general_window::pause(bool status) {
  if (status) {
    ::qDebug() << "open pauseLog";
    pause_log_->exec();
  }
}

void brick_game::general_window::end_game(unsigned short level,
                                          unsigned score) {
  end_dialog_->setDate(level, score);
  ::qDebug() << "open endDialog";
  end_dialog_->exec();
}

void brick_game::general_window::set_game(abstractGame *game) {
  if (cur_game_) {
    ::qDebug() << "begin disconnecting prev game";
    disconnect(this, SIGNAL(start_game_signal()), cur_game_,
               SLOT(start_game_slot()));
    disconnect(this, SIGNAL(finish_game_signal()), cur_game_,
               SLOT(finish_game_slot()));

    disconnect(this, SIGNAL(start_game_signal()), player_, SLOT(begin_theme()));
    disconnect(cur_game_, SIGNAL(end_game_signal()), player_, SLOT(stop()));
    disconnect(&cur_game_->score_, &brick_game::score::send_score, player_,
               &brick_game::player::score_changed);
    disconnect(&cur_game_->level_, &brick_game::level::send_level, player_,
               &brick_game::player::level_up);
    disconnect(cur_game_, SIGNAL(pause_signal(bool)), player_,
               SLOT(pause(bool)));
    disconnect(cur_game_, SIGNAL(activity()), player_, SLOT(activity()));

    disconnect(&cur_game_->score_, &brick_game::score::send_score, screen_,
               &brick_game::screen::set_score);
    disconnect(&cur_game_->level_, &brick_game::level::send_level, screen_,
               &brick_game::screen::set_level);

    disconnect(cur_game_, &brick_game::abstractGame::pause_signal, this,
               &brick_game::general_window::pause);
    disconnect(cur_game_, &brick_game::abstractGame::end_game_signal, this,
               &brick_game::general_window::end_game);

    for (int i = 0; i < screen_->general_pixarr_.size(); ++i) {
      for (int j = 0; j < screen_->general_pixarr_[i].size(); ++j) {
        disconnect(&cur_game_->field_[i][j], &value::changed,
                   screen_->general_pixarr_[i][j], &pix::change);
      }
    }
    for (int i = 0; i < screen_->dop_pixarr_.size(); ++i) {
      for (int j = 0; j < screen_->dop_pixarr_[i].size(); ++j) {
        disconnect(&cur_game_->mini_field_[i][j], &value::changed,
                   screen_->dop_pixarr_[i][j], &pix::change);
      }
    }

    /// for garanted finish game
    cur_game_->finish_game_slot();
    ::qDebug() << "end disconnecting";
  }
  ::qDebug() << "begin connecting game";
  cur_game_ = game;
  player_->stop();
  player_->set_sounds(cur_game_->begin_theme_sound_, cur_game_->activity_sound_,
                      cur_game_->score_sound_, cur_game_->level_up_sound_);
  emit screen_->clear_all();
  if (record_table_) {
    record_table_->set_file_name(::QString{"."} + cur_game_->game_name() +
                                 ::QString{"_record_table.xml"});
  }

  connect(this, SIGNAL(start_game_signal()), cur_game_,
          SLOT(start_game_slot()));
  connect(this, SIGNAL(finish_game_signal()), cur_game_,
          SLOT(finish_game_slot()));

  connect(this, SIGNAL(start_game_signal()), player_, SLOT(begin_theme()));
  connect(cur_game_, SIGNAL(end_game_signal()), player_, SLOT(stop()));
  connect(&cur_game_->score_, &brick_game::score::send_score, player_,
          &brick_game::player::score_changed);
  connect(&cur_game_->level_, &brick_game::level::send_level, player_,
          &brick_game::player::level_up);
  connect(cur_game_, SIGNAL(pause_signal(bool)), player_, SLOT(pause(bool)));
  connect(cur_game_, SIGNAL(activity()), player_, SLOT(activity()));

  connect(&cur_game_->score_, &brick_game::score::send_score, screen_,
          &brick_game::screen::set_score);
  connect(&cur_game_->level_, &brick_game::level::send_level, screen_,
          &brick_game::screen::set_level);

  connect(cur_game_, &brick_game::abstractGame::pause_signal, this,
          &brick_game::general_window::pause);
  connect(cur_game_, &brick_game::abstractGame::end_game_signal, this,
          &brick_game::general_window::end_game);

  for (int i = 0; i < screen_->general_pixarr_.size(); ++i) {
    for (int j = 0; j < screen_->general_pixarr_[i].size(); ++j) {
      connect(&cur_game_->field_[i][j], &value::changed,
              screen_->general_pixarr_[i][j], &pix::change);
    }
  }
  for (int i = 0; i < screen_->dop_pixarr_.size(); ++i) {
    for (int j = 0; j < screen_->dop_pixarr_[i].size(); ++j) {
      connect(&cur_game_->mini_field_[i][j], &value::changed,
              screen_->dop_pixarr_[i][j], &pix::change);
    }
  }

  status_bar_->showMessage(cur_game_->game_name());

  ::qDebug() << "end connecting game";
}
