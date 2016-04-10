#include <cylvionpp/card.h>

#include <cylvionpp/content.h>
#include <cylvionpp/dealer.h>
#include <cylvionpp/field.h>

#include "../empty_actor.h"
#include "../empty_observer.h"

#include <catch.hpp>

TEST_CASE("A blaze card revealed on battle field", "[basic][ravage]") {
    auto pContent = cylvionpp::Content::New();
    auto pObserver = std::make_shared<EmptyObserver>();
    auto pActor = std::make_shared<EmptyActor>();

    SECTION("No other cards on battle field") {
        const auto location = cylvionpp::Location{0, 4};
        pContent->GetField().Put(location, cylvionpp::card::Blaze());

        auto pDealer = cylvionpp::Dealer::New(std::move(pContent), pObserver);
        REQUIRE(pDealer);

        bool res = pDealer->GetContent().GetField().Peek(location).OnBeforeMove(*pDealer, *pActor, location);
        REQUIRE(res);
    }

    SECTION("Elemental cards on battle field") {
        const auto blazeLocation = cylvionpp::Location{0, 4};
        pContent->GetField().Put({0, 4}, cylvionpp::card::Blaze());

        pContent->GetField().Put({1, 1}, cylvionpp::card::Elemental(0, 1));

        auto pDealer = cylvionpp::Dealer::New(std::move(pContent), pObserver);
        REQUIRE(pDealer);

        const auto & field = pDealer->GetContent().GetField();
        bool res = field.Peek(blazeLocation).OnBeforeMove(*pDealer, *pActor, blazeLocation);
        REQUIRE(res);

        auto pDestContent = cylvionpp::Content::New();
        pDestContent->GetField().Put({1, 1}, cylvionpp::card::Elemental(0, 1));
        pDestContent->GetField().Peek({1, 1}).SetBlaze();
        REQUIRE(*pDestContent == pDealer->GetContent());
    }
}
