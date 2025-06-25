#include <iostream>
#include "data.hpp"
using namespace std;

int main()
{
    Date* hoje = new Date("11/09/2001");
    cout << hoje->stringify() << endl;
    return 0;
}
