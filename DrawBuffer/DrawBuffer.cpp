// DrawBuffer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Renderer.h"
#include "DrawBuffer.h"
#include "LightManager.h"
#include "glError.h"

#include "RedProgramES3.h"
#include "BlueProgramES1.h"
#include "DrawBufferProgram.h"
#include "CheckProgram.h"
#include <iostream>
#include <algorithm>    // std::min
#include <array>
#include <io.h>
#include <fcntl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

using namespace Apollo;
const UINT windowWidth = 1024;
const UINT windowHeight = 768;

GLuint vertexBuffer;
GLuint indexBuffer;
GLuint redProgram;
GLuint blueProgram;
GLuint bufferProgram;
GLuint checkProgram;
uint numIndices;
GLuint frameBuffer;
GLenum *bufs = nullptr;
GLint maxUsable = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Update();
void DrawRectTest();
void EmitDrawRect();

void DrawBufferTest();
void EmitDrawBuffer();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DRAWBUFFER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    AllocConsole();
    FILE* pCout = nullptr;
    freopen_s(&pCout, "conout$", "w", stdout); //returns 0

    Renderer &renderer = Renderer::Instance();
    renderer.SetClearColor(Vector4f(0, 1, 0, 1));

    // Perform application initialization
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWBUFFER));

    DrawBufferTest();
    //DrawRectTest();
    memset(&msg, 0, sizeof(msg));    
    // Main message loop:
    while (msg.message != WM_QUIT)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else
      {        
      //  EmitDrawRect();
        EmitDrawBuffer();
      }
    }
        
    renderer.Terminate();
    delete bufs;

    fclose(pCout);
    FreeConsole();

    return (int) msg.wParam;
}

GLuint CreateProgram(const char *vsShader, const char *fsShader)
{
  GLuint program;

  const char* shaderData = vsShader;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  CheckForErrors();
  glShaderSource(vertexShader, 1, &shaderData, NULL);
  CheckForErrors();
  glCompileShader(vertexShader);
  CheckForErrors();

  shaderData = fsShader;
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  CheckForErrors();
  glShaderSource(fragmentShader, 1, &shaderData, NULL);
  CheckForErrors();
  glCompileShader(fragmentShader);
  CheckForErrors();

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
    //The maxLength includes the NULL character
    GLchar infoLog[256];
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);
    //We don't need the shader anymore.
    glDeleteShader(vertexShader);
    //Use the infoLog as you see fit.
    assert(0 && "ContextOGL:: Create vertex shader error");
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
    //The maxLength includes the NULL character
    char infoLog[256];
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);

    //We don't need the shader anymore.
    glDeleteShader(fragmentShader);
    //Use the infoLog as you see fit.
    assert(0 && "ContextOGL:: Create fragment shader error");
  }

  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  const GLuint vertexLoc = 0;
  const GLuint texLoc = 1;
  // Init attributes BEFORE linking
  //glBindAttribLocation(program, vertexLoc, "g_vPositionOS");
  //glBindAttribLocation(program, texLoc, "g_vTextCoordOS");
  glLinkProgram(program);

  // Check for link success
  GLint maxLength = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &maxLength);
  if (!maxLength)
  {
    GLchar infoLog[256];

    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);

    assert(0 && "compile shader failed");
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

void EmitDrawRect()
{
  //// clean color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(1, 1, 0, 1);
  glClearDepth(1.0f);
  glClearStencil(0);
  CheckForErrors();
  //// set program
  glUseProgram(redProgram);
  CheckForErrors();

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  //// set buffer & vertex decl
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (GLvoid *)0);  // pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid *)12);  // texCoord
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  CheckForErrors();

  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
  CheckForErrors();
  //// draw element

  // End frame
  Renderer &renderer = Renderer::Instance();
  renderer.GetGraphics()->EndFrame();
}

std::array<GLuint, 8> attachments;

void DrawUnitQuadToFrameBuffers()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  //// set buffer & vertex decl
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (GLvoid *)0);  // pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid *)12);  // texCoord
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  CheckForErrors();

  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glDrawBuffers(8, bufs);

  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
  CheckForErrors();
}

bool CheckAttachmentsForColorFn(int index, const Vector4f &color)
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glUseProgram(checkProgram);
   
  GLuint tex = attachments[index];

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  DrawUnitQuadToFrameBuffers();

  GLubyte *data = (GLubyte *)malloc(4 * windowWidth * windowWidth);
  glReadPixels(0, 0, windowWidth, windowWidth, GL_RGBA, GL_UNSIGNED_BYTE, data);

  if ((data[0] == color.x * 255) && (data[1] == color.y * 255) &&
    (data[2] == color.z * 255) && (data[3] == color.w * 255)) {

    free(data);
    return true;
  }
  else {
    free(data);
    return false;
  }
}

