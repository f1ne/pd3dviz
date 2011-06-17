//
//  tetrahedron.h
//  simpleTetrahedron
//
//  Created by Rinat Enikeev on 5/11/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//
#ifndef FLTETRAHEDRON_H
#define FLTETRAHEDRON_H
#include "Interfaces.hpp"


class FLTetrahedron: public ISurface {
public:
    FLTetrahedron(); // creates Tetrahedron with bound length of bounds = 1
    FLTetrahedron(float scale, GLenum rm);
    int GetVertexCount() const;
    int GetLineIndexCount() const;
    int GetTriangleIndexCount() const;
    void GenerateVertices(vector<float>& vertices) const; //, unsigned char flags) const;
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
};
#endif