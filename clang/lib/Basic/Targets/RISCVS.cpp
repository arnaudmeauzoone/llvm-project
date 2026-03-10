#include "RISCVS.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

// Registres vitaux (x0-x31)
ArrayRef<const char *> RISCVSTargetInfo::getGCCRegNames() const {
  static const char *const GCCRegNames[] = {
      "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",
      "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15",
      "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
      "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"
  };
  return llvm::ArrayRef(GCCRegNames);
}

// Alias ABI
ArrayRef<TargetInfo::GCCRegAlias> RISCVSTargetInfo::getGCCRegAliases() const {
  static const TargetInfo::GCCRegAlias GCCRegAliases[] = {
      {{"zero"}, "x0"}, {{"ra"}, "x1"}, {{"sp"}, "x2"}, {{"gp"}, "x3"},
      {{"tp"}, "x4"},   {{"t0"}, "x5"}, {{"a0"}, "x10"}, {{"a1"}, "x11"}
  };
  return llvm::ArrayRef(GCCRegAliases);
}

void RISCVSTargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  Builder.defineMacro("__riscv");
  Builder.defineMacro("__riscv_xlen", "64");
  Builder.defineMacro("__riscv_float_abi_soft"); // Indispensable pour IMA sans FPU
  
  // Macros codées en dur pour les extensions IMA que l'on suppose toujours présentes
  Builder.defineMacro("__riscv_mul");
  Builder.defineMacro("__riscv_div");
  Builder.defineMacro("__riscv_atomic");
}