void CheckFrameBufferColor(int index)
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0); // Back to the origin frame buffer

  glUseProgram(checkProgram);

  GLuint tex = attachments[index];

  glActiveTexture(GL_TEXTURE0);  
  glBindTexture(GL_TEXTURE_2D, tex);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  //// set buffer & vertex decl
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (GLvoid *)0);  // pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid *)12);  // texCoord
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  CheckForErrors();

  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
  CheckForErrors();
}

void EmitDrawBuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  // clean color // Can't clean color before use program ?
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(1, 1, 0, 1);
  glClearDepth(1.0f);
  glClearStencil(0);
  CheckForErrors();

  //// draw element
  // Set buffer program and draw
  glUseProgram(bufferProgram);
  CheckForErrors();
  
  DrawUnitQuadToFrameBuffers();

  // set textures for proving via glReadpixels
  bool result;
  
  for (int i = 0; i < maxUsable; ++i) {
    result = CheckAttachmentsForColorFn(0, Vector4f(0, 1, 0, 1));

    printf("Draw buffer color check: %d  (%f , %f, %f ,%f), result %d \n",
      i, 0.0, 1.0, 0.0, 1.0, result);
  }

  // Set red program and draw
  glUseProgram(redProgram);
  CheckForErrors();

  DrawUnitQuadToFrameBuffers();

  result = CheckAttachmentsForColorFn(0, Vector4f(1, 0, 0, 1));

  printf("Draw red color check: %d  (%f , %f, %f ,%f), result %d \n",
    0, 0.0, 1.0, 0.0, 1.0, result);

  for (int i = 1; i < maxUsable; ++i) {
    result = CheckAttachmentsForColorFn(0, Vector4f(0, 1, 0, 1));

    printf("Draw red color check: %d  (%f , %f, %f ,%f), result %d \n",
      i, 0.0, 1.0, 0.0, 1.0, result);
  }

  // Set blue program and draw
  glUseProgram(blueProgram);
  CheckForErrors();

  DrawUnitQuadToFrameBuffers();

  result = CheckAttachmentsForColorFn(0, Vector4f(0, 0, 1, 1));
  printf("Draw blue color check: %d  (%f , %f, %f ,%f), result %d \n",
    0, 0.0, 0.0, 1.0, 1.0, result);

  for (int i = 1; i < maxUsable; ++i) {
    result = CheckAttachmentsForColorFn(0, Vector4f(0, 1, 0, 1));

    printf("Draw blue color check: %d  (%f , %f, %f ,%f), result %d \n",
      i, 0.0, 1.0, 0.0, 1.0, result);
  }

  CheckFrameBufferColor(3);

  //// End frame
  Renderer &renderer = Renderer::Instance();
  renderer.GetGraphics()->EndFrame();
}

