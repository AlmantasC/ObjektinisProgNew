#pragma once
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class studentas {
private:
    std::string vardas, pavarde;
    std::vector<int> paz;
    int egz;
    double rez;
    double gal;

public:
    // Konstruktorius
    studentas()
        : vardas(""), pavarde(""), egz(0), rez(0.0), gal(0.0) {}

    studentas(const std::string& v, const std::string& p,
              const std::vector<int>& pazymiai, int e)
        : vardas(v), pavarde(p), paz(pazymiai), egz(e), rez(0.0), gal(0.0) {}

    // Getteriai
    std::string getVardas()  const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    std::vector<int> getPaz() const { return paz; }
    int getEgz()   const { return egz; }
    double getRez() const { return rez; }
    double getGal() const { return gal; }

    // Setteriai
    void setVardas(const std::string& v)   { vardas = v; }
    void setPavarde(const std::string& p)  { pavarde = p; }
    void setPaz(const std::vector<int>& p) { paz = p; }
    void addPaz(int p)                     { paz.push_back(p); }
    void clearPaz()                        { paz.clear(); }
    void setEgz(int e)                     { egz = e; }
    void setRez(double r)                  { rez = r; }
    void setGal(double g)                  { gal = g; }

    // Skaiciavimai kaip narių funkcijos
    double vid() const {
        if (paz.empty()) return 0.0;
        double suma = 0;
        for (int p : paz) suma += p;
        return suma / paz.size();
    }

    double med() const {
        if (paz.empty()) return 0.0;
        std::vector<int> sorted = paz;
        std::sort(sorted.begin(), sorted.end());
        int n = sorted.size();
        if (n % 2 == 0) return (sorted[n/2-1] + sorted[n/2]) / 2.0;
        else             return sorted[n/2];
    }
};

// Laisvos funkcijos
std::string randomstr();
bool pagalVard(const studentas& a, const studentas& b);
bool pagalPavard(const studentas& a, const studentas& b);
bool pagalGal(const studentas& a, const studentas& b);
int getInt(int min, int max);
std::string getFile();
void printRez(std::ostream& out, std::list<studentas>& A, int skaiciavimas);
void ivestiRanka(std::list<studentas>& A, int& m);
void generuotiPazymius(std::list<studentas>& A, int& m);
void generuotiViska(std::list<studentas>& A, int& m);
void skaitytiIsFailo(std::list<studentas>& A, int& m, std::string& failas);
void generuotiFaila();
void skirstymas(std::list<studentas>& studentai, std::list<studentas>& nevykeliai);
