#include <iostream>
#include "data.hpp"
#include "person.hpp"
using namespace std;

int main()
{
    Date* hoje = new Date();
    Date* outra = new Date(1, 1, 1963);
    outra->setDate(hoje);
    cout << outra->stringify() << endl;
    cout << outra->numOfDaysInMonth() << endl;
    return 0;
}
