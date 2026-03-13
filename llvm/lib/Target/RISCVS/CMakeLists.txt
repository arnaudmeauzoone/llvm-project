# 1. Déclarer le groupe global de l'architecture (C'EST LA CLÉ ICI)
add_llvm_component_group(RISCVS)

add_subdirectory(TargetInfo)

set(LLVM_TARGET_DEFINITIONS RISCVS.td)

# 2. On garde bien le suffixe CodeGen pour la librairie principale
add_llvm_target(RISCVSCodeGen
  RISCVSTargetMachine.cpp

  LINK_COMPONENTS
  Core
  MC
  Support
  Target
  RISCVSInfo
  )