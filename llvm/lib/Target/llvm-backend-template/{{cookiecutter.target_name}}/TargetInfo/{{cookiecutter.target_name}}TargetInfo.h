//===-- {{cookiecutter.target_name}}TargetInfo.h - {{cookiecutter.target_name}} Backend ---===//

#ifndef LLVM_LIB_TARGET_{{cookiecutter.target_name}}_TARGETINFO_{{cookiecutter.target_name}}TARGETINFO_H
#define LLVM_LIB_TARGET_{{cookiecutter.target_name}}_TARGETINFO_{{cookiecutter.target_name}}TARGETINFO_H

namespace llvm {
class Target;
Target &getThe{{cookiecutter.target_name}}Target();
}

#endif