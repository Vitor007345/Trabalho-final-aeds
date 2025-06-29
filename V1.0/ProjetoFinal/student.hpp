#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED


#include <string>
#include <type_traits>
#include <utility>
#include <sstream>
#include "person.hpp"
#include "utils.hpp"

//checagem de tipos
template<typename StringCpf, typename StringName, typename IntOrString>
struct checkTypes{
    static constexpr bool value =
        std::is_convertible<StringCpf, std::string>::value &&
        std::is_convertible<StringName, std::string>::value &&
        (std::is_convertible<IntOrString, std::string>::value ||
         std::is_same<IntOrString, int>::value
        )
    ;
};

class Student : public Person{
    private:
        int matricula;
        static int qntOfInstances;

        template<typename SringCpf, typename StringName, typename IntOrString>
        void configConstruction(IntOrString&& matricula){
            static_assert(
                checkTypes<SringCpf, StringName, IntOrString>::value,
                "cpf e nome devem ser conversiveis pra string e matricula ser int ou string"
            );
            this->setMatricula(std::forward<IntOrString>(matricula));
            qntOfInstances++;
        }
    public:
        Student() : Person() {
            this->setMatricula(0);
            qntOfInstances++;
        }

        template<typename SringCpf, typename StringName, typename IntOrString = int>
        Student(SringCpf&& cpf, StringName&& name, IntOrString&& matricula = 0)
            : Person(std::forward<SringCpf>(cpf), std::forward<StringName>(name))
        {
            configConstruction<SringCpf, StringName, IntOrString>(std::forward<IntOrString>(matricula));
        }

        template<typename SringCpf, typename StringName, typename IntOrString = int>
        Student(SringCpf&& cpf, StringName&& name, int day, int month, int year, IntOrString&& matricula = 0)
            : Person(std::forward<SringCpf>(cpf), std::forward<StringName>(name), day, month, year)
        {
            configConstruction<SringCpf, StringName, IntOrString>(std::forward<IntOrString>(matricula));
        }

        template<typename SringCpf, typename StringName, typename IntOrString = int>
        Student(SringCpf&& cpf, StringName&& name, const Date& birth, IntOrString&& matricula = 0)
            : Person(std::forward<SringCpf>(cpf), std::forward<StringName>(name), birth)
        {
            configConstruction<SringCpf, StringName, IntOrString>(std::forward<IntOrString>(matricula));
        }

        template<typename SringCpf, typename StringName, typename IntOrString = int>
        Student(SringCpf&& cpf, StringName&& name, const Date* birth, IntOrString&& matricula = 0)
            : Student(std::forward<SringCpf>(cpf), std::forward<StringName>(name), *birth, std::forward<IntOrString>(matricula)) {}

        ~Student(){
            qntOfInstances--;
        }

        int getMatricula() const noexcept{
            return this->matricula;
        }
        std::string getMatriculaStr() const noexcept{
            std::string matStr;
            int numDigitsMat = numDigits(this->getMatricula());
            if(numDigitsMat < 6){
                matStr = std::string(6 - numDigitsMat, '0');
            }
            matStr += std::to_string(this->getMatricula());
            return matStr;

        };
        static int getQntOfInstances() noexcept{
            return qntOfInstances;
        }

        bool setMatricula(int matricula){

            bool success = false;
            if(numDigits(matricula) <= 6){
                this->matricula = matricula;
                success = true;
            }
            return success;
        }
        bool setMatricula(const std::string& matriculaStr){
            bool success = false;
            int numMat;
            std::stringstream ss(matriculaStr);
            if(ss >> numMat){
                success = this->setMatricula(numMat);
            }
            return success;
        }

        bool setMatricula(std::string&& matriculaStr){
            bool success = false;
            int numMat;
            std::stringstream ss(std::move(matriculaStr));
            if(ss >> numMat){
                success = this->setMatricula(numMat);
            }
            return success;
        }

        std::string info() const noexcept override{
            return Person::info() + "\nMatricula: " + this->getMatriculaStr();
        }
};

int Student::qntOfInstances = 0;




#endif // STUDENT_HPP_INCLUDED
