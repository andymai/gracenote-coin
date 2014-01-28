#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "util.h"

BOOST_AUTO_TEST_SUITE(getarg_tests)

static void
ResetArgs(const std::string& strArg)
{
    std::vector<std::string> vecArg;
    boost::split(vecArg, strArg, boost::is_space(), boost::token_compress_on);

    // Insert dummy executable name:
    vecArg.insert(vecArg.begin(), "testbitcoin");

    // Convert to char*:
    std::vector<const char*> vecChar;
    BOOST_FOREACH(std::string& s, vecArg)
        vecChar.push_back(s.c_str());

    ParseParameters(vecChar.size(), &vecChar[0]);
}

BOOST_AUTO_TEST_CASE(boolarg)
{
    ResetArgs("-GNC");
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", false));
    BOOST_CHECK(GetBoolArg("-GNC", true));

    BOOST_CHECK(!GetBoolArg("-fo"));
    BOOST_CHECK(!GetBoolArg("-fo", false));
    BOOST_CHECK(GetBoolArg("-fo", true));

    BOOST_CHECK(!GetBoolArg("-GNCo"));
    BOOST_CHECK(!GetBoolArg("-GNCo", false));
    BOOST_CHECK(GetBoolArg("-GNCo", true));

    ResetArgs("-GNC=0");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", false));
    BOOST_CHECK(!GetBoolArg("-GNC", true));

    ResetArgs("-GNC=1");
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", false));
    BOOST_CHECK(GetBoolArg("-GNC", true));

    // New 0.6 feature: auto-map -nosomething to !-something:
    ResetArgs("-noGNC");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", false));
    BOOST_CHECK(!GetBoolArg("-GNC", true));

    ResetArgs("-noGNC=1");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", false));
    BOOST_CHECK(!GetBoolArg("-GNC", true));

    ResetArgs("-GNC -noGNC");  // -GNC should win
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", false));
    BOOST_CHECK(GetBoolArg("-GNC", true));

    ResetArgs("-GNC=1 -noGNC=1");  // -GNC should win
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", false));
    BOOST_CHECK(GetBoolArg("-GNC", true));

    ResetArgs("-GNC=0 -noGNC=0");  // -GNC should win
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", false));
    BOOST_CHECK(!GetBoolArg("-GNC", true));

    // New 0.6 feature: treat -- same as -:
    ResetArgs("--GNC=1");
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", false));
    BOOST_CHECK(GetBoolArg("-GNC", true));

    ResetArgs("--noGNC=1");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", false));
    BOOST_CHECK(!GetBoolArg("-GNC", true));

}

BOOST_AUTO_TEST_CASE(stringarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-GNC", "eleven"), "eleven");

    ResetArgs("-GNC -GNC");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-GNC", "eleven"), "");

    ResetArgs("-GNC=");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-GNC", "eleven"), "");

    ResetArgs("-GNC=11");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "11");
    BOOST_CHECK_EQUAL(GetArg("-GNC", "eleven"), "11");

    ResetArgs("-GNC=eleven");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "eleven");
    BOOST_CHECK_EQUAL(GetArg("-GNC", "eleven"), "eleven");

}

BOOST_AUTO_TEST_CASE(intarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-GNC", 11), 11);
    BOOST_CHECK_EQUAL(GetArg("-GNC", 0), 0);

    ResetArgs("-GNC -GNC");
    BOOST_CHECK_EQUAL(GetArg("-GNC", 11), 0);
    BOOST_CHECK_EQUAL(GetArg("-GNC", 11), 0);

    ResetArgs("-GNC=11 -GNC=12");
    BOOST_CHECK_EQUAL(GetArg("-GNC", 0), 11);
    BOOST_CHECK_EQUAL(GetArg("-GNC", 11), 12);

    ResetArgs("-GNC=NaN -GNC=NotANumber");
    BOOST_CHECK_EQUAL(GetArg("-GNC", 1), 0);
    BOOST_CHECK_EQUAL(GetArg("-GNC", 11), 0);
}

BOOST_AUTO_TEST_CASE(doubledash)
{
    ResetArgs("--GNC");
    BOOST_CHECK_EQUAL(GetBoolArg("-GNC"), true);

    ResetArgs("--GNC=verbose --GNC=1");
    BOOST_CHECK_EQUAL(GetArg("-GNC", ""), "verbose");
    BOOST_CHECK_EQUAL(GetArg("-GNC", 0), 1);
}

BOOST_AUTO_TEST_CASE(boolargno)
{
    ResetArgs("-noGNC");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", true));
    BOOST_CHECK(!GetBoolArg("-GNC", false));

    ResetArgs("-noGNC=1");
    BOOST_CHECK(!GetBoolArg("-GNC"));
    BOOST_CHECK(!GetBoolArg("-GNC", true));
    BOOST_CHECK(!GetBoolArg("-GNC", false));

    ResetArgs("-noGNC=0");
    BOOST_CHECK(GetBoolArg("-GNC"));
    BOOST_CHECK(GetBoolArg("-GNC", true));
    BOOST_CHECK(GetBoolArg("-GNC", false));

    ResetArgs("-GNC --noGNC");
    BOOST_CHECK(GetBoolArg("-GNC"));

    ResetArgs("-noGNC -GNC"); // GNC always wins:
    BOOST_CHECK(GetBoolArg("-GNC"));
}

BOOST_AUTO_TEST_SUITE_END()
