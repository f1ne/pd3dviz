//
//  TetrahedronQuaternaryPhaseDiagram.cpp
//  compoundsModel
//
//  Created by Rinat Enikeev on 5/12/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLTetrahedronQuaternaryPhaseDiagram.hpp"
#import <list>
#import <fstream>
#import <assert.h>

using namespace std;

FLTetrahedronQuaternaryPhaseDiagram::FLTetrahedronQuaternaryPhaseDiagram(const string& name, float scale, GLenum rm)
:
m_name(name),
m_vertexCount(0)
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
    
    RenderMode = rm;
    
    ifstream compoundFile(m_name.c_str());
//    compoundsCount = count(istreambuf_iterator<char>(compoundFile),
//                      istreambuf_iterator<char>(),'\n');
    compoundsCount = 48;
    quaternaryCompounds.resize(compoundsCount);
    
    vector<FLQuaternaryCompound>::iterator compound = quaternaryCompounds.begin();
    while (compoundFile) {
        compoundFile.get();
        assert(compound != quaternaryCompounds.end() && "parse error");
        compoundFile >> compound->fractionA >> compound->fractionB >> compound->fractionC >> compound->fractionD;
        *compound++;
        compoundFile.ignore(MaxLineSize, '\n');
    }
    assert(compound == quaternaryCompounds.end() && "parse error");
}

int FLTetrahedronQuaternaryPhaseDiagram::GetVertexCount() const
{
    m_vertexCount = compoundsCount * 4;
    return m_vertexCount; // every compound generates 4 vertices for mini tetrahedron
}

int FLTetrahedronQuaternaryPhaseDiagram::GetTriangleIndexCount() const
{
    return m_vertexCount * 3; // 1 compound is a little tetrahedron, 4 vertices generates 12 indexes (GL_TRIANGLES mode) 
}

FLTetrahedronQuaternaryPhaseDiagram::FLTetrahedronQuaternaryPhaseDiagram(GLenum rm)
{
    leftVertex.Position  = vec3(0.0f, 0.0f, 0.0f) ;
    leftVertex.Normal    = vec3(-sqrtf(2.0f/3.0f), -sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    rightVertex.Position = vec3(1.0f, 0.0f, 0.0f);
    rightVertex.Normal   = vec3(sqrtf(2.0f/3.0f), -sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    frontVertex.Position = vec3(0.5f, sqrtf(3.0f)/2.0f, 0.0f);
    frontVertex.Normal   = vec3(0, 2.0f*sqrtf(2.0f)/3.0f, -1.0f/3.0f);
    
    topVertex.Position   = vec3(0.5f, 1.0f/(2.0f*sqrtf(3.0f)), sqrtf(2.0f/3.0f));
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
    
    RenderMode = rm;
}

void FLTetrahedronQuaternaryPhaseDiagram::insertQuaternaryCompound(FLQuaternaryCompound quaternaryCompound)
{
    quaternaryCompounds.push_back(quaternaryCompound);
    compoundsCount++;
}

vector<float> FLTetrahedronQuaternaryPhaseDiagram::arrayOfTripleVertexCoordinatesOfCompounds()
{
    
    quaternaryCompoundsCoordinates.resize(compoundsCount * 6); // vertices and normals
    
    int arrIt = 0;

    for (int i=0; i<compoundsCount; i++) {
        
        vec3 CompoundsCoordVector = quaternaryCompoundCoordinatesInTetrahedron(quaternaryCompounds[i]);
        quaternaryCompoundsCoordinates[arrIt] = CompoundsCoordVector.x;
        arrIt++;
        quaternaryCompoundsCoordinates[arrIt] = CompoundsCoordVector.y;
        arrIt++;
        quaternaryCompoundsCoordinates[arrIt] = CompoundsCoordVector.z;
        arrIt++;
    }
    
    return quaternaryCompoundsCoordinates;
}

void FLTetrahedronQuaternaryPhaseDiagram::GenerateVertices(vector<float> &vertices) const
{
    
    // Read in the vertex positions and initialize lighting normals to (0, 0, 0).
    vertices.resize(GetVertexCount() * 11); //  x,y,z of vertex plus x,y,z of Normal plus 4 color
    Vertex* vertex = (Vertex*) &vertices[0];

    vec3 pointPosition;
    vec3 leftV;
    vec3 rightV;
    vec3 frontV;
    vec3 topV;

    vec3 translateOriginToCenterOfMassVector = vec3(
        topVertex.Position.x * 0.25 + rightVertex.Position.x * 0.25 + leftVertex.Position.x * 0.25 + frontVertex.Position.x * 0.25,
        topVertex.Position.y * 0.25 + rightVertex.Position.y * 0.25 + leftVertex.Position.y * 0.25 + frontVertex.Position.y * 0.25,
        topVertex.Position.z * 0.25 + rightVertex.Position.z * 0.25 + leftVertex.Position.z * 0.25 + frontVertex.Position.z * 0.25
        );
    
    for (int i=0; i<compoundsCount; i++)
    {
        pointPosition = quaternaryCompoundCoordinatesInTetrahedron(quaternaryCompounds[i]);
        
        leftV = pointPosition - (translateOriginToCenterOfMassVector / 50);
        rightV = leftV + (rightVertex.Position / 50);
        frontV = leftV + (frontVertex.Position / 50);
        topV = leftV + (topVertex.Position / 50);
        
        vertex->Normal = topVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 0.0f, 255.0f);
        (vertex++)->Position = topV - translateOriginToCenterOfMassVector;
        
        vertex->Normal = rightVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 0.0f, 255.0f);
        (vertex++)->Position = rightV - translateOriginToCenterOfMassVector;
        
        vertex->Normal = leftVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 0.0f, 255.0f);
        (vertex++)->Position = leftV - translateOriginToCenterOfMassVector;
        
        vertex->Normal = frontVertex.Normal;
        vertex->SourceColor = vec3(0.0f, 0.0f, 255.0f);
        (vertex++)->Position = frontV - translateOriginToCenterOfMassVector;
    }
    
}

