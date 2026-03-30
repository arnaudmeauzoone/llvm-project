//===-- {{cookiecutter.target_name}}Subtarget.cpp - {{cookiecutter.target_name}} Backend ---===//

#include "{{cookiecutter.target_name}}Subtarget.h"
#include "{{cookiecutter.target_name}}TargetMachine.h"
#include "GIsel/{{cookiecutter.target_name}}CallLowering.h"
#include "GIsel/{{cookiecutter.target_name}}LegalizerInfo.h"
#include "GIsel/{{cookiecutter.target_name}}RegisterBankInfo.h"
#include "GIsel/{{cookiecutter.target_name}}InstructionSelector.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "{{cookiecutter.target_name}}-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "{{cookiecutter.target_name}}GenSubtargetInfo.inc"

void {{cookiecutter.target_name}}Subtarget::anchor() {}

{{cookiecutter.target_name}}Subtarget::{{cookiecutter.target_name}}Subtarget(const Triple &TT, const std::string &CPU,
                                                                             const std::string &FS,
                                                                             const TargetMachine &TM)
    : {{cookiecutter.target_name}}GenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS),
      RegInfo(),
      InstrInfo(*this),
      FrameLowering(*this),
      TLInfo(TM, *this) {

  // 1. Analyse des features (TableGen). 
  // Même pour une architecture simple, TableGen en a besoin.
  ParseSubtargetFeatures(CPU, CPU, FS);

  // 2. Initialisation du pipeline GlobalISel (100% GISel)
  
  // Le CallLowering gère l'ABI (les appels de fonctions)
  CallLoweringInfo.reset(new {{cookiecutter.target_name}}CallLowering(*getTargetLowering()));
  
  // Le Legalizer s'assure que les instructions sont supportées par la cible
  Legalizer.reset(new {{cookiecutter.target_name}}LegalizerInfo(*this));
  
  // Gestion des banques de registres (ex: GPR vs FPR, bien que tu n'aies que GPR ici)
  auto *RBI = new {{cookiecutter.target_name}}RegisterBankInfo(*getRegisterInfo());
  RegBankInfo.reset(RBI);
  
  // Le sélecteur d'instructions final (machine code)
  InstSelector.reset(new {{cookiecutter.target_name}}InstructionSelector(TM, *this, *RBI));
}