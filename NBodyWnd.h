#ifndef _NBODYWND_H
#define	_NBODYWND_H

#include "SDLWnd.h"
#include "Galaxy.h"

#include <stdint.h>
#include <fstream>

/** \brief Main window of th n-body simulation. */
class NBodyWnd : public SDLWindow
{
public:
    
    NBodyWnd(int sz, std::string caption);
    virtual ~NBodyWnd();
    
    virtual void Render();
    virtual void OnProcessEvents(SDL_Event &e);
    
    void Init();
    
private:
    
    enum EDisp
    {
        dspNONE           = 0,
        dspAXIS           = 1 << 0,
        dspSTARS          = 1 << 1,
        dspSTAT           = 1 << 2,
        dspPAUSE          = 1 << 3,
        dspHELP           = 1 << 4,
        dspROI            = 1 << 5,
        dspRADII          = 1 << 7,
        dspDUST           = 1 << 9,
#if TARGET_OS_IPHONE==0
        dspDENSITY_WAVES  = 1 << 6,
        dspVELOCITY       = 1 << 8,
#endif
        dspH2             = 1 << 10
    };
    
    struct Color
    {
        double r;
        double g;
        double b;
    };
    
    NBodyWnd(const NBodyWnd& orig);
    
#if TARGET_OS_IPHONE==0
    void DrawStars();
    void DrawDust();
    void DrawH2();
    void DrawGalaxyRadii();
    void DrawDensityWaves(int num, double rad);
    void DrawVelocity();
#endif
    void DrawStat();
    void DrawHelp();
    void DrawCenterOfMass();
    void DrawEllipse(double a, double b, double angle);
    Color ColorFromTemperature(double temp) const;
    
    int m_camOrient;    ///< Index of the camera orientation to use
    int m_starRenderType;
    double m_roi;       ///< Radius of the region of interest
    uint32_t m_flags;   ///< The display flags
    bool m_bDumpImage;
    
    Galaxy m_galaxy;
    
    // Star color management
    int m_colNum;
    double m_t0, m_t1, m_dt;
    Color m_col[200];
};

#endif	/* _NBODYWND_H */

