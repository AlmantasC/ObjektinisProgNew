#include "mylib.h"
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <sstream>

namespace chr = std::chrono;

std::string randomstr(){
    int l = rand()%10+1;
    std::string name="", table="abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i<l; i++)
        name+=table[rand()%26];
    name[0]=toupper(name[0]);
    return name;
}

bool pagalVard(const studentas& a, const studentas& b){ return a.getVardas() < b.getVardas(); }
bool pagalPavard(const studentas& a, const studentas& b){ return a.getPavarde() < b.getPavarde(); }
bool pagalGal(const studentas& a, const studentas& b){ return a.getGal() < b.getGal(); }

int getInt(int min, int max) {
    int value;
    while (true) {
        try {
            if (!(std::cin>>value)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::runtime_error("Neteisinga įvestis");
            }
            char leftover;
            if (std::cin.get(leftover)&&leftover!='\n') {
                std::cin.ignore(10000, '\n');
                throw std::runtime_error("Neteisinga įvestis");
            }
            if (value<min||value>max)
                throw std::runtime_error("Pasirinkimas turi būti tarp "+std::to_string(min)+" ir "+std::to_string(max));
            return value;
        }
        catch (const std::runtime_error& e) {
            std::cout<<e.what()<<", pabandykite dar kartą: ";
        }
    }
}

std::string getFile() {
    std::string failas;
    std::cout << "Įveskite failo pavadinimą: ";
    std::cin >> failas;
    while (true) {
        try {
            std::ifstream fin(failas);
            if (!fin.is_open())
                throw std::runtime_error("Failas \"" + failas + "\" nerastas");
            fin.close();
            return failas;
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what() << ", pabandykite dar karta: ";
            std::cin >> failas;
        }
    }
}

void printRez(std::ostream& out, std::deque<studentas>& A, int skaiciavimas) {
    out<<std::fixed<<std::setprecision(2)<<std::left<<std::setw(15)<<"Vardas"<<std::setw(15)<<" Pavardė"<<"\tGalutinis ";
    out<<(skaiciavimas == 1 ? "(Vid.)" : "(Med.)");
    out<<"\n------------------------------------------------\n";
    for (const auto& s : A)
        out << s << '\n';
}

void ivestiRanka(std::deque<studentas>& A, int& m) {
    studentas temp;
    int x;
    std::string v, p;
    std::cout<<"Įrašykite studento vardą (arba -1 baigti): ";
    while (std::cin>>v && v!="-1") {
        temp.setVardas(v);
        std::cout<<"Įrašykite studento pavardę: ";
        std::cin>>p;
        temp.setPavarde(p);
        m++;
        temp.clearPaz();
        std::cout<<"Įrašykite studento nd pažymį (arba -1 baigti): ";
        while (true) {
            x=getInt(-1, 10);
            if(x==-1) break;
            temp.addPaz(x);
            std::cout<<"Irasykite studento nd pazymi (arba -1 baigti): ";
        }
        std::cout<<"Įrašykite studento egzamino pažymį: ";
        temp.setEgz(getInt(0, 10));
        A.push_back(temp);
        std::cout<<"Įrašykite studento vardą (arba -1 baigti): ";
    }
}

void generuotiPazymius(std::deque<studentas>& A, int& m) {
    studentas temp;
    int n;
    std::string v, p;
    std::cout<<"Po kiek nd pažymių generuoti: ";
    std::cin>>n;
    std::cout<<"Įrašykite studento vardą (arba -1 baigti): ";
    while (std::cin>>v && v!="-1") {
        temp.setVardas(v);
        std::cout<<"Įrašykite studento pavardę: ";
        std::cin>>p;
        temp.setPavarde(p);
        m++;
        temp.clearPaz();
        for (int i=0; i<n; i++) temp.addPaz(rand()%10+1);
        temp.setEgz(rand()%10+1);
        A.push_back(temp);
        std::cout<<"Įrašykite studento vardą (arba -1 baigti): ";
    }
}

void generuotiViska(std::deque<studentas>& A, int& m) {
    studentas temp;
    int n;
    std::cout<<"Kiek studentų sugeneruoti: ";
    std::cin>>m;
    std::cout<<"Po kiek nd pažymių generuoti: ";
    std::cin>>n;
    for (int i=0; i<m; i++) {
        temp.setVardas(randomstr());
        temp.setPavarde(randomstr());
        temp.clearPaz();
        for (int j=0; j<n; j++) temp.addPaz(rand()%10+1);
        temp.setEgz(rand()%10+1);
        A.push_back(temp);
    }
}

void skaitytiIsFailo(std::deque<studentas>& A, int& m, std::string& failas) {
    std::string line;
    std::ifstream fin(failas);
    std::getline(fin, line); // antraštė
    while (std::getline(fin, line)) {
        studentas temp;
        std::istringstream iss(line);
        iss >> temp;
        A.push_back(std::move(temp));
        m++;
    }
    fin.close();
}

void generuotiFaila(){
    int n;
    std::cout<<"Kiek studentu norite generuoti?: ";
    n=getInt(1,10000000);
    auto tStart = chr::high_resolution_clock::now();
    std::ofstream fout("generuotas.txt");
    fout<<std::left<<std::setw(20)<<"Vardas"<<std::setw(20)<<"Pavarde";
    for (int i=0; i<15; i++) fout<<std::setw(20)<<("ND" + std::to_string(i + 1));
    fout<<"Egz.";
    for (int i=1; i<=n; i++) {
        fout<<'\n'<<std::setw(20)<<("Vardas"+std::to_string(i))<<std::setw(20)<<("Pavarde"+std::to_string(i));
        for (int j=0; j<16; j++) fout<<std::setw(20)<<rand()%10+1;
    }
    fout.close();
    auto tEnd = chr::high_resolution_clock::now();
    std::cout<<"Failo kurimas ("<<n<<" studentu): "<<chr::duration_cast<chr::milliseconds>(tEnd-tStart).count()<<" ms\n";
}

void skirstymas(std::deque<studentas>& studentai, std::deque<studentas>& nevykeliai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
        [](const studentas& s){ return s.getGal() >= 5; });
    nevykeliai.assign(std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
    studentai.erase(it, studentai.end());
}
