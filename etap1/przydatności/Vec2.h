#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "all.h"
//using namespace std;

//TODO add casting from int to double fo example


template <class data_type>
class Vec2{
protected:
    data_type data[2];
public:
    /*constructors*/
    Vec2() noexcept;                                                          //normal constructor
    Vec2(const data_type x, const data_type y) noexcept;   //normal constructor
    Vec2(const data_type other_data[2]) noexcept;                             //normal constructor
    Vec2(const Vec2<data_type>& other) noexcept;                              //copying constructor
    Vec2(Vec2<data_type>&& other) noexcept;                                   //moving constructor

    /*deconstructor*/
    //~Vec2();

    /*methods*/
    void clear();
    type_calc length();
    void normalise();

    /*operators[]*/
    data_type& operator[](int i);
    const data_type& operator[](int i) const;

    /*Vec2-scalar operators*/
    Vec2<data_type>& operator=(const data_type val) noexcept;
    Vec2<data_type> operator+(const data_type val) const;
    Vec2<data_type> operator-(const data_type val) const;
    Vec2<data_type> operator*(const data_type val) const;
    Vec2<data_type> operator/(const data_type val) const;
    void operator+=(const data_type val);
    void operator-=(const data_type val);
    void operator*=(const data_type val);
    void operator/=(const data_type val);

    /*Vec2-Vec2 operators*/
    Vec2<data_type>& operator=(const Vec2<data_type>& other) noexcept;  //copying operator
    Vec2<data_type>& operator=(Vec2<data_type>&& other) noexcept;       //moving operator
    Vec2<data_type> operator+(const Vec2<data_type>& other) const;
    Vec2<data_type> operator-(const Vec2<data_type>& other) const;
    data_type operator*(const Vec2<data_type>& other) const;
    Vec2<data_type> operator/(const Vec2<data_type>& other) = delete;
    void operator+=(const Vec2<data_type>& other);
    void operator-=(const Vec2<data_type>& other);
    void operator*=(const Vec2<data_type>& other) = delete;
    void operator/=(const Vec2<data_type>& other) = delete;

};

/*constructors*/
template <class data_type>
Vec2<data_type>::Vec2() noexcept: data{0,0}{
};
template <class data_type>
Vec2<data_type>::Vec2(const data_type x, const data_type y) noexcept: data{x, y}{
};
template <class data_type>
Vec2<data_type>::Vec2(const data_type other_data[2]) noexcept: data{other_data[0], other_data[1]}{
};
template <class data_type>
Vec2<data_type>::Vec2(const Vec2<data_type>& other) noexcept: data{other.data[0], other.data[1]}{
};
template <class data_type>
Vec2<data_type>::Vec2(Vec2<data_type>&& other) noexcept: data{other.data[0], other.data[1]}{
};

/*methods*/
template <class data_type>
void Vec2<data_type>::clear(){
    for(int i = 0; i < 2; i ++){
        data[i] = 0;
    }
};
template <class data_type>
type_calc Vec2<data_type>::length(){
    return sqrt((*this)*(*this));
};
template <class data_type>
void Vec2<data_type>::normalise(){
    (*this)/=(*this).length();
};

/*operators[]*/
template <class data_type>
data_type& Vec2<data_type>::operator[](int i){
    return data[i];
};
template <class data_type>
const data_type& Vec2<data_type>::operator[](int i) const {
    return data[i];
}

