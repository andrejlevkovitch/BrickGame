// record_table.hpp

#pragma once

#include <QAbstractTableModel>
#include <tuple>
#include <vector>

class QDomNode;
class QDomElement;
class QDomDocument;

#ifdef __linux__
const ::QString HOME{getenv("HOME")};
#elif _WIN32
const ::QString HOME{getenv("LOCALAPPDATA")};
#endif

namespace brick_game {
class recordTable : public ::QAbstractTableModel {
  Q_OBJECT
public:
  static unsigned short N_MEMBERS();
  static unsigned short NAME_SIZE();
  static const ::QString &DOM_ROOT();
  static const ::QString &HEAD_TAG();
  static const ::QString &HEAD_TAG_ATTR();
  static const ::QString &FIRST_TAG();
  static const ::QString &SECOND_TAG();
  static const ::QString &THRID_TAG();

private:
  ::QString file_;
  std::vector<std::tuple<::QString, unsigned short, unsigned>> record_list_;

public:
  recordTable(const ::QString &file, ::QObject *parent = nullptr);
  ~recordTable();
  void set_record(const ::QString &member, unsigned short level, unsigned size);

private:
  void read_file();
  void write_file();
  void traverse_node(const QDomNode &);
  QDomElement record_holder(QDomDocument &d_doc, const ::QString &name,
                            unsigned short level, unsigned score,
                            unsigned short number);
  QDomElement make_dom_element(QDomDocument &d_doc, const ::QString &name,
                               const ::QString &atr = ::QString{},
                               const ::QString &text = ::QString{});
  ::QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
  int rowCount(const ::QModelIndex &parent = ::QModelIndex{}) const override;
  int columnCount(const ::QModelIndex &parent = ::QModelIndex{}) const override;
  ::QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

public slots:
  bool is_record(unsigned score);

signals:
  void record();
  void norecord();
};
}; // namespace brick_game
