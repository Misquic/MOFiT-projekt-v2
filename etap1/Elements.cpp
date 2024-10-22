#include "Elements.h"
#include "funkc.h"

Node::Node(int name, std::vector<float> pos): name{name}, pos{pos}{
};
Node::Node(const Node& other): name{other.name}, pos{other.pos}{
};  
Node::Node(Node&& other): name{other.name}, pos{std::move(other.pos)}{
    other.pos.clear();
};

// Node& Node::operator=(const Node& other){
//     name = other.name;
//     pos = other.pos;
//     return *this;
// };
// Node& Node::operator=(Node&& other){
//     if(this!=&other){
//         name = other.name;
//         pos = std::move(other.pos);
//         other.pos.clear();
//     }

//     return *this;
// };
std::ostream& operator<<(std::ostream& out, const Node node){
    out << "node: " << node.name << " pos: " << node.getPos() << " "; 
    return out;
};


/*metody*/
int Node::getName() const{
    return name;
};
std::vector<float> Node::getPos() const{
    return pos;
};
float Node::getPos(int i) const{
    return pos[i];
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Element::Element(int name, float anm): name{name}, anm{anm}, a{anm*Const::nm_au}{
    //numer kom do wezlow
    nodes.reserve(4);
    std::vector<float> pos(2);

    for(int i = 1; i <=4; i++){
        pos = i_kom_i_wewn2pos(this->name, i);
        nodes.emplace_back(nlg_fun(this->name, i), pos);
    }
};

Element::Element(const Element& other): name{other.name}, anm{other.anm}, a{other.anm*Const::nm_au}, nodes{other.nodes}{
};
Element::Element(Element&& other): name{other.name}, anm{other.anm}, a{other.anm*Const::nm_au}, nodes{std::move(other.nodes)}{
    other.nodes.clear();
};
// Element& Element::operator=(const Element& other){
//     name = other.name;
//     anm = other.anm;
//     a = other.a;
//     nodes = other.nodes;
//     return *this;
// };
// Element& Element::operator=(Element&& other){
//     if(this!=&other){
//         name = other.name;
//         anm = other.anm;
//         a = other.a;
//         nodes = std::move(other.nodes);
//         other.nodes.clear();
//     }
//     return *this;

// };

/*metody*/

int Element::getName() const{
    return name;
};
float Element::getA() const{
    return a;
};
float Element::getAnm() const{
    return anm;
};
std::vector<Node> Element::getNodes() const{
    return nodes;
};
Node Element::getNode(int i) const{
    return nodes[i];
};

std::ostream& operator<<(std::ostream& out, const Element element){
    for(int i_wewn = 1; i_wewn <= element.getNodes().size(); i_wewn++ ){
        out << "iw: " << i_wewn << " " << element.getNode(i_wewn-1) << " ";
    }
    return out;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Elements::Elements(int N, float Lnm): N{N}, Lnm{Lnm}, L{Lnm*Const::nm_au}{

    elements.reserve(4*N*N);

    for(int i = 1; i <= 4*N*N; i++){
        elements.emplace_back(i, Lnm/(2*N));
    }

};
Elements::Elements(const Elements& other): N{other.N}, Lnm{other.Lnm}, L{other.L}, elements{other.elements}{
};
Elements::Elements(Elements&& other): N{other.N}, Lnm{other.Lnm}, L{other.L}, elements{std::move(other.elements)}{
    other.elements.clear();
};

std::vector<Element> Elements::getElements() const{
    return elements;
};
Element Elements::getElement(int i) const{
    return elements[i];
};

std::ostream& operator<<(std::ostream& out, const Elements elements){
    for(int i_kom = 1; i_kom <= elements.getElements().size(); i_kom++){
        out << "Element ikom: "<< i_kom << "\n" << elements.getElement(i_kom-1) << "\n";
    }
    return out;
};
