// score.hpp

#pragma once

#include <QObject>

namespace brick_game {
/// simple score-class for abstractGame
class score : public ::QObject {
  Q_OBJECT
private:
  unsigned score_;

public:
  score(::QObject *parent = nullptr);
  operator unsigned() const;
  score &operator=(int number);
  score &operator+=(int number);
  score &operator++();
  score &operator++(int);

signals:
  void send_score(unsigned score);
};
}; // namespace brick_game
