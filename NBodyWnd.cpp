#include "NBodyWnd.h"

//--- Standard icludes ---------------------------------------------------------
#include <iostream>
#include <cassert>
#include <limits>
#include <stdexcept>

//------------------------------------------------------------------------------
#include "Constants.h"
#include "specrend.h"
#include "FastMath.h"


//------------------------------------------------------------------------------
NBodyWnd::NBodyWnd(int width, int height, std::string caption)
:SDLWindow(width, height, 35000.0, caption)
  ,m_touchControlSetting(0)
  ,m_flags(dspSTARS | dspDUST | dspH2)
  ,m_bDumpImage(false)
  ,m_galaxy()
  ,m_colNum(200)
  ,m_t0(1000)
  ,m_t1(10000)
  ,m_dt( (m_t1-m_t0) /m_colNum)
{
  double x, y, z;
  for (int i=0; i<m_colNum; ++i)
  {
    Color &col = m_col[i];
    colourSystem *cs = &SMPTEsystem;
    bbTemp = m_t0 + m_dt*i;
    spectrum_to_xyz(bb_spectrum, &x, &y, &z);
    xyz_to_rgb(cs, x, y, z, &col.r, &col.g, &col.b);
    norm_rgb(&col.r, &col.g, &col.b);
  }
}

//------------------------------------------------------------------------------
NBodyWnd::~NBodyWnd()
{}

//------------------------------------------------------------------------------
void NBodyWnd::Init()
{
/*
  m_galaxy.Reset(15000,    // radius of the galaxy
                 4000,     // radius of the core
                 0.000306, // angluar offset of the density wave per parsec of radius
                 0.8,      // excentricity at the edge of the core
                 0.85,     // excentricity at the edge of the disk
                 200,      // orbital velocity at the edge of the core
                 300,      // orbital velovity at the edge of the disk
                 40000);   // total number of stars
*/
  m_galaxy.Reset(13000,    // radius of the galaxy
                 4000,     // radius of the core
                 0.0004,   // angluar offset of the density wave per parsec of radius
                 0.9,      // excentricity at the edge of the core
                 0.9,      // excentricity at the edge of the disk
                 0.5,
                 200,      // orbital velocity at the edge of the core
                 300,      // orbital velovity at the edge of the disk
                 5000);   // total number of stars


  m_roi = m_galaxy.GetFarFieldRad() * 1.3;

  // OpenGL initialization
  glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glLineWidth (1);

  glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_POINT_SPRITE_OES);
  glDisable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.03f, 0.0f);  // black background
  SetCameraOrientation(Vec3D(0, 1, 0));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//------------------------------------------------------------------------------
void NBodyWnd::Render()
{
  static long ct = 0;
  if (!(m_flags & dspPAUSE))
  {
    ++ct;

    if (m_bDumpImage && ct%5==0)
      SaveToTGA();
  }

  glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

  Vec3D orient;
  orient.x = 0;
  orient.y = 1;
  orient.z = 0;

  Vec3D lookAt(0, 0, 0),
        pos(0, 0, 5000);
  SetCamera(pos, lookAt, orient);

  if (!(m_flags & dspPAUSE))
  {
    m_galaxy.SingleTimeStep(100000); // time in years
  }

#ifdef VERY_SLOW_DEBUG_CODE
  if (m_flags & dspSTAT)
    DrawStat();
#endif
    
  if (m_flags & dspDUST)
    DrawDust();
    
  if (m_flags & dspH2)
    DrawH2();
    
  if (m_flags & dspSTARS)
    DrawStars();

#if TARGET_OS_IPHONE==0
  if (m_flags & dspAXIS)
    DrawAxis(Vec2D(0, 0));
    
  if (m_flags & dspDENSITY_WAVES)
    DrawDensityWaves(50, m_galaxy.GetFarFieldRad());

  if (m_flags & dspRADII)
    DrawGalaxyRadii();
    
  if (m_flags & dspVELOCITY)
    DrawVelocity();
#endif

#ifdef VERY_SLOW_DEBUG_CODE
  if (m_flags & dspHELP)
    DrawHelp();
#endif

  SDL_GL_SwapWindow(window);// Swap on-screen/off-screen buffers (double buffering)
}

