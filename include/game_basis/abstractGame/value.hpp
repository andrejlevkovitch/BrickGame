// value.hpp

#pragma once

#include "brick_game.hpp"
#include <QObject>

namespace brick_game {
  /**\brief element of class brick_game::field*/
class value : public ::QObject {
  Q_OBJECT

private:
  Value val_;

public:
  explicit value(Value value = Value::NONE);
  value(const value &val);
  /**\param value set this in value::val_ and send signal changed*/
  value &operator=(const value &value);
  value &operator=(value &&value) = delete;
  value &operator=(const Value value);
  /**\brief reduction to brick_game::Value*/
  operator Value() const;

  bool operator==(const Value value) const;
  bool operator!=(const Value value) const;

signals:
  /**\brief emit if value changed
   * \param value new value*/
  void changed(Value value);
};
}; // namespace brick_game
