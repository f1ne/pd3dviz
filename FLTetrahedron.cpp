//
//  tetrahedron.cpp
//  simpleTetrahedron
//
//  Created by Rinat Enikeev on 5/11/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#include "FLTetrahedron.hpp"

FLTetrahedron::FLTetrahedron()
{
    // Ox to the right, Oy to the front, Oz up.
    leftVertex.Position  = vec3(0.0f, 0.0f, 0.0f);
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
    
}

FLTetrahedron::FLTetrahedron(float scale, GLenum rm)
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
    
}

int FLTetrahedron::GetVertexCount() const
{
    return 4;
}
int FLTetrahedron::GetLineIndexCount() const
{
    return 12;
}
int FLTetrahedron::GetTriangleIndexCount() const
{
    return 12;
}
void FLTetrahedron::GenerateVertices(vector<float>& vertices) const//, unsigned char flags) const
{
    
    vertices.resize(GetVertexCount() * 11); // 3:xyz;3:normal;3:color;2:texcoord;
    Vertex* vertex = (Vertex*) &vertices[0];

    vec3 translateOriginToCenterOfMassVector = vec3(
            topVertex.Position.x * 0.25 + rightVertex.Position.x * 0.25 + leftVertex.Position.x * 0.25 + frontVertex.Position.x * 0.25,
            topVertex.Position.y * 0.25 + rightVertex.Position.y * 0.25 + leftVertex.Position.y * 0.25 + frontVertex.Position.y * 0.25,
            topVertex.Position.z * 0.25 + rightVertex.Position.z * 0.25 + leftVertex.Position.z * 0.25 + frontVertex.Position.z * 0.25
            );

    
    vertex->Normal = topVertex.Normal;
    vertex->SourceColor = vec3(255.0,0.0,0.0);
    vertex->TexCoord = vec2(0.0, 0.0);
    (vertex++)->Position = topVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = rightVertex.Normal;
    vertex->SourceColor = vec3(0.0,255.0,0.0);
    vertex->TexCoord = vec2(0.0, 1.0);
    (vertex++)->Position = rightVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = leftVertex.Normal;
    vertex->SourceColor = vec3(0.0,0.0,255.0);
    vertex->TexCoord = vec2(1.0, 0.0);
    (vertex++)->Position = leftVertex.Position - translateOriginToCenterOfMassVector;
    
    
    vertex->Normal = frontVertex.Normal;
    vertex->SourceColor = vec3(0.0,0.0,0.0);
    vertex->TexCoord = vec2(1.0, 1.0);
    (vertex++)->Position = frontVertex.Position - translateOriginToCenterOfMassVector;
    
}
void FLTetrahedron::GenerateLineIndices(vector<unsigned short>& indices) const
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
}
void FLTetrahedron::GenerateTriangleIndices(vector<unsigned short>& indices) const
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

}
