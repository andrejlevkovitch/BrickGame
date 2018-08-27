// boost_test_recordTable.cpp

#define BOOST_TEST_MODULE test_module_recordTable
#include <boost/test/included/unit_test.hpp>

#include <boost/filesystem.hpp>
#include "recordTable/recordTable.hpp"
#include "test_slot.hpp"
#include "brick_game.hpp"

BOOST_AUTO_TEST_SUITE(recordTable)

struct fixture_recordTable : public brick_game::recordTable {
  ::QString file_name{"test_record_table.xml"};
};

BOOST_FIXTURE_TEST_CASE(test_case_1, fixture_recordTable) {
  BOOST_CHECK(columnCount());
  BOOST_CHECK(rowCount());
}

BOOST_FIXTURE_TEST_CASE(test_case_2, fixture_recordTable) {
  BOOST_CHECK(!is_record(0));
}

BOOST_FIXTURE_TEST_CASE(test_case_3, fixture_recordTable) {
  test_slot ts;
  ::QObject::connect(this, &brick_game::recordTable::record, &ts, 
      &test_slot::connect_slot);
  BOOST_CHECK(!is_record(1));
  BOOST_CHECK(ts.is_connected());

  BOOST_CHECK(!is_record(0));
  BOOST_CHECK(ts.is_connected());
}

BOOST_FIXTURE_TEST_CASE(test_case_4, fixture_recordTable) {
  test_slot ts;
  set_file_name(file_name);
  ::QObject::connect(this, &brick_game::recordTable::record, &ts, 
      &test_slot::connect_slot);
  BOOST_CHECK(is_record(1));
  BOOST_CHECK(ts.is_connected());

  BOOST_CHECK(!is_record(0));
  BOOST_CHECK(ts.is_connected());
}

BOOST_FIXTURE_TEST_CASE(test_case_5, fixture_recordTable) {
  BOOST_CHECK(!set_record("any_name", 10, 10));
}

BOOST_FIXTURE_TEST_CASE(test_case_6, fixture_recordTable) {
  set_file_name(file_name);
  BOOST_CHECK(!set_record("any_record_holder_name", 0, 0));
  BOOST_CHECK(set_record("any_record_holder_name", 10, 10));
  boost::filesystem::remove((brick_game::HOME + file_name).toStdString().c_str());
}

BOOST_AUTO_TEST_SUITE_END()
