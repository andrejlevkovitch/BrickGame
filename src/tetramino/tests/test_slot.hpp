// test_slot.hpp

#include <QObject>

/**\brief class for testing signals and slots*/
class test_slot : public ::QObject {
  Q_OBJECT
private:
  bool is_connected_;

public:
  test_slot() : ::QObject{nullptr}, is_connected_{false}, a_{}, b_{} {};
  /**\return true if catch signal, and false if not
   * \warning second use this function without some input signal return false*/
  bool is_connected() {
    if (is_connected_) {
      is_connected_ = false;
      return true;
    } else {
      return false;
    }
  };

  int a_;
  int b_;
public slots:
  /**\brief set flag is_connected_ equal true*/
  void connect_slot() { is_connected_ = true; };
  void test_date_slot(int a, int b) {
    a_ = a;
    b_ = b;
    is_connected_ = true;
  };
signals:
  void test_signal();
};
