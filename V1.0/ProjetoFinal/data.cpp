#include <string>
#include <stdexcept>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include "data.hpp"
using namespace std;


bool Date::validateDay(int day, int month, int year){
    return day >= 1 && day <= Date::numOfDaysInMonth(month, year);
}
bool Date::validateMonth(int month){
    return month >= 1 && month <= 12; // 1 a 12
}
bool Date::validateYear(int year){
    return true; //o ano pode ser qualquer n�mero inteiro
}
bool Date::validateDate(int day, int month, int year){
    return
        Date::validateYear(year) &&
        Date::validateMonth(month) &&
        Date::validateDay(day, month, year)
    ;
}
bool Date::isLeapYear(int year){
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)); //divisivel por 4 e n�o divisivel por 100 exceto se for por 400 tbm
}

int Date::numOfDaysInMonth(int month, int year){
    int days = 0;
    if(Date::validateMonth(month) && Date::validateYear(year)){
        if(month == 2 && Date::isLeapYear(year)){
            days = 29;
        }else{
            static const int numOfDays[] = {
                31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31
            };
            days = numOfDays[month - 1];
        }
    }
    return days;
}
Date::Date(){
    if(!this->setDate()){
        throw runtime_error("Erro na cria��o da data");
    }
}
Date::Date(int day, int month, int year){
    if(!this->setDate(day, month, year)){
        throw runtime_error("Data invalida");
    }
}
Date::Date(const std::string& dateStr){
    if(!this->setDate(dateStr)){
        throw runtime_error("Data invalida");
    }
}


int Date::getDay() const{return this->day;}
int Date::getMonth() const{return this->month;}
int Date::getYear() const{return this->year;}

string Date::stringify() const{
    ostringstream oss;
    oss << setfill('0')
        << setw(2) << this->getDay() << "/"
        << setw(2) << this->getMonth() << "/"
        << setw(4) << this->getYear();
    return oss.str();
}

bool Date::setDay(int day){
    bool success = Date::validateDate(day, this->getMonth(), this->getYear());
    if(success){
        this->day = day;
    }
    return success;
}
bool Date::setMonth(int month){
    bool success = Date::validateDate(this->getDay(), month, this->getYear());
    if(success){
        this->month = month;
    }
    return success;
}
bool Date::setYear(int year){
    bool success = Date::validateDate(this->getDay(), this->getMonth(), year);
    if(success){
        this->year = year;
    }
    return success;
}
bool Date::setDate(){
    time_t now = time(nullptr);            //tempo em segundos desde 1970
    tm* localTime = localtime(&now);       //convers�o para struct com data e hora local
    int year = localTime->tm_year + 1900;  //ano desde 1900, por isso soma 1900
    int month = localTime->tm_mon + 1;     //meses v�o de 0 a 11, por isso soma 1
    int day = localTime->tm_mday;          //dia do m�s

    return this->setDate(day, month, year);
}
bool Date::setDate(int day, int month, int year){
    bool success = Date::validateDate(day, month, year);
    if(success){
        this->day = day;
        this->month =  month;
        this->year = year;
    }
    return success;
}

bool Date::setDate(const std::string& dateStr){
    int day, month, year;
    sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);
    return this->setDate(day, month, year);
}



bool Date::isLeap() const{
    return Date::isLeapYear(this->getYear());
};
int Date::numOfDaysInMonth() const{
    return Date::numOfDaysInMonth(this->getMonth(), this->getYear());
}
string Date::strMonth() const{
    static const string strsMonths[] = {
        "Janeiro",
        "Fevereiro",
        "Mar�o",
        "Abril",
        "Maio",
        "Junho",
        "Julho",
        "Agosto",
        "Setembro",
        "Outubro",
        "Novembro",
        "Dezembro"
    };
    return strsMonths[this->getMonth() - 1];
};
string Date::weekDay() const{
    int q = this->getDay();
    int m = this->getMonth();
    int j = this->getYear() / 100;
    int k = this->getYear() % 100;
    if(m < 3){
        m += 12;
        k--;
    }
    int h = q + (((13 * (m + 1))/5) + k + (k/4) + (j/4) - (2*j))%7;
    if(h < 0) h += 7;
    static const string weekDays[] = {
        "S�bado",
        "Domingo",
        "Segunda",
        "Ter�a",
        "Quarta",
        "Quinta",
        "Sexta"
    };
    return weekDays[h];
};
