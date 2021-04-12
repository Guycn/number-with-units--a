/**
*
*Guy Cohen
*
*/
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<cmath>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;
constexpr double EPS = 0.00001;


namespace ariel{
    static map<string, map<string, double>> con_map;

    NumberWithUnits::NumberWithUnits(double val, const string& type){//init
                this->type = type;
                this->val = val;
    }

    void NumberWithUnits::add_values(const string &unit_a, const string &unit_b){
        for(auto &var : con_map[unit_b]){
            if(var.first != unit_a){
                con_map[unit_a][var.first] = var.second*con_map[unit_a][unit_b];
                con_map[var.first][unit_a] = 1/(var.second*con_map[unit_a][unit_b]);
            }
        }
    }

    //read the units from the file
    void NumberWithUnits::read_units(ifstream &units_file){
        std::string unit_A;
        std::string unit_B;
        std::string buffer;
        double value1 = 0;
        double value2 = 0;
        while(!(units_file.eof())){
            units_file >> value1 >> unit_A >> buffer >> value2 >> unit_B;
            con_map[unit_A][unit_B] = value2;
            con_map[unit_B][unit_A] = 1/value2;
            add_values(unit_A,unit_B);
            add_values(unit_B,unit_A);
        }
    }
    /**
    *
    *arithmethic operators
    */
    NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2){ //+ operator
        double temp = 0;
        if(num1.type == num2.type){
            return NumberWithUnits((num1.val + num2.val), num1.type);
        }
        try{
            temp = con_map.at(num2.type).at(num1.type);
            return NumberWithUnits((num1.val + (num2.val*temp)), num1.type);
        }
        catch(exception& e){
            throw invalid_argument("Different units"); //different types of units
        }
    }

    NumberWithUnits operator+(const NumberWithUnits &num1, double num){ //(+) operator
        return NumberWithUnits((num1.val + num), num1.type);
    }

    NumberWithUnits operator-(const NumberWithUnits& num1, double num){//(-) operator
        return NumberWithUnits((num1.val - num), num1.type);
    }

    NumberWithUnits operator-(NumberWithUnits& num1){
        return NumberWithUnits(-num1.val, num1.type);
    }

    NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2){//(-) operator
        double temp = 0;
        if(num1.type == num2.type){
            return NumberWithUnits((num1.val - num2.val), num1.type);
        }
        try{
            temp = con_map.at(num2.type).at(num1.type);
            return NumberWithUnits((num1.val - (num2.val*temp)), num1.type); //different types of units
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }

    }

    NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2){//(-=) operator
        double temp = 0;
        if(num1.type == num2.type){
            num1.val -= num2.val;
            return num1;
        }
        try{
            temp = con_map.at(num2.type).at(num1.type);
            num1.val -= num2.val*temp; 
            return num1;
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }

    }


    NumberWithUnits operator+=(NumberWithUnits &num1, const NumberWithUnits &num2){//(+=) operator
        double temp = 0;
        if(num1.type == num2.type){
            num1.val += num2.val;
            return num1;
        }
        try{
            temp = con_map.at(num2.type).at(num1.type);
            num1.val += num2.val*temp; 
            return num1;
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }
    /**
    *
    *comparison operators.
    *return boolean value
    */

    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2){ //bigger
        double temp = 0;
        if(num1.type == num2.type){
            return (num1.val > num2.val); //if num1 value bigger than num2 value: return true, else return false
        }
        try{
            temp = con_map.at(num2.type).at(num1.type); 
            return ((num1.val - num2.val*temp)>0);               //if num1 value bigger than num2 value: return true, else return false
        }
        catch(exception& e){
            throw invalid_argument("Different units");   //different types of units
        }
    }
    bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2){ //smaller
        double temp = 0;
        if(num1.type == num2.type){
            return (num1.val < num2.val);   //if num2 value bigger than num1 value: return true, else return false 
        }
        try{
            temp = con_map.at(num2.type).at(num1.type); 
            return (num1.val < num2.val*temp);    //if num2 value bigger than num1 value: return true, else return false
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }
    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2){//bigger or equal
        double temp = 0;
        if(num1.type == num2.type){
            return ((num1.val > num2.val) || num1.val == num2.val);   //if num1 value bigger or equal than num2 value: return true, else return false 
        }
        try{
            temp = con_map.at(num2.type).at(num1.type);
            return ((num1.val > num2.val*temp) || (num1.val == num2.val*temp));    //if num1 value bigger or equal than num2 value: return true, else return false 
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }

    bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2){//smaller or equal
        double temp = 0;
        if(num1.type == num2.type){
            return ((num1.val < num2.val) || (num1.val == num2.val));   //if num2 value bigger or equal than num1 value: return true, else return false 
        }   
        try{
            temp = con_map.at(num2.type).at(num1.type); 
            return ((num1.val < num2.val*temp) || (num1.val == num2.val*temp));    //if num2 value bigger or equal than num1 value: return true, else return false 
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }

    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2){//equal
        double temp = 0;
        if(num1.type == num2.type){
            return (num1.val == num2.val);   //if num2 value equal to num1 value: return true, else return false 
        }
        try{
            temp = con_map.at(num2.type).at(num1.type); 
            return (fabs(temp*num2.val - num1.val)<EPS);    //if num2 value equal to num1 value: return true, else return false 
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }
    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2){//not equal
        double temp = 0;
        if(num1.type == num2.type){
            return (!(num1.val == num2.val));   //if num2 value not equal to num1 value: return true, else return false 
        }
        try{
            temp = con_map.at(num2.type).at(num1.type); 
            return (!(num1.val == num2.val*temp));    //if num2 value not equal to num1 value: return true, else return false 
        }
        catch(exception& e){
            throw invalid_argument("Different units");//different types of units
        }
    }

    /*
    Operator name 	   Syntax 	     	        Prototype examples
    *                              Inside class definition 	  Outside class definition
    *pre-increment 	    ++a 	 	 T& T::operator++(); 	     T& operator++(T& a);
    *pre-decrement 	    --a 	 	 T& T::operator--(); 	     T& operator--(T& a);
    *post-increment 	a++ 	 	 T T::operator++(int); 	     T operator++(T& a, int);
    *post-decrement 	a-- 	 	 T T::operator--(int); 	     T operator--(T& a, int);
    */
    NumberWithUnits operator++(NumberWithUnits &num){ //++a
        return NumberWithUnits(++num.val, num.type);
    }
    NumberWithUnits operator--(NumberWithUnits &num){ //--a
        return NumberWithUnits(--num.val, num.type);
    }
    NumberWithUnits operator++(NumberWithUnits &num, int){//a++
        return NumberWithUnits(num.val++, num.type);
    }
    NumberWithUnits operator--(NumberWithUnits &num, int){//a--
        return NumberWithUnits(num.val--, num.type);
    }

    /**
    *
    *dup operator
    *
    */
    NumberWithUnits operator*(NumberWithUnits &num1, double num){
        return NumberWithUnits((num1.val * num), num1.type);
    }

    NumberWithUnits operator*(double num, NumberWithUnits &num1){
        return NumberWithUnits((num1.val * num), num1.type);
    }

    /**
    *
    *output and input
    */
    ostream &operator << (std::ostream& out, const NumberWithUnits &type){
        return out << type.val << "[" << type.type << "]";
    }

    istream &operator >> (std::istream& in, NumberWithUnits &type){
        std::string s;
        in >> type.val >> s >> type.type;
        return in;
    }


}