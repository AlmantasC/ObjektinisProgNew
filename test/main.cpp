#include "mylib.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <windows.h>
void pass(const std::string& name) {
    std::cout << "[OK] " << name << "\n";
}

// --- Destruktorius ---

void test_destruktorius() {
    studentas* s = new studentas("Jonas", "Jonaitis", {8, 9}, 10);
    delete s; // jei sugriauna — destruktorius sulaužytas
    s = nullptr;
    assert(s == nullptr);
    pass("Destruktorius");
}

// --- Konstruktoriai ---

void test_numatytasis() {
    studentas s;
    assert(s.getVardas()  == "");
    assert(s.getPavarde() == "");
    assert(s.getEgz()     == 0);
    assert(s.getGal()     == 0.0);
    assert(s.getPaz().empty());
    pass("Numatytasis konstruktorius");
}

void test_parametrinis() {
    studentas s("Jonas", "Jonaitis", {8, 9, 7}, 10);
    assert(s.getVardas()  == "Jonas");
    assert(s.getPavarde() == "Jonaitis");
    assert(s.getEgz()     == 10);
    assert(s.getPaz().size() == 3);
    pass("Parametrinis konstruktorius");
}

// --- Rule of Five ---

void test_kopijavimo_konstruktorius() {
    studentas a("Jonas", "Jonaitis", {8, 9}, 10);
    studentas b(a);
    assert(b.getVardas() == "Jonas");
    assert(b.getPaz().size() == 2);
    // Nepriklausomumas — keičiam b, a nesikeičia
    b.setVardas("Petras");
    b.addPaz(5);
    assert(a.getVardas()     == "Jonas");
    assert(a.getPaz().size() == 2);
    pass("Kopijavimo konstruktorius");
}

void test_kopijavimo_priskyrimas() {
    studentas a("Jonas", "Jonaitis", {8, 9}, 10);
    studentas b;
    b = a;
    assert(b.getVardas() == "Jonas");
    // Savipriskyrimas neturi sulaužyti
    b = b;
    assert(b.getVardas() == "Jonas");
    pass("Kopijavimo priskyrimo operatorius");
}

void test_perkelimo_konstruktorius() {
    studentas a("Jonas", "Jonaitis", {8, 9}, 10);
    studentas b(std::move(a));
    assert(b.getVardas()  == "Jonas");
    assert(b.getEgz()     == 10);
    assert(b.getPaz().size() == 2);
    // a turi būti tuščias
    assert(a.getVardas()  == "");
    assert(a.getEgz()     == 0);
    assert(a.getPaz().empty());
    pass("Perkėlimo konstruktorius");
}

void test_perkelimo_priskyrimas() {
    studentas a("Jonas", "Jonaitis", {8, 9}, 10);
    studentas b;
    b = std::move(a);
    assert(b.getVardas()  == "Jonas");
    assert(b.getEgz()     == 10);
    assert(a.getVardas()  == "");
    assert(a.getEgz()     == 0);
    // Savipriskyrimas
    b = std::move(b);
    assert(b.getVardas()  == "Jonas");
    pass("Perkėlimo priskyrimo operatorius");
}

// --- Operatoriai ---

void test_isvesties_operatorius() {
    studentas s("Jonas", "Jonaitis", {8, 9}, 10);
    s.setGal(8.40);
    std::ostringstream oss;
    oss << s;
    // Tikrinam kad yra vardas, pavardė ir galutinis
    assert(oss.str().find("Jonas")    != std::string::npos);
    assert(oss.str().find("Jonaitis") != std::string::npos);
    assert(oss.str().find("8.40")     != std::string::npos);
    pass("Išvesties operatorius <<");
}

void test_ivesties_operatorius() {
    studentas s;
    std::istringstream iss("Jonas Jonaitis 8 9 10");
    iss >> s;
    assert(s.getVardas()     == "Jonas");
    assert(s.getPavarde()    == "Jonaitis");
    assert(s.getEgz()        == 10);
    assert(s.getPaz().size() == 2);
    assert(s.getPaz()[0]     == 8);
    assert(s.getPaz()[1]     == 9);
    pass("Įvesties operatorius >>");
}

void test_roundtrip() {
    // >> nuskaito, << išveda — tikrinam kad duomenys išlieka
    studentas a;
    std::istringstream iss("Petras Petraitis 7 8 9 6");
    iss >> a;
    a.setGal(0.4*a.vid() + 0.6*a.getEgz());

    std::ostringstream oss;
    oss << a;
    assert(oss.str().find("Petras")    != std::string::npos);
    assert(oss.str().find("Petraitis") != std::string::npos);
    pass(">> / << round-trip");
}

// --- Skaičiavimai ---

void test_vid() {
    studentas s("", "", {6, 8, 10}, 0);
    assert(s.vid() == 8.0);
    pass("vid()");
}

void test_med_nelyginis() {
    studentas s("", "", {6, 8, 10}, 0);
    assert(s.med() == 8.0);
    pass("med() nelyginis");
}

void test_med_lyginis() {
    studentas s("", "", {6, 8}, 0);
    assert(s.med() == 7.0);
    pass("med() lyginis");
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    test_destruktorius();
    test_numatytasis();
    test_parametrinis();
    test_kopijavimo_konstruktorius();
    test_kopijavimo_priskyrimas();
    test_perkelimo_konstruktorius();
    test_perkelimo_priskyrimas();
    test_isvesties_operatorius();
    test_ivesties_operatorius();
    test_roundtrip();
    test_vid();
    test_med_nelyginis();
    test_med_lyginis();

    std::cout << "\nVisi testai praejo.\n";
    return 0;
}
