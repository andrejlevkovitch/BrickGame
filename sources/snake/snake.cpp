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

brick_game::snake::snake(::QObject *parent)
    : brick_game::abstractGame{parent}, time_interval_{}, level_{}, score_{},
      is_avalible_{false}, is_active_{false} {
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
        switch (temp_ev->direction()) {
        case Direction::UP:
          if (cur_direction_ == Direction::DOWN) {
            return;
          }
          if (!move_up()) {
            emit end_game_signal(level_, score_);
          }
          break;
        case Direction::DOWN:
          if (cur_direction_ == Direction::UP) {
            return;
          }
          if (!move_down()) {
            emit end_game_signal(level_, score_);
          }
          break;
        case Direction::RIGHT:
          if (cur_direction_ == Direction::LEFT) {
            return;
          }
          if (!move_right()) {
            emit end_game_signal(level_, score_);
          }
          break;
        case Direction::LEFT:
          if (cur_direction_ == Direction::RIGHT) {
            return;
          }
          if (!move_left()) {
            emit end_game_signal(level_, score_);
          }
          break;
        default:
          break;
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

bool brick_game::snake::move_up() {
  auto temp_pos = snake_body_.front();
  temp_pos.up();
  if (!is_passible(temp_pos)) {
    temp_pos = point{temp_pos.getX(), END_FIELD().getY() - 1};
  }
  snake_body_.push_front(temp_pos);
  switch (field_(temp_pos)) {
  case ONE:
    return false;
    break;
  case TWO:
    new_feed();
    break;
  default:
    field_(snake_body_.back()) = Value::NONE;
    snake_body_.pop_back();
    break;
  }
  field_(temp_pos) = Value::ONE;
  cur_direction_ = Direction::UP;
  return true;
}

bool brick_game::snake::move_down() {
  auto temp_pos = snake_body_.front();
  temp_pos.down();
  if (!is_passible(temp_pos)) {
    temp_pos = point{temp_pos.getX(), RBEGIN_FIELD().getY() + 1};
  }
  snake_body_.push_front(temp_pos);
  switch (field_(temp_pos)) {
  case ONE:
    return false;
    break;
  case TWO:
    new_feed();
    break;
  default:
    field_(snake_body_.back()) = Value::NONE;
    snake_body_.pop_back();
    break;
  }
  field_(temp_pos) = Value::ONE;
  cur_direction_ = Direction::DOWN;
  return true;
}

bool brick_game::snake::move_right() {
  auto temp_pos = snake_body_.front();
  temp_pos.right();
  if (!is_passible(temp_pos)) {
    temp_pos = point{RBEGIN_FIELD().getX() + 1, temp_pos.getY()};
  }
  snake_body_.push_front(temp_pos);
  switch (field_(temp_pos)) {
  case ONE:
    return false;
    break;
  case TWO:
    new_feed();
    break;
  default:
    field_(snake_body_.back()) = Value::NONE;
    snake_body_.pop_back();
    break;
  }
  field_(temp_pos) = Value::ONE;
  cur_direction_ = Direction::RIGHT;
  return true;
}

bool brick_game::snake::move_left() {
  auto temp_pos = snake_body_.front();
  temp_pos.left();
  if (!is_passible(temp_pos)) {
    temp_pos = point{END_FIELD().getX() - 1, temp_pos.getY()};
  }
  snake_body_.push_front(temp_pos);
  switch (field_(temp_pos)) {
  case ONE:
    return false;
    break;
  case TWO:
    new_feed();
    break;
  default:
    field_(snake_body_.back()) = Value::NONE;
    snake_body_.pop_back();
    break;
  }
  field_(temp_pos) = Value::ONE;
  cur_direction_ = Direction::LEFT;
  return true;
}

void brick_game::snake::new_feed() {
  point temp{0, 0};
  do {
    std::uniform_int_distribution<int> distY(0, END_FIELD().getY() - 1);
    std::uniform_int_distribution<int> distX(0, END_FIELD().getX() - 1);
    temp = point{distX(engine), distY(engine)};
  } while (field_(temp) != Value::NONE);
  field_(temp) = TWO;
}

void brick_game::snake::start_game_slot() {
  field_.clear_all();
  snake_body_.clear();
  time_interval_ = BEGIN_TIME_INTERVAL();
  level_ = 0;
  score_ = 0;

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
  level_ = 0;
  score_ = 0;
}
