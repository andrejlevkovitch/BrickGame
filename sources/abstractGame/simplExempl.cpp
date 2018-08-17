// simplExempl.cpp

#include "abstractGame/simplExempl.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include <QUrl>

brick_game::point brick_game::simplExempl::BEGIN_POS() {
  static const brick_game::point retval{0, 0};
  return retval;
}

brick_game::simplExempl::simplExempl(::QObject *parent)
    : abstractGame{parent}, cur_pos_{BEGIN_POS()} {
  field_.resize(brick_game::FIELD_SIZE.height(),
                decltype(field_)::value_type(brick_game::FIELD_SIZE.width(),
                                             Value::NONE));
}

void brick_game::simplExempl::start_game() {
  for (auto &i : field_) {
    for (auto &j : i) {
      j = Value::NONE;
    }
  }
  cur_pos_ = BEGIN_POS();
  changed(cur_pos_, ONE);
}

void brick_game::simplExempl::finish_game() {}

void brick_game::simplExempl::customEvent(::QEvent *event) {
  if (event->type() == static_cast<::QEvent::Type>(Event::pauseEvent)) {
    return;
  }
  if (event->type() == static_cast<::QEvent::Type>(Event::directionEvent)) {
    auto d_event = static_cast<directionEvent *>(event);
    emit changed(cur_pos_, NONE);
    auto temp = cur_pos_;
    switch (d_event->direction()) {
    case Direction::UP:
      cur_pos_.up();
      break;
    case Direction::DOWN:
      cur_pos_.down();
      break;
    case Direction::RIGHT:
      cur_pos_.right();
      break;
    case Direction::LEFT:
      cur_pos_.left();
      break;
    }
    if (!is_passible(cur_pos_)) {
      cur_pos_ = temp;
    } else if (!soundless_) {
      player_.stop();
      if (player_.media() != ::QUrl{"qrc:/audio/activity.mp3"}) {
        player_.setMedia(::QUrl{"qrc:/audio/activity.mp3"});
      }
      player_.play();
    }
    emit changed(cur_pos_, ONE);
    return;
  }
}
