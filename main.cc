#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>

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

    inline std::ostream& operator<<(std::ostream& oss, symbol sym)
    {
        // TODO
        return oss << "?";
    }

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

    static symbol read_symbol()
    {
        char s = io::read_one_of("rock, paper, scissors... ?", {'r', 'p', 's'});
        return to_symbol(s);
    }

    struct game
    {


        int get_scope_ai() const { return _score_ai; }
        int get_scope_hum() const { return _score_hum; }

    private:
        int _score_ai;
        int _score_hum;
    };

}

int main()
{
    for (bool play = true; play; )
    {
        rps::game g;
       // rps::symbol sym = rps::io::read_symbol();
        play = io::play_again();
    }

    return 0;
}

