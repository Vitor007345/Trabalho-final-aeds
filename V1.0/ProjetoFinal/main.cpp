#include <iostream>
#include "data.hpp"
#include "person.hpp"
#include "customizableError.hpp"
#include "student.hpp"
#include "teacher.hpp"
using namespace std;

int main()
{
    try{
        cout << "Person:" <<Person::getQntOfInstances() <<endl;
        cout <<"Student: " <<Student::getQntOfInstances() <<endl;
        Person* p1 = new Person("000.000.000-00", "Pinto grosso", {"11/09/2001"});
        Person* s1 = new Student("111.000.000-00", "Pau mole", 28, 2, 2001, 123456);
        Person* t1 = new Teacher("111.001.690-12", "pica dura", 12, 2, 1940, "Mestre");
        p1->setCpf("000.000.111-00");
        cout << "Person: " << endl;
        cout << p1->info() << endl;
        cout << "Student: " << endl;
        cout << s1->info() << endl;

        cout << "Teacher: " << endl;
        cout << t1->info() << endl;



    }catch(const BaseCustomizableError& e){
        cout << e.fullMsg();
    }

    cout << "Person:" <<Person::getQntOfInstances() <<endl;
    cout <<"Student: " <<Student::getQntOfInstances() <<endl;
    cout << "Teacher: "<<Teacher::getQntOfInstances() <<endl;
    return 0;
}
