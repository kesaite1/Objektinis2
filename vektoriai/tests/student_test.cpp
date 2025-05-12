#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../vektoriai/students.h"


TEST_CASE("Studentas constructor and getters") {
    Studentas s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    s.pazymys_vidurkis();
    s.pazymys_mediana();

    REQUIRE(s.getVardas() == "Jonas");
    REQUIRE(s.getPavarde() == "Jonaitis");
    REQUIRE(s.getEgzaminas() == 9);
    REQUIRE(s.getHw().size() == 3);
    REQUIRE(s.getPazVid() == 8.0);
    REQUIRE(s.getPazM() == 8.0);
}

TEST_CASE("The Rule of Five") {
    Studentas s1("Petras", "Petraitis", {5, 9, 10, 8},7);

    Studentas copy(s1); // Copy constructor
    REQUIRE(copy.getVardas() == "Petras");
    
    Studentas s2;
    s2 = s1;
    REQUIRE(s2.getEgzaminas() == 8);

    Studentas s3("Saule", "Saulyte", {6, 4, 8}, 4);
    Studentas s4(move(s3)); // Move constructor
    REQUIRE(s4.getVardas() == "Saule");

    Studentas s5("Egle", "Eglaite", {10, 9}, 8 );
    Studentas s6;
    s6 = move(s5);
    REQUIRE(s6.getEgzaminas() == 8);
}
