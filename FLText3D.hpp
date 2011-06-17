//
//  FLText3D.h
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/27/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//
#include "Interfaces.hpp"
#include "lowCaseLettersTexture.h"

class FLText3D: public ISurface {
public:
    FLText3D(string text, vec3 inputPosition);
    int GetVertexCount() const;
    int GetLineIndexCount() const;
    int GetTriangleIndexCount() const;
    void GenerateVertices(vector<float>& vertices) const; //, unsigned char flags) const;
    void GenerateLineIndices(vector<unsigned short>& indices) const;
    void GenerateTriangleIndices(vector<unsigned short>& indices) const;
    
    struct Vertex {
        vec3 Position;
        vec3 Normal; 
        vec3 SourceColor;
        vec2 TexCoord;
    };
    
    vec3 textPosition;
    
    string text;
    
private:
    void WriteGlyphVertex(const Glyph& glyph, vec3 position, int corner, Vertex* vertex) const;
    vec2 m_textureSize;
};