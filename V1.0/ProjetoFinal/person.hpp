#include <string>
#include "data.hpp"
#ifndef PERSON_HPP_INCLUDED
#define PERSON_HPP_INCLUDED

class Person{
    private:
        std::string cpf;
        std::string name;
        Date* birth;
        static int qntOfInstances;
    public:
        Person();
        Person(const std::string& name);
        Person(const std::string& cpf, const std::string& name);
        Person(const std::string& name, int day, int month, int year);
        Person(const std::string& cpf, const std::string& name, int day, int month, int year);
        Person(const std::string& name, const Date& birth);
        Person(const std::string& name, const Date* birth);
        Person(const std::string& cpf, const std::string& name, const Date& birth);
        Person(const std::string& cpf, const std::string& name, const Date* birth);

        virtual ~Person();

        std::string getCpf() const;
        std::string getName() const;
        const Date& getBirth() const;
        static int getQntOfInstances();

        bool setCpf(const std::string& cpf);
        bool setName(const std::string& name);

        bool setBirth(int day, int month, int year);
        bool setBirth(const Date& birth);
        bool setBirth(const Date* birth);



};


#endif // PERSON_HPP_INCLUDED
