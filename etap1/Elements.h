#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "Parameters.h"

class Node{
public:
    const Parameters& pm;
    std::vector<float> pos;  //realna pozycja wezla

    const int name;                           //nazwa wezla
    Node (int name, std::vector<float> pos, const Parameters& pm);  //zwykly konstruktor
    // Node (const Node& other);                 //konstruktor kopiujący
    // Node (Node&& other);                      //konstruktor przenoszący (na wszelki wypadek)
    
    // Node& operator=(const Node& other);
    // Node& operator=(Node&& other);

    int getName() const;  //gettery
    std::vector<float> getPos() const;
    float getPos(int i) const;

};

std::ostream& operator<<(std::ostream& out, const Node node); //do wypisywania, mozna dac inna wersje bo taka przydatna byla do testowania



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Element{
public:
    std::vector<std::vector<float>> S = std::vector<std::vector<float>>(4,std::vector<float>(4));
    std::vector<std::vector<float>> H = std::vector<std::vector<float>>(4,std::vector<float>(4));
    const Parameters& pm;
    std::vector<Node> nodes;                      // kontener na wezly stowarzyszone z elementem(komorka), w element posiada 4 wezly
    const             int name;                   // numer/nazwa elementu
    Element(int name, const Parameters& pm);  //zwykly konstruktor
                                                  // Element(const Element& other);              //konstruktor kopiujacy
                                                  // Element(Element&& other);                   // konstruktor przenoszacy w ramach dobrego programowania

    //TODO
    // Element& operator=(const Element& other);
    // Element& operator=(Element&& other);

    int getName() const; //gettery
    float getA() const;
    float getAnm() const;
    std::vector<Node> getNodes() const;
    Node getNode(int i) const;
    std::vector<float> ksi2r(float ksi_x, float ksi_y);  //dla konkretnego elementu i ksi wylicz pozycję globalną
    std::vector<float> ksi2r(float ksi);                 //wrapper gdy podamy tylko jedno ksi
    
    
    void S_filter(); 

};

std::ostream& operator<<(std::ostream& out, const Element element);  //do wypisywania, zmienic, jesli potrzeba wygodniej wyswietlac


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Elements{
public:
    std::vector<Element> elements; //kontener elementow, cala baza sluzy jako kontener tych elementow w zasadzie
    const Parameters& pm;

    Elements(const Parameters& pm);  //normalny konstruktor
    std::vector<Element> getElements() const; //gettery
    Element getElement(int name) const;
};

std::ostream& operator<<(std::ostream& out, const Elements elements); //do wypisywania, zmienic, jesli potrzeba wygodniej wyswietlac




#endif // ELEMENTS_H