//===-- {{cookiecutter.target_name}}RegisterBankInfo.cpp - {{cookiecutter.target_name}} Backend ---===//


#include "{{cookiecutter.target_name}}RegisterBankInfo.h"
#include "llvm/CodeGen/GlobalISel/GenericMachineInstrs.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_TARGET_REGBANK_IMPL
#include "{{cookiecutter.target_name}}GenRegisterBank.inc"

using namespace llvm;

{{cookiecutter.target_name}}RegisterBankInfo::{{cookiecutter.target_name}}RegisterBankInfo(const TargetRegisterInfo &TRI)
    : {{cookiecutter.target_name}}GenRegisterBankInfo() {}

const RegisterBankInfo::InstructionMapping &
{{cookiecutter.target_name}}RegisterBankInfo::getInstrMapping(const MachineInstr &MI) const {
  const unsigned Opc = MI.getOpcode();

  // Si c'est déjà une instruction machine spécifique à la cible (pas générique),
  // on retourne le mapping par défaut.
  if (!isPreISelGenericOpcode(Opc)) {
    const RegisterBankInfo::InstructionMapping &Mapping = getInstrMappingImpl(MI);
    if (Mapping.isValid())
      return Mapping;
  }

  // --- Stratégie pour le jeu d'instructions "I" pur ---
  // On récupère le nombre d'opérandes de l'instruction
  unsigned NumOperands = MI.getNumOperands();
  
  // On demande au framework GlobalISel de nous fournir un mapping standard.
  // getOperandsMapping va créer un tableau où CHAQUE opérande est assigné à la banque spécifiée.
  // Ici : {{cookiecutter.target_name}}::GPRRegBankID (généré par TableGen).
  const ValueMapping *OperandsMapping =
      &getValueMapping(0, 32, getRegBank({{cookiecutter.target_name}}::GPRRegBankID));

  // On retourne le mapping complet pour cette instruction
  return getInstructionMapping(
      /* ID */ 1, /* Cost */ 1,
      getOperandsMapping({OperandsMapping, OperandsMapping, OperandsMapping}), 
      NumOperands);
}