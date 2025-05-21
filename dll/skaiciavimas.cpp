#define SKAICIAVIMAS_EXPORTS  
#include <iostream>
#include <cmath>
#include "../vektoriai/students.h"
#include "../vektoriai/Zmogus.h"
#include "skaiciavimas.h"


double vidurkis(const int* hw, int dydis)
{
    double suma = 0;
   
    for (int i=0; i < dydis; ++i)
    {
        suma += hw[i];
    }
    return dydis != 0 ? suma / dydis : 0;
}