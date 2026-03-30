//===-- {{cookiecutter.target_name}}RegisterBankInfo.h - {{cookiecutter.target_name}} Backend ---===//

#ifndef LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_GISEL_{{cookiecutter.target_name | upper}}REGISTERBANKINFO_H
#define LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_GISEL_{{cookiecutter.target_name | upper}}REGISTERBANKINFO_H

#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"

#define GET_REGBANK_DECLARATIONS
#include "{{cookiecutter.target_name}}GenRegisterBank.inc"

namespace llvm {

class TargetRegisterInfo;

class {{cookiecutter.target_name}}RegisterBankInfo final : public {{cookiecutter.target_name}}GenRegisterBankInfo {
public:
  {{cookiecutter.target_name}}RegisterBankInfo(const TargetRegisterInfo &TRI);

  // La fonction principale qui décide de la banque pour chaque opérande
  const InstructionMapping &
  getInstrMapping(const MachineInstr &MI) const override;
};

} // end namespace llvm

#endif