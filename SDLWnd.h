#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

#include <string>

#ifdef __APPLE__
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE==1
extern "C" {
#include "jwzglesI.h"
}
#include "jwzgles.h"

#elif TARGET_OS_MAC==1
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#define GL_POINT_SPRITE_OES GL_POINT_SPRITE
#define GL_COORD_REPLACE_OES GL_COORD_REPLACE_ARB
#else
#error "Unsupported Apple platform (only OS X and iPhone are supported out of the box)"
#endif

#else /* ifdef __APPLE__ */
#error "Replace this line with #define linux, and prepare to do minor adjustments"

#ifdef SDL_VIDEO_OPENGL_ES2 /* for Android, TODO: add proper ifdef
Android version of SDL loads libGLESv1_CM.so and imports GL10 (ES 1.0 lib)
but the manifest enables OpenGL ES 2.0 for some reason */
#error "You should use version 1 of GLES"
#endif
#endif /* ifdef __APPLE__ */

#ifdef linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glx.h>
# ifndef  GL_GLEXT_PROTOTYPES
#  define GL_GLEXT_PROTOTYPES /* for glBindBuffer */
# endif
#endif



#include "SDL.h"
#if TARGET_OS_IPHONE==1
#include "SDL_opengles.h"
#else
#include "SDL_opengl.h"
#endif

#include "Vector.h"

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
    
    static void TextOut(int x, int y, const char *fmt, ...);
    
protected:
    
    double m_fov;  ///< Length of an axis
    int m_width;       ///< Width of the window in pixel
    int m_height;      ///< Height of the window in pixel
    float max_size;    ///< for dust clouds
    int m_fps;
    int m_idxSnapshot;
    
    Vec3D m_camPos;    ///< Position of the camera
    Vec3D m_camLookAt; ///< Point atwhich the camera is aimed
    Vec3D m_camOrient; ///< orientation of the camera (rotation as it aims at its target)
    
    SDL_Surface *surface;
    SDL_Window* window;
    GLuint m_texStar;
    
    volatile bool m_bRunning;
    
private:
    
    void InitGL();
    void TextureLoading();
};

#endif
