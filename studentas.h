#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>


class Zmogus{
// realizacija
protected:
    std::string vardas_;
    std::string pavarde_;
public:
    Zmogus(std::string vardas = "", std::string pavarde = "") : vardas_{vardas}, pavarde_{pavarde} {}
    virtual inline std::string vardas() const = 0;
    virtual inline std::string pavarde() const = 0;
    virtual ~Zmogus() = default;
};

class Studentas:public Zmogus{
// realizacija
private:
  double vidurkis_;
  double mediana_;

// interfeisas
public:
    // Rule of five
    Studentas() = default;
    Studentas(std::string vardas="", std::string pavarde= "", double vidurkis=0, double mediana=0)
    : Zmogus{vardas, pavarde}, vidurkis_{vidurkis}, mediana_{mediana} {}

    Studentas(const Studentas& s) = default;
    Studentas& operator=(const Studentas& s) = default;
    ~Studentas() = default;

    // Overriding vardas() and pavarde() from Zmogus
    inline std::string vardas() const { return vardas_; }    // get'eriai, inline
    inline std::string pavarde() const { return pavarde_; }  // get'eriai, inline
    
    inline double vidurkis() const { return vidurkis_; }    // get'eriai, inline
    inline double mediana() const { return mediana_; }       // get'eriai, inline

    // Overloading << operator
    friend std::ostream& operator<< (std::ostream& out, const Studentas& point);

};


void sortVector(std::vector<Studentas>& studentai);
int GetIntInput();
int CountN(std::string line);

// Generates randomly
void Ivestis3(std::vector<Studentas> &studentai);
// Gets from user input
void Ivestis2(std::vector<Studentas> &studentai);
// Reads from file
void Ivestis(std::vector<Studentas> &studentai, int &kiekis);

#endif
