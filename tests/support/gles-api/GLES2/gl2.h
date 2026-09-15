#pragma once
// Test-only GLES2 ABI declarations for the isolated EGL/Mesa UI probe. The
// shipped desktop ALWAYS requires the platform's genuine GLES development SDK.
// No functions are emulated: these declarations link to GLVND's real dispatcher.
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned int GLenum,GLuint,GLbitfield;
typedef int GLint,GLsizei;
typedef unsigned char GLboolean;
typedef float GLfloat;
typedef ptrdiff_t GLsizeiptr;
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW 0x88E0
#define GL_FLOAT 0x1406
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FALSE 0
#define GL_TRIANGLES 0x0004
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_LINEAR 0x2601
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RGBA 0x1908
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_SCISSOR_TEST 0x0C11
#define GL_DEPTH_TEST 0x0B71
#define GL_CULL_FACE 0x0B44
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_NO_ERROR 0
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
GLuint glCreateShader(GLenum);
void glShaderSource(GLuint,GLsizei,const char* const*,const GLint*);
void glCompileShader(GLuint);
void glGetShaderiv(GLuint,GLenum,GLint*);
void glGetShaderInfoLog(GLuint,GLsizei,GLsizei*,char*);
void glDeleteShader(GLuint);
GLuint glCreateProgram(void);
void glAttachShader(GLuint,GLuint);
void glBindAttribLocation(GLuint,GLuint,const char*);
void glLinkProgram(GLuint);
void glGetProgramiv(GLuint,GLenum,GLint*);
void glDeleteProgram(GLuint);
GLint glGetUniformLocation(GLuint,const char*);
void glGenBuffers(GLsizei,GLuint*);
void glDeleteBuffers(GLsizei,const GLuint*);
void glDeleteTextures(GLsizei,const GLuint*);
void glUniform4fv(GLint,GLsizei,const GLfloat*);
void glUniform2f(GLint,GLfloat,GLfloat);
void glUniform1i(GLint,GLint);
void glActiveTexture(GLenum);
void glBindTexture(GLenum,GLuint);
void glBufferData(GLenum,GLsizeiptr,const void*,GLenum);
void glDrawArrays(GLenum,GLint,GLsizei);
void glGetIntegerv(GLenum,GLint*);
void glGenTextures(GLsizei,GLuint*);
void glTexParameteri(GLenum,GLenum,GLint);
void glTexImage2D(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
void glViewport(GLint,GLint,GLsizei,GLsizei);
void glDisable(GLenum);
void glEnable(GLenum);
void glClearColor(GLfloat,GLfloat,GLfloat,GLfloat);
void glClear(GLbitfield);
void glBlendFunc(GLenum,GLenum);
void glUseProgram(GLuint);
void glBindBuffer(GLenum,GLuint);
void glEnableVertexAttribArray(GLuint);
void glDisableVertexAttribArray(GLuint);
void glVertexAttribPointer(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*);
GLenum glGetError(void);
void glReadPixels(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,void*);
void glFinish(void);
const unsigned char* glGetString(GLenum);
#ifdef __cplusplus
}
#endif
