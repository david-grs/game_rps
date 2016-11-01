#include <iostream>
#include <string>

namespace io
{
bool play_again()
{
    char res{' '};
    while (res != 'y' && res != 'n')
    {
        std::cout << "play again? [y/n] ";
        std::cin >> res;
        res = std::tolower(res);
    }

    return res == 'y';
}
}

namespace rps
{

enum struct symbol
{
    rock,
    scissors,
    paper
};

inline std::ostream& operator<<(std::ostream& oss, symbol sym)
{
    // TODO
    return oss << "?";
}

namespace io
{
    static symbol read_symbol()
    {
        return {};
    }
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
        rps::symbol sym = rps::io::read_symbol();
        play = io::play_again();
    }

    return 0;
}

