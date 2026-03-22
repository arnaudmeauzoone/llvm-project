# File: CMakeLists.txt

add_llvm_component_library(LLVM{{cookiecutter.target_name}}Info
  {{cookiecutter.target_name}}TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  )