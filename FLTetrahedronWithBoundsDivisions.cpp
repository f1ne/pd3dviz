//
//  FLTetrahedronWithBoundsDivisions.cpp
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/18/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLTetrahedronWithBoundsDivisions.hpp"

using namespace std;

FLTetrahedronWithBoundsDivisions::FLTetrahedronWithBoundsDivisions(float scale, GLenum rm)
{
    // Ox to the right, Oy to the front, Oz up.
    leftVertex.Position  = vec3(0.0f, 0.0f, 0.0f) * scale;
    leftVertex.Normal    = vec3(-sqrtf(2.0f/3.0f), -sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    rightVertex.Position = vec3(1.0f, 0.0f, 0.0f) * scale;
    rightVertex.Normal   = vec3(sqrtf(2.0f/3.0f), -sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    frontVertex.Position = vec3(0.5f, sqrtf(3.0f)/2.0f, 0.0f) * scale;
    frontVertex.Normal   = vec3(0, 2.0f*sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    topVertex.Position   = vec3(0.5f, 1.0f/(2.0f*sqrtf(3.0f)), sqrtf(2.0f/3.0f)) * scale;
    topVertex.Normal     = vec3(0, 0, 1.0f);
    
    
    bottomFace.Normal      = vec3(0, 0, -1.0);
    bottomFace.vertices[0] = leftVertex.Position;
    bottomFace.vertices[1] = rightVertex.Position;
    bottomFace.vertices[2] = frontVertex.Position;
    
    leftFace.Normal        = vec3(-sqrtf(2.0f/3.0f), sqrtf(2.0f)/3.0f, 1.0f/3.0f);
    leftFace.vertices[0]   = leftVertex.Position;
    leftFace.vertices[1]   = frontVertex.Position;
    leftFace.vertices[2]   = topVertex.Position;
    
    rightFace.Normal       = vec3(sqrtf(2.0f/3.0f), sqrtf(2.0f)/3.0f, 1.0f/3.0f);
    rightFace.vertices[0]  = rightVertex.Position;
    rightFace.vertices[1]  = topVertex.Position;
    rightFace.vertices[2]  = frontVertex.Position;
    
    backFace.Normal       = vec3(0, -2.0f*sqrtf(2.0f)/3.0f, 1.0f/3.0f);;
    backFace.vertices[0]  = leftVertex.Position;
    backFace.vertices[1]  = topVertex.Position;
    backFace.vertices[2]  = rightVertex.Position;
    
    translateOriginToCenterOfMassVector = vec3(
                                               topVertex.Position.x * 0.25 + rightVertex.Position.x * 0.25 + leftVertex.Position.x * 0.25 + frontVertex.Position.x * 0.25,
                                               topVertex.Position.y * 0.25 + rightVertex.Position.y * 0.25 + leftVertex.Position.y * 0.25 + frontVertex.Position.y * 0.25,
                                               topVertex.Position.z * 0.25 + rightVertex.Position.z * 0.25 + leftVertex.Position.z * 0.25 + frontVertex.Position.z * 0.25
                                               );
    
    RenderMode = rm;
    
}

void FLTetrahedronWithBoundsDivisions::GenerateVertices(vector<float>& vertices) const
{
    vertices.resize(GetVertexCount() * 11);
    Vertex* vertex = (Vertex*) &vertices[0];
    
    
    vertex->Normal = topVertex.Normal;
    vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
    
    (vertex++)->Position = topVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = rightVertex.Normal;
    vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
    (vertex++)->Position = rightVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = leftVertex.Normal;
    vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
    (vertex++)->Position = leftVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = frontVertex.Normal;
    vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
    (vertex++)->Position = frontVertex.Position - translateOriginToCenterOfMassVector;
    
    // adding divisions
    
    // vector on bottom face
    // vec3 bottomParallelVector = vec3(0.5, 1.0f/(2.0f*sqrtf(3.0f)), 0).Normalized() / 10.0;
    vec3 frontBound = topVertex.Position - frontVertex.Position;
    vec3 rightBound = topVertex.Position - rightVertex.Position;
    
    vec3 rightBottomBound = frontVertex.Position - rightVertex.Position;
    
    for (int i = 1; i<4; i++) {
        
        vertex->Normal = topVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (topVertex.Position * 0.25 * i) - translateOriginToCenterOfMassVector;
        
        vertex->Normal = frontVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (frontVertex.Position + (frontBound * 0.25 * i)) - translateOriginToCenterOfMassVector;
        
        vertex->Normal = frontVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (rightVertex.Position + (rightBound * 0.25 * i)) - translateOriginToCenterOfMassVector;
        
        vertex->Normal = frontVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (frontVertex.Position * 0.25 * i) - translateOriginToCenterOfMassVector;
        
        vertex->Normal = rightVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (rightVertex.Position * 0.25 * i) - translateOriginToCenterOfMassVector;
        
        vertex->Normal = rightVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 255.0f, 0.0f);
        (vertex++)->Position = (rightVertex.Position + (rightBottomBound * 0.25 * i)) - translateOriginToCenterOfMassVector;
    }
    
    // vector front to top
     
    //bottomParallelVector = vec3(frontBound.x, frontBound.y, 0).Normalized() / 10.0;
    
//    for (int i = 1; i<10; i++) {
//        
//        vertex->Normal = frontVertex.Normal;
//        (vertex++)->Position = (frontVertex.Position + (frontBound * i / 10.0)) - translateOriginToCenterOfMassVector;
        
//        vertex->Normal = frontVertex.Normal;
//        (vertex++)->Position = ((frontVertex.Position + (frontBound * i / 10.0)) + bottomParallelVector) - translateOriginToCenterOfMassVector;
  //  }
    
    
}

int FLTetrahedronWithBoundsDivisions::GetVertexCount() const
{
    return 4 + 18;//(9 * 2) + (9 * 2);
}
int FLTetrahedronWithBoundsDivisions::GetLineIndexCount() const
{
    return 12 + 24 + 30;//(9 * 2) + (9 * 2);
}
int FLTetrahedronWithBoundsDivisions::GetTriangleIndexCount() const
{
    return 12 + 24 + 30;//(9 * 2) + (9 * 2);
}

void FLTetrahedronWithBoundsDivisions::GenerateLineIndices(vector<unsigned short>& indices) const
{
    indices.resize(GetTriangleIndexCount());
    vector<unsigned short>::iterator index = indices.begin();
    
    *index++ = 0;
    *index++ = 2;
    *index++ = 1;
    
    *index++ = 0;
    *index++ = 1;
    *index++ = 3;
    
    *index++ = 0;
    *index++ = 3;
    *index++ = 2;
    
    *index++ = 1;
    *index++ = 2;
    *index++ = 3;
    
    
    // divisions left bound
    for (int i = 4; i<22; i = i + 6) {
        
        *index++ = i;
        *index++ = i+1;
        
        *index++ = i;
        *index++ = i+2;
        
        *index++ = i;
        *index++ = i+3;
        
        *index++ = i;
        *index++ = i+4;
    }
    
    for (int i = 5; i<22; i = i + 6) {
       
        *index++ = i;
        *index++ = i+1;
        
//        *index++ = i;
//        *index++ = i+2;
        
//        *index++ = i;
//        *index++ = i+4;
    }
        *index++ = 5;
        *index++ = 21;

        *index++ = 11;
        *index++ = 15;
    
        *index++ = 17;
        *index++ = 9;
    
    
    
        *index++ = 5;
        *index++ = 19;
        
        *index++ = 11;
        *index++ = 13;
    
        *index++ = 17;
        *index++ = 7;
    
    
    
    
    *index++ = 6;
    *index++ = 9;
    
    *index++ = 12;
    *index++ = 15;
    
    *index++ = 18;
    *index++ = 21;
    
    
    
    
    *index++ = 6;
    *index++ = 20;
    
    *index++ = 12;
    *index++ = 14;
    
    *index++ = 18;
    *index++ = 8;
    
    
//    // division
//    for (int i = 4; i<22; i = i + 2) {
//        *index++ = i;
//        *index++ = i+1;
//    }
//    
//    // division
//    for (int i = 22; i<40; i = i + 2) {
//        *index++ = i;
//        *index++ = i+1;
//    }
    
}

void FLTetrahedronWithBoundsDivisions::GenerateTriangleIndices(vector<unsigned short>& indices) const
{
    indices.resize(GetTriangleIndexCount());
    vector<unsigned short>::iterator index = indices.begin();
    
    *index++ = 0;
    *index++ = 2;
    *index++ = 1;
    
    *index++ = 0;
    *index++ = 1;
    *index++ = 3;
    
    *index++ = 0;
    *index++ = 3;
    *index++ = 2;
    
    *index++ = 1;
    *index++ = 2;
    *index++ = 3;
    
    // division
    for (int i = 4; i<10; i = i + 2) {
        *index++ = i;
        *index++ = i+1;
    }
    
//    // division
//    for (int i = 4; i<22; i = i + 2) {
//        *index++ = i;
//        *index++ = i+1;
//    }
//    
//    // division
//    for (int i = 22; i<40; i = i + 2) {
//        *index++ = i;
//        *index++ = i+1;
//    }
    
}