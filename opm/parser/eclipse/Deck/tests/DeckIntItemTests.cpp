/*
  Copyright 2013 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE DeckItemTests

#include <opm/common/utility/platform_dependent/disable_warnings.h>
#include <boost/test/unit_test.hpp>
#include <opm/common/utility/platform_dependent/reenable_warnings.h>

#include <stdexcept>
#include <opm/parser/eclipse/Deck/DeckIntItem.hpp>

using namespace Opm;

BOOST_AUTO_TEST_CASE(Initialize) {
    BOOST_REQUIRE_NO_THROW(DeckIntItem deckIntItem("TEST"));
}


BOOST_AUTO_TEST_CASE(HasValue) {
    DeckIntItem deckIntItem("TEST");
    BOOST_CHECK_EQUAL( false , deckIntItem.hasValue(0) );
    deckIntItem.push_back(1);
    BOOST_CHECK_EQUAL( true  , deckIntItem.hasValue(0) );
    BOOST_CHECK_EQUAL( false , deckIntItem.hasValue(1) );
}




BOOST_AUTO_TEST_CASE(DummyDefaults) {
    DeckIntItem deckIntItem("TEST");
    BOOST_CHECK_EQUAL(deckIntItem.size(), 0);

    deckIntItem.push_backDummyDefault();
    BOOST_CHECK_EQUAL(deckIntItem.size(), 0);
    BOOST_CHECK_EQUAL(true, deckIntItem.defaultApplied(0));
    BOOST_CHECK_EQUAL( false , deckIntItem.hasValue(0));
    BOOST_CHECK_EQUAL( false , deckIntItem.hasValue(1));
    BOOST_CHECK_THROW(deckIntItem.getInt(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(GetIntAtIndex_NoData_ExceptionThrown) {
    DeckIntItem deckIntItem("TEST");
    deckIntItem.push_back(100);
    BOOST_CHECK(deckIntItem.getInt(0) == 100);
    BOOST_CHECK_THROW(deckIntItem.getInt(1), std::out_of_range);
}





BOOST_AUTO_TEST_CASE(InitializeDefaultApplied) {
    DeckIntItem deckIntItem("TEST");
    BOOST_CHECK( deckIntItem.size() == 0 );
}

BOOST_AUTO_TEST_CASE(size_correct) {
    DeckIntItem deckIntItem("TEST");

    BOOST_CHECK_EQUAL( 0U , deckIntItem.size());
    deckIntItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 1U , deckIntItem.size());

    deckIntItem.push_back( 100 );
    deckIntItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 3U , deckIntItem.size());
}

BOOST_AUTO_TEST_CASE(DefaultNotApplied) {
    DeckIntItem deckIntItem("TEST");
    BOOST_CHECK( deckIntItem.size() == 0 );

    deckIntItem.push_back( 100 );
    BOOST_CHECK( deckIntItem.size() == 1 );
    BOOST_CHECK( deckIntItem.getInt(0) == 100 );
    BOOST_CHECK( !deckIntItem.defaultApplied(0) );

    BOOST_CHECK_THROW( deckIntItem.defaultApplied(1), std::out_of_range );
    BOOST_CHECK_THROW( deckIntItem.getInt(1), std::out_of_range );
}

BOOST_AUTO_TEST_CASE(UseDefault) {
    DeckIntItem deckIntItem("TEST");

    deckIntItem.push_backDefault( 100 );

    BOOST_CHECK( deckIntItem.defaultApplied(0) );
    BOOST_CHECK( deckIntItem.getInt(0) == 100 );

    BOOST_CHECK_THROW( deckIntItem.defaultApplied(1), std::out_of_range );
    BOOST_CHECK_THROW( deckIntItem.getInt(1), std::out_of_range );
}

BOOST_AUTO_TEST_CASE(DefaultApplied) {
    DeckIntItem deckIntItem("TEST");
    BOOST_CHECK( deckIntItem.size() == 0 );

    deckIntItem.push_backDefault( 100 );
    BOOST_CHECK( deckIntItem.size() == 1 );
    BOOST_CHECK( deckIntItem.getInt(0) == 100 );
    BOOST_CHECK( deckIntItem.defaultApplied(0) );
    deckIntItem.push_back( 10 );
    BOOST_CHECK_EQUAL( false, deckIntItem.defaultApplied(1) );
    deckIntItem.push_backDefault( 1 );
    BOOST_CHECK_EQUAL( true , deckIntItem.defaultApplied(2) );
    BOOST_CHECK_EQUAL( 3 , deckIntItem.size() );
}


BOOST_AUTO_TEST_CASE(PushBackMultiple) {
    DeckIntItem item("HEI");
    item.push_backMultiple(10 , 100U );
    BOOST_CHECK_EQUAL( 100U , item.size() );
    for (size_t i=0; i < 100; i++)
        BOOST_CHECK_EQUAL(10 , item.getInt(i));
}



