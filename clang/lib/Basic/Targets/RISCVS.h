#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_RISCVS_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_RISCVS_H

#include "clang/Basic/TargetInfo.h"

namespace clang {
namespace targets {

class RISCVSTargetInfo : public TargetInfo {
protected:
  std::string ABI;

public:
  RISCVSTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    // Configuration minimale
    LongDoubleWidth = 128;
    LongDoubleAlign = 128;
    LongDoubleFormat = &llvm::APFloat::IEEEquad();
    SuitableAlign = 128;
    WCharType = SignedInt;
    WIntType = UnsignedInt;
  }

  void getTargetDefines(const LangOptions &Opts, MacroBuilder &Builder) const override;
  ArrayRef<const char *> getGCCRegNames() const override;
  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;
  
  bool validateAsmConstraint(const char *&Name, TargetInfo::ConstraintInfo &Info) const override {
    return Name[0] == 'I' || Name[0] == 'm' || Name[0] == 'r';
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }
  llvm::SmallVector<clang::Builtin::InfosShard> getTargetBuiltins() const override {
    return {}; 
  }

  // 2. Déclarer qu'aucun registre spécifique n'est altéré par défaut par l'assembleur
  std::string_view getClobbers() const override {
    return ""; 
  }
};

// Version 64 bits spécifique
class RISCVS64TargetInfo : public RISCVSTargetInfo {
public:
  RISCVS64TargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : RISCVSTargetInfo(Triple, Opts) {
    LongWidth = LongAlign = PointerWidth = PointerAlign = 64;
    IntMaxType = SignedLong;
    // Indispensable pour générer de l'IR LLVM correct. 
    // Signifie : little-endian, pointeurs 64 bits, entiers alignés sur 64/128, etc.
    resetDataLayout("e-m:e-p:64:64-i64:64-i128:128-n32:64-S128");
  }
};

} // namespace targets
} // namespace clang
#endif