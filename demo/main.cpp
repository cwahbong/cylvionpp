#include <iostream>
#include <string>

#include <cylvionpp/actor.h>
#include <cylvionpp/card.h>
#include <cylvionpp/content.h>
#include <cylvionpp/field.h>
#include <cylvionpp/hand.h>
#include <cylvionpp/observer.h>
#include <cylvionpp/operation.h>
#include <cylvionpp/game.h>
#include <cylvionpp/intro.h>

#include <sstream>

std::string
DumpCard(const cylvionpp::Card & card)
{
    std::ostringstream oss;
    if (card.IsCylvan()) {
        oss << "c";
        oss << card.GetStrength();
    } else if (card.IsRavage()) {
        oss << (card.IsBlazing() ? "R" : "r");
        oss << card.GetStrength();
    } else {
        oss << "XX";
    }
    return oss.str();
}

std::string
DumpField(const cylvionpp::Field & field)
{
    std::ostringstream oss;
    for (cylvionpp::Index row = 0; row < cylvionpp::Field::row; ++row) {
        for (cylvionpp::Index col = 0; col < cylvionpp::Field::col; ++col) {
            oss << " [" << DumpCard(field.Peek({row, col})) << "]";
        }
        oss << "\n";
    }
    return oss.str();
}

std::string
DumpHand(const cylvionpp::Hand & hand)
{
    std::ostringstream oss;
    for (cylvionpp::Index idx = 0; idx < (int) hand.Size(); ++idx) {
        oss << " [" << DumpCard(*hand.Peek(idx)) << "]";
    }
    oss << "\n";
    return oss.str();
}

std::string
DumpContent(const cylvionpp::Content & content)
{
    std::ostringstream oss;
    oss << "Content:\n"
        << DumpField(content.GetField())
        << "---\n"
        << "Mana: " << content.GetMana() << "\n"
        << DumpHand(content.GetHand());
    return oss.str();
}

cylvionpp::Action
ParseAction(const std::string & line)
{
    std::istringstream iss(line);
    std::string action;
    iss >> action;
    if (action == "end") {
        return cylvionpp::Action{true, {}};
    } else if (action == "use" || action == "discard") {
        std::string idx;
        iss >> idx;
        return cylvionpp::Action{false, {
            {"type", action},
            {"idx", idx}
            }};
    }
    std::cerr << "err, treat as end\n";
    return cylvionpp::Action{true, {}};
}

class MyActor: public cylvionpp::Actor {
public:
    cylvionpp::Index AnswerIndex(const std::string & question) const override;
    cylvionpp::Action RevealAction(const cylvionpp::Content &) const override;
    cylvionpp::Action DefendAction(const cylvionpp::Content &) const override;
};

cylvionpp::Index
MyActor::AnswerIndex(const std::string & question) const
{
    std::cout << "Question: " << question << std::endl;
    std::string line;
    std::getline(std::cin, line);
    return std::stoul(line);
}

cylvionpp::Action
MyActor::RevealAction(const cylvionpp::Content & content) const
{
    std::cout << DumpContent(content) << std::endl;
    std::cout << "Reveal action:" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    return ParseAction(line);
}

cylvionpp::Action
MyActor::DefendAction(const cylvionpp::Content & content) const
{
    std::cout << DumpContent(content) << std::endl;
    std::cout << "Defend action:" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    return ParseAction(line);
}

class MyObserver: public cylvionpp::Observer {
    void BeforeOperation(const cylvionpp::Operation &) override;
    void AfterOperation(const cylvionpp::Operation &) override;
};

void
MyObserver::BeforeOperation(const cylvionpp::Operation &)
{/* Empty. */}

void
MyObserver::AfterOperation(const cylvionpp::Operation & operation)
{
    std::cout << "Dealer do [" << operation.GetName()
              << "]: " << operation.GetDescription() << "." << std::endl;
}

int main()
{
    auto actor = std::make_shared<MyActor>();
    auto observer = std::make_shared<MyObserver>();
    auto game = cylvionpp::MakeIntroGame(actor, observer);
    if (game->Run()) {
        std::cout << "Win" << std::endl;
    } else {
        std::cout << "Lose" << std::endl;
    }
}
