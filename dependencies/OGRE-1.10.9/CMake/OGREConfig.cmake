#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Find OGRE includes and library
#
# This module defines
#  OGRE_INCLUDE_DIRS - the OGRE include directories 
#  OGRE_LIBRARIES - link these to use the OGRE core
#  OGRE_LIBRARY_DIRS, the location of the libraries
#  OGRE_STATIC - whther ogre was build as static lib
#  OGRE_${COMPONENT}_FOUND - ${COMPONENT} is available
#  OGRE_${COMPONENT}_INCLUDE_DIRS - additional include directories for ${COMPONENT}
#  OGRE_${COMPONENT}_LIBRARIES - link these to use ${COMPONENT} 
#  OGRE_PLUGIN_DIR - The directory where the OGRE plugins are located
#  OGRE_MEDIA_DIR - The directory where the OGRE sample media is located
#  OGRE_CONFIG_DIR - The directory where the OGRE config files are located


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was OGREConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(OGRE_STATIC OFF)
set(OGRE_MEDIA_DIR "${PACKAGE_PREFIX_DIR}/Media")
set(OGRE_PLUGIN_DIR "${PACKAGE_PREFIX_DIR}/lib/OGRE")
set(OGRE_CONFIG_DIR "${PACKAGE_PREFIX_DIR}/bin") 

set(OGRE_PREFIX_DIR "${PACKAGE_PREFIX_DIR}")
get_filename_component(OGRE_LIBRARY_DIRS "${OGRE_PREFIX_DIR}/lib" ABSOLUTE)
get_filename_component(OGRE_INCLUDE_DIRS "${OGRE_PREFIX_DIR}/include/OGRE" ABSOLUTE)
if(APPLE AND NOT APPLE_IOS)
    # Note: OGRE_INCLUDE_DIRS is not yet a list
    list(APPEND OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS}/OSX)
endif()
set(OGRE_LIBRARIES)

cmake_policy(PUSH)
cmake_policy(SET CMP0012 NEW)

if(0 EQUAL 1)
    list(APPEND OGRE_INCLUDE_DIRS Boost_INCLUDE_DIR-NOTFOUND)
endif()

list(APPEND OGRE_LIBRARIES )

set(OGRE_COMPONENTS)
set(OGRE_PLUGINS)

macro(ogre_declare_component COMPONENT)
    set(OGRE_${COMPONENT}_FOUND TRUE)
    set(OGRE_${COMPONENT}_INCLUDE_DIRS "${OGRE_PREFIX_DIR}/include/OGRE/${COMPONENT}")
    set(OGRE_${COMPONENT}_LIBRARIES "Ogre${COMPONENT}")
    
    list(APPEND OGRE_COMPONENTS ${COMPONENT})
    
    list(APPEND OGRE_INCLUDE_DIRS ${OGRE_${COMPONENT}_INCLUDE_DIRS})
    list(APPEND OGRE_LIBRARIES ${OGRE_${COMPONENT}_LIBRARIES})
endmacro()

macro(ogre_declare_plugin TYPE COMPONENT)
    set(OGRE_${TYPE}_${COMPONENT}_FOUND TRUE)
    set(OGRE_${TYPE}_${COMPONENT}_INCLUDE_DIRS "${OGRE_PREFIX_DIR}/include/OGRE/${TYPE}s/${COMPONENT}")
    set(OGRE_${TYPE}_${COMPONENT}_LIBRARIES "${TYPE}_${COMPONENT}")
    
    if(OFF)
        list(APPEND OGRE_LIBRARIES ${OGRE_${TYPE}_${COMPONENT}_LIBRARIES})
    endif()
    
    list(APPEND OGRE_PLUGINS ${TYPE}_${COMPONENT})
endmacro()

## COMPONENTS
if(ON)
    ogre_declare_component(Bites)
    
    if(TRUE)
        list(APPEND OGRE_Bites_INCLUDE_DIRS C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/include/SDL2)
        list(APPEND OGRE_Bites_LIBRARIES winmm;imm32;version;msimg32;C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/lib/SDL2main.lib;C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/lib/SDL2.lib)
        
        list(APPEND OGRE_INCLUDE_DIRS C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/include/SDL2)
        list(APPEND OGRE_LIBRARIES "winmm;imm32;version;msimg32;C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/lib/SDL2main.lib;C:/Users/taylo/Documents/Code/Libraries/OGRE-1.10.9/build/Dependencies/lib/SDL2.lib")
    endif()
endif()
if(ON)
    ogre_declare_component(HLMS)
endif()
if(ON)
    ogre_declare_component(MeshLodGenerator)
endif()
if(ON)
    ogre_declare_component(Overlay)
endif()
if(ON)
    ogre_declare_component(Paging)
endif()
if(ON)
    ogre_declare_component(Property)
endif()
if(ON)
    ogre_declare_component(RTShaderSystem)
endif()
if(ON)
    ogre_declare_component(Terrain)
endif()
if(ON)
    ogre_declare_component(Volume)
endif()

## PLUGINS
if(ON)
    ogre_declare_plugin(Plugin BSPSceneManager)
endif()

if(ON)
    ogre_declare_plugin(Plugin CgProgramManager)
endif()

if(ON)
    ogre_declare_plugin(Plugin OctreeSceneManager)
endif()

if(ON)
    ogre_declare_plugin(Plugin PCZSceneManager)
endif()

if(ON)
    ogre_declare_plugin(Plugin ParticleFX)
endif()

if(ON)
    ogre_declare_plugin(RenderSystem GL)
endif()

if(OFF)
    ogre_declare_plugin(RenderSystem GLES2)
endif()

if(ON)
    ogre_declare_plugin(RenderSystem GL3Plus)
endif()

if(ON)
    ogre_declare_plugin(RenderSystem Direct3D9)
endif()

if(ON)
    ogre_declare_plugin(RenderSystem Direct3D11)
endif()
cmake_policy(POP)

if(OFF)
    list(APPEND OGRE_LIBRARIES OgreGLSupport ) # glXXw uses dlopen
    list(APPEND OGRE_LIBRARY_DIRS "${OGRE_LIBRARY_DIRS}/OGRE") # plugins folder
endif()

# must come last in case of static build
list(APPEND OGRE_LIBRARIES "OgreMain")

if(NOT OGRE_FIND_QUIETLY)
    message(STATUS "Found OGRE")
    message(STATUS "  static     : ${OGRE_STATIC}")
    message(STATUS "  components : ${OGRE_COMPONENTS}")
    message(STATUS "  plugins    : ${OGRE_PLUGINS}")
    message(STATUS "  media      : ${OGRE_MEDIA_DIR}")
endif()
