// {{cookiecutter.target_name}} TableGen Definition


// Définit la banque de registres généraux (GPR)
// GPRRegClass est la classe de registres (X0-X31) que tu as dû définir dans ton TargetRegisterInfo.td
def GPRRegBank : RegisterBank<"GPRB", [GPRRegClass]>;