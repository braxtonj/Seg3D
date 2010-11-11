
#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2009 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

##################################################
# Set sources
##################################################

SET(APPLICATION_FILTERS_SRCS
  LayerFilter.h
  LayerFilter.cc
  LayerFilterLock.h
  LayerFilterLock.cc
  ITKFilter.h
  ITKFilter.cc
  NrrdFilter.h
  NrrdFilter.cc
  LayerResampler.h
  LayerResampler.cc
)

SET(APPLICATION_FILTERS_ACTIONS_SRCS
  Actions/ActionResample.h
  Actions/ActionResample.cc
  Actions/ActionCannyEdgeDetectionFilter.h
  Actions/ActionCannyEdgeDetectionFilter.cc
  Actions/ActionConfidenceConnectedFilter.h
  Actions/ActionConfidenceConnectedFilter.cc
  Actions/ActionConnectedComponentFilter.h
  Actions/ActionConnectedComponentFilter.cc
  Actions/ActionConnectedComponentSizeFilter.h
  Actions/ActionConnectedComponentSizeFilter.cc
  Actions/ActionCurvatureAnisotropicDiffusionFilter.h
  Actions/ActionCurvatureAnisotropicDiffusionFilter.cc
  Actions/ActionDilateFilter.h
  Actions/ActionDilateFilter.cc
  Actions/ActionDilateErodeFilter.h
  Actions/ActionDilateErodeFilter.cc
  Actions/ActionDiscreteGaussianFilter.h
  Actions/ActionDiscreteGaussianFilter.cc
  Actions/ActionDistanceFilter.h
  Actions/ActionDistanceFilter.cc
  Actions/ActionErodeFilter.h
  Actions/ActionErodeFilter.cc
  Actions/ActionGradientAnisotropicDiffusionFilter.h
  Actions/ActionGradientAnisotropicDiffusionFilter.cc
  Actions/ActionGradientMagnitudeFilter.h
  Actions/ActionGradientMagnitudeFilter.cc
  Actions/ActionFillHolesFilter.h
  Actions/ActionFillHolesFilter.cc
  Actions/ActionHistogramEqualizationFilter.h
  Actions/ActionHistogramEqualizationFilter.cc
  Actions/ActionIntensityCorrectionFilter.h
  Actions/ActionIntensityCorrectionFilter.cc
  Actions/ActionMaskDataFilter.h
  Actions/ActionMaskDataFilter.cc
  Actions/ActionMedianFilter.h
  Actions/ActionMedianFilter.cc
  Actions/ActionMeanFilter.h
  Actions/ActionMeanFilter.cc
  Actions/ActionNeighborhoodConnectedFilter.h
  Actions/ActionNeighborhoodConnectedFilter.cc
  Actions/ActionOtsuThresholdFilter.h
  Actions/ActionOtsuThresholdFilter.cc
  Actions/ActionThreshold.h
  Actions/ActionThreshold.cc
  Actions/ActionInvert.h
  Actions/ActionInvert.cc
  Actions/ActionCrop.h
  Actions/ActionCrop.cc
  Actions/ActionArithmeticFilter.h
  Actions/ActionArithmeticFilter.cc
  Actions/ActionPermute.h
  Actions/ActionPermute.cc
  Actions/ActionTransform.h
  Actions/ActionTransform.cc
  )

CORE_ADD_LIBRARY(Application_Filters ${APPLICATION_FILTERS_SRCS}
            ${APPLICATION_FILTERS_ACTIONS_SRCS} )
            
TARGET_LINK_LIBRARIES(Application_Filters
                      Core_Utils
                      Core_Action
                      Core_State
                      Core_Parser
                      Application_Layer
                      Application_LayerManager
                      ${SCI_BOOST_LIBRARY})

# Register action classes
REGISTER_LIBRARY_AND_CLASSES(Application_Filters
							 ${APPLICATION_FILTERS_ACTIONS_SRCS})
                    