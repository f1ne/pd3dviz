//
//  FLTetrahedronWithBoundsDivisions.h
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/18/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLTetrahedron.hpp"

using namespace std;

class FLTetrahedronWithBoundsDivisions: public FLTetrahedron {
public:
    FLTetrahedronWithBoundsDivisions(); // creates Tetrahedron with bound length of bounds = 1
    FLTetrahedronWithBoundsDivisions(float scale, GLenum rm);
    int GetVertexCount() const;
    int GetLineIndexCount() const;
    int GetTriangleIndexCount() const;
    void GenerateVertices(vector<float>& vertices) const;
    void GenerateLineIndices(vector<unsigned short>& indices) const;
    void GenerateTriangleIndices(vector<unsigned short>& indices) const;
    
    struct Vertex {
        vec3 Position;
        vec3 Normal; // normal to vertex defined as a vector sum of normals to faces around this vertex
        vec3 SourceColor;
        vec2 TexCoord;
    };
    struct Face {
        vec3 vertices [3];
        vec3 Normal;        
    };
    
    Vertex topVertex;
    Vertex leftVertex;
    Vertex rightVertex;
    Vertex frontVertex;
    
    Face leftFace;
    Face rightFace;
    Face backFace;
    Face bottomFace;
    
    vec3 translateOriginToCenterOfMassVector;
};
