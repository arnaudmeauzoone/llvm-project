add_llvm_component_library(LLVMRISCVSInfo
  RISCVSTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  )