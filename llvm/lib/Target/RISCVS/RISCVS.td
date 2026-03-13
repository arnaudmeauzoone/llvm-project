include "llvm/Target/Target.td"

// Un composant bidon pour satisfaire l'analyseur
def RISCVSInstrInfo : InstrInfo;

// La définition de la cible
def RISCVS : Target {
  let InstructionSet = RISCVSInstrInfo;
}