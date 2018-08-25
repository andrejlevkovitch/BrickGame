// pauseLog.hpp

#pragma once

#include <QDialog>

namespace brick_game {
class pauseLog : public ::QDialog {
  Q_OBJECT
private:
  ::QWidget *parent_;

public:
  pauseLog(QWidget *parent);

protected:
  void keyPressEvent(::QKeyEvent *event) override;
};
}; // namespace brick_game
