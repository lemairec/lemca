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
    add("FR", "OK", "OK");
    add("FR", "CANCEL", "Annuler");
    add("FR", "FAIL", "Erreur");
    
    add("FR", "HOME_BINEUSE", "Bineuse");
    add("FR", "HOME_GPS", "GPS");
    add("FR", "HOME_SERIAL", "Série");
    add("FR", "HOME_INFOS", "Infos");
    add("FR", "HOME_REMOTE", "Accès à dist");
    add("FR", "HOME_WIFI", "Wifi");
    add("FR", "HOME_OFF", "Eteindre");

    add("FR", "INFOS_AV_TITLE", "Menu avancé (infos)");
    add("FR", "OPT_LANGAGE", "Langue");
    add("FR", "EN", "Anglais");
    add("FR", "FR", "Francais");
    add("FR", "DE", "Deutsch");
    add("FR", "OPT_UNITY", "Unité");
    add("FR", "METRIQUE", "Métrique");
    add("FR", "VERSION", "Version");
    
    add("FR", "UPDATE", "Mise à jour");
    add("FR", "UPDATE_WIFI", "Mise à jour par WIFI");
    add("FR", "UPDATE_BINEUSE_WIFI", "Mise à jour de Bineuse");
    add("FR", "UPDATE_GPS_WIFI", "Mise à jour de GPS");
    add("FR", "UPDATE_SERIAL_WIFI", "Mise à jour de Serie");
    add("FR", "UPDATE_USB", "Mise à jour par Clef USB");
    add("FR", "UPDATE_BINEUSE_USB", "Mise à jour de Bineuse");
    
    add("FR", "INFOS_OPTIONS", "Options");
    add("FR", "SOFTWARE", "Logiciel activé");
    add("FR", "GPS", "GPS");
    add("FR", "SERIAL", "Série");
    add("FR", "OPTIONS", "Options");
    add("FR", "UPDATE_WIFI_ENABLE", "Activer la mise a jour WIFI");
    add("FR", "UPDATE_USB_ENABLE", "Activer la mise a jour USB");
    add("FR", "REMOTE_ENABLE", "Activer l'accès à dist");
    add("FR", "OPERATING_SYSTEM", "Système d'exploitations");
    add("FR", "UPDATE_OS", "Mise à jour");
    add("FR", "UPDATE_DEPS", "Installer dépendances");
    
    
        
    
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
