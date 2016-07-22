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

  class DrawBufferProgram
  {
  public:

    //--------------------------------------------------------------------------------------
    /// @brief Constructor, write shader here
    //--------------------------------------------------------------------------------------
    DrawBufferProgram()
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
        "uniform vec4 u_colors[8]; \n"
        "out vec4 my_FragData[8]; \n"
        "\n"
        "void main(void) \n"
        "{ \n"
        "  my_FragData[0] = u_colors[0]; \n"
        "  my_FragData[1] = u_colors[1]; \n"
        "  my_FragData[2] = u_colors[2]; \n"
        "  my_FragData[3] = u_colors[3]; \n"
        "  my_FragData[4] = u_colors[4]; \n"
        "  my_FragData[5] = u_colors[5]; \n"
        "  my_FragData[6] = u_colors[6]; \n"
        "  my_FragData[7] = u_colors[7]; \n"
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