void NBodyWnd::DrawEllipse(double a, double b, double angle)
{
  const int steps = 100;
  const double x = 0;
  const double y = 0;

  // Angle is given by Degree Value
  double beta = -angle * M_PI / 180; //(Math.PI/180) converts Degree Value into Radians
  double sinbeta = sin(beta);
  double cosbeta = cos(beta);

  glBegin(GL_LINE_STRIP);

  for (int i=0; i<361; i += 360 / steps)
  {
    double alpha = i * (M_PI / 180) ;
    double sinalpha = sin(alpha);
    double cosalpha = cos(alpha);

    double X = x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta);
    double Y = y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta);

    glVertex3f(X, Y, 0);
   }
   glEnd();
}


#if TARGET_OS_IPHONE==0
// note that this is not part of the galaxy simulation so no real need to port to GLES
//------------------------------------------------------------------------------
void NBodyWnd::DrawVelocity()
{
    Star *pStars = m_galaxy.GetStars();
    
    double dt_in_sec = m_galaxy.GetTimeStep() * Constant::SEC_PER_YEAR;
    glPointSize(1);
    glColor3f(0.5, 0.7, 0.5);
    glBegin(GL_POINTS);
    for (int i=0; i<m_galaxy.GetNumStars(); ++i)
    {
        const Vec2D &vel = pStars[i].m_vel;
        double r = pStars[i].m_a; //(pStars[i].m_a + pStars[i].m_b)/2;
        
        // umrechnen in km/s
        double v = sqrt(vel.x*vel.x + vel.y*vel.y);   // pc / timestep
        v /= dt_in_sec;          // v in pc/sec
        v *= Constant::PC_TO_KM; // v in km/s
        
        glVertex3f(r, v*10, 0.0f);
    }
    glEnd();
}

//------------------------------------------------------------------------------
// note that this is not part of the galaxy simulation so no real need to port to GLES
void NBodyWnd::DrawDensityWaves(int num, double rad)
{    double dr = rad / num;
    
    for (int i=0; i<=num; ++i)
    {
        double r = (i+1) * dr;
        glColor3f(1,1,1);
        DrawEllipse(r,
                     r * m_galaxy.GetExcentricity(r),
                     Constant::RAD_TO_DEG * m_galaxy.GetAngularOffset(r));
    }
}
#endif

//------------------------------------------------------------------------------
void NBodyWnd::DrawStars()
{
  glBindTexture(GL_TEXTURE_2D, m_texStar);

  glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);

  glEnable(GL_POINT_SPRITE_OES);
  glEnable(GL_TEXTURE_2D);       // point sprite texture support
  glEnable(GL_BLEND);            // soft blending of point sprites
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  int num = m_galaxy.GetNumStars();
  Star *pStars = m_galaxy.GetStars();

  glPointSize(3); //pStars[i].m_mag*10);
  glBegin(GL_POINTS);

  for (int i=1; i<num; ++i)
  {
    const Vec2D &pos = pStars[i].m_pos;
    const Color &col = ColorFromTemperature(pStars[i].m_temp);
    glColor3f(col.r * pStars[i].m_mag,
              col.g * pStars[i].m_mag,
              col.b * pStars[i].m_mag);
    glVertex3f(pos.x, pos.y, 0.0f);

  }
  glEnd();

  glDisable(GL_POINT_SPRITE_OES);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}

