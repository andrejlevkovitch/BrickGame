// main.cpp

#include "brick_game.hpp"
#include "general_window.hpp"
#include <QApplication>
#include <QFile>
#include <QLatin1String>
#include <boost/filesystem.hpp>
#include <exception>

#include "messageToFile.hpp"
#include <QDebug>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  {
    if (!boost::filesystem::is_directory(
            brick_game::HOME.toStdString().c_str())) {
      ::qDebug() << "Directory with game files dosn't exists";
      if (boost::filesystem::create_directory(
              brick_game::HOME.toStdString().c_str())) {
        ::qDebug() << "Directory created";
      } else {
        ::qWarning() << "Directry dosn't created";
      }
    }
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
