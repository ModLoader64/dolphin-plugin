if (NOT MSVC)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(SRCS
  cimgui.cpp
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
)

add_library(cimgui SHARED ${SRCS})
dolphin_disable_warnings_msvc(cimgui)
target_include_directories(cimgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
