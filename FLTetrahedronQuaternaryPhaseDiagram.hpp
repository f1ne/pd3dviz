//
//  FLTetrahedronQuaternaryPhaseDiagram.h
//  compoundsModel
//
//  Created by Rinat Enikeev on 5/12/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLTetrahedron.hpp"
#include "FLQuaternaryCompound.hpp"
#include <vector>
#include <string>

using namespace std;

class FLTetrahedronQuaternaryPhaseDiagram: public FLTetrahedron
{
public:
    FLTetrahedronQuaternaryPhaseDiagram(GLenum rm);
    FLTetrahedronQuaternaryPhaseDiagram(const string& name, float scale, GLenum rm);
    void GenerateVertices(vector<float>& vertices) const;
    void GenerateLineIndices(vector<unsigned short> &indices) const;
    void GenerateTriangleIndices(vector<unsigned short>& indices) const;
    int GetTriangleIndexCount() const;
    int GetLineIndexCount() const;
    int GetVertexCount() const;
    
    void insertQuaternaryCompound(FLQuaternaryCompound quaternaryCompound);
    vector<float> arrayOfTripleVertexCoordinatesOfCompounds();
    int compoundsCount;
    
    struct Vertex {
        vec3 Position;
        vec3 Normal; // normal to vertex defined as a vector sum of normals to faces around this vertex
        vec3 SourceColor;
        vec2 TexCoord;
    };
    
private:
    void readFromFile(const string& name);
    vector<FLQuaternaryCompound> quaternaryCompounds;
    vector<float> quaternaryCompoundsCoordinates;
    vec3 quaternaryCompoundCoordinatesInTetrahedron(FLQuaternaryCompound quaternaryCompound) const;
    static const int MaxLineSize = 128;
    mutable size_t m_vertexCount;
    string m_name;
};