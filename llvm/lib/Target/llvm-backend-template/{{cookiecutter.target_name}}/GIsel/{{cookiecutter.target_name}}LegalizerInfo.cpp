//===-- {{cookiecutter.target_name}}LegalizerInfo.cpp - {{cookiecutter.target_name}} Backend ---===//

#include "{{cookiecutter.target_name}}LegalizerInfo.h"
#include "{{cookiecutter.target_name}}Subtarget.h"
#include "llvm/CodeGen/GlobalISel/LegalizerHelper.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

using namespace llvm;
using namespace LegalityPredicates;

{{cookiecutter.target_name}}LegalizerInfo::{{cookiecutter.target_name}}LegalizerInfo(const {{cookiecutter.target_name}}Subtarget &ST) {
  // On définit nos types de base
  const LLT s32 = LLT::scalar(32);
  const LLT p0 = LLT::pointer(0, 32); // Pointeur dans l'adresse 0, taille 32 bits

  // --- 1. Opérations Arithmétiques de base (Supportées par "I") ---
  getActionDefinitionsBuilder({G_ADD, G_SUB, G_AND, G_OR, G_XOR, G_SHL, G_ASHR, G_LSHR})
      .legalFor({s32})     // Légal pour les entiers 32 bits
      .clampScalar(0, s32, s32); // Tout ce qui est plus petit (s8, s16) est promu à s32

  // --- 2. Cas de la Multiplication (G_MUL) ---
  // Comme on est en "I" pur, on n'a PAS d'instruction MUL.
  // On demande à LLVM de transformer G_MUL en appel de fonction (libcall: __mulsi3)
  getActionDefinitionsBuilder(G_MUL)
      .libcallFor({s32});

  // --- 3. Accès Mémoire (Load/Store) ---
  getActionDefinitionsBuilder({G_LOAD, G_STORE})
      .legalForTypesWithMemDesc({ {s32, p0, s32, 8},  // Load 32 bits depuis p0
                                  {s32, p0, s8, 8},   // Load 8 bits (LB)
                                  {s32, p0, s16, 8} }); // Load 16 bits (LH)

  // --- 4. Constantes et Pointeurs ---
  getActionDefinitionsBuilder(G_CONSTANT)
      .legalFor({s32});

  getActionDefinitionsBuilder(G_FRAME_INDEX)
      .legalFor({p0});

  // --- 5. Terminaisons (Return) ---
  // Pour la simplicité, on accepte le retour d'un s32 (registre a0)
  getActionDefinitionsBuilder(G_RET)
      .alwaysLegal();

  // On finit par calculer les tables de légalité
  getLegacyLegalizerInfo().computeTables();
}