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

  class BlueProgramES1
  {
  public:

    //--------------------------------------------------------------------------------------
    /// @brief Constructor, write shader here
    //--------------------------------------------------------------------------------------
    BlueProgramES1()
    {
      _vertexShader =
        "attribute vec4 a_position; \n"        
        "\n"
        "void main() \n"
        "{ \n"
        "   gl_Position = a_position; \n"
        "} \n";

      _fragmentShader =
        "precision mediump float; \n"
        "\n"
        "void main(void) \n"
        "{ \n"
        "  gl_FragColor = vec4(0, 0, 1, 1); \n"
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