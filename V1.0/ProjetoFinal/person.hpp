#ifndef PERSON_HPP_INCLUDED
#define PERSON_HPP_INCLUDED

#include <string>
#include <utility>
#include "customizableError.hpp"
#include "data.hpp"

class Person{
    private:
        std::string cpf;
        std::string name;
        Date* birth;
        static int qntOfInstances;
    public:
        Person();
        Person(const std::string& cpf, const std::string& name);
        Person(const std::string& cpf, const std::string& name, int day, int month, int year);
        Person(const std::string& cpf, const std::string& name, const Date& birth);
        Person(const std::string& cpf, const std::string& name, const Date* birth);

        virtual ~Person();

        std::string getCpf() const noexcept;
        std::string getName() const noexcept;
        const Date* getBirth() const noexcept;
        static int getQntOfInstances() noexcept;

        bool setCpf(const std::string& cpf) noexcept;
        bool setName(const std::string& name) noexcept;

        /********************************************************
        *   *Apenas erros inesperados s�o lan�ados novamente*
        *
        *   Caso da data seja invalida s� engole e retorna false,
        *   para mater os pad�res dos sets da classe Date que retornam
        *   bool se foi poss�vel alterar a data ou n�o no caso de n�o
        *   estar valido os valores passados
        **********************************************************/
        template<typename... Args>
        bool setBirth(Args&&... args){ //tive q botar o corpo dessa fun��o aqui pq no cpp buga
            bool success = false;
            if(this->birth == nullptr){
                try{
                    this->birth = new Date(std::forward<Args>(args)...);
                    success = true;
                }catch(const CustomizableError<std::invalid_argument>& e){

                    if(e.getMsg("type") != std::string("Invalid date")){
                        throw e;
                    }

                    //aqui, qnd data � inv�lida, success continua false, valor inicializado na variavel success
                }
            }else{
                success = this->birth->setDate(std::forward<Args>(args)...);
            }

            return success;
        }


        std::string info() const noexcept;


};


#endif // PERSON_HPP_INCLUDED