/*Vec2-scalar operators*/
template <class data_type>
Vec2<data_type>& Vec2<data_type>::operator=(const data_type val) noexcept{
    for(int i = 0; i < 2; i++){
        data[i] = val;
    }
    return (*this); //nie było tego i było okej?
    
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator+(const data_type val) const{
    Vec2<data_type> ret(*this); /*probably faster than creating empty Vec2 and then adding, other behaviour for field (i think so?)*/
    for(int i = 0; i < 2; i++){
        ret.data[i] += val;
    }
    return ret;
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator-(const data_type val) const{
    Vec2<data_type> ret(*this);
    for(int i = 0; i < 2; i++){
        ret.data[i] -= val;
    }
    return ret;
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator*(const data_type val) const{
    Vec2<data_type> ret(*this);
    for(int i = 0; i < 2; i++){
        ret.data[i] *= val;
    }
    return ret;
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator/(const data_type val) const{
    Vec2<data_type> ret(*this);
    data_type inverse_val = 1.0/val;
    for(int i = 0; i < 2; i++){
        ret.data[i] *= inverse_val;
    }
    return ret;
};
template <class data_type>
void Vec2<data_type>::operator+=(const data_type val){
    for(int i = 0; i < 2; i++){
        data[i] += val;
    }
};
template <class data_type>
void Vec2<data_type>::operator-=(const data_type val){
    for(int i = 0; i < 2; i++){
        data[i] -= val;
    }
};
template <class data_type>
void Vec2<data_type>::operator*=(const data_type val){
    for(int i = 0; i < 2; i++){
        data[i] *= val;
    }
};
template <class data_type>
void Vec2<data_type>::operator/=(const data_type val){
    data_type inverse_val = 1.0/val;
    for(int i = 0; i < 2; i++){
        data[i] *= inverse_val;
    }
};

/*Vec2-Vec2 operators*/
template <class data_type>
Vec2<data_type>& Vec2<data_type>::operator=(const Vec2<data_type>& other) noexcept{
    for(int i = 0; i < 2; i++){
        this->data[i] = other.data[i];
    }
    return *this;
};
template <class data_type>
Vec2<data_type>& Vec2<data_type>::operator=(Vec2<data_type>&& other) noexcept{
    if(this != &other){
        for(int i = 0; i < 2; i++){
            this->data[i] = other.data[i];
        }
    }
    return *this;
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator+(const Vec2<data_type>& other) const{
    Vec2<data_type> ret(*this);
    for(int i = 0; i < 2; i++){
        ret.data[i] += other.data[i];
    }
    ///
    //Vec2<data_type> ret();
    //for(int i = 0; i<3; i++){
    //    ret.data[i] = this->data[i] + other.data[i] /*which is faster?*/
    //}
    //
    ///
    return ret;
};
template <class data_type>
Vec2<data_type> Vec2<data_type>::operator-(const Vec2<data_type>& other) const{
    Vec2<data_type> ret(*this);
    for(int i = 0; i < 2; i++){
        ret.data[i] -= other.data[i];
    }
    return ret;
};
template <class data_type>
data_type Vec2<data_type>::operator*(const Vec2<data_type>& other) const{
    return this->data[0]*other.data[0] + this->data[1]*other.data[1];
};
template <class data_type>
void Vec2<data_type>::operator+=(const Vec2<data_type>& other){
    for(int i = 0; i < 2; i++){
        this->data[i] += other.data[i];
    }
};
template <class data_type>
void Vec2<data_type>::operator-=(const Vec2<data_type>& other){
        for(int i = 0; i < 2; i++){
        this->data[i] -= other.data[i];
    }
};

/*sclalar-Vec2 operators*/
template <class data_type>
Vec2<data_type> operator+(const data_type& val, const Vec2<data_type>& Vec2) {
    return Vec2 + val;
};
template <class data_type>
Vec2<data_type> operator-(const data_type& val, const Vec2<data_type>& Vec2) {
    return Vec2 - val;
};
template <class data_type>
Vec2<data_type> operator*(const data_type& val, const Vec2<data_type>& Vec2) {
    return Vec2 * val;
};
template <class data_type>
Vec2<data_type> operator/(const data_type& val, const Vec2<data_type>& Vec2) {
    return Vec2 / val;
};

template<typename data_type, typename val_name>
Vec2<data_type> operator+(const val_name& val, const Vec2<data_type>& Vec2) {
    return Vec2 + data_type( val);
};
template<typename data_type, typename val_name>
Vec2<data_type> operator-(const val_name& val, const Vec2<data_type>& Vec2) {
    return Vec2 - data_type( val);
};
template<typename data_type, typename val_name>
Vec2<data_type> operator*(const val_name& val, const Vec2<data_type>& Vec2) {
    return Vec2 * data_type( val);
};
template<typename data_type, typename val_name>
Vec2<data_type> operator/(const val_name& val, const Vec2<data_type>& Vec2) {
    return Vec2 / data_type( val);
};

/*functions*/
template <class data_type>
std::ostream& operator<<(std::ostream &out, const Vec2<data_type> &Vec2){

    //out << std::setprecision(5);// <<"{ "; /*to change?*/
    out << Vec2[0] << " " << Vec2[1];
    // for(int i=0; i<3; i++){
    //     out << Vec2[i] << " ";
    // }
    // out;// << "}";
    return out;
};


using double2 = Vec2<double>;
using type_calc2 = Vec2<type_calc>;
using int3 = Vec2<int>;

#endif