//------------------------------------------------------------------------------
void NBodyWnd::DrawDust()
{    
  glBindTexture(GL_TEXTURE_2D, m_texStar);

  glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);

  glEnable(GL_POINT_SPRITE_OES);
  glEnable(GL_TEXTURE_2D);       // point sprite texture support
  glEnable(GL_BLEND);            // soft blending of point sprites
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  Star *pDust = m_galaxy.GetDust();
  int num = m_galaxy.GetNumDust();

  glPointSize(max_size+10.0f); //*(double)rand()/(double)RAND_MAX);
  glBegin(GL_POINTS);

  for (int i=0; i<num; ++i)
  {
    const Vec2D &pos = pDust[i].m_pos;
    const Color &col = ColorFromTemperature(pDust[i].m_temp);
    glColor3f(col.r * pDust[i].m_mag,
              col.g * pDust[i].m_mag,
              col.b * pDust[i].m_mag);
    glVertex3f(pos.x, pos.y, 0.0f);

  }
  glEnd();

  glDisable(GL_POINT_SPRITE_OES);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);    
}

//------------------------------------------------------------------------------
void NBodyWnd::DrawH2()
{
  glBindTexture(GL_TEXTURE_2D, m_texStar);

  glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);

  glEnable(GL_POINT_SPRITE_OES);
  glEnable(GL_TEXTURE_2D);       // point sprite texture support
  glEnable(GL_BLEND);            // soft blending of point sprites
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  Star *pH2 = m_galaxy.GetH2();
  int num = m_galaxy.GetNumH2();

  glPointSize(max_size); //*(double)rand()/(double)RAND_MAX);

  for (int i=0; i<num; ++i)
  {
    int k1 = 2*i;
    int k2 = 2*i+1;

    const Vec2D &p1 = pH2[k1].m_pos;
    const Vec2D &p2 = pH2[k2].m_pos;

    double dst = sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
    double size = ((1000-dst) / 10) - 50;
    if (size<1)
      continue;

    glPointSize(2*size);
    glBegin(GL_POINTS);
    const Color &col = ColorFromTemperature(pH2[k1].m_temp);
    glColor3f(col.r * pH2[i].m_mag * 2,
              col.g * pH2[i].m_mag,
              col.b * pH2[i].m_mag);
    glVertex3f(p1.x, p1.y, 0.0f);
    glEnd();

    glPointSize(size/6);
    glBegin(GL_POINTS);
      glColor3f(1,1,1);
      glVertex3f(p1.x, p1.y, 0.0f);
    glEnd();
  }

  glDisable(GL_POINT_SPRITE_OES);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

//------------------------------------------------------------------------------
void NBodyWnd::DrawStat()
{
  double x0 = 10, y0 = 20, dy = 20;
  int line = 0;

#if TARGET_OS_IPHONE==0
  glColor3f(1, 1, 1);
  TextOut(x0, y0 + dy * line++, "FPS:      %d", GetFPS());
  TextOut(x0, y0 + dy * line++, "Time:     %2.2e y", m_galaxy.GetTime());
  TextOut(x0, y0 + dy * line++, "RadCore:     %d pc", (int)m_galaxy.GetCoreRad());
  TextOut(x0, y0 + dy * line++, "RadGalaxy:   %d pc", (int)m_galaxy.GetRad());
  TextOut(x0, y0 + dy * line++, "RadFarField: %d pc", (int)m_galaxy.GetFarFieldRad());
  TextOut(x0, y0 + dy * line++, "ExInner:     %2.2f", m_galaxy.GetExInner());
  TextOut(x0, y0 + dy * line++, "ExOuter:     %2.2f", m_galaxy.GetExOuter());
  TextOut(x0, y0 + dy * line++, "Sigma:       %2.2f", m_galaxy.GetSigma());
  TextOut(x0, y0 + dy * line++, "AngOff:      %1.4f deg/pc", m_galaxy.GetAngularOffset());
#endif
}

#if TARGET_OS_IPHONE==0
// note that this is not part of the galaxy simulation so no real need to port to GLES
void NBodyWnd::DrawGalaxyRadii()
{
  double r;

  glColor3f(1, 1, 0);
  r = m_galaxy.GetCoreRad();
  if (r>0)
    DrawEllipse(r, r, 0);

  glColor3f(0, 1, 0);
  r = m_galaxy.GetRad();
  DrawEllipse(r, r, 0);

  glColor3f(1, 0, 0);
  r = m_galaxy.GetFarFieldRad();
  DrawEllipse(r, r, 0);
}
#endif

