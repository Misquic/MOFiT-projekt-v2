#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "Const.h"



class Node{
private:
    std::vector<float> pos; //realna pozycja wezla
public:
    const int name;                           //nazwa wezla
    Node (int name, std::vector<float> pos);  //zwykly konstruktor
    Node (const Node& other);                 //konstruktor kopiujący
    Node (Node&& other);                      //konstruktor przenoszący (na wszelki wypadek)
    
    // Node& operator=(const Node& other);
    // Node& operator=(Node&& other);

    int getName() const;  //gettery
    std::vector<float> getPos() const;
    float getPos(int i) const;

};

std::ostream& operator<<(std::ostream& out, const Node node); //do wypisywania, mozna dac inna wersje bo taka przydatna byla do testowania



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Element{
private:
    std::vector<Node> nodes;  // kontener na wezly stowarzyszone z elementem(komorka), w element posiada 4 wezly
    float             anm;    // bok elemetu w nm //musi byc zadeklarowany przed L, bo taka konwencja w konstruktorach
    float             a;      // bok elementu, moze sie przyda tu
public:
    const   int name;                           // numer/nazwa elementu
    Element(int name, float anm = Const::anm);  //zwykly konstruktor
    Element(const Element& other);              //konstruktor kopiujacy
    Element(Element&& other);                   // konstruktor przenoszacy w ramach dobrego programowania

    //TODO
    // Element& operator=(const Element& other);
    // Element& operator=(Element&& other);

    int getName() const; //gettery
    float getA() const;
    float getAnm() const;
    std::vector<Node> getNodes() const;
    Node getNode(int i) const;
};

std::ostream& operator<<(std::ostream& out, const Element element);  //do wypisywania, zmienic, jesli potrzeba wygodniej wyswietlac


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Elements{
private:
    std::vector<Element> elements; //kontener elementow, cala baza sluzy jako kontener tych elementow w zasadzie
public:
    const int N;      //samo sie tlumaczy, no zwiazane z rozmiarem tych siatek
    const float Lnm;  // dlugosc calej siatki w nm //musi byc zadeklarowany przed L, bo taka konwencja w konstruktorach
    const float L;    // dlugosc w au

    Elements(int N, float Lnm);       //normalny konstruktor
    Elements(const Elements& other);  //konstruktor kopiujacy
    Elements(Elements&& other);       //konstruktor przenoszacy, bo dobre programowanie

    std::vector<Element> getElements() const; //gettery
    Element getElement(int name) const;
};

std::ostream& operator<<(std::ostream& out, const Elements elements); //do wypisywania, zmienic, jesli potrzeba wygodniej wyswietlac




#endif // ELEMENTS_H