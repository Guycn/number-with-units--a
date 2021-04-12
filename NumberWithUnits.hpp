/**
*Guy Cohen
*
*/




#include <iostream>
#include <string>

using namespace std;

namespace ariel{
    class NumberWithUnits{
        private:
            double val;
            std::string type;


        public:
            NumberWithUnits(double, const std::string &);
            static void read_units(ifstream &units_file);
            static void add_values(const string &unit_a, const string &unit_b);
            /**
            *
            *arithmethic operators
            */
            friend NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend NumberWithUnits operator+(const NumberWithUnits& num1, double num);
            friend NumberWithUnits operator-(const NumberWithUnits& num1, double num);
            friend NumberWithUnits operator-(NumberWithUnits& num1);
            friend NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend NumberWithUnits operator+=(NumberWithUnits& num1, const NumberWithUnits& num2);
            friend NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2);

            /**
            *
            *comparison operators.
            *return boolean value
            */
            friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2); //bigger
            friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2); //smaller
            friend bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2);//bigger or equal
            friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);//smaller or equal
            friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);//equal
            friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);//not equal

            /*
            Operator name 	Syntax 	     	        Prototype examples
                                        Inside class definition 	Outside class definition
            pre-increment 	++a 	 	T& T::operator++(); 	    T& operator++(T& a);
            pre-decrement 	--a 	 	T& T::operator--(); 	    T& operator--(T& a);
            post-increment 	a++ 	 	T T::operator++(int); 	    T operator++(T& a, int);
            post-decrement 	a-- 	 	T T::operator--(int); 	    T operator--(T& a, int);
            */
            friend NumberWithUnits operator++(NumberWithUnits& num); //++a
            friend NumberWithUnits operator--(NumberWithUnits& num); //--a
            friend NumberWithUnits operator++(NumberWithUnits& num, int);//a++
            friend NumberWithUnits operator--(NumberWithUnits& num, int);//a--

            /*
            *
            *dup opertator
            */

            friend NumberWithUnits operator*(NumberWithUnits& num1, double num);
            friend NumberWithUnits operator*(double num, NumberWithUnits& num1);

            /**
            *
            *output and input
            */
            friend std::ostream &operator << (std::ostream& out, const NumberWithUnits& type);   //output
            friend std::istream &operator >> (std::istream& in, NumberWithUnits& type);   //input
            

            


    };
};