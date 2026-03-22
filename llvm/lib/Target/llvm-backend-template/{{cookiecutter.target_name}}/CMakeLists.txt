# File: CMakeLists.txt

# 1. Déclarer le groupe global de l'architecture
add_llvm_component_group({{cookiecutter.target_name}})

# 2. Sous-répertoires requis pour l'infrastructure
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(GIsel) # Crucial ici

# 3. Définir le fichier TableGen principal
set(LLVM_TARGET_DEFINITIONS {{cookiecutter.target_name}}.td)

# 4. Déclarer la bibliothèque de génération de code
add_llvm_target(
  {{cookiecutter.target_name}}CodeGen
  {{cookiecutter.target_name}}TargetMachine.cpp
  {{cookiecutter.target_name}}Subtarget.cpp
  {{cookiecutter.target_name}}TargetLowering.cpp
  {{cookiecutter.target_name}}FrameLowering.cpp
  {{cookiecutter.target_name}}RegisterInfo.cpp
  {{cookiecutter.target_name}}InstrInfo.cpp
  {{cookiecutter.target_name}}AsmPrinter.cpp
  {{cookiecutter.target_name}}MCInstLower.cpp

  LINK_COMPONENTS
  # Composants cœur
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  Support
  Target
  
  # Pipeline GlobalISel (Remplace SelectionDAG)
  GlobalISel
  
  # Tes composants internes
  {{cookiecutter.target_name}}Info
  {{cookiecutter.target_name}}Desc
  {{cookiecutter.target_name}}AsmParser
  {{cookiecutter.target_name}}Disassembler
  {{cookiecutter.target_name}}GIsel
  )