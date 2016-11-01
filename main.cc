#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
#include <random>
#include <experimental/optional>

namespace io
{

    // ask question and read the input until any of the character in choices has been read
    // choices has to be size() > 1
    char read_one_of(const char* question, const std::vector<char>& choices)
    {
        assert(choices.size() > 1);

        char res;

        std::ostringstream oss;
        for (auto it = choices.begin(); it != choices.end() - 1; ++it)
            oss << *it << "/";

        oss << choices.back();
        std::string choice = oss.str();

        do
        {
            std::cout << question << " " << choice << " ";
            std::cin >> res;
        }
        while (!std::any_of(std::cbegin(choices), std::cend(choices), [&res](char opt) { return res == opt; }));

        return res;
    }

    bool play_again()
    {
        return read_one_of("play again?", {'y', 'n'}) == 'y';
    }

}


namespace rps
{

    enum struct symbol
    {
        rock,
        paper,
        scissors,
    };

    symbol to_symbol(char sym)
    {
        switch(sym)
        {
        case 'r': return symbol::rock;
        case 'p': return symbol::paper;
        case 's': return symbol::scissors;
        default: throw std::runtime_error("unknown symbol: " + sym);
        }
    }

    static symbol read_symbol_stdin()
    {
        char s = io::read_one_of("rock, paper, scissors... ?", {'r', 'p', 's'});
        return to_symbol(s);
    }

    namespace detail
    {
        static std::experimental::optional<std::string> fight(symbol lhs, symbol rhs)
        {
            if (lhs == symbol::rock && rhs == symbol::scissors)
                return {"rock blunts scissors!"};
            else if (lhs == symbol::paper && rhs == symbol::rock)
                return {"paper wraps rock!"};
            else if (lhs == symbol::scissors && rhs == symbol::paper)
                return {"scissors cuts paper!"};
            return {};
        }
    }

    static std::pair<int, std::string> fight(symbol lhs, symbol rhs)
    {
        auto msg = detail::fight(lhs, rhs);
        if (msg)
            return {1, *msg};

        msg = detail::fight(rhs, lhs);
        if (msg)
            return {-1, *msg};

        return {0, "tie!"};
    }

    struct game
    {
        game()
         : _gen(_rd()),
           _rng(0, 2) // generate random numbers in [0-2]
        {}

        void play()
        {
            symbol hum_sym = read_symbol_stdin();

            static const char choices[] = {'r','p','s'};
            symbol ai_sym = to_symbol(choices[_rng(_gen)]);

            auto p = fight(hum_sym, ai_sym);

            assert(p.first >= -1 && p.first <= 1);

            if (p.first == 1)
                ++_score_hum;
            else if (p.first == -1)
                ++_score_ai;

            std::cout << p.second << std::endl;
        }

        int get_scope_ai() const { return _score_ai; }
        int get_scope_hum() const { return _score_hum; }

    private:

        int _score_ai = 0;
        int _score_hum = 0;

        std::random_device _rd;
        std::mt19937 _gen;
        std::uniform_int_distribution<> _rng;
    };

}

int main()
{
    for (bool play = true; play; )
    {
        rps::game g;
        g.play();

        play = io::play_again();
    }

    return 0;
}

