// recordTable.hpp

#pragma once

#include <QAbstractTableModel>
#include <tuple>
#include <vector>

class QDomNode;
class QDomElement;
class QDomDocument;

namespace brick_game {
/**\brief this class is model of record table
 * All datas set in another file for every game
 * Information save in xml format*/
class recordTable : public ::QAbstractTableModel {
  Q_OBJECT
public:
  /**\return size of record_table*/
  static unsigned short N_MEMBERS();
  /**\return max size of input name*/
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
  explicit recordTable(::QObject *parent = nullptr);
  ~recordTable();
  /**\brief set name of file, where is current record table*/
  void set_file_name(const ::QString &file_name);
  /**\brief set new record in the table
   * \param member name of record holder
   * \return true if record set, false if not*/
  bool set_record(::QString member, unsigned short level,
                  unsigned score);

protected:
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

public:
  int columnCount(const ::QModelIndex &parent = ::QModelIndex{}) const override;

protected:
  /**\return names of columns and rows of this record table*/
  ::QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

public slots:
  /**\brief check score
   * \param score checke value
   * \return if this is new record true, if not false*/
  bool is_record(unsigned score);

signals:
  /**\brief report about new record
   * \param is_record true if is new record, false if not*/
  void record(bool is_record);
};
}; // namespace brick_game
