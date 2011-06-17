//
//  QuaternaryCompound.cpp
//  simpleTetrahedron
//
//  Created by Rinat Enikeev on 5/12/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLQuaternaryCompound.hpp"
FLQuaternaryCompound::FLQuaternaryCompound()
{
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    
    fractionA = 0;
    fractionB = 0;
    fractionC = 0;
    fractionD = 0;
}
    
FLQuaternaryCompound::FLQuaternaryCompound(FLChemicalElement* pA, float fA, 
                                           FLChemicalElement* pB, float fB, 
                                           FLChemicalElement* pC, float fC, 
                                           FLChemicalElement* pD, float fD)  
{
    A = pA;
    B = pB;
    C = pC;
    D = pD;
    
    fractionA = fA;
    fractionB = fB;
    fractionC = fC;
    fractionD = fD;
}