void FLTetrahedronQuaternaryPhaseDiagram::GenerateTriangleIndices(vector<unsigned short>& indices) const
{
    int indicesCount = GetTriangleIndexCount();
    indices.resize(indicesCount);
    vector<unsigned short>::iterator index = indices.begin();
    
    // compounds
    for (int i=0; i < m_vertexCount; i = i+4)
    {
        *index++ = i+1;
        *index++ = i+2;
        *index++ = i;

        *index++ = i+1;
        *index++ = i;
        *index++ = i+3;

        *index++ = i+1;
        *index++ = i+3;
        *index++ = i+2;


        *index++ = i+3;
        *index++ = i;
        *index++ = i+2;
    }
}

void FLTetrahedronQuaternaryPhaseDiagram::GenerateLineIndices(vector<unsigned short> &indices) const
{
    indices.resize(GetLineIndexCount());
    vector<unsigned short>::iterator index = indices.begin();
    
    *index++ = 0;
    *index++ = 1;
    
    *index++ = 0;
    *index++ = 2;
    
    *index++ = 0;
    *index++ = 3;
    
    *index++ = 1;
    *index++ = 2;
    
    *index++ = 2;
    *index++ = 3;
    
    *index++ = 3;
    *index++ = 1;
}

int FLTetrahedronQuaternaryPhaseDiagram::GetLineIndexCount() const
{
    return 12;
}

vec3 FLTetrahedronQuaternaryPhaseDiagram::quaternaryCompoundCoordinatesInTetrahedron(FLQuaternaryCompound quaternaryCompound) const
{
    return vec3(
                topVertex.Position.x * quaternaryCompound.fractionA + rightVertex.Position.x * quaternaryCompound.fractionB + leftVertex.Position.x * quaternaryCompound.fractionC + frontVertex.Position.x * quaternaryCompound.fractionD,
                topVertex.Position.y * quaternaryCompound.fractionA + rightVertex.Position.y * quaternaryCompound.fractionB + leftVertex.Position.y * quaternaryCompound.fractionC + frontVertex.Position.y * quaternaryCompound.fractionD,
                topVertex.Position.z * quaternaryCompound.fractionA + rightVertex.Position.z * quaternaryCompound.fractionB + leftVertex.Position.z * quaternaryCompound.fractionC + frontVertex.Position.z * quaternaryCompound.fractionD
                );
}