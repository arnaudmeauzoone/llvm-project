//===-- {{cookiecutter.target_name}}.td - Fichier racine pour le backend {{cookiecutter.target_name}} ----===//
//
// Ce fichier centralise la description de l'architecture pour TableGen.
//
//===----------------------------------------------------------------------===//

// Inclusion des définitions de base de LLVM (indispensable)
include "llvm/Target/Target.td"

// 1. Définition des registres (GPR, Control Registers, etc.)
include "{{cookiecutter.target_name}}RegisterInfo.td"

// 2. Définition des banques de registres (CRUCIAL pour GlobalISel)
// Ce fichier fait souvent le pont entre les classes de registres et GlobalISel.
include "GIsel/{{cookiecutter.target_name}}RegisterBanks.td"

// 3. Définition des conventions d'appel (Passage de paramètres, pile)
include "{{cookiecutter.target_name}}CallingConv.td"

// 4. Définition du jeu d'instructions (Encodage, patterns)
include "{{cookiecutter.target_name}}InstrInfo.td"

// 5. Définition du modèle de processeur
// On définit un modèle générique sans ordonnancement complexe (NoSchedModel)
def : ProcessorModel<"generic-{{cookiecutter.target_name}}", NoSchedModel, []>;

// 6. Définition de la cible LLVM (L'objet Target principal)
def {{cookiecutter.target_name}} : Target {
  // On pointe vers l'instance de 'InstrInfo' définie dans {{cookiecutter.target_name}}InstrInfo.td
  let InstructionSet = {{cookiecutter.target_name}}InstrInfo;
}