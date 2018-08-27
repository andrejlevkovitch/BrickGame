// simplExempl.cpp

#include "simplExempl.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"

brick_game::point brick_game::simplExempl::BEGIN_POS() {
  static const brick_game::point retval{0, 0};
  return retval;
}

brick_game::simplExempl::simplExempl(::QObject *parent)
    : abstractGame{parent},
      cur_pos_{BEGIN_POS()} {}

void brick_game::simplExempl::start_game_slot() {
  field_.clear_all();
  cur_pos_ = BEGIN_POS();
  field_(cur_pos_) = Value::ONE;
}

void brick_game::simplExempl::finish_game_slot() {}

::QString brick_game::simplExempl::game_name() const {
  return ::QString{"simpleGame"};
}

void brick_game::simplExempl::customEvent(::QEvent *event) {
  if (event->type() == static_cast<::QEvent::Type>(Event::pauseEvent)) {
    return;
  }
  if (event->type() == static_cast<::QEvent::Type>(Event::directionEvent)) {
    auto d_event = static_cast<directionEvent *>(event);
    field_(cur_pos_) = Value::NONE;
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
    default:
      break;
    }
    if (!is_passible(cur_pos_)) {
      cur_pos_ = temp;
    } else {
      emit activity();
    }
    field_(cur_pos_) = Value::ONE;
    return;
  }
}
