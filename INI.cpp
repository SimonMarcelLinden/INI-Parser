/*
 * @author Simon Marcel Linden
 * @date 08.05.2020
 * @file INI.cpp
 */

#include <regex>
#include "INI.h"

/* Helper functions */
void INI::trim(std::string &str) {
    if (str[0] == ' '){
        str = str.substr(1, str.length());
        trim(str);
    }
    if (str[str.length()-1] == ' '){
        str = str.substr(0, str.length() - 1);
        trim(str);
    }
    if (str[0] == '['){
        str = str.substr(1, str.length());
        trim(str);
    }
    if(str[str.length()-1] == ']') {
        str = str.substr(0, str.length() - 1);
        trim(str);
    }
    if(str[0] == '=') {
        str = str.substr(1, str.length());
        trim(str);
    }
}
void INI::split(std::string str, std::string &left, std::string &right) {

    int index = 0;
    int jndex = 0;

    for (index = 0; str[index] != '='; index++);

    left.resize(index);
    right.resize(str.length() - index);


    for (int i = 0; i < index; i++){
        left[i] = str[i];
    }

    for (int i = index; i < str.length(); i++){
        right[jndex++] = str[i];
    }

    trim(left);
    trim(right);
}
bool INI::exists(const std::string& section, const std::string& key){
    std::map<std::string, std::map<std::string, std::string> >::iterator parentIterator;
    for (parentIterator = ini.begin(); parentIterator != ini.end(); parentIterator++) {
        if (section == parentIterator->first) {
            if (!key.empty()) {
                std::map<std::string, std::string>::iterator childIterator;
                for (childIterator = parentIterator->second.begin(); childIterator != parentIterator->second.end(); childIterator++) {
                    if ( key == childIterator->first )
                        return true;
                }
                return false;
            }
            return true;
        };
    }
    return false;
}
void INI::writeINI() {
    std::map<std::string, std::map<std::string, std::string> >::iterator parentIterator;
    std::map<std::string, std::string>::iterator childIterator;

    newFile.open(this->filename, std::ios::out | std::ios::trunc);

    if (!newFile.is_open()) {
        newFile.open(this->filename, std::ios::out | std::ios::trunc);
    } else {
        for (parentIterator = ini.begin(); parentIterator != ini.end(); parentIterator++) {
            newFile << "[" + parentIterator->first + "]\n";
            for (childIterator = parentIterator->second.begin(); childIterator != parentIterator->second.end(); childIterator++) {
                newFile << childIterator->first << " = " << childIterator->second << "\n";
            }
        }
    }
    newFile.close();

    /*
    std::string temp;
    std::string key;
    std::smatch matches;

    std::string left;
    std::string right;

    bool parentExists = false;

    std::map<std::string, std::map<std::string, std::string> >::iterator parentIterator;
    std::map<std::string, std::string>::iterator childIterator;

    file.clear();                 // clear fail and eof bits
    file.seekg(0, std::ios::beg);

    while (file.good()) {
        getline(file, temp);
        if ( std::regex_search( temp, matches, std::regex("\\[.+\\]") ) ) {
            trim(temp);
            for (parentIterator = ini.begin(); parentIterator != ini.end(); parentIterator++) {
                if ( parentIterator->first == temp ) {
                    key = temp;
                    continue;
                }
            }
        }
        if ( std::regex_search( temp, matches, std::regex(".+=.+") ) ) {
            split(temp, left, right);

            for (childIterator = ini[key].begin(); childIterator != ini[key].end(); childIterator++) {
                if ( left == childIterator->first && right != childIterator->second ){
                    file << childIterator->first << " = " << childIterator->second << "\n";
                }
            }
        }
    }*/
}
void INI::readINI(){

    std::string temp;
    std::string key;
    std::smatch matches;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!file.is_open()) {
        file.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
    } else {
        while (file.good()) {
            getline(file, temp);
            if ( std::regex_search( temp, matches, std::regex("\\[.+\\]") ) ) {
                trim(temp);
                key = temp;
            }else{
                if ( std::regex_search( temp, matches, std::regex("^#") ) || temp.empty()) {
                    continue;
                }else{
                    std::string left;
                    std::string right;

                    split(temp, left, right);
                    ini[key][left] = right;
                }
            }
        };
    }
    file.close();
}

/* Main functions */
INI::INI(const std::string filename) {
    this->filename = filename;
    readINI();
}
INI::~INI(){
    writeINI();
}

bool INI::sectionExists(const std::string& section){
    return exists(section);
};
bool INI::keyExists(const std::string& section, const std::string& key){
   return exists(section, key);
}

std::string INI::getValue(const std::string& section, const std::string& key){
    if( keyExists( section, key )){
        return ini[section][key];
    }
    return "";
};

void INI::writeValue(const std::string& section, const std::string& key, const std::string& value){
    ini[section][key] = value;
};