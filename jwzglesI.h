/* xscreensaver, Copyright (c) 2012 Jamie Zawinski <jwz@jwz.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 */

/* A compatibility shim to allow OpenGL 1.3 source code to work in an
   OpenGLES environment, where almost every OpenGL 1.3 function has
   been "deprecated".  See jwzgles.c for details.
 */

#ifndef __JWZGLES_I_H__
#define __JWZGLES_I_H__

#ifdef GL_VERSION_ES_CM_1_0  /* compiling against OpenGLES 1.x */

/* These OpenGL 1.3 constants are not present in OpenGLES 1.
   Fortunately, it looks like they didn't re-use any of the numbers,
   so we can just keep using the OpenGL 1.3 values.  I'm actually
   kind of shocked that the GLES folks passed up that opportunity
   for further clusterfuckery.
 */
# define GLdouble double

# define GL_ACCUM_BUFFER_BIT			0x00000200
# define GL_ALL_ATTRIB_BITS			0x000FFFFF
# define GL_AUTO_NORMAL				0x0D80
# define GL_BLEND_SRC_ALPHA			0x80CB
# define GL_C3F_V3F				0x2A24
# define GL_C4F_N3F_V3F				0x2A26
# define GL_C4UB_V2F				0x2A22
# define GL_C4UB_V3F				0x2A23
# define GL_CLAMP				0x2900
# define GL_COLOR_BUFFER_BIT			0x00004000
# define GL_COLOR_MATERIAL_FACE			0x0B55
# define GL_COLOR_MATERIAL_PARAMETER		0x0B56
# define GL_COMPILE				0x1300
# define GL_CURRENT_BIT				0x00000001
# define GL_DEPTH_BUFFER_BIT			0x00000100
# define GL_DOUBLEBUFFER			0x0C32
# define GL_ENABLE_BIT				0x00002000
# define GL_EVAL_BIT				0x00010000
# define GL_EYE_LINEAR				0x2400
# define GL_EYE_PLANE				0x2502
# define GL_FEEDBACK				0x1C01
# define GL_FILL				0x1B02
# define GL_FOG_BIT				0x00000080
# define GL_HINT_BIT				0x00008000
# define GL_INTENSITY				0x8049
# define GL_LIGHTING_BIT			0x00000040
# define GL_LIGHT_MODEL_COLOR_CONTROL		0x81F8
# define GL_LIGHT_MODEL_LOCAL_VIEWER		0x0B51
# define GL_LINE				0x1B01
# define GL_LINE_BIT				0x00000004
# define GL_LIST_BIT				0x00020000
# define GL_N3F_V3F				0x2A25
# define GL_OBJECT_LINEAR			0x2401
# define GL_OBJECT_PLANE			0x2501
# define GL_PIXEL_MODE_BIT			0x00000020
# define GL_POINT_BIT				0x00000002
# define GL_POLYGON				0x0009
# define GL_POLYGON_BIT				0x00000008
# define GL_POLYGON_MODE			0x0B40
# define GL_POLYGON_SMOOTH			0x0B41
# define GL_POLYGON_STIPPLE			0x0B42
# define GL_POLYGON_STIPPLE_BIT			0x00000010
# define GL_Q					0x2003
# define GL_QUADS				0x0007
# define GL_QUAD_STRIP				0x0008
# define GL_R					0x2002
# define GL_RENDER				0x1C00
# define GL_RGBA_MODE				0x0C31
# define GL_S					0x2000
# define GL_SCISSOR_BIT				0x00080000
# define GL_SELECT				0x1C02
# define GL_SEPARATE_SPECULAR_COLOR		0x81FA
# define GL_SINGLE_COLOR			0x81F9
# define GL_SPHERE_MAP				0x2402
# define GL_STENCIL_BUFFER_BIT			0x00000400
# define GL_T					0x2001
# define GL_T2F_C3F_V3F				0x2A2A
# define GL_T2F_C4F_N3F_V3F			0x2A2C
# define GL_T2F_C4UB_V3F			0x2A29
# define GL_T2F_N3F_V3F				0x2A2B
# define GL_T2F_V3F				0x2A27
# define GL_T4F_C4F_N3F_V4F			0x2A2D
# define GL_T4F_V4F				0x2A28
# define GL_TEXTURE_1D				0x0DE0
# define GL_TEXTURE_ALPHA_SIZE			0x805F
# define GL_TEXTURE_BIT				0x00040000
# define GL_TEXTURE_BLUE_SIZE			0x805E
# define GL_TEXTURE_BORDER			0x1005
# define GL_TEXTURE_BORDER_COLOR		0x1004
# define GL_TEXTURE_COMPONENTS			0x1003
# define GL_TEXTURE_GEN_MODE			0x2500
# define GL_TEXTURE_GEN_Q			0x0C63
# define GL_TEXTURE_GEN_R			0x0C62
# define GL_TEXTURE_GEN_S			0x0C60
# define GL_TEXTURE_GEN_T			0x0C61
# define GL_TEXTURE_GREEN_SIZE			0x805D
# define GL_TEXTURE_HEIGHT			0x1001
# define GL_TEXTURE_INTENSITY_SIZE		0x8061
# define GL_TEXTURE_LUMINANCE_SIZE		0x8060
# define GL_TEXTURE_RED_SIZE			0x805C
# define GL_TEXTURE_WIDTH			0x1000
# define GL_TRANSFORM_BIT			0x00001000
# define GL_UNPACK_ROW_LENGTH			0x0CF2
# define GL_UNSIGNED_INT_8_8_8_8_REV		0x8367
# define GL_V2F					0x2A20
# define GL_V3F					0x2A21
# define GL_VIEWPORT_BIT			0x00000800

