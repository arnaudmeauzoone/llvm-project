//===-- {{cookiecutter.target_name}}Subtarget.h - {{cookiecutter.target_name}} Backend ---===//

#ifndef LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_{{cookiecutter.target_name | upper}}SUBTARGET_H
#define LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_{{cookiecutter.target_name | upper}}SUBTARGET_H

#include "{{cookiecutter.target_name}}FrameLowering.h"
#include "{{cookiecutter.target_name}}InstrInfo.h"
#include "{{cookiecutter.target_name}}RegisterInfo.h"
#include "{{cookiecutter.target_name}}TargetLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"

#define GET_SUBTARGETINFO_HEADER
#include "{{cookiecutter.target_name}}GenSubtargetInfo.inc"

namespace llvm {
class StringRef;
class TargetMachine;

class {{cookiecutter.target_name}}Subtarget : public {{cookiecutter.target_name}}GenSubtargetInfo {
  virtual void anchor();

  // --- Composants basiques du backend ---
  {{cookiecutter.target_name}}RegisterInfo RegInfo;
  {{cookiecutter.target_name}}InstrInfo InstrInfo;
  {{cookiecutter.target_name}}FrameLowering FrameLowering;
  {{cookiecutter.target_name}}TargetLowering TLInfo;

  // --- Composants exclusifs à GlobalISel ---
  std::unique_ptr<CallLowering> CallLoweringInfo;
  std::unique_ptr<LegalizerInfo> Legalizer;
  std::unique_ptr<RegisterBankInfo> RegBankInfo;
  std::unique_ptr<InstructionSelector> InstSelector;

public:
  {{cookiecutter.target_name}}Subtarget(const Triple &TT, const std::string &CPU,
                                        const std::string &FS, const TargetMachine &TM);

  // Auto-généré par TableGen (via le fichier .td)
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  // --- Getters standards ---
  const {{cookiecutter.target_name}}InstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const {{cookiecutter.target_name}}RegisterInfo *getRegisterInfo() const override { return &RegInfo; }
  const {{cookiecutter.target_name}}TargetLowering *getTargetLowering() const override { return &TLInfo; }
  const {{cookiecutter.target_name}}FrameLowering *getFrameLowering() const override { return &FrameLowering; }

  // --- Getters GlobalISel ---
  const CallLowering *getCallLowering() const override { return CallLoweringInfo.get(); }
  const LegalizerInfo *getLegalizerInfo() const override { return Legalizer.get(); }
  const RegisterBankInfo *getRegBankInfo() const override { return RegBankInfo.get(); }
  const InstructionSelector *getInstructionSelector() const override { return InstSelector.get(); }
};
} // end namespace llvm

#endif