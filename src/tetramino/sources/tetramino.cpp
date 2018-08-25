// tetramino.cpp

#include "tetramino.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include <QCoreApplication>

std::chrono::milliseconds brick_game::tetramino::BEGIN_TIME_DOWN() {
  static const std::chrono::milliseconds retval{800};
  return retval;
}

unsigned short brick_game::tetramino::LINES_TO_NEXT_LEVEL() {
  static const unsigned short retval{8};
  return retval;
}

unsigned short brick_game::tetramino::PRICE_FOR_LINE(unsigned short n_line) {
  static const std::vector<unsigned short> prices{100, 300, 700, 1500};
  return prices[n_line];
}

unsigned short brick_game::tetramino::TIME_DIVIDED() {
  static const unsigned short retval{10};
  return retval;
}

const brick_game::point &brick_game::tetramino::BEG_POSITION() {
  static const point retval{brick_game::FIELD_SIZE.width() / 2, -1};
  return retval;
}

brick_game::tetramino::tetramino(::QObject *parent)
    : brick_game::abstractGame{parent},
      cur_brick_position_{BEG_POSITION()}, time_interval_{BEGIN_TIME_DOWN()},
      score_{}, level_{}, lines_{}, active_{true}, is_avalibale_{false} {

  connect(&timer_, &::QTimer::timeout, this, [=]() {
    directionEvent event(Direction::DOWN);
    ::QCoreApplication::sendEvent(this, &event);
  });
  connect(this, SIGNAL(end_game_signal(unsigned short, unsigned)),
          SLOT(finish_game_slot()));
};

void brick_game::tetramino::start_game_slot() {
  field_.clear_all();
  level_ = 0;
  score_ = 0;
  lines_ = 0;

  cur_brick_position_ = BEG_POSITION();
  reverse_cur_brick();
  set_next_brick();
  emit send_level(level_);
  emit send_score(score_);
  active_ = true;
  is_avalibale_ = true;
  timer_.start(BEGIN_TIME_DOWN());
}

void brick_game::tetramino::finish_game_slot() {
  if (sender() != this) {
    emit end_game_signal(level_, score_);
    return;
  }
  level_ = 0;
  score_ = 0;
  lines_ = 0;
  active_ = false;
  is_avalibale_ = false;
  timer_.stop();
}

::QString brick_game::tetramino::game_name() const {
  return ::QString{"tetramino"};
}

void brick_game::tetramino::customEvent(::QEvent *event) {
  if (event->type() == static_cast<::QEvent::Type>(Event::pauseEvent)) {
    pause();
    return;
  }
  if (event->type() == static_cast<::QEvent::Type>(Event::directionEvent)) {
    if (!active_) {
      return;
    }
    auto d_event = static_cast<directionEvent *>(event);
    switch (d_event->direction()) {
    case Direction::UP:
      rotade_cur_brick();
      break;
    case Direction::DOWN:
      set_brick_down();
      break;
    case Direction::RIGHT:
      set_brick_right();
      break;
    case Direction::LEFT:
      set_brick_left();
      break;
    default:
      break;
    }
    return;
  }
}

void brick_game::tetramino::pause() {
  if (is_avalibale_) {
    if (timer_.isActive()) {
      active_ = false;
      timer_.stop();
      emit pause_signal(true);
    } else {
      active_ = true;
      timer_.start(time_interval_);
      emit pause_signal(false);
    }
  }
}

brick_game::point brick_game::tetramino::left_up_brick_corner() const {
  return cur_brick_position_ - cur_brick_.center_;
}

brick_game::point brick_game::tetramino::right_down_brick_corner() const {
  return left_up_brick_corner() +
         point(cur_brick_.field_[0].size() - 1, cur_brick_.field_.size() - 1);
}

bool brick_game::tetramino::is_passible() const {
  auto left_corner = left_up_brick_corner();
  auto right_corner = right_down_brick_corner();
  if (right_corner < END_FIELD() &&
      left_corner.getX() > REND_FIELD().getX()) {
    for (auto &i : cur_brick_.field_) {
      auto temp = left_corner;
      for (auto &j : i) {
        if (j != Value::NONE && temp.getY() >= 0 &&
            field_(temp) != Value::NONE) {
          return false;
        }
        temp.right();
      }
      left_corner.down();
    }
    return true;
  }
  return false;
}

