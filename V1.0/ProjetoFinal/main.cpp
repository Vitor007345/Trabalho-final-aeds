#include <iostream>
#include "data.hpp"
#include "person.hpp"
#include "customizableError.hpp"
using namespace std;

int main()
{
    try{
        Person* p1 = new Person("000.000.000-00", "Pinto grosso", 11, 9, 2009);
        printf("%s\n", p1->setBirth(Date(32, 1, 2007))? "true" : "false");
        cout << p1->info() << endl;
    }catch(const BaseCustomizableError& e){
        cout << e.fullMsg();
    }

    return 0;
}
