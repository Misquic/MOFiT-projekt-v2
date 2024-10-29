#include "Elements.h"
#include "funkc.h"
#include <vector>

Node::Node(int name, std::vector<float> pos, const Parameters& pm): name{name}, pos{pos}, pm{pm}{
};
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

Element::Element(int name, const Parameters& pm): name{name}, pm{pm}{
    //numer kom do wezlow
    nodes.reserve(4);
    std::vector<float> pos(2);
    
    for(int i = 1; i <=4; i++){
        pos = i_kom_i_wewn2pos(this->name, i, pm);
        nodes.emplace_back(nlg_fun(this->name, i, pm.N), pos, pm);
    }
};


/*metody*/

int Element::getName() const{
    return name;
};
std::vector<Node> Element::getNodes() const{
    return nodes;
};
Node Element::getNode(int i_wewn) const{ //numeracja wg instrukcji
    return nodes[i_wewn-1];
};
std::vector<float> Element::ksi2r(float ksi_x, float ksi_y){
    std::vector<float> pos(2);

    for(int i_wewn = 1; i_wewn < 5; i_wewn++){
        pos[0]+=this->getNode(i_wewn).getPos()[0]*g(ksi_x, ksi_y, i_wewn);
        pos[1]+=this->getNode(i_wewn).getPos()[1]*g(ksi_x, ksi_y, i_wewn);
    }
    return pos;
};
std::vector<float> Element::ksi2r(float ksi){
    return this->ksi2r(ksi, ksi);
};

std::ostream& operator<<(std::ostream& out, const Element element){
    out << "el: " << element.name << "\n";
    for(int i_wewn = 1; i_wewn <= element.getNodes().size(); i_wewn++ ){
        out << "iw: " << i_wewn << " " << element.getNode(i_wewn) << " ";
    }
    return out;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Elements::Elements(const Parameters& pm): pm{pm}{

    elements.reserve(4*pm.N*pm.N);

    for(int i = 1; i <= 4*pm.N*pm.N; i++){
        elements.emplace_back(i, pm);
    }

};

std::vector<Element> Elements::getElements() const{
    return elements;
};
Element Elements::getElement(int i_kom) const{
    return elements[i_kom-1];
};

std::ostream& operator<<(std::ostream& out, const Elements elements){
    for(int i_kom = 1; i_kom <= elements.getElements().size(); i_kom++){
        out << "Element ikom: "<< i_kom << "\n" << elements.getElement(i_kom) << "\n";
    }
    return out;

};

