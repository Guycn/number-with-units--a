//Guy Cohen
#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};


TEST_CASE("Arithmethic Operators (+)"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "kg"};
    NumberWithUnits b{1900, "g"};
    NumberWithUnits c{0.3, "ton"};
    NumberWithUnits d{1900, "m"};
    NumberWithUnits f{19, "km"};
    //------------------(+)---------------------
    CHECK_EQ((a+b), NumberWithUnits(6.9, "kg"));
    CHECK_EQ((3*a), NumberWithUnits(15, "kg"));
    CHECK_EQ((0.5*a), NumberWithUnits(2.5, "kg"));
    CHECK_EQ((b+a), NumberWithUnits(6900, "g"));
    CHECK_EQ((a+c), NumberWithUnits(305, "kg"));
    CHECK_EQ((c+a), NumberWithUnits(0.305, "ton"));
    CHECK_EQ((a+100), NumberWithUnits(105, "kg"));
    CHECK_EQ((2*d+2*f), NumberWithUnits(41800, "m"));
    CHECK_THROWS(a+d);
    CHECK_THROWS(d+a);
    CHECK_THROWS(c+d);
    CHECK_THROWS(a+f);
}

    //------------------(-)---------------------
TEST_CASE("Arithmethic Operators (-)"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "kg"};
    NumberWithUnits b{1900, "g"};
    NumberWithUnits c{0.3, "ton"};
    NumberWithUnits d{1900, "m"};
    NumberWithUnits f{19, "km"};
    CHECK_EQ((-a), NumberWithUnits(-5, "kg"));
    CHECK_EQ((c-b), NumberWithUnits(0.2981, "ton"));
    CHECK_EQ((b-a), NumberWithUnits(-3100, "g"));
    CHECK_EQ(((5*a)-(10*b)), NumberWithUnits(6, "kg"));
    CHECK_EQ((-3*a), NumberWithUnits(-15, "kg"));
    CHECK_EQ((-f), NumberWithUnits(-19, "km"));
    CHECK_THROWS(a-d);
    CHECK_THROWS(b-d);
    CHECK_THROWS(c-d);
    CHECK_THROWS(-a+d);

    //-------------(+=)-----(-=)-----------------
    CHECK_EQ((a+=a), NumberWithUnits(10, "kg"));   //a=5 --> a+a=10
    CHECK_EQ((a+=b), NumberWithUnits(11.9, "kg")); //a=10, b = 1.9 --> a=a+b = 11.9
    CHECK_EQ((b+=a), NumberWithUnits(13800, "g"));  //a=11900, b=1900, b=b+a=13800
    CHECK_EQ((a-=a), NumberWithUnits(0, "kg"));    //a=a-a=0
    CHECK_EQ((a-=b), NumberWithUnits(-13.8, "kg"));  //a=-13800
    CHECK_THROWS(a+=d);
    CHECK_THROWS(a+=f);
    CHECK_THROWS(a-=d);
    CHECK_THROWS(b-=f);
}

