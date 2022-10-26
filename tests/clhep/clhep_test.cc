
// CLHEP units
#include "CLHEP/Units/PhysicalConstants.h"
using namespace CLHEP;

int main(int argc, char* argv[]) {
    """print CLHEP length units"""
    std::cout << "CLHEP length units:" << std::endl;
    std::cout << "  1 mm = " << 1.0/mm << " mm" << std::endl;
    std::cout << "  1 cm = " << 1.0/cm << " cm" << std::endl;
    std::cout << "  1 m  = " << 1.0/m << " m" << std::endl;
    std::cout << "  1 km = " << 1.0/km << " km" << std::endl;
    std::cout << "  1 fm = " << 1.0/fm << " fm" << std::endl;
    std::cout << "  1 um = " << 1.0/um << " um" << std::endl;
    std::cout << "  1 nm = " << 1.0/nm << " nm" << std::endl;
    std::cout << "  1 pm = " << 1.0/pm << " pm" << std::endl;
    std::cout << "  1 am = " << 1.0/am << " am" << std::endl;
    std::cout << "  1 barn = " << 1.0/barn << " barn" << std::endl;
    std::cout << "  1 millibarn = " << 1.0/millibarn << " millibarn" << std::endl;
    std::cout << "  1 microbarn = " << 1.0/microbarn << " microbarn" << std::endl;
    std::cout << "  1 nanobarn = " << 1.0/nanobarn << " nanobarn" << std::endl;
    std::cout << "  1 picobarn = " << 1.0/picobarn << " picobarn" << std::endl;
    std::cout << "  1 femtobarn = " << 1.0/femtobarn << " femtobarn" << std::endl;
    std::cout << "  1 attobarn = " << 1.0/attobarn << " attobarn" << std::endl;
    std::cout << "  1 zeptobarn = " << 1.0/zeptobarn << " zeptobarn" << std::endl;
    std::cout << "  1 yoctobarn = " << 1.0/yoctobarn << " yoctobarn" << std::endl;
    std::cout << "  1 kilometer = " << 1.0/kilometer << " kilometer" << std::endl;
    std::cout << "  1 megameter = " << 1.0/megameter << " megameter" << std::endl;
    std::cout << "  1 gigameter = " << 1.0/gigameter << " gigameter" << std::endl;
    std::cout << "  1 terameter = " << 1.0/terameter << " terameter" << std::endl;
    std::cout << "  1 petameter = " << 1.0/petameter << " petameter" << std::endl;
    std::cout << "  1 exameter = " << 1.0/exameter << " exameter" << std::endl;
    std::cout << "  1 zettameter = " << 1.0/zettameter << " zettameter" << std::endl;
    std::cout << "  1 yottameter = " << 1.0/yottameter << " yottameter" << std::endl;
    std::cout << "  1 angstrom = " << 1.0/angstrom << " angstrom" << std::endl;
    std::cout << "  1 fermi = " << 1.0/fermi << " fermi" << std::endl;
    std::cout << "  1 micrometer = " << 1.0/micrometer << " micrometer" << std::endl;
    std::cout << "  1 nanometer = " << 1.0/nanometer << " nanometer" << std::endl;
    std::cout << "  1 picometer = " << 1.0/picometer << " picometer" << std::endl;
    std::cout << "  1 femtometer = " << 1.0/femtometer << " femtometer" << std::endl;
    std::cout << "  1 attometer = " << 1.0/attometer << " attometer" << std::endl;
    std::cout << "  1 zeptometer = " << 1.0/zeptometer << " zeptometer" << std::endl;
    std::cout << "  1 yoctometer = " << 1.0/yoctometer << " yoctometer" << std::endl;
    std::cout << "  1 astronomical unit = " << 1.0/astronomical_unit << " astronomical unit" << std::endl;
    std::cout << "  1 light year = " << 1.0/light_year << " light year" << std::endl;
    std::cout << "  1 parsec = " << 1.0/parsec << " parsec" << std::endl;
    std::cout << "  1 kiloparsec = " << 1.0/kiloparsec << " kiloparsec" << std::endl;
    std::cout << "  1 megaparsec = " << 1.0/megaparsec << " megaparsec" << std::endl;
    std::cout << "  1 gigaparsec = " << 1.0/gigaparsec << " gigaparsec" << std::endl;
    std::cout << "  1 teraparsec = " << 1.0/teraparsec << " teraparsec" << std::endl;
    std::cout << "  1 petaparsec = " << 1.0/petaparsec << " petaparsec" << std::endl;
    std::cout << "  1 examaparsec = " << 1.0/examaparsec << " examaparsec" << std::endl;



    std::cout << "CLHEP Constants:" << std::endl;
    std::cout << "  pi = " << pi << std::endl;
    std::cout << "  twopi = " << twopi << std::endl;
    std::cout << "  halfpi = " << halfpi << std::endl;
    std::cout << "  radian = " << radian << std::endl;
    std::cout << "  degree = " << degree << std::endl;
    std::cout << "  steradian = " << steradian << std::endl;
    std::cout << "  electron_mass_c2 = " << electron_mass_c2 << std::endl;
    std::cout << "  proton_mass_c2 = " << proton_mass_c2 << std::endl;
    std::cout << "  neutron_mass_c2 = " << neutron_mass_c2 << std::endl;
    std::cout << "  amu_c2 = " << amu_c2 << std::endl;
    std::cout << "  hbarc = " << hbarc << std::endl;
    std::cout << "  hbar_Planck = " << hbar_Planck << std::endl;
    std::cout << "  h_Planck = " << h_Planck << std::endl;
    std::cout << "  c_light = " << c_light << std::endl;
    std::cout << "  c_squared = " << c_squared << std::endl;
    std::cout << "  fine_structure_const = " << fine_structure_const << std::endl;
    std::cout << "  avogadro = " << avogadro << std::endl;
    std::cout << "  k_Boltzmann = " << k_Boltzmann << std::endl;
    std::cout << "  kGasThreshold = " << kGasThreshold << std::endl;
    std::cout << "  sigma_T = " << sigma_T << std::endl;
    std::cout << "  epsilon0 = " << epsilon0 << std::endl;
    std::cout << "  mu0 = " << mu0 << std::endl;
    std::cout << "  e_SI = " << e_SI << std::endl;
    std::cout << "  e_squared = " << e_squared << std::endl;
    std::cout << "  m_e_SI = " << m_e_SI << std::endl;
    std::cout << "  m_p_SI = " << m_p_SI << std::endl;
    std::cout << "  m_n_SI = " << m_n_SI << std::endl;
    std::cout << "  m_mu_SI = " << m_mu_SI << std::endl;
    std::cout << "  G_SI = " << G_SI << std::endl;
    std::cout << "  c_light_SI = " << c_light_SI << std::endl;
    std::cout << "  c_squared_SI = " << c_squared_SI << std::endl;
    std::cout << "  h_Planck_SI = " << h_Planck_SI << std::endl;
    std::cout << "  hbar_Planck_SI = " << hbar_Planck_SI << std::endl;
    std::cout << "  hbarc_SI = " << hbarc_SI << std::endl;
    std::cout << "  eV_SI = " << eV_SI << std::endl;
    std::cout << "  alpha_rcl2_SI = " << alpha_rcl2_SI << std::endl;
    std::cout << "  twopi_mc2_rcl2_SI = " << twopi_mc2_rcl2_SI << std::endl;
    std::cout << "  k_Boltzmann_SI = " << k_Boltzmann_SI << std::endl;
    std::cout << "  kGasThreshold_SI = " << kGasThreshold_SI << std::endl;
    std::cout << "  sigma_T_SI = " << sigma_T_SI << std::endl;
    std::cout << "  lambda_e_SI = " << lambda_e_SI << std::endl;
    std::cout << "  lambda_mu_SI = " << lambda_mu_SI << std::endl;
}