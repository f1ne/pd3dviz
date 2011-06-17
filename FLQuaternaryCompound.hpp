//
//  QuaternaryCompound.h
//  simpleTetrahedron
//
//  Created by Rinat Enikeev on 5/12/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//
#include "FLCompound.hpp"
#include "FLChemicalElement.hpp"

class FLQuaternaryCompound : FLCompound
{
public:
    FLQuaternaryCompound();
    FLQuaternaryCompound(FLChemicalElement* pA, float fractionA, 
                         FLChemicalElement* pB, float fractionB, 
                         FLChemicalElement* pC, float fractionC, 
                         FLChemicalElement* pD, float fractionD);
    
    FLChemicalElement* A;
    FLChemicalElement* B;
    FLChemicalElement* C;
    FLChemicalElement* D;
    
    float fractionA;
    float fractionB;
    float fractionC;
    float fractionD;
    
};
