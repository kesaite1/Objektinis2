#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../vektoriai/students.h"
#include "../vektoriai/Zmogus.h"


TEST_CASE("Studentas constructor and getters") {
    auto zm = make_unique<Studentas>("Jonas", "Jonaitis", ManoVektorius<int>{8, 9, 10}, 9);
    Studentas* s = dynamic_cast<Studentas*>(zm.get()); 
    s->pazymys_vidurkis();
    s->pazymys_mediana();

    REQUIRE(zm->getVardas() == "Jonas");
    REQUIRE(zm->getPavarde() == "Jonaitis");
    REQUIRE(s->getEgzaminas() == 9);
    REQUIRE(s->getHw().size() == 3);
    REQUIRE(s->getPazVid() > 8.0);
    REQUIRE(s->getPazM() > 8.0);
}

TEST_CASE("The Rule of Five") {
    auto zm1 = make_unique<Studentas>("Petras", "Petraitis", ManoVektorius<int>{5, 9, 10, 8}, 7);
    Studentas* s1 = dynamic_cast<Studentas*>(zm1.get()); 

    Studentas copy(*s1); // Copy constructor
    REQUIRE(copy.getVardas() == "Petras");
    
    Studentas s2;
    s2 = *s1;
    REQUIRE(s2.getEgzaminas() == 7);

    Studentas s3("Saule", "Saulyte", {6, 4, 8}, 4);
    Studentas s4(move(s3)); // Move constructor
    REQUIRE(s4.getVardas() == "Saule");

    Studentas s5("Egle", "Eglaite", {10, 9}, 8 );
    Studentas s6;
    s6 = move(s5);
    REQUIRE(s6.getEgzaminas() == 8);
    REQUIRE(s5.getEgzaminas() == 0); 

}

TEST_CASE("Default constructor") {
    ManoVektorius<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("push_back and operator[]") {
    ManoVektorius<int> v;
    v.push_back(42);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 42);

    v.push_back(100);
    REQUIRE(v[1] == 100);
}

TEST_CASE("pop_back") {
    ManoVektorius<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);
}

TEST_CASE("at() throws on bad index") {
    ManoVektorius<int> v;
    v.push_back(10);
    REQUIRE_THROWS_AS(v.at(1), std::out_of_range);
}

TEST_CASE("clear and empty") {
    ManoVektorius<int> v;
    v.push_back(1);
    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("erase") {
    ManoVektorius<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.erase(1); // remove 20
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 30);
}

TEST_CASE("back") {
    ManoVektorius<int> v;
    v.push_back(5);
    v.push_back(9);
    REQUIRE(v.back() == 9);

     system("pause");
}