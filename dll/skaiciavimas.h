#pragma once

#ifdef SKAICIAVIMAS_EXPORTS
#define SKAICIAVIMAS_API __declspec(dllexport)
#else
#define SKAICIAVIMAS_API __declspec(dllimport)
#endif

#include "../vektoriai/students.h"
#include "../vektoriai/Zmogus.h"

extern "C" {
    SKAICIAVIMAS_API double vidurkis(const int* hw, int dydis);
}