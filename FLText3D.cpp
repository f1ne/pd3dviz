//
//  FLText3D.cpp
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/27/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLText3D.hpp"

typedef unsigned int PVRTuint32;

int vertexCount;

struct PVR_Texture_Header {
    PVRTuint32 dwHeaderSize;
    PVRTuint32 dwHeight;
    PVRTuint32 dwWidth;
    PVRTuint32 dwMipMapCount;
    PVRTuint32 dwpfFlags;
    PVRTuint32 dwTextureDataSize;
    PVRTuint32 dwBitCount;
    PVRTuint32 dwRBitMask;
    PVRTuint32 dwGBitMask;
    PVRTuint32 dwBBitMask;
    PVRTuint32 dwAlphaBitMask;
    PVRTuint32 dwPVR;
    PVRTuint32 dwNumSurfs;
};

FLText3D::FLText3D(string inputText, vec3 inputPosition)
{
    PVR_Texture_Header* header = (PVR_Texture_Header*) lowCaseLettersTexture;
    
    int w = header->dwWidth;
    int h = header->dwHeight;
    m_textureSize = vec2(w, h);
    
    vertexCount = 12;
    
    textPosition = inputPosition;
    
    text = inputText;
    
    RenderMode = GL_TRIANGLES;
}


int FLText3D::GetVertexCount() const
{
    return vertexCount;
}
int FLText3D::GetLineIndexCount() const
{
    return 0; 
}
int FLText3D::GetTriangleIndexCount() const
{
    return vertexCount;
}
void FLText3D::GenerateVertices(vector<float>& vertices) const 
{
    vertices.resize(GetVertexCount() * 11); // 3:xyz;3:normal;3:color;2:texcoord;
    Vertex* vertex = (Vertex*) &vertices[0];
    
    vec3 pos = vec3(0.0, 0.0, 0.0);
    
    char digits[3 + 1] = {text[0], text[1]};

    for (char* digit = &digits[0]; *digit; ++digit) {
        int glyphIndex = *digit - 97;
        const Glyph& glyph = NumeralGlyphs[glyphIndex];
        WriteGlyphVertex(glyph, pos, 0, vertex);
        vertex++;
        WriteGlyphVertex(glyph, pos, 1, vertex);
        vertex++;
        WriteGlyphVertex(glyph, pos, 2, vertex);
        vertex++;
        WriteGlyphVertex(glyph, pos, 2, vertex);
        vertex++;
        WriteGlyphVertex(glyph, pos, 3, vertex);
        vertex++;
        WriteGlyphVertex(glyph, pos, 1, vertex);
        vertex++;
        pos.x += glyph.Metrics.XAdvance;
    }
}
void FLText3D::GenerateLineIndices(vector<unsigned short>& indices) const 
{
    
}
void FLText3D::GenerateTriangleIndices(vector<unsigned short>& indices) const
{   
    indices.resize(vertexCount);
    vector<unsigned short>::iterator index = indices.begin();
    
    for (int i = 0; i < vertexCount; i++) {
        *index++ = i;
    }
}
void FLText3D::WriteGlyphVertex(const Glyph& glyph, vec3 position, int corner, Vertex* vertex) const
{
    vec2 texcoord;
    texcoord.x = glyph.Position.X;
    texcoord.y = glyph.Position.Y + glyph.Metrics.Height;
    
    position.y -= glyph.Metrics.Height + glyph.Metrics.YBearing;
    
    if (corner % 2) {
        position.x += glyph.Metrics.Width;
        texcoord.x += glyph.Metrics.Width;
    }
    
    if (corner / 2) {
        position.y += glyph.Metrics.Height;
        texcoord.y -= glyph.Metrics.Height;
    }
    
    vertex->Normal = vec3(0.0, 0.0, 1.0);
    vertex->SourceColor = vec3(255.0,177.0,0.0);
    vertex->TexCoord = vec2((1 + texcoord.x) / m_textureSize.x, (1 + texcoord.y) / m_textureSize.y - 1);
    vertex->Position = vec3(position.x, position.y, position.z) * 0.01 + textPosition;

}


