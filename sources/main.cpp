// main.cpp

#include "general_window.hpp"
#include <QApplication>
#include <QFile>
#include <QLatin1String>

#include <QDebug>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);

  ::QFile file{":/style/default.qss"};
  if (file.open(::QFile::ReadOnly)) {
    ::QString style = ::QLatin1String{file.readAll()};
    app.setStyleSheet(style);
    file.close();
  }

  brick_game::general_window brick_game_window;
  brick_game_window.show();

  return app.exec();
}
