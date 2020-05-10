/*
 * @author Simon Marcel Linden
 * @date 08.05.2020
 * @file INI.h
 */
#define INI_EXPORTS

#pragma once

#ifdef INI_EXPORTS
    #define INI_API __declspec(dllexport)
#else
    #define INI_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

class  INI_API INI {
private:
    std::fstream file;
    std::ofstream newFile;

    std::string filename;

    std::map<std::string, std::map<std::string, std::string>> ini;

    /* Helper functions */
    /**
     * @description Removes spaces, [and = at the beginning and end of a string.
     * @param str
     */
    static void trim(std::string &str);
    /**
     * @description Splits the specified string = character.
     * Returns the left and right sides of the drawing sequences
     * @param str
     * @param left
     * @param right
     */
    static void split(std::string str, std::string &left, std::string &right);
    /**
     * @descriptiom Searches for a section and / or key. Returns true if found, otherwise false
     * @param section
     * @param key
     * @return bool
     */
    bool exists(const std::string& section, const std::string& key = "");
    void readINI();
    void writeINI();
public:
    INI(const std::string filename);
    ~INI();

    bool sectionExists  (const std::string& section);
    bool keyExists      (const std::string& section, const std::string& key);

    //Todo: GetValue from section
    std::string getValue(const std::string& section, const std::string& key);
    //Todo:: WriteValue to section
    void writeValue(const std::string& section, const std::string& key, const std::string& value);
};