#include "test/basic_test.h"
#include <boost/test/test_case_template.hpp>
#include <cstdio>

namespace
{
    struct sqlite_fixture
    {
        sqlite_fixture()
        {

        }

        ~sqlite_fixture()
        {
            std::remove("nanodbc.db");
        }

    };

    // According to the sqliteodbc documentation,
    // driver name is different on Windows and Unix.
#ifdef _WIN32
    const nanodbc::string_type driver_name(NANODBC_TEXT("SQLite3 ODBC Driver"));
#else
    const nanodbc::string_type driver_name(NANODBC_TEXT("SQLite3"));
#endif
    const nanodbc::string_type connection_string
        = NANODBC_TEXT("Driver=") + driver_name
        + NANODBC_TEXT(";Database=nanodbc.db;");
    basic_test test(connection_string);
}

BOOST_FIXTURE_TEST_SUITE(sqlite, sqlite_fixture)

BOOST_AUTO_TEST_CASE(decimal_conversion_test)
{
    test.decimal_conversion_test();
}

BOOST_AUTO_TEST_CASE(exception_test)
{
    test.exception_test();
}

BOOST_AUTO_TEST_CASE(execute_multiple_transaction_test)
{
    test.execute_multiple_transaction_test();
}

BOOST_AUTO_TEST_CASE(execute_multiple_test)
{
    test.execute_multiple_test();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(integral_test, T, basic_test::integral_test_types)
{
    test.integral_test_template<T>();
}

#ifndef BOOST_NO_RVALUE_REFERENCES
    BOOST_AUTO_TEST_CASE(move_test)
    {
        test.move_test();
    }
#endif

BOOST_AUTO_TEST_CASE(null_test)
{
    test.null_test();
}

BOOST_AUTO_TEST_CASE(simple_test)
{
    test.simple_test();
}

BOOST_AUTO_TEST_CASE(string_test)
{
    test.string_test();
}

BOOST_AUTO_TEST_CASE(transaction_test)
{
    test.transaction_test();
}

BOOST_AUTO_TEST_SUITE_END()
