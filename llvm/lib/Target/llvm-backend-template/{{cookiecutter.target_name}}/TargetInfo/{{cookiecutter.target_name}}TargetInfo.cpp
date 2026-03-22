//===-- {{cookiecutter.target_name}}TargetInfo.cpp - {{cookiecutter.target_name}} Backend ---===//
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h" // Assurez-vous d'inclure ceci pour Triple::{{cookiecutter.target_name}}
#include "{{cookiecutter.target_name}}TargetInfo.h"

using namespace llvm;

namespace llvm {
  // Déclaration de la fonction pour qu'elle soit connue dans le namespace llvm
  Target &getThe{{cookiecutter.target_name}}Target();
}

// Définition de la fonction
Target &llvm::getThe{{cookiecutter.target_name}}Target() {
  static Target The{{cookiecutter.target_name}}Target;
  return The{{cookiecutter.target_name}}Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitialize{{cookiecutter.target_name}}TargetInfo() {
  RegisterTarget<Triple::{{cookiecutter.target_name}}, /*HasJIT=*/false>
      X(getThe{{cookiecutter.target_name}}Target(), "{{cookiecutter.target_name}}", "RISC-Vs Target", "{{cookiecutter.target_name}}");
}
