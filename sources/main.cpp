// main.cpp

#include "brick_game.hpp"
#include "general/general_window.hpp"
#include <QApplication>
#include <QFile>
#include <QLatin1String>
#include <exception>

#ifdef _WIN32
#include <direct.h>
#elif __linux__
#include <sys/stat.h>
#endif

#include "general/messageToFile.hpp"
#include <QDebug>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  {
#ifdef _WIN32
    ::mkdir(brick_game::HOME.toStdString().c_str());
#elif __linux__
    ::mkdir(brick_game::HOME.toStdString().c_str(), 0777);
#endif
    ::QFile file(file_protocol_name);
    if (file.open(::QIODevice::WriteOnly)) {
      file.close();
    }
    ::qInstallMessageHandler(messageToFile);
  }

  ::QFile file{":/style/default.qss"};
  if (file.open(::QFile::ReadOnly)) {
    ::qDebug() << "open style file";
    ::QString style = ::QLatin1String{file.readAll()};
    app.setStyleSheet(style);
    file.close();
  }

  brick_game::general_window brick_game_window;
  brick_game_window.show();

  return app.exec();
}
