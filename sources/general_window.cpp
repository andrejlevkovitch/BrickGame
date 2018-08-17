// general_window.cpp

#include "general_window.hpp"
#include "abstractGame/abstractGame.hpp"
#include <QCoreApplication>
#include "tetramino/tetramino.hpp"
#include "abstractGame/simplExempl.hpp"
#include "screen/screen.hpp"
#include <QAction>
#include <QBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

brick_game::general_window::general_window(::QWidget *parent)
    : ::QWidget{parent}, screen_{nullptr}, cur_game_{nullptr} {
  screen_ = new brick_game::screen;
  auto general_layout = new ::QVBoxLayout;
  {
    auto status_bar = new ::QStatusBar;
    auto menu_bar = new ::QMenuBar;
    {
      auto game_menu = new ::QMenu{"Games"};
      {
        auto simpl_exempl = new ::QAction{"simplExempl", game_menu};
        {
          connect(simpl_exempl, &::QAction::triggered, this, [=]() {
            if (cur_game_) {
              delete cur_game_;
              cur_game_ = nullptr;
            }
            cur_game_ = new brick_game::simplExempl;
            screen_->set_game(cur_game_);
            status_bar->showMessage("simplExempl");
          });
        }
        auto tetramino = new ::QAction{"tetramino", game_menu};
        connect(tetramino, &::QAction::triggered, this, [=]() {
          if (cur_game_) {
            delete cur_game_;
            cur_game_ = nullptr;
          }
          cur_game_ = new brick_game::tetramino;
          screen_->set_game(cur_game_);
          status_bar->showMessage("tetramino");
        });
        game_menu->addAction(simpl_exempl);
        game_menu->addAction(tetramino);
      }
      auto sound_action =
          new ::QAction{::QPixmap{":/sound.png"}, "sound", menu_bar};
      {
        connect(sound_action, &::QAction::triggered, this, [=]() {
          if (cur_game_) {
            cur_game_->remove_sound_slot();
          }
        });
      }
      menu_bar->addMenu(game_menu);
      menu_bar->addAction(sound_action);
    }
    general_layout->addWidget(menu_bar);
    general_layout->addWidget(screen_);
    general_layout->addWidget(status_bar);
  }
  this->setLayout(general_layout);
}

brick_game::general_window::~general_window() {
  if (cur_game_) {
    delete cur_game_;
  }
}

void brick_game::general_window::keyPressEvent(::QKeyEvent *event) {
  ::QCoreApplication::sendEvent(screen_, reinterpret_cast<::QEvent *>(event));
}
