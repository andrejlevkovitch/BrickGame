// endDialog.cpp

#include "logs/endDialog.hpp"
#include "recordTable/recordTable.hpp"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>

brick_game::endDialog::endDialog(::QWidget *parent)
    : ::QDialog{parent, Qt::CustomizeWindowHint}, record_table_view_{nullptr} {
  auto general_layout = new ::QVBoxLayout;
  {
    record_table_view_ = new ::QTreeView;

    auto name_lbl = new ::QLabel{"&Name"};
    name_edit_ = new ::QLineEdit;
    name_edit_->hide();
    name_edit_->setMaxLength(recordTable::NAME_SIZE());
    { connect(name_edit_, SIGNAL(returnPressed()), this, SLOT(set_record())); }
    name_lbl->setBuddy(name_edit_);
    auto exit_button = new ::QPushButton{"&Exit"};
    {
      connect(exit_button, &::QPushButton::clicked, this, [=]() {
        set_record();
        this->accept();
      });
    }

    general_layout->addWidget(record_table_view_);
    general_layout->addWidget(name_lbl);
    general_layout->addWidget(name_edit_);
    general_layout->addWidget(exit_button);
  }
  this->setLayout(general_layout);
}

void brick_game::endDialog::setRecordTable(
    brick_game::recordTable *record_table) {
  record_table_view_->setModel(record_table);
  for (int i = 0; i < record_table->columnCount(); ++i) {
    record_table_view_->resizeColumnToContents(i);
  }

  connect(record_table, &brick_game::recordTable::record, name_edit_, [=]() {
    name_edit_->show();
    name_edit_->setFocus();
  });
  connect(record_table, &brick_game::recordTable::norecord, name_edit_,
          [=]() { name_edit_->hide(); });
}

void brick_game::endDialog::set_record() {
  auto rT = dynamic_cast<recordTable *>(record_table_view_->model());
  if (rT) {
    rT->set_record(name_edit_->text(), level_, score_);
  }
  name_edit_->clear();
}

void brick_game::endDialog::setDate(unsigned short level, unsigned score) {
  level_ = level;
  score_ = score;
  auto rT = dynamic_cast<recordTable *>(record_table_view_->model());
  if (rT) {
    rT->is_record(score_);
  }
}
