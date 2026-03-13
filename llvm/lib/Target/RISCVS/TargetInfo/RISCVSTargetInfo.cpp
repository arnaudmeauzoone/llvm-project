#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h" // Assurez-vous d'inclure ceci pour Triple::riscvs
#include "RISCVSTargetInfo.h"

using namespace llvm;

namespace llvm {
  // Déclaration de la fonction pour qu'elle soit connue dans le namespace llvm
  Target &getTheRISCVSTarget();
}

// Définition de la fonction
Target &llvm::getTheRISCVSTarget() {
  static Target TheRISCVSTarget;
  return TheRISCVSTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCVSTargetInfo() {
  RegisterTarget<Triple::riscvs, /*HasJIT=*/false>
      X(getTheRISCVSTarget(), "riscvs", "RISC-Vs Target", "RISCVS");
}