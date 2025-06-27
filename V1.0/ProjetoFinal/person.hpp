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
        *   *Apenas erros inesperados são lançados novamente*
        *
        *   Caso da data seja invalida só engole e retorna false,
        *   para mater os padõres dos sets da classe Date que retornam
        *   bool se foi possível alterar a data ou não no caso de não
        *   estar valido os valores passados
        **********************************************************/
        template<typename... Args>
        bool setBirth(Args&&... args){ //tive q botar o corpo dessa função aqui pq no cpp buga
            bool success = false;
            if(this->birth == nullptr){
                try{
                    this->birth = new Date(std::forward<Args>(args)...);
                    success = true;
                }catch(const CustomizableError<std::invalid_argument>& e){

                    if(e.getMsg("type") != std::string("Invalid date")){
                        throw e;
                    }

                    //aqui, qnd data é inválida, success continua false, valor inicializado na variavel success
                }
            }else{
                success = this->birth->setDate(std::forward<Args>(args)...);
            }

            return success;
        }


        std::string info() const noexcept;


};


#endif // PERSON_HPP_INCLUDED