#endif

#ifdef __cplusplus
extern "C" {
#endif
    
/* Prototypes for the things re-implemented in jwzgles.c 
 */

 int  jwzgles_glGenLists (int n);
 void jwzgles_glNewList (int id, int mode);
 void jwzgles_glEndList (void);
 void jwzgles_glDeleteLists (int list, int range);
 void jwzgles_glBegin (int mode);
 void jwzgles_glNormal3fv (const GLfloat *);
 void jwzgles_glNormal3f (GLfloat x, GLfloat y, GLfloat z);
 void jwzgles_glTexCoord1f (GLfloat s);
 void jwzgles_glTexCoord2fv (const GLfloat *);
 void jwzgles_glTexCoord2f (GLfloat s, GLfloat t);
 void jwzgles_glTexCoord3fv (const GLfloat *);
 void jwzgles_glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
 void jwzgles_glTexCoord4fv (const GLfloat *);
 void jwzgles_glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
 void jwzgles_glVertex2f (GLfloat x, GLfloat y);
 void jwzgles_glVertex2fv (const GLfloat *);
 void jwzgles_glVertex2i (GLint x, GLint y);
 void jwzgles_glVertex3f (GLfloat x, GLfloat y, GLfloat z);
 void jwzgles_glVertex3dv (const GLdouble *);
 void jwzgles_glVertex3fv (const GLfloat *);
 void jwzgles_glVertex3i (GLint x, GLint y, GLint z);
 void jwzgles_glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
 void jwzgles_glVertex4fv (const GLfloat *);
 void jwzgles_glVertex4i (GLint x, GLint y, GLint z, GLint w);
 void jwzgles_glEnd (void);
 void jwzgles_glCallList (int id);
 void jwzgles_glClearIndex(GLfloat c);
 void jwzgles_glBitmap (GLsizei, GLsizei, GLfloat, GLfloat, GLfloat,
                              GLfloat, const GLubyte *);
 void jwzgles_glPushAttrib(int);
 void jwzgles_glPopAttrib(void);


/* These functions are present in both OpenGL 1.3 and in OpenGLES 1,
   but are allowed within glNewList/glEndList, so we must wrap them
   to allow them to be recorded.
 */
 void jwzgles_glActiveTexture (GLuint);
 void jwzgles_glBindTexture (GLuint, GLuint);
 void jwzgles_glBlendFunc (GLuint, GLuint);
 void jwzgles_glClear (GLuint);
 void jwzgles_glClearColor (GLclampf, GLclampf, GLclampf, GLclampf);
 void jwzgles_glClearStencil (GLuint);
 void jwzgles_glColorMask (GLuint, GLuint, GLuint, GLuint);
 void jwzgles_glCullFace (GLuint);
 void jwzgles_glDepthFunc (GLuint);
 void jwzgles_glDepthMask (GLuint);
 void jwzgles_glDisable (GLuint);
 void jwzgles_glDrawArrays (GLuint, GLuint, GLuint);
 GLboolean jwzgles_glIsEnabled (GLuint);
 void jwzgles_glEnable (GLuint);
 void jwzgles_glFrontFace (GLuint);
 void jwzgles_glHint (GLuint, GLuint);
 void jwzgles_glLineWidth (GLfloat);
 void jwzgles_glLoadIdentity (void);
 void jwzgles_glLogicOp (GLuint);
 void jwzgles_glMatrixMode (GLuint);
 void jwzgles_glMultMatrixf (const GLfloat *);
 void jwzgles_glPointSize (GLfloat);
 void jwzgles_glPolygonOffset (GLfloat, GLfloat);
 void jwzgles_glPopMatrix (void);
 void jwzgles_glPushMatrix (void);
 void jwzgles_glScissor (GLuint, GLuint, GLuint, GLuint);
 void jwzgles_glShadeModel (GLuint);
 void jwzgles_glStencilFunc (GLuint, GLuint, GLuint);
 void jwzgles_glStencilMask (GLuint);
 void jwzgles_glStencilOp (GLuint, GLuint, GLuint);
 void jwzgles_glViewport (GLuint, GLuint, GLuint, GLuint);
 void jwzgles_glTranslatef (GLfloat, GLfloat, GLfloat);
 void jwzgles_glRotatef (GLfloat, GLfloat, GLfloat, GLfloat);
 void jwzgles_glRotated (GLdouble, GLdouble x, GLdouble y, GLdouble z);
 void jwzgles_glScalef (GLfloat, GLfloat, GLfloat);
 void jwzgles_glColor3f (GLfloat, GLfloat, GLfloat);
 void jwzgles_glColor4f (GLfloat, GLfloat, GLfloat, GLfloat);
 void jwzgles_glColor3fv (const GLfloat *);
 void jwzgles_glColor4fv (const GLfloat *);
 void jwzgles_glColor4i (GLuint, GLuint, GLuint, GLuint);
 void jwzgles_glColor3i (GLuint, GLuint, GLuint);
 void jwzgles_glColor3iv (const GLint *);
 void jwzgles_glColor4iv (const GLint *);
 void jwzgles_glColor4ub (GLubyte, GLubyte, GLubyte, GLubyte);
 void jwzgles_glColor3ub (GLubyte, GLubyte, GLubyte);
 void jwzgles_glMaterialf (GLuint, GLuint, GLfloat);
 void jwzgles_glMateriali (GLuint, GLuint, GLuint);
 void jwzgles_glMaterialfv (GLuint, GLuint, const GLfloat *);
 void jwzgles_glMaterialiv (GLuint, GLuint, const GLint *);
 void jwzgles_glFinish (void);
 void jwzgles_glFlush (void);
 void jwzgles_glPixelStorei (GLuint, GLuint);
 void jwzgles_glEnableClientState (GLuint);
 void jwzgles_glDisableClientState (GLuint);

 void jwzgles_glInitNames (void);
 void jwzgles_glPushName (GLuint);
 GLuint jwzgles_glPopName (void);
 GLuint jwzgles_glRenderMode (GLuint);
 void jwzgles_glSelectBuffer (GLsizei, GLuint *);
 void jwzgles_glLightf (GLenum, GLenum, GLfloat);
 void jwzgles_glLighti (GLenum, GLenum, GLint);
 void jwzgles_glLightfv (GLenum, GLenum, const GLfloat *);
 void jwzgles_glLightiv (GLenum, GLenum, const GLint *);
 void jwzgles_glLightModelf (GLenum, GLfloat);
 void jwzgles_glLightModeli (GLenum, GLint);
 void jwzgles_glLightModelfv (GLenum, const GLfloat *);
 void jwzgles_glLightModeliv (GLenum, const GLint *);
 void jwzgles_glGenTextures (GLuint, GLuint *);
 void jwzgles_glFrustum (GLfloat, GLfloat, GLfloat, GLfloat,
                               GLfloat, GLfloat);
 void jwzgles_glOrtho (GLfloat, GLfloat, GLfloat, GLfloat, 
                             GLfloat, GLfloat);
 void jwzgles_glTexImage1D (GLenum target, GLint level,
                                  GLint internalFormat,
                                  GLsizei width, GLint border,
                                  GLenum format, GLenum type,
                                  const GLvoid *pixels);
 void jwzgles_glTexImage2D (GLenum target,
                                  GLint  	level,
                                  GLint  	internalFormat,
                                  GLsizei  	width,
                                  GLsizei  	height,
                                  GLint  	border,
                                  GLenum  	format,
                                  GLenum  	type,
                                  const GLvoid *data);
 void jwzgles_glTexSubImage2D (GLenum target, GLint level,
                                     GLint xoffset, GLint yoffset,
                                     GLsizei width, GLsizei height,
                                     GLenum format, GLenum type,
                                     const GLvoid *pixels);
 void jwzgles_glCopyTexImage2D (GLenum target, GLint level, 
                                      GLenum internalformat,
                                      GLint x, GLint y, 
                                      GLsizei width, GLsizei height, 
                                      GLint border);
 void jwzgles_glInterleavedArrays (GLenum, GLsizei, const GLvoid *);
 void jwzgles_glTexEnvf (GLuint, GLuint, GLfloat);
 void jwzgles_glTexEnvi (GLuint, GLuint, GLuint);
 void jwzgles_glTexParameterf (GLuint, GLuint, GLfloat);
 void jwzgles_glTexParameteri (GLuint, GLuint, GLuint);
 void jwzgles_glTexGeni (GLenum, GLenum, GLint);
 void jwzgles_glTexGenfv (GLenum, GLenum, const GLfloat *);
 void jwzgles_glRectf (GLfloat, GLfloat, GLfloat, GLfloat);
 void jwzgles_glRecti (GLint, GLint, GLint, GLint);
 void jwzgles_glLightModelfv (GLenum, const GLfloat *);
 void jwzgles_glClearDepth (GLfloat);
 GLboolean jwzgles_glIsList (GLuint);
 void jwzgles_glColorMaterial (GLenum, GLenum);
 void jwzgles_glPolygonMode (GLenum, GLenum);
 void jwzgles_glFogf (GLenum, GLfloat);
 void jwzgles_glFogi (GLenum, GLint);
 void jwzgles_glFogfv (GLenum, const GLfloat *);
 void jwzgles_glFogiv (GLenum, const GLint *);
 void jwzgles_glAlphaFunc (GLenum, GLfloat);
 void jwzgles_glClipPlane (GLenum, const GLdouble *);
 void jwzgles_glDrawBuffer (GLenum);
 void jwzgles_glDeleteTextures (GLuint, const GLuint *);

 void jwzgles_gluPerspective (GLdouble fovy, GLdouble aspect, 
                                    GLdouble near, GLdouble far);
 void jwzgles_gluLookAt (GLfloat eyex, GLfloat eyey, GLfloat eyez,
                               GLfloat centerx, GLfloat centery, 
                               GLfloat centerz,
                               GLfloat upx, GLfloat upy, GLfloat upz);
 GLint jwzgles_gluProject (GLdouble objx, GLdouble objy, GLdouble objz, 
                                 const GLdouble modelMatrix[16], 
                                 const GLdouble projMatrix[16],
                                 const GLint viewport[4],
                                 GLdouble *winx, GLdouble *winy, 
                                 GLdouble *winz);
 int jwzgles_gluBuild2DMipmaps (GLenum target,
                                      GLint internalFormat,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum format,
                                      GLenum type,
                                      const GLvoid *data);
 void jwzgles_glGetFloatv (GLenum pname, GLfloat *params);
 void jwzgles_glGetPointerv (GLenum pname, GLvoid *params);
 void jwzgles_glGetDoublev (GLenum pname, GLdouble *params);
 void jwzgles_glGetIntegerv (GLenum pname, GLint *params);
 void jwzgles_glGetBooleanv (GLenum pname, GLboolean *params);
 void jwzgles_glVertexPointer (GLuint, GLuint, GLuint, const void *);
 void jwzgles_glNormalPointer (GLenum, GLuint, const void *);
 void jwzgles_glColorPointer (GLuint, GLuint, GLuint, const void *);
 void jwzgles_glTexCoordPointer (GLuint, GLuint, GLuint, const void *);
 void jwzgles_glBindBuffer (GLuint, GLuint);
 void jwzgles_glBufferData (GLenum, GLsizeiptr, const void *, GLenum);
 const char *jwzgles_gluErrorString (GLenum error);

#ifdef __cplusplus
}
#endif

#endif /* __JWZGLES_I_H__ */
