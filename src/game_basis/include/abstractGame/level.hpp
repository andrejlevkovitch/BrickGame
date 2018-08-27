// level.hpp

#pragma once

#include <QObject>

namespace brick_game {
/// simple level-class for abstractGame
class level : public ::QObject {
  Q_OBJECT
private:
  unsigned short level_;

public:
  level(::QObject *parent = nullptr);
  operator unsigned short() const;
  level &operator=(int number);
  level &operator+=(int number);
  level &operator++();
  level &operator++(int);

signals:
  void send_level(unsigned short level);
};
}; // namespace brick_game
