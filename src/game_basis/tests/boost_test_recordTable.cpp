// boost_test_recordTable.cpp

#define BOOST_TEST_MODULE test_module_recordTable
#include <boost/test/included/unit_test.hpp>

#include "recordTable/recordTable.hpp"
#include "test_slot.hpp"

BOOST_AUTO_TEST_SUITE(recordTable)

struct fixture_recordTable : public brick_game::recordTable {};

BOOST_FIXTURE_TEST_CASE(test_case_1, fixture_recordTable) {
  BOOST_CHECK(columnCount());
  BOOST_CHECK(rowCount());
}

BOOST_FIXTURE_TEST_CASE(test_case_2, fixture_recordTable) {
  BOOST_CHECK(!is_record(0));
}

BOOST_AUTO_TEST_CASE(test_case_3) {
  test_slot ts;
  brick_game::recordTable rt;
  ::QObject::connect(&rt, &brick_game::recordTable::record, &ts, 
      &test_slot::connect_slot);
  BOOST_CHECK(!rt.is_record(1));
  BOOST_CHECK(ts.is_connected());

  BOOST_CHECK(!rt.is_record(0));
  BOOST_CHECK(ts.is_connected());
}

BOOST_AUTO_TEST_CASE(test_case_4) {
  test_slot ts;
  brick_game::recordTable rt;
  rt.set_file_name("test_record_table.xml");
  ::QObject::connect(&rt, &brick_game::recordTable::record, &ts, 
      &test_slot::connect_slot);
  BOOST_CHECK(rt.is_record(1));
  BOOST_CHECK(ts.is_connected());

  BOOST_CHECK(!rt.is_record(0));
  BOOST_CHECK(ts.is_connected());
}

BOOST_FIXTURE_TEST_CASE(test_case_5, fixture_recordTable) {
  BOOST_CHECK(!set_record("any_name", 10, 10));
}

BOOST_FIXTURE_TEST_CASE(test_case_6, fixture_recordTable) {
  set_file_name("test_record_table.xml");
  BOOST_CHECK(!set_record("any_record_holder_name", 0, 0));
  BOOST_CHECK(set_record("any_record_holder_name", 10, 10));
}

BOOST_AUTO_TEST_SUITE_END()
