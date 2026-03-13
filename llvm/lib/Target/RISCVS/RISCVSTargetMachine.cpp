#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"
#include "RISCVSTargetMachine.h"
#include "TargetInfo/RISCVSTargetInfo.h"
#include <optional>

using namespace llvm;

namespace {
// 1. On hérite directement de TargetMachine
class RISCVSTargetMachine : public TargetMachine { 
public:
  RISCVSTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM,
                      CodeGenOptLevel OL, bool JIT)
      // 2. On appelle TargetMachine (et on retire RM, CM, OL des arguments transmis)
      : TargetMachine(T, "e-m:e-p:32:32-i64:64-n32-S128", TT, CPU, FS, Options) {}

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override {
    return new TargetPassConfig(*this, PM);
  }
};
} // end anonymous namespace

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCVSTargetMC() {
  // Vide pour le moment, juste pour satisfaire le linker lors de l'appel
  // à InitializeAllTargetMCs() dans llc.
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCVSTarget() {
  RegisterTargetMachine<RISCVSTargetMachine> X(getTheRISCVSTarget());
}