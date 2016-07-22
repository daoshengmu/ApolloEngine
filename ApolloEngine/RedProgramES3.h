#pragma once

#include <string>

/**
*
* @file     FragbufferArrayES1.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* FragbufferArrayES1 shader for temporary experiment, this should be more general
*
*/

namespace Apollo
{

  class RedProgrameES3
  {
  public:

    //--------------------------------------------------------------------------------------
    /// @brief Constructor, write shader here
    //--------------------------------------------------------------------------------------
    RedProgrameES3()
    {
      _vertexShader =
        "in vec4 a_position; \n"
        "\n"
        "void main() \n"
        "{ \n"
        "  gl_Position = a_position; \n"
        "} \n";

      _fragmentShader =
        "#version 430 \n"
        "precision mediump float; \n"
        "out vec4 my_FragColor; \n"
        "\n"
        "void main(void) \n"
        "{ \n"
        "  my_FragColor = vec4(1, 0, 0, 1); \n"
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