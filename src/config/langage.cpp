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
    if(l.m_l == MyLangage_nl){
        auto i = l.m_nl.find(ref);
        if(i != l.m_nl.end()){
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
    }else if(s == "NL"){
        l.m_l = MyLangage_nl;
    }
}


Langage::Langage(){
    add("FR", "OK", "OK");
    add("FR", "CANCEL", "Annuler");
    add("FR", "FAIL", "Erreur");
    add("FR", "LOADING", "Chargement ...");
    
    add("FR", "HOME_BINEUSE", "Bineuse");
    add("FR", "HOME_GPS", "GPS");
    add("FR", "HOME_SERIAL", "Série");
    add("FR", "HOME_INFOS", "Infos");
    add("FR", "HOME_REMOTE", "Accès à dist");
    add("FR", "HOME_WIFI", "Wifi");
    add("FR", "HOME_OFF", "Eteindre");

    add("FR", "INFOS_AV_TITLE", "Menu avancé (infos)");
    add("FR", "INFOS_LIC_PANEL", "panel : ");
    
    add("FR", "OPT_LANGAGE", "Langue");
    add("FR", "EN", "Anglais");
    add("FR", "FR", "Francais");
    add("FR", "DE", "Allemand");
    add("FR", "NL", "Néerlandais");
    add("FR", "OPT_UNITY", "Unité");
    add("FR", "METRIQUE", "Métrique");
    add("FR", "VERSION", "Version");
    add("FR", "SEND_IMAGES", "Envoyer les images");
    
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
    add("FR", "UPDATE_WIFI_ENABLE", "Activer la mise à jour WIFI");
    add("FR", "UPDATE_USB_ENABLE", "Activer la mise à jour USB");
    add("FR", "UPDATE_INVALID_PANEL_NUMBER", "Numéro du panel non valide");
    add("FR", "UPDATE_CONTINUE", "Continuer");
    add("FR", "UPDATE_CANCEL", "Annuler");
    add("FR", "REMOTE_ENABLE", "Activer l'accès à dist");
    add("FR", "OPERATING_SYSTEM", "Système d'exploitations");
    add("FR", "UPDATE_OS", "Mise à jour");
    add("FR", "UPDATE_DEPS", "Installer dépendances");
    add("FR", "RESET_OS", "Reinitialiser");
    
    
    add("EN", "OK", "OK");
    add("EN", "CANCEL", "Cancel");
    add("EN", "FAIL", "Error");
    add("EN", "LOADING", "Loading ...");
    
    add("EN", "HOME_BINEUSE", "Hoe");
    add("EN", "HOME_GPS", "GPS");
    add("EN", "HOME_SERIAL", "Serial");
    add("EN", "HOME_INFOS", "Infos");
    add("EN", "HOME_REMOTE", "Remote");
    add("EN", "HOME_WIFI", "Wifi");
    add("EN", "HOME_OFF", "Off");

    add("EN", "INFOS_AV_TITLE", "Advanced menu (infos)");
    add("EN", "INFOS_LIC_PANEL", "panel : ");
    add("EN", "OPT_LANGAGE", "Language");
    add("EN", "EN", "English");
    add("EN", "FR", "French");
    add("EN", "DE", "Deutsch");
    add("EN", "NL", "Dutch");
    add("EN", "OPT_UNITY", "Unity");
    add("EN", "METRIQUE", "Metric");
    add("EN", "VERSION", "Version");
    add("EN", "SEND_IMAGES", "Send pictures");
    
    add("EN", "UPDATE", "Update");
    add("EN", "UPDATE_WIFI", "Update by WIFI");
    add("EN", "UPDATE_BINEUSE_WIFI", "Hoe update");
    add("EN", "UPDATE_GPS_WIFI", "GPS update");
    add("EN", "UPDATE_SERIAL_WIFI", "Serial Update");
    add("EN", "UPDATE_USB", "Update by USB key");
    add("EN", "UPDATE_BINEUSE_USB", "Hoe update");
    add("EN", "UPDATE_INVALID_PANEL_NUMBER", "Invalid panel number");
    add("EN", "UPDATE_CONTINUE", "Continue");
    add("EN", "UPDATE_CANCEL", "Cancel");
    
    
    add("EN", "INFOS_OPTIONS", "Options");
    add("EN", "SOFTWARE", "Software activated");
    add("EN", "GPS", "GPS");
    add("EN", "SERIAL", "Sérial");
    add("EN", "OPTIONS", "Options");
    add("EN", "UPDATE_WIFI_ENABLE", "Enable WIFI update");
    add("EN", "UPDATE_USB_ENABLE", "Enable USB key update");
    add("EN", "REMOTE_ENABLE", "Enable remote");
    add("EN", "OPERATING_SYSTEM", "Operating System");
    add("EN", "UPDATE_OS", "Update OS");
    add("EN", "UPDATE_DEPS", "Install dependances");
    add("EN", "RESET_OS", "reset");
    
    add("NL", "OK", "OK");
    add("NL", "CANCEL", "annuleren");
    add("NL", "FAIL", "Fout");
    add("NL", "LOADING", "Bezig met laden...");
    add("NL", "HOME_BINEUSE", "Schoffel");
    add("NL", "HOME_GPS", "GPS");
    add("NL", "HOME_SERIAL", "Serial");
    add("NL", "HOME_INFOS", "Info");
    add("NL", "HOME_REMOTE", "Remote");
    add("NL", "HOME_WIFI", "Wifi");
    add("NL", "HOME_OFF", "Uitschakelen");
    add("NL", "INFOS_AV_TITLE", "Geavanceerd menu (info)");
    add("NL", "INFOS_LIC_PANEL", "Paneel :");
    add("NL", "OPT_LANGAGE", "Taal");
    add("NL", "EN", "English");
    add("NL", "FR", "Français");
    add("NL", "DE", "Deutsch");
    add("NL", "NL", "Nederlands");
    add("NL", "OPT_UNITY", "Eenheid");
    add("NL", "METRIQUE", "Metrisch");
    add("NL", "VERSION", "Versie");
    add("NL", "SEND_IMAGES", "Stuur foto's");
    add("NL", "UPDATE", "Bijwerken");
    add("NL", "UPDATE_WIFI", "Bijwerken via WIFI");
    add("NL", "UPDATE_BINEUSE_WIFI", "Software-update");
    add("NL", "UPDATE_GPS_WIFI", "GPS-update");
    add("NL", "UPDATE_SERIAL_WIFI", "Serie-update");
    add("NL", "UPDATE_USB", "Bijwerken via USB-sleutel");
    add("NL", "UPDATE_BINEUSE_USB", "Software-update");
    add("NL", "INFOS_OPTIONS", "Opties");
    add("NL", "SOFTWARE", "Software geactiveerd");
    add("NL", "GPS", "GPS");
    add("NL", "SERIAL", "Serial");
    add("NL", "OPTIONS", "Opties");
    add("NL", "UPDATE_WIFI_ENABLE", "WIFI-update inschakelen");
    add("NL", "UPDATE_USB_ENABLE", "Schakel USB-update in");
    add("NL", "REMOTE_ENABLE", "Schakel externe toegang in");
    add("NL", "OPERATING_SYSTEM", "Besturingssysteem");
    add("NL", "UPDATE_OS", "Bijwerken");
    add("NL", "UPDATE_DEPS", "Afhankelijkheden installeren");
    add("NL", "RESET_OS", "Opnieuw instellen");
    //verifyAll();
}

