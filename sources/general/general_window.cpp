// general_window.cpp

#include "general/general_window.hpp"
#include "abstractGame/abstractGame.hpp"
#include "abstractGame/simplExempl.hpp"
#include "recordTable/recordTable.hpp"
#include "screen/endDialog.hpp"
#include "screen/screen.hpp"
#include "tetramino/tetramino.hpp"
#include <QAction>
#include <QBoxLayout>
#include <QCoreApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <QDebug>
#include <QtGlobal>

brick_game::general_window::general_window(::QWidget *parent)
    : ::QWidget{parent}, screen_{nullptr}, cur_game_{nullptr}, record_table_{
                                                                   nullptr} {
  screen_ = new brick_game::screen;
  record_table_ = new brick_game::recordTable{this};
  screen_->set_record_table(record_table_);

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
          connect(simpl_exempl_action, &::QAction::triggered, this,
                  [=]() { emit set_game_signal(new brick_game::simplExempl); });
        }
        auto tetramino_action = new ::QAction{"tetramino", game_menu};
        {
          connect(tetramino_action, &::QAction::triggered, this,
                  [=]() { emit set_game_signal(new brick_game::tetramino); });
        }
        game_menu->addAction(simpl_exempl_action);
        game_menu->addAction(tetramino_action);
      }
      auto sound_action =
          new ::QAction{::QPixmap{":/image/sound.png"}, "sound", menu_bar};
      {
        connect(sound_action, &::QAction::triggered, this, [=]() {
          if (cur_game_) {
            cur_game_->remove_sound_slot();
          }
        });
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
  ::QCoreApplication::sendEvent(screen_, reinterpret_cast<::QEvent *>(event));
}

void brick_game::general_window::set_game_slot(abstractGame *game) {
  Q_CHECK_PTR(game);
  ::qDebug() << "begin connecting game";
  if (cur_game_) {
    delete cur_game_;
    cur_game_ = nullptr;
  }
  cur_game_ = game;
  screen_->set_game(cur_game_);
  if (record_table_) {
    record_table_->set_file_name(::QString{"/."} + cur_game_->game_name() +
                                 ::QString{"_record_table.xml"});
  }
  ::qDebug() << "game set";
}
