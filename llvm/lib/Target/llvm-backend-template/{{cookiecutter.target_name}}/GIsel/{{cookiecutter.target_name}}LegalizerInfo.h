//===-- {{cookiecutter.target_name}}LegalizerInfo.h - {{cookiecutter.target_name}} Backend ---===//

#ifndef LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_GISEL_{{cookiecutter.target_name | upper}}LEGALIZERINFO_H
#define LLVM_LIB_TARGET_{{cookiecutter.target_name | upper}}_GISEL_{{cookiecutter.target_name | upper}}LEGALIZERINFO_H

#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"

namespace llvm {
class {{cookiecutter.target_name}}Subtarget;

class {{cookiecutter.target_name}}LegalizerInfo : public LegalizerInfo {
public:
  {{cookiecutter.target_name}}LegalizerInfo(const {{cookiecutter.target_name}}Subtarget &ST);
};
} // end namespace llvm

#endif