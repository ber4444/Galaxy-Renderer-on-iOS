#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

#include <string>

#ifdef __APPLE__
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE==1
#include <OpenGLES/ES1/gl.h> // include ES 1.1, we don't need ES2
#include <OpenGLES/ES1/glext.h>
extern "C" {
#include "jwzglesI.h"
}
#include "jwzgles.h"
#define GL_POINT_SIZE_MAX_ARB                              0x8127
#define GL_POINT_SIZE_MIN_ARB                              0x8126
#define GL_POINT_SPRITE_ARB                                0x8861
#define GL_POINT_SPRITE_ARB                                0x8861
#define GL_COORD_REPLACE_ARB                               0x8862

#define GL_POINT_SPRITE GL_POINT_SPRITE_OES

#elif TARGET_OS_MAC==1
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

#else
#error "Unsupported Apple platform (only OS X and iPhone are supported out of the box)"
#endif

#else
#error "Replace this line with #define linux, and prepare to do minor adjustments"
#endif

#ifdef linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glx.h>
#endif

#include "SDL.h"
#include "SDL_opengl.h" 

#include "Vector.h"

// leaving out features that would be harder to port to GLES:
#define debug_on_osx 0

/** \brief Basic infrastructure for grafical output using SDL/OpenGL */
class SDLWindow
{
public:
    
    SDLWindow(int width, int height, double axisLen, const std::string &caption);
    virtual ~SDLWindow();
    void MainLoop();
    void ExitMainLoop();
    int GetWidth() const;
    int GetHeight() const;
    virtual void Render() = 0;
    
protected:
    
    virtual void PollEvents();
    virtual void OnProcessEvents(SDL_Event &e);
    
    //-----------------------------------------
    // Camera setup
    //-----------------------------------------
    
    const Vec3D& GetCamPos() const;
    const Vec3D& GetCamOrient() const;
    const Vec3D& GetCamLookAt() const;
    void SetCameraOrientation(const Vec3D &orientation);
    void SetCamera(const Vec3D &pos, const Vec3D &lookAt, const Vec3D &orient);
    void AdjustCamera();
    
    //-----------------------------------------
    // Basic graphics functionality
    //-----------------------------------------
#if TARGET_OS_IPHONE==0
    void DrawAxis(const Vec2D &origin);
#endif
    int GetFPS() const;
    void SaveToTGA(const std::string &sName);
    void SaveToTGA(int idx = -1);
    
    //-----------------------------------------
    // misc
    //-----------------------------------------
    
    void ScaleAxis(double scale);
    double GetFOV() const;
    SDL_Surface *Surface();
    
#ifdef linux
    static void InitFont();
    static void KillFont();
    static void TextOut(const char *fmt, ...);
    static void TextOut(int x, int y, const char *fmt, ...);
    static Vec3D GetOGLPos(int x, int y);
    
    static GLuint s_fontBase;
#else
    static void TextOut(const char *fmt, ...) {};
    static void TextOut(int x, int y, const char *fmt, ...) {};
#endif
    
protected:
    
    double m_fov;  ///< Length of an axis
    int m_width;       ///< Width of the window in pixel
    int m_height;      ///< Height of the window in pixel
    int m_fps;
    int m_idxSnapshot;
    
    Vec3D m_camPos;    ///< Position of the camera
    Vec3D m_camLookAt; ///< Point atwhich the camera is aimed
    Vec3D m_camOrient; ///< orientation of the camera (rotation as it aims at its target)
    
    SDL_Surface *surface;
    SDL_Window* window;
    GLuint m_texStar;
    
#if defined linux || TARGET_OS_IPHONE==1    // function pointer for point sprite extension
    typedef void(* 	PFNGLPOINTPARAMETERFARBPROC )(GLenum pname, GLfloat param);
    typedef void(* 	PFNGLPOINTPARAMETERFEXTPROC )(GLenum pname, GLfloat param);
    PFNGLPOINTPARAMETERFARBPROC  glPointParameterfARB;
#endif
    
    volatile bool m_bRunning;
    
private:
    
    void InitGL();
    void InitPointSpriteExtension();
};

#endif
