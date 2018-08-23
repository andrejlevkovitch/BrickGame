// value.hpp

#pragma once

#include "brick_game.hpp"
#include <QObject>

namespace brick_game {
class value : public ::QObject {
  Q_OBJECT
private:
  Value val_;

public:
  explicit value(Value value = NONE);
  value(const value &val);
  value &operator=(const value &value);
  value &operator=(value &&value) = delete;
  value &operator=(const Value value);
  operator Value() const;

  bool operator==(const Value value) const;
  bool operator!=(const Value value) const;

signals:
  void changed(Value value);
};
}; // namespace brick_game
