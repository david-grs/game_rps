#include <iostream>

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

int main()
{
    for (bool play = true; play; )
    {


        play = io::play_again();
    }

    return 0;
}