//------------------------------------------------------------------------------
void NBodyWnd::DrawHelp()
{
  double x0 = 10, y0 = 20, dy = 20;
  int line = 0;
  Vec3D p;

#if TARGET_OS_IPHONE==0
  glColor3f(1, 1, 1);
  TextOut(x0, y0 + dy * line++, "Keyboard commands");
  TextOut(x0, y0 + dy * line++, "Galaxy geometry");
  TextOut(x0, y0 + dy * line++, "  q     - increase inner excentricity");
  TextOut(x0, y0 + dy * line++, "  a     - decrease inner excentricity");
  TextOut(x0, y0 + dy * line++, "  w     - increase outer excentricity");
  TextOut(x0, y0 + dy * line++, "  s     - decrease outer excentricity");
  TextOut(x0, y0 + dy * line++, "  e     - increase angular shift of orbits");
  TextOut(x0, y0 + dy * line++, "  d     - decrease angular shift of orbits"); 
  TextOut(x0, y0 + dy * line++, "  r     - increase core size");
  TextOut(x0, y0 + dy * line++, "  f     - decrease core size");
  TextOut(x0, y0 + dy * line++, "  t     - increase galaxy size");
  TextOut(x0, y0 + dy * line++, "  g     - decrease galaxy size");  
  TextOut(x0, y0 + dy * line++, "  y     - increase the speed of the stars at the edge of the galaxy");
  TextOut(x0, y0 + dy * line++, "  h     - decrease the speed of the stars at the edge of the galaxy");
  TextOut(x0, y0 + dy * line++, "  p     - velocity graph");
  TextOut(x0, y0 + dy * line++, "Display features");
  TextOut(x0, y0 + dy * line++, "  F1    - Help screen");
  TextOut(x0, y0 + dy * line++, "  F2    - Galaxy data");
  TextOut(x0, y0 + dy * line++, "  F4    - turns off dust");
  TextOut(x0, y0 + dy * line++, "  F5    - turns off H2 regions");
  TextOut(x0, y0 + dy * line++, "  F6    - Density waves (Star orbits)");
  TextOut(x0, y0 + dy * line++, "  F7    - Axis");
  TextOut(x0, y0 + dy * line++, "  F8    - Radii");
  TextOut(x0, y0 + dy * line++, "  +     - Zoom in");
  TextOut(x0, y0 + dy * line++, "  -     - Zoom out");
  TextOut(x0, y0 + dy * line++, "Misc");
  TextOut(x0, y0 + dy * line++, "  pause - halt simulation");
  TextOut(x0, y0 + dy * line++, "  F12   - Write frames to TGA");
#endif
}

//------------------------------------------------------------------------------
NBodyWnd::Color NBodyWnd::ColorFromTemperature(double temp) const
{
  int idx = (temp - m_t0) / (m_t1-m_t0) * m_colNum;
  idx = std::min(m_colNum-1, idx);
  idx = std::max(0, idx);
  return m_col[idx];
}