void Langage::add(std::string langage, std::string key, std::string trad){
    if(langage == "FR"){
        m_fr[key] = trad;
    } else if(langage == "EN"){
        m_en[key] = trad;
    } else if(langage == "DE"){
        m_de[key] = trad;
    } else if(langage == "NL"){
        m_nl[key] = trad;
    }
    for(auto e : m_all){
        if(e == key){
            return;
        }
    }
    m_all.push_back(key);
}

void Langage::VerifyLangage(std::string lg, std::ofstream & myfile2){
    auto & dico_trad = m_nl;
    if(lg == "EN"){
        dico_trad = m_en;
    } else if(lg == "DE"){
        dico_trad = m_de;
    } else if(lg == "NL"){
        dico_trad = m_nl;
    }
    
    for(auto s : m_all){
        std::string trad = "*****";
        std::string s2 = s;
        auto i = dico_trad.find(s2);
        
        if(i != dico_trad.end()){
            trad = i->second;
            myfile2 << "add(\"" << lg << "\", \"" << s << "\", \"" << trad << "\");\n";
        } else {
            std::string trad_fr = "*****";
            std::string s2_fr = s;
            auto i_fr = m_fr.find(s2);
            if(i_fr != m_fr.end()){
                trad_fr = i_fr->second;
            }
            
            myfile2 << "add(\"" << lg << "\", \"" << s << "\", \"" << trad << "\");//" << trad_fr << "\n";
        }
    }
}


void Langage::verifyAll(){

    std::ofstream myfile;
    myfile.open ("/Users/lemairec/workspace/lemca/all.txt");
    for(auto s : m_all){
        myfile << s << "\n";
        
    }
    myfile.close();
    
    std::ofstream myfile2;
    myfile2.open ("/Users/lemairec/workspace/lemca/all2.txt");
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
    VerifyLangage("EN", myfile2);
    
    myfile2 << "\n";
    myfile2 << "\n";
    VerifyLangage("DE", myfile2);
    
    myfile2 << "\n";
    myfile2 << "\n";
    VerifyLangage("NL", myfile2);
    
    
    myfile2.close();
        
}
