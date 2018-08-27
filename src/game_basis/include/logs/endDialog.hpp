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
  /**\brief set model for view
   * \warning don't set ownership of record_table*/
  void setRecordTable(brick_game::recordTable *record_table);

protected slots:
  /// set record on the record table
  void set_record();

public slots:
  /// save values level and score and emit passible_record signal
  void setDate(unsigned short level, unsigned score);
};
}; // namespace brick_game