void DrawBufferTest()
{
  // Create frame buffer 
  glGenFramebuffers(1, &frameBuffer);

  CheckForErrors();

  GLint maxDrawingBuffers = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawingBuffers);
  GLint maxColorAttachments = 0;
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments);
  GLint maxUniformVectors = 0;
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxUniformVectors);

  maxUsable = min(maxDrawingBuffers, min(maxColorAttachments, maxUniformVectors));
  GLuint tex;
  const uint width = 64;
  const uint height = 64;
  
  float vertexArray[] = {
    -1.0f, -1.0f, 0.3f, 0, 0,
    1.0f, -1.0f,  0.3f, 1, 0,
    -1.0f, 1.0f,  0.3f, 0, 1,
    1.0f,  1.0f,  0.3f, 1, 1
  };

  unsigned short indexArray[] = { 0,1,3, 0,3,2 };

  uint numVertices = 4;
  uint vertexSize = 20;
  numIndices = 6;
  float* vertexData = (float *)malloc(vertexSize * numVertices);
  memcpy_s(vertexData, vertexSize * numVertices, vertexArray, sizeof(vertexArray));

  unsigned short* indexData = (uint16 *)malloc(numIndices * sizeof(uint16));
  memcpy_s(indexData, numIndices * sizeof(uint16), indexArray, sizeof(indexArray));

  bool check;

  glGenBuffers(1, &vertexBuffer);
  check = CheckForErrors();
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  check = CheckForErrors();
  glBufferData(GL_ARRAY_BUFFER, numVertices * vertexSize, vertexData, GL_DYNAMIC_DRAW);
  check = CheckForErrors();

  glGenBuffers(1, &indexBuffer);
  check = CheckForErrors();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  check = CheckForErrors();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint16), indexData, GL_DYNAMIC_DRAW);
  check = CheckForErrors();

  // Create shader
  RedProgrameES3 redProgramRaw;
  BlueProgramES1 blueProgramRaw;
  DrawBufferProgram bufferProgramRaw;
  CheckProgram checkProgramRaw;

  // Create blueProgram
  blueProgram = CreateProgram(blueProgramRaw.GetVertexShader()->c_str(),
                              blueProgramRaw.GetFragmentShader()->c_str());

  // Create redProgram
  redProgram = CreateProgram(redProgramRaw.GetVertexShader()->c_str(),
                             redProgramRaw.GetFragmentShader()->c_str());

  // Create bufferProgram
  bufferProgram = CreateProgram(bufferProgramRaw.GetVertexShader()->c_str(),
                                bufferProgramRaw.GetFragmentShader()->c_str());

  // Create checkProgram
  checkProgram = CreateProgram(checkProgramRaw.GetVertexShader()->c_str(),
                               checkProgramRaw.GetFragmentShader()->c_str());

  glUseProgram(bufferProgram);

  bufs = new GLenum[maxUsable];
  for (int ii = 0; ii < maxUsable; ++ii) {  // Bind tes
    bufs[ii] = (GL_COLOR_ATTACHMENT0 + ii);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Bind buffer and draw buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    CheckForErrors();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ii, GL_TEXTURE_2D, tex, 0);
    CheckForErrors();

    GLfloat floatColor[4] = { 0, 1, 0, 1 }; // framebuffer default color...
    std::string str;

    str.append("u_colors[");
    char temp[20];
    //std::string buf = "";
    _itoa_s(ii, temp, 10);
    str.append(temp);
    str.append("]");
    uint location = glGetUniformLocation(bufferProgram, str.c_str());

    if (location < 0) {
      assert(0);
    }
    glUniform4fv(location, 1, floatColor);
    CheckForErrors();

    attachments[ii] = tex;
  }

  //glDrawBuffers(maxUsable, bufs);
  CheckForErrors();

  uint error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (error != GL_FRAMEBUFFER_COMPLETE) {
    assert(0 && error);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DrawRectTest()
{
  // Create frame buffer
  //GLuint frameBuffer = 0;
  //glGenFramebuffers(1, &frameBuffer);

  //CheckForErrors();

  //GLint maxDrawingBuffers = 0;
  //glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawingBuffers);
  //GLint maxColorAttachments = 0;
  //glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments);
  //GLint maxUniformVectors = 0;
  //glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxUniformVectors);

  //GLint maxUsable = min(maxDrawingBuffers, min(maxColorAttachments, maxUniformVectors));
  //GLenum *bufs = new GLenum[maxUsable];
  //for (int ii = 0; ii < maxUsable; ++ii) {
  //  bufs[ii] = (GL_COLOR_ATTACHMENT0 + ii);
  //}

  //// Bind buffer and draw buffer
  //glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  //CheckForErrors();
  //glDrawBuffers(maxUsable, bufs);
  //CheckForErrors();
  //delete bufs;
  
  
  // Setup unit rect with texCoord
  // Initialize vertex and index data ( pos, color, uv, normal )
  /*float vertexArray[] = {
    -0.5, -0.5, 0.3, 0,0,
    0.5, -0.5,  0.3, 1,0,
    -0.5, 0.5,  0.3, 0,1,
    0.5,  0.5,  0.3, 1,1
  };*/
  float vertexArray[] = {
    -1.0f, -1.0f, 0.3f, 0, 0,
    1.0f, -1.0f,  0.3f, 1, 0,
    -1.0f, 1.0f,  0.3f, 0, 1,
    1.0f,  1.0f,  0.3f, 1, 1
  };

  unsigned short indexArray[] = { 0,1,3, 0,3,2 };

  uint numVertices = 4;
  uint vertexSize = 20;
  numIndices = 6;
  float* vertexData = (float *)malloc(vertexSize * numVertices);
  memcpy_s(vertexData, vertexSize * numVertices, vertexArray, sizeof(vertexArray));

  unsigned short* indexData = (uint16 *)malloc(numIndices * sizeof(uint16));
  memcpy_s(indexData, numIndices * sizeof(uint16), indexArray, sizeof(indexArray));
   
  bool check;

  glGenBuffers(1, &vertexBuffer);
  check = CheckForErrors();
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  check = CheckForErrors();
  glBufferData(GL_ARRAY_BUFFER, numVertices * vertexSize, vertexData, GL_DYNAMIC_DRAW);
  check = CheckForErrors();

  glGenBuffers(1, &indexBuffer);
  check = CheckForErrors();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  check = CheckForErrors();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint16), indexData, GL_DYNAMIC_DRAW);
  check = CheckForErrors();

  // Create shader
  RedProgrameES3 redProgramRaw;
  BlueProgramES1 blueProgramRaw;

  redProgram = CreateProgram(redProgramRaw.GetVertexShader()->c_str(),
                             redProgramRaw.GetFragmentShader()->c_str());

  //// Create dummy texture
  //// The texture we're going to render to
  //GLuint tex = 0;
  //int width, height;
  //width = height = 128;

  //glGenTextures(1, &tex);
  //glBindTexture(GL_TEXTURE_2D, tex);

  //unsigned int* data = (unsigned int*)new GLuint[((width * height) * 4 * sizeof(unsigned int))];
  //memset(data, 255, ((width * height) * 4 * sizeof(unsigned int)));	// Clear Storage Memory

  //// change the color to red
  //for (int i = 0; i < width * height; i+=4) {
  //  data[i + 1] = 0;
  //  data[i + 2] = 0;
  //}

  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  //delete[] data;

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  

 ///* GLuint redProgram = wtu.setupProgram(gl, ["vshaderESSL3", "fshaderRed"], ["a_position"]);
 // GLuint blueProgramESSL1 = wtu.setupProgram(gl, ["vshaderESSL1", "fshaderBlueESSL1"], ["a_position"]);*/


 // /* LightManager::Instance().SetAmbientColor(Vector4f(0.2f, 0.2f, 0.2f, 1));
 // Vector3f dir(0, -1, -15);
 // dir.Normalize();
 // LightManager::Instance().SetDirection(dir);
 // LightManager::Instance().SetDirectionalColor(Vector4f(1, 1, 0, 1));*/

 // // Test clearing clears all the textures
 // GLuint tex = 0;

 // int width, height;
 // width = height = 128;

 // // The texture we're going to render to
 // glGenTextures(1, &tex);
 // glBindTexture(GL_TEXTURE_2D, tex);

 // unsigned int* data = (unsigned int*)new GLuint[((width * height) * 4 * sizeof(unsigned int))];
 // memset(data, 0, ((width * height) * 4 * sizeof(unsigned int)));	// Clear Storage Memory
 // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
 // delete[] data;

 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

 // Graphics* pGraphics = renderer.GetGraphics();

 // const uint max_fb = 8;
 // GLuint fb = 0;

 // for (int i = 0; i < max_fb; ++i) {
 //   fb = pGraphics->CreateFramebuffer();

 //   pGraphics->BindFramebuffer(i, fb, tex);
 // }

 // //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
 // glBindFramebuffer(GL_FRAMEBUFFER, 0);
 // pGraphics->ClearBit(GL_COLOR_BUFFER_BIT, Vector4f(0, 1, 0, 1));

 // // Setup shader
 // Square* squareA = renderer.CreateSquare();
 // FragbufferArrayES1 es1Shader;
 // squareA->GetSurface()->GetMaterial()->CreateProgram(*es1Shader.GetVertexShader(), *es1Shader.GetFragmentShader());
 // renderer.AddRenderItem(squareA);

 // // Test success shader to confirm MRT in OGL

 // // Read buffer

 // // Test failed shader
 // 
 // //   glBindFramebuffer(GL_FRAMEBUFFER, fb);

 // //CheckForErrors();
 // GLenum ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);

 // if (ret != GL_FRAMEBUFFER_COMPLETE) {
 //   assert(0);
 //   // GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
 //   // No images are attached to the framebuffer.
 // }
 // glBindFramebuffer(GL_FRAMEBUFFER, fb);
 // glDrawBuffers(8, bufs);
 // CheckForErrors();
 // //glUseProgram(blueProgramESSL1);
 // pGraphics->Draw(squareA->GetSurface());
 // Apollo::CheckForErrors();
 // // Read buffer
 // glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, fb);
}

//--------------------------------------------------------------------------------------
/// @brief Update, set cubeB to CubeA distance, and the parent node
/// 
/// @param [in] distanceBA cubeB to CubeA distance
///
/// @param [in] transformNode The rotating parent node
//--------------------------------------------------------------------------------------
void Update()
{
  Renderer &renderer = Renderer::Instance();
  renderer.Update();
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWBUFFER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DRAWBUFFER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   Renderer &renderer = Renderer::Instance();
   renderer.Initialize(hWnd, windowWidth, windowHeight);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
