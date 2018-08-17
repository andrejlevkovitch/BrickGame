//pauseLog.hpp

#pragma once

#include <QDialog>

namespace brick_game {
  class pauseLog : public ::QDialog {
    Q_OBJECT
    private:
      ::QWidget *parent_;
    public:
      pauseLog(QWidget *parent);
    private:
      void keyPressEvent(::QKeyEvent *event) override;
  };
};
