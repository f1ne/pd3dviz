//
//  Interfaces.hpp
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/14/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//
#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "Vector.hpp"
#include "Quaternion.hpp"
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include <string>

using std::vector;
using namespace std;

enum VertexFlags {
    VertexFlagsNormals     = 0 << 1,
    VertexFlagsSourceColor = 0 << 2,
    VertexFlagsTexCoords   = 0 << 3,
};

struct ISurface {
    virtual int GetVertexCount() const = 0;
    virtual int GetLineIndexCount() const = 0;
    virtual int GetTriangleIndexCount() const = 0;
    virtual void GenerateVertices(vector<float>& vertices) const = 0;
    virtual void GenerateLineIndices(vector<unsigned short>& indices) const = 0;
    virtual void GenerateTriangleIndices(vector<unsigned short>& indices) const = 0;
    virtual ~ISurface() {}
    GLenum RenderMode;
};

struct Visual {
    vec3 Color;
    ivec2 ViewportSize;
    Quaternion Orientation;
    GLenum RenderMode;
};

enum TextureFormat {
    TextureFormatGray,
    TextureFormatGrayAlpha,
    TextureFormatRgb,
    TextureFormatRgba,
    TextureFormatPvrtcRgb2,
    TextureFormatPvrtcRgba2,
    TextureFormatPvrtcRgb4,
    TextureFormatPvrtcRgba4,
    TextureFormat565,
    TextureFormat5551,
};

struct TextureDescription {
    TextureFormat Format;
    int BitsPerComponent;
    ivec2 Size;
    int MipCount;
};

struct IApplicationEngine {
    virtual void Initialize(int width, int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAnimation(float timeStep) = 0;
    virtual void OnFingerUp(ivec2 location) = 0;
    virtual void OnFingerDown(ivec2 location) = 0;
    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) = 0;
    virtual ~IApplicationEngine() {}
};

struct IRenderingEngine {
    virtual void Initialize(const vector<ISurface*>& surfaces) = 0;
    virtual void Render(const vector<Visual>& visuals) const = 0;
    virtual void SetPngTexture(const string& file) const = 0;
    virtual void SetPvrTexture(const string& file) const = 0;
    virtual ~IRenderingEngine() {}
};


struct IResourceManager {
    virtual string GetResourcePath() const = 0;
    virtual TextureDescription LoadPngImage(const string& filename) = 0;
    virtual TextureDescription LoadPvrImage(const string& filename) = 0;
    virtual TextureDescription LoadImage(const string& filename) = 0;
    virtual TextureDescription GenerateCircle() = 0;
    virtual void* GetImageData() = 0;
    virtual void UnloadImage() = 0;
    virtual ~IResourceManager() {}
};
IResourceManager* CreateResourceManager();

namespace tetraCompound { IApplicationEngine* CreateApplicationEngine(IRenderingEngine*, IResourceManager*);}
namespace ES2 { IRenderingEngine* CreateRenderingEngine(IResourceManager* resourceManager); }
#endif