/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#include <Application/Renderer/SliceShader.h>

#include <Core/Utils/Log.h>

namespace Seg3D
{

const char* SliceShader::FRAG_SHADER_SOURCE_C[] =
{
#include "SliceShader_frag"
#include "Lighting_frag"
#include "Fog_frag"
};

const char* SliceShader::VERT_SHADER_SOURCE_C[] =
{
#include "SliceShader_vert"
#include "Lighting_vert"
#include "Fog_vert"
};

SliceShader::SliceShader() :
  valid_( false )
{
}

SliceShader::~SliceShader()
{
}

bool SliceShader::initialize()
{
  this->glsl_frag_shader_ = Core::GLSLShaderHandle( new Core::GLSLFragmentShader );
  this->glsl_frag_shader_->set_source( sizeof( FRAG_SHADER_SOURCE_C ) / sizeof( char* ),
    FRAG_SHADER_SOURCE_C );
  if ( !this->glsl_frag_shader_->compile() )
  {
    std::string error_info = this->glsl_frag_shader_->get_info_log();
    CORE_LOG_ERROR( std::string( "Failed compiling SliceShader source: \n" ) + error_info );
    this->glsl_frag_shader_.reset();
    assert( false );
    return false;
  }

  this->glsl_vert_shader_.reset( new Core::GLSLVertexShader );
  this->glsl_vert_shader_->set_source( sizeof( VERT_SHADER_SOURCE_C ) / sizeof( char* ),
    VERT_SHADER_SOURCE_C );
  if ( !this->glsl_vert_shader_->compile() )
  {
    std::string error_info = this->glsl_vert_shader_->get_info_log();
    CORE_LOG_ERROR( std::string( "Failed compiling SliceShader source: \n" ) + error_info );
    this->glsl_frag_shader_.reset();
    this->glsl_vert_shader_.reset();
    assert( false );
    return false;
  }
  
  this->glsl_prog_ = Core::GLSLProgramHandle( new Core::GLSLProgram );
  this->glsl_prog_->attach_shader( this->glsl_vert_shader_ );
  this->glsl_prog_->attach_shader( this->glsl_frag_shader_ );
  if ( !this->glsl_prog_->link() )
  {
    std::string error_info = this->glsl_prog_->get_info_log();
    CORE_LOG_ERROR( std::string( "Failed linking SliceShader program: \n" ) + error_info );
    this->glsl_vert_shader_.reset();
    this->glsl_frag_shader_.reset();
    this->glsl_prog_.reset();
    assert( false );
    return false;
  }

  this->glsl_prog_->enable();
  this->slice_tex_loc_ = this->glsl_prog_->get_uniform_location( "slice_tex" );
  this->pattern_tex_loc_ = this->glsl_prog_->get_uniform_location( "pattern_tex" );
  this->opacity_loc_ = this->glsl_prog_->get_uniform_location( "opacity" );
  this->mask_mode_loc_ = this->glsl_prog_->get_uniform_location( "mask_mode" );
  this->scale_bias_loc_ = this->glsl_prog_->get_uniform_location( "scale_bias" );
  this->pixel_size_loc_ = this->glsl_prog_->get_uniform_location( "pixel_size" );
  this->border_width_loc_ = this->glsl_prog_->get_uniform_location( "border_width" );
  this->volume_type_loc_ = this->glsl_prog_->get_uniform_location( "volume_type" );
  this->mask_color_loc_ = this->glsl_prog_->get_uniform_location( "mask_color" );
  this->enable_lighting_loc_ = this->glsl_prog_->get_uniform_location( "enable_lighting" );
  this->enable_fog_loc_ = this->glsl_prog_->get_uniform_location( "enable_fog" );
  this->fog_range_loc_ = this->glsl_prog_->get_uniform_location( "fog_range" );
  this->glsl_prog_->disable();

  this->valid_ = true;
  return true;
}

void SliceShader::enable()
{
  assert( this->valid_ );
  this->glsl_prog_->enable();
}

void SliceShader::disable()
{
  assert( this->valid_ );
  this->glsl_prog_->disable();
}

void SliceShader::set_slice_texture( int tex_unit )
{
  glUniform1i( this->slice_tex_loc_, tex_unit );
}

void SliceShader::set_pattern_texture( int tex_unit )
{
  glUniform1i( this->pattern_tex_loc_, tex_unit );
}

void SliceShader::set_opacity( float opacity )
{
  glUniform1f( this->opacity_loc_, opacity );
}

void SliceShader::set_mask_mode( int mask_mode )
{
  glUniform1i( this->mask_mode_loc_, mask_mode );
}

void SliceShader::set_scale_bias( float scale, float bias )
{
  glUniform2f( this->scale_bias_loc_, scale, bias );
}

void SliceShader::set_pixel_size( float width, float height )
{
  glUniform2f( this->pixel_size_loc_, width, height );
}

void SliceShader::set_border_width( int width )
{
  glUniform1i( this->border_width_loc_, width );
}

void SliceShader::set_volume_type( int volume_type )
{
  glUniform1i( this->volume_type_loc_, volume_type );
}

void SliceShader::set_mask_color( float r, float g, float b )
{
  glUniform3f( this->mask_color_loc_, r, g, b );
}

void SliceShader::set_lighting( bool enabled )
{
  glUniform1i( this->enable_lighting_loc_, enabled );
}

void SliceShader::set_fog( bool enabled )
{
  glUniform1i( this->enable_fog_loc_, enabled );
}

void SliceShader::set_fog_range( float znear, float zfar )
{
  glUniform2f( this->fog_range_loc_, znear, zfar );
}

} // end namespace Seg3D