// messageToFile.hpp

#pragma once

#include "brick_game.hpp"
#include <QMessageLogContext>
#include <QString>

const ::QString file_protocol_name{brick_game::HOME + "/protocol.log"};

void messageToFile(::QtMsgType type, const ::QMessageLogContext &context,
                   const ::QString &msg);
