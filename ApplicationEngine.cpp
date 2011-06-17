//
//  ApplicationEngine.cpp
//  tetraCompound
//
//  Created by Rinat Enikeev on 5/14/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//
#include "Interfaces.hpp"
#include "FLTetrahedron.hpp"
#include "FLTetrahedronQuaternaryPhaseDiagram.hpp"
#include "FLTetrahedronWithBoundsDivisions.hpp"
#include "FLText3D.hpp"

using namespace std;

namespace tetraCompound {
    
static const int SurfaceCount = 6;
        
struct Animation {
    bool Active;
    float Elapsed;
    float Duration;
    Visual StartingVisuals[SurfaceCount];
    Visual EndingVisuals[SurfaceCount];
};
    
class ApplicationEngine : public IApplicationEngine {
public:
    ApplicationEngine(IRenderingEngine* renderingEngine, IResourceManager* resourceManager); 
    void Initialize(int width, int height);
    
    ~ApplicationEngine();
    
    void OnFingerUp(ivec2 location);
    void OnFingerDown(ivec2 location);
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
    
    void Render() const;
    void UpdateAnimation(float timeStep);
    
private:
        
    vec3 MapToSphere(ivec2 touchpoint) const;
    
    IRenderingEngine* m_renderingEngine;
    IResourceManager* m_resourceManager;
    int m_currentSurface;
    Animation m_animation;
    Quaternion m_orientation;
    Quaternion m_previousOrientation;
    
    ivec2 m_screenSize;
    ivec2 m_centerPoint;
    float m_trackballRadius;
    bool m_spinning;
    
    ivec2 m_fingerStart;
};
    
IApplicationEngine* CreateApplicationEngine(IRenderingEngine* renderingEngine, IResourceManager* resourceManager)
{
    return new ApplicationEngine(renderingEngine, resourceManager);
}

ApplicationEngine::ApplicationEngine(IRenderingEngine* renderingEngine, IResourceManager* resourceManager) :
    m_renderingEngine(renderingEngine),
    m_spinning(false),
    m_resourceManager(resourceManager)
{
    m_animation.Active = false;
    m_currentSurface = 0;
}
    
void ApplicationEngine::Initialize(int width, int height)
{
    m_trackballRadius = width / 3;
    m_screenSize = ivec2(width, height);
    m_centerPoint = m_screenSize / 2;
    string path = m_resourceManager->GetResourcePath();
    
    vector<ISurface*> surfaces(SurfaceCount);

    FLTetrahedronWithBoundsDivisions* FLTWBD = new FLTetrahedronWithBoundsDivisions(2.5, GL_LINES);
    
    surfaces[0] = new FLTetrahedronQuaternaryPhaseDiagram(path + "/nimninco.ABCD", 2.5, GL_TRIANGLES);
    
    surfaces[1] = FLTWBD;

    surfaces[2] = new FLText3D("ni", (FLTWBD->topVertex.Position) - (FLTWBD->translateOriginToCenterOfMassVector));
     
    surfaces[3] = new FLText3D("mn", (FLTWBD->rightVertex.Position) - (FLTWBD->translateOriginToCenterOfMassVector));

    surfaces[4] = new FLText3D("in", (FLTWBD->leftVertex.Position) - (FLTWBD->translateOriginToCenterOfMassVector));
    
    surfaces[5] = new FLText3D("co", (FLTWBD->frontVertex.Position) - (FLTWBD->translateOriginToCenterOfMassVector));
    
    m_renderingEngine->Initialize(surfaces);
    for (int i = 0; i < SurfaceCount; i++)
        delete surfaces[i];
}
void ApplicationEngine::Render() const
{
    vector<Visual> visuals(SurfaceCount);
    
    visuals[0].Color = vec3(255.0f, 1.0f, 1.0f);
    visuals[0].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[0].Orientation = m_orientation;
    visuals[0].RenderMode = GL_TRIANGLES;
    
    visuals[1].Color = vec3(0.0f, 0.0f, 128.0f);
    visuals[1].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[1].Orientation = m_orientation;
    visuals[1].RenderMode = GL_LINES; // must be the same as in Initialize
    
    visuals[2].Color = vec3(0.0f, 128.0f, 0.0f);
    visuals[2].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[2].Orientation = m_orientation;
    visuals[2].RenderMode = GL_TRIANGLES; // must be the same as in Initialize
    
    visuals[3].Color = vec3(0.0f, 128.0f, 0.0f);
    visuals[3].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[3].Orientation = m_orientation;
    visuals[3].RenderMode = GL_TRIANGLES; // must be the same as in Initialize
    
    visuals[4].Color = vec3(0.0f, 128.0f, 0.0f);
    visuals[4].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[4].Orientation = m_orientation;
    visuals[4].RenderMode = GL_TRIANGLES; // must be the same as in Initialize
    
    visuals[5].Color = vec3(0.0f, 128.0f, 0.0f);
    visuals[5].ViewportSize = ivec2(m_screenSize.x, m_screenSize.y);
    visuals[5].Orientation = m_orientation;
    visuals[5].RenderMode = GL_TRIANGLES; // must be the same as in Initialize
    
    
    m_renderingEngine->Render(visuals);
}
    
void ApplicationEngine::UpdateAnimation(float dt)
{
    if (m_animation.Active) {
        m_animation.Elapsed += dt;
        if (m_animation.Elapsed > m_animation.Duration)
            m_animation.Active = false;
    }
}
    
    
vec3 ApplicationEngine::MapToSphere(ivec2 touchpoint) const
{
    vec2 p = touchpoint - m_centerPoint;
    
    // Flip the Y axis because pixel coords increase towards the bottom.
    p.y = -p.y;
    
    const float radius = m_trackballRadius;
    const float safeRadius = radius - 1;
    
    if (p.Length() > safeRadius) {
        float theta = atan2(p.y, p.x);
        p.x = safeRadius * cos(theta);
        p.y = safeRadius * sin(theta);
    }
    
    float z = sqrt(radius * radius - p.LengthSquared());
    vec3 mapped = vec3(p.x, p.y, z);
    return mapped / radius;
}
    
    void ApplicationEngine::OnFingerUp(ivec2 location)
    {
        m_spinning = false;
        
    }
    
    void ApplicationEngine::OnFingerDown(ivec2 location)
    {
        m_fingerStart = location;
        m_previousOrientation = m_orientation;
        m_spinning = true;
    }
    
    void ApplicationEngine::OnFingerMove(ivec2 oldLocation, ivec2 location)
    {
        if (m_spinning) {
            vec3 start = MapToSphere(m_fingerStart);
            vec3 end = MapToSphere(location);
            Quaternion delta = Quaternion::CreateFromVectors(start, end);
            m_orientation = delta.Rotated(m_previousOrientation);
        }
    }

    
ApplicationEngine::~ApplicationEngine()
{
    delete m_renderingEngine;
}
}