// endDialog.hpp

#pragma once

#include <QDialog>

class QTreeView;
class QLineEdit;

namespace brick_game {
class recordTable;

class endDialog : public ::QDialog {
  Q_OBJECT
private:
  ::QTreeView *record_table_view_;
  ::QLineEdit *name_edit_;
  unsigned short level_;
  unsigned score_;

public:
  endDialog(::QWidget *parent = nullptr);
  void setRecordTable(brick_game::recordTable *record_table);

private slots:
  void set_record();

public slots:
  void setDate(unsigned short level, unsigned score);
};
}; // namespace brick_game
