#include "langage.hpp"
#include <iostream>
#include <fstream>

Langage & Langage::instance(){
    static Langage obj;
    return obj;
}


const std::string & Langage::getKey(const std::string & ref){
    Langage & l = instance();
    if(l.m_l == MyLangage_fr){
        auto i = l.m_fr.find(ref);
        if(i != l.m_fr.end()){
            return i->second;
        }
    }
    if(l.m_l == MyLangage_en){
        auto i = l.m_en.find(ref);
        if(i != l.m_en.end()){
            return i->second;
        }
    }
    if(l.m_l == MyLangage_de){
        auto i = l.m_de.find(ref);
        if(i != l.m_de.end()){
            return i->second;
        }
    }
    l.m_fr["ref"] = "$" + ref;
    return l.m_fr["ref"];
}

void Langage::setLangage(int i){
    Langage & l = instance();
    l.m_l = (MyLangage)i;
}

void Langage::setLangage(const std::string & s){
    Langage & l = instance();
    if(s == "FR"){
        l.m_l = MyLangage_fr;
    } else if(s == "EN"){
        l.m_l = MyLangage_en;
    } else if(s == "DE"){
        l.m_l = MyLangage_de;
    }
}


Langage::Langage(){
    add("FR", "HOME_BINEUSE", "Bineuse");
    add("FR", "HOME_GPS", "GPS");

    add("FR", "OPTION_1_TITLE", "Mise à jour");
}

void Langage::add(std::string langage, std::string key, std::string trad){
    if(langage == "FR"){
        m_fr[key] = trad;
    } else if(langage == "EN"){
        m_en[key] = trad;
    } else if(langage == "DE"){
        m_de[key] = trad;
    }
    for(auto e : m_all){
        if(e == key){
            return;
        }
    }
    m_all.push_back(key);
}


void Langage::verifyAll(){

    std::ofstream myfile;
    myfile.open ("/Users/lemairec/workspace/bineuse/all.txt");
    for(auto s : m_all){
        myfile << s << "\n";
        
    }
    myfile.close();
    
    std::ofstream myfile2;
    myfile2.open ("/Users/lemairec/workspace/bineuse/all2.txt");
    for(auto s : m_all){
        std::string trad = "*****";
        std::string s2 = s;
        auto i = m_fr.find(s2);
        if(i != m_fr.end()){
            trad = i->second;
        }
        myfile2 << "add(\"FR\", \"" << s << "\", \"" << trad << "\");\n";
    }
    myfile2 << "\n";
    myfile2 << "\n";
    
    for(auto s : m_all){
        std::string trad = "*****";
        std::string s2 = s;
        auto i = m_en.find(s2);
        if(i != m_en.end()){
            trad = i->second;
            myfile2 << "add(\"EN\", \"" << s << "\", \"" << trad << "\");\n";
        } else {
            myfile2 << "add(\"EN\", \"" << s << "\", \"" << trad << "\");//" << m_fr[s]<<"\n";
        }
    }
    
    myfile2 << "\n";
    myfile2 << "\n";
    for(auto s : m_all){
        std::string trad = "*****";
        std::string s2 = s;
        auto i = m_de.find(s2);
        if(i != m_de.end()){
            trad = i->second;
            myfile2 << "add(\"DE\", \"" << s << "\", \"" << trad << "\");\n";
        } else {
            myfile2 << "add(\"DE\", \"" << s << "\", \"" << trad << "\");\n";
        }
        
    }
    
    for(auto s : m_all){
        std::string trad = "*****";
        std::string s2 = s;
        myfile2 << "add(\"NL\", \"" << s << "\", \"" << m_fr[s] << "\");" <<"\n";
        
    }
    myfile2.close();
        
}