//------------------------------------------------------------------------------
void NBodyWnd::OnProcessEvents(SDL_Event &e)
{
    
    // Reverses the spiral arm direction after a couple of taps (or 'd' keystrokes on OS X) 
    if (e.type == SDL_FINGERDOWN) {
        if (m_touchControlSetting==7) {
            m_touchControlSetting=0;
            m_galaxy.SetAngularOffset(m_galaxy.GetAngularOffset()+0.0007); // back to normal
        } else {
            m_touchControlSetting++;
            m_galaxy.SetAngularOffset(m_galaxy.GetAngularOffset()-0.0001);
        }
    }
    
    if (e.type == SDL_KEYDOWN)
        switch (e.key.keysym.sym)
        {
          case SDLK_q:
                m_galaxy.SetExInner(m_galaxy.GetExInner() + 0.05);
                break;

          case SDLK_a:
                m_galaxy.SetExInner(std::max(m_galaxy.GetExInner() - 0.05, 0.0));
                break;

          case SDLK_w:
                m_galaxy.SetExOuter(m_galaxy.GetExOuter() + 0.05);
                break;

          case SDLK_s:
                m_galaxy.SetExOuter(std::max(m_galaxy.GetExOuter() - 0.05, 0.0));
                break;

          case SDLK_e:
                m_galaxy.SetAngularOffset(m_galaxy.GetAngularOffset()+0.0001);
                break;

          case SDLK_d:
                m_galaxy.SetAngularOffset(m_galaxy.GetAngularOffset()-0.0001);
                break;

          case SDLK_r:
                if (m_galaxy.GetRad()>m_galaxy.GetCoreRad()+500)
                {
                  m_galaxy.SetCoreRad(m_galaxy.GetCoreRad()+500);
                }
                std::cout << "Bulge radius " << m_galaxy.GetCoreRad() << "\n";
                break;

          case SDLK_f:
                m_galaxy.SetCoreRad(std::max(m_galaxy.GetCoreRad()-500, 0.0));
                std::cout << "Bulge radius " << m_galaxy.GetCoreRad() << "\n";
                break;

          case SDLK_t:
                m_galaxy.SetRad(m_galaxy.GetRad()+1000);
                break;

          case SDLK_g:
                m_galaxy.SetRad(std::max(m_galaxy.GetRad()-1000, 0.0));
                break;

          case SDLK_z:
          case SDLK_y:
                m_galaxy.SetSigma(m_galaxy.GetSigma()+0.05);
                break;

          case SDLK_h:
                m_galaxy.SetSigma(std::max(m_galaxy.GetSigma()-0.05, 0.05));
                break;
                
          case  SDLK_F1:
                std::cout << "Display:  help screen" << ((m_flags & dspHELP) ? "off" : "on") << "\n";
                m_flags ^= dspHELP;
                m_flags &= ~dspSTAT;
                break;

          case  SDLK_F2:
                std::cout << "Display:  statistic" << ((m_flags & dspSTAT) ? "off" : "on") << "\n";
                m_flags ^= dspSTAT;
                m_flags &= ~dspHELP;
                break;

          case  SDLK_F4:
                std::cout << "Display:  Toggling dust " << ((m_flags & dspDUST) ? "off" : "on") << "\n";
                m_flags ^= dspDUST;
                break;

          case  SDLK_F5:
                std::cout << "Display:  Toggling h2 regions " << ((m_flags & dspH2) ? "off" : "on") << "\n";
                m_flags ^= dspH2;
                break;
                
#if TARGET_OS_IPHONE==0
                
          case SDLK_F6:
                std::cout << "Display:  Density waves axis " << ((m_flags & dspDENSITY_WAVES) ? "off" : "on") << "\n";
                m_flags ^= dspDENSITY_WAVES;
                break;
                
          case SDLK_F8:
                std::cout << "Display:  Radii" << ((m_flags & dspRADII) ? "off" : "on") << "\n";
                m_flags ^= dspRADII;
                break;

          case SDLK_F7:
                std::cout << "Display:  Axis" << ((m_flags & dspAXIS) ? "off" : "on") << "\n";
                m_flags ^= dspAXIS;
                break;
            
          case  SDLK_p:
                std::cout << "Display:  Toggling Velocity graph " << ((m_flags & dspVELOCITY) ? "off" : "on") << "\n";
                m_flags ^= dspVELOCITY;
                break;
#endif

          case  SDLK_PAUSE:
                std::cout << "Simulation:  pause " << ((m_flags & dspPAUSE) ? "off" : "on") << "\n";
                m_flags ^= dspPAUSE;
                break;

          case SDLK_F12:
               m_bDumpImage ^= true;
               m_idxSnapshot = 0;
               std::cout << "Image dumping is " << ((m_bDumpImage) ? "enabled" : "disabled") << std::endl;
               break;

          case SDLK_PLUS:
          case SDLK_KP_PLUS:
               ScaleAxis(0.9);
               SetCameraOrientation(Vec3D(0,1,0));
               break;


          case SDLK_MINUS:
          case SDLK_KP_MINUS:
               ScaleAxis(1.1);
               SetCameraOrientation(Vec3D(0,1,0));
               break;
        }
}
