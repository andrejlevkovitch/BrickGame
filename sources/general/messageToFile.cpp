// messageToFile.cpp

#include "general/messageToFile.hpp"
#include <QDebug>
#include <QFile>

void messageToFile(::QtMsgType type, const ::QMessageLogContext &context,
                   const ::QString &msg) {
  ::QFile file(file_protocol_name);
  if (file.open(::QIODevice::WriteOnly | ::QIODevice::Text |
                ::QIODevice::Append)) {
    ::QTextStream out(&file);
    switch (type) {
    case ::QtDebugMsg:
      out << "Debug: " << msg << ", " << context.file << endl;
      break;
    case ::QtWarningMsg:
      out << "Warning: " << msg << ", " << context.file << endl;
      break;
    case ::QtCriticalMsg:
      out << "Critical: " << msg << ", " << context.file << endl;
      break;
    case ::QtFatalMsg:
      out << "Fatal: " << msg << ", " << context.file << endl;
      abort();
      break;
    default:
      break;
    }
  } else {
    ::qWarning() << "protocol file not open!!!";
  }
}
