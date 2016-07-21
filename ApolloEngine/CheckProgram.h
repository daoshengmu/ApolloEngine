#pragma once

#include <string>

/**
*
* @file     FragbufferArrayES3.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* FragbufferArrayES3 shader for temporary experiment, this should be more general
*
*/

namespace Apollo
{

  class CheckProgram
  {
  public:

    //--------------------------------------------------------------------------------------
    /// @brief Constructor, write shader here
    //--------------------------------------------------------------------------------------
    CheckProgram()
    {
      _vertexShader =
        "attribute vec4 vPosition; \n"
        "attribute vec2 texCoord0; \n"
        "varying vec2 texCoord;    \n"
        "\n"
        "void main() \n"
        "{ \n"
        "   gl_Position = vPosition; \n"
        "   texCoord = texCoord0;    \n"
        "} \n";

      _fragmentShader =
        "precision mediump float; \n"
        "uniform sampler2D tex; \n"
        "varying vec2 texCoord; \n"
        "\n"
        "void main(void) \n"
        "{ \n"
        "  gl_FragData[0] = texture2D(tex, texCoord); \n"
        "} \n";
    }

    //--------------------------------------------------------------------------------------
    /// @brief Get vertex shader
    /// 
    /// @return vertex shader
    //-------------------------------------------------------------------------------------
    const std::string* GetVertexShader() { return &_vertexShader; }


    //--------------------------------------------------------------------------------------
    /// @brief Get fragment shader
    ///  
    /// @return fragement shader
    //--------------------------------------------------------------------------------------
    const std::string* GetFragmentShader() { return &_fragmentShader; }

  private:
    std::string _vertexShader;
    std::string _fragmentShader;

  };

}