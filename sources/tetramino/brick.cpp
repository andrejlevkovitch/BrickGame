// brick.cpp

#include "brick.hpp"
#include <chrono>
#include <random>

brick_game::point brick_game::brick::DEF_CENTER() {
  static const brick_game::point retval{1, 0};
  return retval;
}

brick_game::brick::brick(::QObject *parent)
    : ::QObject{parent}, center_{DEF_CENTER()} {
#ifdef __linux__
  static std::random_device rd;
  static std::default_random_engine engine{rd()};
#elif _WIN32
  static std::default_random_engine engine{
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
#endif

  std::uniform_int_distribution<int> value_dist(
      1, static_cast<int>(Value::SIZE) - 1);
  auto value = static_cast<Value>(value_dist(engine));

  std::uniform_int_distribution<int> type_dist(0, SIZE_BRICKS - 1);

  type_ = static_cast<BrickType>(type_dist(engine));

  switch (type_) {
  case O_BRICK:
    field_.resize(2, decltype(field_)::value_type(2, value));
    break;
  case T_BRICK:
    field_.resize(2, decltype(field_)::value_type(3, value));
    field_[0][0] = field_[0][2] = Value::NONE;
    break;
  case L_BRICK:
    field_.resize(2, decltype(field_)::value_type(3, value));
    field_[0][0] = field_[0][1] = Value::NONE;
    break;
  case J_BRICK:
    field_.resize(2, decltype(field_)::value_type(3, value));
    field_[0][2] = field_[0][1] = Value::NONE;
    break;
  case I_BRICK:
    field_.resize(1, decltype(field_)::value_type(4, value));
    break;
  case S_BRICK:
    field_.resize(2, decltype(field_)::value_type(3, value));
    field_[0][0] = field_[1][2] = Value::NONE;
    break;
  case Z_BRICK:
    field_.resize(2, decltype(field_)::value_type(3, value));
    field_[1][0] = field_[0][2] = Value::NONE;
    break;
  default:
    break;
  }

  std::uniform_int_distribution<int> rotade_dist(0, 3);
  auto n_turn = rotade_dist(engine);
  for (int i = 0; i < n_turn; ++i) {
    turn();
  }
}

bool brick_game::brick::turn() {
  if (type_ != O_BRICK) {
    decltype(field_) temp;
    temp.resize(field_[0].size(),
                decltype(field_)::value_type(field_.size(), Value::NONE));
    bool no_update_center{true};
    for (int i{}; i < field_.size(); ++i) {
      for (int j{}; j < field_[i].size(); ++j) {
        int n = field_.size() - i - 1;
        temp[j][n] = field_[i][j];
        if (center_ == point{j, i} && no_update_center) {
          center_ = point{n, j};
          no_update_center = false;
        }
      }
    }
    field_ = temp;
    return true;
  }
  return false;
}

brick_game::brick &brick_game::brick::operator=(brick &&rhs) {
  field_ = rhs.field_;
  type_ = rhs.type_;
  center_ = rhs.center_;
  return *this;
}

brick_game::brick &brick_game::brick::operator=(const brick &rhs) {
  field_ = rhs.field_;
  type_ = rhs.type_;
  center_ = rhs.center_;
  return *this;
}