void brick_game::tetramino::delete_solutions() {
  auto temp_fild_copy{field_};
  bool solution{true};
  unsigned short lines_counter{};
  for (int i = field_.size() - 1; i >= lines_counter; --i) {
    for (const auto &j : field_[i]) {
      if (j == Value::NONE) {
        solution = false;
        break;
      }
    }
    if (solution) {
      ++lines_counter;
      field_.erase_row_shift_down(i);
      ++i;
    }
    solution = true;
  }
  if (lines_counter) {
    lines_ += lines_counter;
    if (lines_ >= LINES_TO_NEXT_LEVEL()) {
      lines_ = 0;
      ++level_;
      emit send_level(level_);
      time_interval_ -= time_interval_ / TIME_DIVIDED();
    }
    score_ += PRICE_FOR_LINE(lines_counter - 1);
    emit send_score(score_);
  }
}

void brick_game::tetramino::reverse_cur_brick() {
  auto pos = left_up_brick_corner();
  auto temp = pos;
  for (const auto &i : cur_brick_.field_) {
    temp = pos;
    for (const auto &j : i) {
      if (j != Value::NONE && temp.getY() >= 0) {
        field_(temp) =
            (field_(temp) == Value::NONE) ? j : Value::NONE;
      }
      temp.right();
    }
    pos.down();
  }
}

void brick_game::tetramino::rotade_cur_brick() {
  reverse_cur_brick();
  if (!cur_brick_.turn()) {
    reverse_cur_brick();
    return;
  }
  bool is_turned{true};
  bool first_time{true};
begin:
  if (!is_passible()) {
    cur_brick_position_.right();
    if (!is_passible()) {
      cur_brick_position_.right();
      if (!is_passible()) {
        cur_brick_position_.left();
      } else {
        goto end;
      }
      cur_brick_position_.left();
      cur_brick_position_.left();
      if (!is_passible()) {
        cur_brick_position_.left();
        if (!is_passible()) {
          cur_brick_position_.right();
        } else {
          goto end;
        }
        cur_brick_position_.right();
        cur_brick_position_.down();
        if (!is_passible()) {
          cur_brick_position_.down();
          if (!is_passible()) {
            cur_brick_position_.up();
          } else {
            goto end;
          }
          cur_brick_position_.up();
          if (first_time) {
            cur_brick_.turn();
            first_time = false;
            goto begin;
          }
          if (!is_passible()) {
            for (int i = 0; i < 2; ++i) {
              cur_brick_.turn();
            }
            is_turned = false;
          }
        }
      }
    }
  }
end:
  reverse_cur_brick();

  if (is_turned) {
    emit activity();
  }
}

void brick_game::tetramino::set_brick_down() {
  reverse_cur_brick();
  cur_brick_position_.down();
  if (!is_passible()) {
    cur_brick_position_.up();
    reverse_cur_brick();
    if (left_up_brick_corner().getY() < 0) {
      emit end_game_signal(level_, score_);
    } else {
      delete_solutions();
      cur_brick_position_ = BEG_POSITION();
      cleare_next_brick();
      cur_brick_ = next_brick_;
      reverse_cur_brick();
      next_brick_ = brick{};
      set_next_brick();
    }
  } else {
    reverse_cur_brick();
  }
  timer_.start(time_interval_);
}

void brick_game::tetramino::set_brick_left() {
  reverse_cur_brick();
  cur_brick_position_.left();
  if (!is_passible()) {
    cur_brick_position_.right();
  }
  reverse_cur_brick();
}

void brick_game::tetramino::set_brick_right() {
  reverse_cur_brick();
  cur_brick_position_.right();
  if (!is_passible()) {
    cur_brick_position_.left();
  }
  reverse_cur_brick();
}

void brick_game::tetramino::set_next_brick() {
  for (int i = 0; i < next_brick_.field_.size(); ++i) {
    for (int j = 0; j < next_brick_.field_[i].size(); ++j) {
      if (next_brick_.field_[i][j] != Value::NONE) {
        mini_field_[i][j] = next_brick_.field_[i][j];
      }
    }
  }
}

void brick_game::tetramino::cleare_next_brick() {
  for (int i = 0; i < next_brick_.field_.size(); ++i) {
    for (int j = 0; j < next_brick_.field_[i].size(); ++j) {
      if (next_brick_.field_[i][j] != Value::NONE) {
        mini_field_[i][j] = Value::NONE;
      }
    }
  }
}
