// record_table.cpp

#include "screen/record_table.hpp"
#include <QDomNode>
#include <QFile>

unsigned short brick_game::recordTable::N_MEMBERS() {
  static const unsigned short retval{10};
  return retval;
}

unsigned short brick_game::recordTable::NAME_SIZE() {
  static const unsigned short retval{10};
  return retval;
}

const ::QString &brick_game::recordTable::DOM_ROOT() {
  static const ::QString retval{"record_table"};
  return retval;
}
const ::QString &brick_game::recordTable::HEAD_TAG() {
  static const ::QString retval{"record_holder"};
  return retval;
}

const ::QString &brick_game::recordTable::HEAD_TAG_ATTR() {
  static const ::QString retval{"number"};
  return retval;
}

const ::QString &brick_game::recordTable::FIRST_TAG() {
  static const ::QString retval{"name"};
  return retval;
}

const ::QString &brick_game::recordTable::SECOND_TAG() {
  static const ::QString retval{"level"};
  return retval;
}

const ::QString &brick_game::recordTable::THRID_TAG() {
  static const ::QString retval{"score"};
  return retval;
}

brick_game::recordTable::recordTable(const ::QString &file, ::QObject *parent)
    : ::QAbstractTableModel{parent}, file_{file},
      record_list_{decltype(record_list_){N_MEMBERS(),
                                          std::make_tuple("default", 0, 0)}} {
  read_file();
}

brick_game::recordTable::~recordTable() {}

void brick_game::recordTable::read_file() {
  ::QFile file(file_);
  if (file.open(::QIODevice::ReadOnly)) {
    ::QDomDocument dom_doc;
    dom_doc.setContent(&file);
    traverse_node(dom_doc.documentElement());
    file.close();
  }
}

void brick_game::recordTable::write_file() {
  ::QFile file(file_);
  if (file.open(::QIODevice::WriteOnly)) {
    ::QDomDocument dom_doc{"record_table"};
    ::QDomElement dom_elem{dom_doc.createElement(DOM_ROOT())};
    dom_doc.appendChild(dom_elem);
    for (int i{}; i < N_MEMBERS(); ++i) {
      dom_elem.appendChild(record_holder(dom_doc, std::get<0>(record_list_[i]),
                                         std::get<1>(record_list_[i]),
                                         std::get<2>(record_list_[i]), i));
    }
    file.write(dom_doc.toByteArray());
    file.close();
  }
}

void brick_game::recordTable::traverse_node(const QDomNode &in_node) {
  ::QDomNode d_node = in_node.firstChild();
  while (!d_node.isNull()) {
    if (d_node.isElement()) {
      ::QDomElement d_elem = d_node.toElement();
      if (!d_elem.isNull()) {
        if (d_elem.tagName() == HEAD_TAG()) {
          auto d_child_list = d_elem.childNodes();
          bool isGood{false};
          int number = d_elem.attribute(HEAD_TAG_ATTR()).toInt(&isGood);
          if (isGood && record_list_.size() > number) {
            for (int i = 0; i < d_child_list.size(); ++i) {
              auto element = d_child_list.item(i).toElement();
              if (!element.isNull()) {
                switch (i) {
                case 0:
                  if (element.tagName() == FIRST_TAG()) {
                    std::get<0>(record_list_[number]) = element.text();
                  }
                  break;
                case 1:
                  if (element.tagName() == SECOND_TAG()) {
                    std::get<1>(record_list_[number]) = element.text().toInt();
                  }
                  break;
                case 2:
                  if (element.tagName() == THRID_TAG()) {
                    std::get<2>(record_list_[number]) = element.text().toInt();
                  }
                  break;
                default:
                  break;
                }
              }
            }
          }
        }
      }
    }
    d_node = d_node.nextSibling();
  }
}

::QDomElement brick_game::recordTable::record_holder(::QDomDocument &dom_doc,
                                                     const ::QString &name,
                                                     unsigned short level,
                                                     unsigned score,
                                                     unsigned short number) {
  ::QDomElement dom_elem =
      make_dom_element(dom_doc, HEAD_TAG(), ::QString::number(number));
  ++number;
  dom_elem.appendChild(make_dom_element(dom_doc, FIRST_TAG(), "", name));
  dom_elem.appendChild(
      make_dom_element(dom_doc, SECOND_TAG(), "", ::QString::number(level)));
  dom_elem.appendChild(
      make_dom_element(dom_doc, THRID_TAG(), "", ::QString::number(score)));
  return dom_elem;
}

::QDomElement brick_game::recordTable::make_dom_element(
    ::QDomDocument &dom_doc, const ::QString &node_name, const ::QString &atr,
    const ::QString &text) {
  ::QDomElement d_element = dom_doc.createElement(node_name);
  if (!atr.isEmpty()) {
    d_element.setAttribute(HEAD_TAG_ATTR(), atr);
  }
  if (!text.isEmpty()) {
    ::QDomText d_text = dom_doc.createTextNode(text);
    d_element.appendChild(d_text);
  }
  return d_element;
}

void brick_game::recordTable::set_record(const ::QString &member,
                                         unsigned short level, unsigned score) {
  for (auto i = record_list_.begin(); i != record_list_.end(); ++i) {
    if (score > std::get<2>(*i)) {
      record_list_.insert(i, std::make_tuple(member, level, score));
      break;
    }
  }
  write_file();
}

bool brick_game::recordTable::is_record(unsigned score) {
  read_file();
  auto iter = record_list_.begin();
  std::advance(iter, N_MEMBERS() - 1);
  if (score > std::get<2>(*iter)) {
    emit record();
    return true;
  }
  emit norecord();
  return false;
}

::QVariant brick_game::recordTable::data(const QModelIndex &index,
                                         int role) const {
  if (!index.isValid() || index.row() >= rowCount() || index.row() < 0 ||
      index.column() >= columnCount() || index.column() < 0) {
    return ::QVariant{};
  }
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return std::get<0>(record_list_[index.row()]);
    case 1:
      return std::get<1>(record_list_[index.row()]);
    case 2:
      return std::get<2>(record_list_[index.row()]);
    default:
      break;
    }
  }

  return ::QVariant{};
}

int brick_game::recordTable::rowCount(const ::QModelIndex &parent) const {
  return record_list_.size();
}

int brick_game::recordTable::columnCount(const ::QModelIndex &parent) const {
  return std::tuple_size<decltype(record_list_)::value_type>::value;
}

::QVariant brick_game::recordTable::headerData(int section,
                                               Qt::Orientation orientation,
                                               int role) const {
  if (role == Qt::DisplayRole) {
    if (orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return "Name";
      case 1:
        return "Level";
      case 2:
        return "Score";
      default:
        break;
      }
    } else {
      return section + 1;
    }
  }
  return ::QVariant{};
}