// The following binary check macros are also defined :
//    Macro                 operator applied
// ------------------------------------------
// CHECK_EQ(val1, val2)      val1 == val2
// CHECK_NE(val1, val2)      val1 != val2
// CHECK_GT(val1, val2)      val1 > val2
// CHECK_GE(val1, val2)      val1 >= val2
// CHECK_LT(val1, val2)      val1 < val2
// CHECK_LE(val1, val2)      val1 <= val2
TEST_CASE("Comparison Operators"){
    NumberWithUnits::read_units(units_file);
            // CHECK_EQ(val1, val2)      val1 == val2
    CHECK_EQ(NumberWithUnits(10, "km"), NumberWithUnits(10, "km"));
    CHECK_EQ(NumberWithUnits(10, "km"), NumberWithUnits(10000, "m"));
    CHECK_EQ(NumberWithUnits(1000, "m"), NumberWithUnits(1, "km"));
    CHECK_EQ(NumberWithUnits(1000, "kg"), NumberWithUnits(1, "ton"));
    CHECK_EQ(NumberWithUnits(1, "ton"), NumberWithUnits(1000000, "g"));

            // CHECK_NE(val1, val2)      val1 != val2
    CHECK_NE(NumberWithUnits(1, "ton"), NumberWithUnits(10000, "g"));
    CHECK_NE(NumberWithUnits(1, "kg"), NumberWithUnits(1, "g"));
    CHECK_NE(NumberWithUnits(10, "ton"), NumberWithUnits(10000, "g"));
    CHECK_NE(NumberWithUnits(1, "km"), NumberWithUnits(1, "m"));
    CHECK_NE(NumberWithUnits(1, "m"), NumberWithUnits(1000, "km"));
            // CHECK_GT(val1, val2)      val1 > val2
    CHECK_GT(NumberWithUnits(1, "km"), NumberWithUnits(100, "m"));
    CHECK_GT(NumberWithUnits(1001, "m"), NumberWithUnits(1, "km"));
    CHECK_GT(NumberWithUnits(101.2, "km"), NumberWithUnits(101, "km"));
    CHECK_GT(NumberWithUnits(1, "kg"), NumberWithUnits(100, "g"));
    CHECK_GT(NumberWithUnits(1, "ton"), NumberWithUnits(1000, "g"));
            // CHECK_GE(val1, val2)      val1 >= val2
    CHECK_GE(NumberWithUnits(1, "km"), NumberWithUnits(100, "m"));
    CHECK_GE(NumberWithUnits(1001, "m"), NumberWithUnits(1, "km"));
    CHECK_GE(NumberWithUnits(101.2, "km"), NumberWithUnits(101, "km"));
    CHECK_GE(NumberWithUnits(1, "kg"), NumberWithUnits(100, "g"));
    CHECK_GE(NumberWithUnits(1, "ton"), NumberWithUnits(1000, "kg"));
    CHECK_GE(NumberWithUnits(1, "km"), NumberWithUnits(1000, "m"));
    CHECK_GE(NumberWithUnits(1200, "m"), NumberWithUnits(1.2, "km"));
            // CHECK_LT(val1, val2)      val1 < val2
    CHECK_LT(NumberWithUnits(1000, "g"), NumberWithUnits(1, "ton"));
    CHECK_LT(NumberWithUnits(1, "g"), NumberWithUnits(1, "kg"));
    CHECK_LT(NumberWithUnits(10, "kg"), NumberWithUnits(10001, "g"));
    CHECK_LT(NumberWithUnits(1, "m"), NumberWithUnits(1, "km"));
    CHECK_LT(NumberWithUnits(10000, "m"), NumberWithUnits(10.1, "km"));
            // CHECK_LE(val1, val2)      val1 <= val2
    CHECK_LE(NumberWithUnits(1000, "g"), NumberWithUnits(1, "ton"));
    CHECK_LE(NumberWithUnits(1, "g"), NumberWithUnits(1, "kg"));
    CHECK_LE(NumberWithUnits(10, "kg"), NumberWithUnits(10001, "g"));
    CHECK_LE(NumberWithUnits(1, "m"), NumberWithUnits(1, "km"));
    CHECK_LE(NumberWithUnits(10000, "m"), NumberWithUnits(10.1, "km"));
    CHECK_LE(NumberWithUnits(1000, "g"), NumberWithUnits(1, "kg"));
    CHECK_LE(NumberWithUnits(1, "g"), NumberWithUnits(1, "g"));
    CHECK_LE(NumberWithUnits(10, "kg"), NumberWithUnits(10000, "g"));
}


/*
*Operator name 	        Syntax 	     	          Prototype examples
*                                   Inside class definition 	Outside class definition
*pre-increment 	        ++a 	 	T& T::operator++(); 	    T& operator++(T& a);
*pre-decrement 	        --a 	 	T& T::operator--(); 	    T& operator--(T& a);
*post-increment 	    a++ 	 	T T::operator++(int); 	    T operator++(T& a, int);
*post-decrement 	    a-- 	 	T T::operator--(int); 	    T operator--(T& a, int);
*/

TEST_CASE("Operators check: ++a, a++, --a, a--"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "kg"};
    CHECK_EQ(a++, NumberWithUnits(5, "kg")); //a = 5, second row --> a=6
    CHECK_EQ(a, NumberWithUnits(6, "kg"));   // a = 6
    CHECK_EQ(--a, NumberWithUnits(5, "kg")); // a = 5
    CHECK_EQ(a--, NumberWithUnits(5, "kg")); // a = 5, second row --> a = 4
    CHECK_EQ(a++, NumberWithUnits(4, "kg")); //a = 4, second row --> a = 5
    CHECK_EQ(a++, NumberWithUnits(5, "kg")); // a = 5
}

/*
*
*Multiplication operators
*/

TEST_CASE("Multiplication operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "kg"};
    CHECK_EQ(3*a, NumberWithUnits(15, "kg"));
    CHECK_EQ(2*a, NumberWithUnits(10, "kg"));
    CHECK_EQ(0.1*a, NumberWithUnits(0.5, "kg"));
    CHECK_EQ(a*0.1, NumberWithUnits(0.5, "kg"));
}


