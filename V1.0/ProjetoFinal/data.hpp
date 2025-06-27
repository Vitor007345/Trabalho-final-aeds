#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

#include <string>

//classe data feita para ser sempre válida, por isso não tem o método para conferir se é valido
class Date{
    private:
        int day;
        int month;
        int year;

        static bool validateDay(int day, int month, int year);
        static bool validateMonth(int month);
        static bool validateYear(int year);
        static bool validateDate(int day, int month, int year);
        static bool isLeapYear(int year);
        static int numOfDaysInMonth(int month, int year);
    public:
        Date();
        Date(int day, int month, int year);
        Date(const std::string& dateStr);
        Date(int year);
        Date(const Date& date);
        Date(const Date* date);

        int getDay() const;
        int getMonth() const;
        int getYear() const;

        static std::string stringifyAnyDate(int day, int month, int year);
        std::string stringify() const;

        bool setDay(int day);
        bool setMonth(int month);
        bool setYear(int year);

        bool setDate();
        bool setDate(int day, int month, int year);
        bool setDate(const std::string& dateStr);
        bool setDate(int year);
        bool setDate(const Date& date);
        bool setDate(const Date* date);


        bool isLeap() const;
        int numOfDaysInMonth() const;
        std::string strMonth() const;
        std::string weekDay() const;

};

#endif // DATA_HPP_INCLUDED
