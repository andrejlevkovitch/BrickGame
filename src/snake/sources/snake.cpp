// snake.cpp

#include "snake.hpp"
#include "brick_game.hpp"
#include "events/directionEvent.hpp"
#include "events/pauseEvent.hpp"
#include <QCoreApplication>
#include <QEvent>
#include <random>

#ifdef __linux__
static std::random_device rd;
static std::default_random_engine engine{rd()};
#elif _WIN32
static std::default_random_engine engine{
    std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
#endif

std::chrono::milliseconds brick_game::snake::BEGIN_TIME_INTERVAL() {
  static const std::chrono::milliseconds retval{800};
  return retval;
}

int brick_game::snake::SCORE_FOR_FEED() {
  static const int retval{100};
  return retval;
}

int brick_game::snake::BEGIN_LEVEL_FOR_SCORE() {
  static const int retval{500};
  return retval;
}

brick_game::snake::snake(::QObject *parent)
    : brick_game::abstractGame{parent}, time_interval_{}, is_avalible_{false},
      is_active_{false}, last_level_score_{} {
  connect(this, SIGNAL(end_game_signal(unsigned short, unsigned)), this,
          SLOT(finish_game_slot()));
  connect(&timer_, &::QTimer::timeout, this, [=]() {
    brick_game::directionEvent event(cur_direction_);
    ::QCoreApplication::sendEvent(this, &event);
  });
}

::QString brick_game::snake::game_name() const { return ::QString{"snake"}; }

void brick_game::snake::customEvent(::QEvent *event) {
  if (is_avalible_) {
    if (event->type() == static_cast<::QEvent::Type>(Event::pauseEvent)) {
      pause();
      return;
    }
    if (event->type() == static_cast<::QEvent::Type>(Event::directionEvent)) {
      if (is_active_) {
        auto temp_ev = reinterpret_cast<brick_game::directionEvent *>(event);
        bool rezult = false;
        auto temp_direction = cur_direction_;
        switch (temp_ev->direction()) {
        case Direction::UP:
          if (cur_direction_ == Direction::DOWN) {
            return;
          }
          rezult = move_up();
          break;
        case Direction::DOWN:
          if (cur_direction_ == Direction::UP) {
            return;
          }
          rezult = move_down();
          break;
        case Direction::RIGHT:
          if (cur_direction_ == Direction::LEFT) {
            return;
          }
          rezult = move_right();
          break;
        case Direction::LEFT:
          if (cur_direction_ == Direction::RIGHT) {
            return;
          }
          rezult = move_left();
          break;
        default:
          break;
        }
        if (!rezult) {
          emit end_game_signal(level_, score_);
        } else {
          if (temp_direction != cur_direction_) {
            emit activity();
          }
        }
        timer_.start(time_interval_);
      }
    }
    return;
  }
}

void brick_game::snake::pause() {
  if (is_active_) {
    if (timer_.isActive()) {
      timer_.stop();
      is_active_ = false;
      emit pause_signal(true);
    } else {
      timer_.start(time_interval_);
      is_active_ = true;
      emit pause_signal(false);
    }
  }
}

bool brick_game::snake::motion(brick_game::point pos) {
  snake_body_.push_front(pos);
  switch (field_(pos)) {
  case Value::ONE:
    return false;
    break;
  case Value::TWO:
    new_feed();
    score_ += SCORE_FOR_FEED();
    if ((score_ - last_level_score_) == BEGIN_LEVEL_FOR_SCORE()) {
      level_up();
    }
    break;
  default:
    field_(snake_body_.back()) = Value::NONE;
    snake_body_.pop_back();
    break;
  }
  field_(pos) = Value::ONE;
  return true;
}

bool brick_game::snake::move_up() {
  auto temp_pos = snake_body_.front();
  temp_pos.up();
  if (!is_passible(temp_pos)) {
    temp_pos = point{temp_pos.getX(), END_FIELD().getY() - 1};
  }
  cur_direction_ = Direction::UP;
  return motion(temp_pos);
}

bool brick_game::snake::move_down() {
  auto temp_pos = snake_body_.front();
  temp_pos.down();
  if (!is_passible(temp_pos)) {
    temp_pos = point{temp_pos.getX(), REND_FIELD().getY() + 1};
  }
  cur_direction_ = Direction::DOWN;
  return motion(temp_pos);
}

bool brick_game::snake::move_right() {
  auto temp_pos = snake_body_.front();
  temp_pos.right();
  if (!is_passible(temp_pos)) {
    temp_pos = point{REND_FIELD().getX() + 1, temp_pos.getY()};
  }
  cur_direction_ = Direction::RIGHT;
  return motion(temp_pos);
}

bool brick_game::snake::move_left() {
  auto temp_pos = snake_body_.front();
  temp_pos.left();
  if (!is_passible(temp_pos)) {
    temp_pos = point{END_FIELD().getX() - 1, temp_pos.getY()};
  }
  cur_direction_ = Direction::LEFT;
  return motion(temp_pos);
}

void brick_game::snake::new_feed() {
  point temp{0, 0};
  do {
    std::uniform_int_distribution<int> distY(0, END_FIELD().getY() - 1);
    std::uniform_int_distribution<int> distX(0, END_FIELD().getX() - 1);
    temp = point{distX(engine), distY(engine)};
  } while (field_(temp) != Value::NONE);
  field_(temp) = Value::TWO;
}

void brick_game::snake::level_up() {
  ++level_;
  last_level_score_ = score_ + level_ * SCORE_FOR_FEED();
  time_interval_ -= time_interval_ / 10;
  for (auto &i : snake_body_) {
    field_(i) = brick_game::Value::NONE;
  }
  auto temp = *snake_body_.begin();
  snake_body_.clear();
  snake_body_.push_back(temp);
  field_(temp) = Value::ONE;
}

void brick_game::snake::start_game_slot() {
  field_.clear_all();
  snake_body_.clear();
  time_interval_ = BEGIN_TIME_INTERVAL();

  {
    std::uniform_int_distribution<int> dist{
        0, static_cast<int>(Direction::SIZE) - 1};
    cur_direction_ = static_cast<Direction>(dist(engine));
  }

  {
    std::uniform_int_distribution<int> distY(0, END_FIELD().getY() - 1);
    std::uniform_int_distribution<int> distX(0, END_FIELD().getX() - 1);

    auto temp = point{distX(engine), distY(engine)};
    snake_body_.push_front(temp);
    field_(temp) = Value::ONE;
  }

  new_feed();

  is_avalible_ = true;
  is_active_ = true;
  timer_.start(time_interval_);
}

void brick_game::snake::finish_game_slot() {
  if (sender() != this) {
    emit end_game_signal(level_, score_);
    return;
  }
  timer_.stop();
  is_avalible_ = false;
  is_active_ = false;
}
