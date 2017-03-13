/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
// Original class author: A.M. Jokisaari,  O. Heinonen

#ifndef DYMRUPLINEARELASTICMATERIAL_H
#define DYMRUPLINEARELASTICMATERIAL_H

#include "TensorMechanicsMaterial.h"

/**
 * LinearElasticMaterial handles a fully anisotropic, single-crystal material's elastic
 * constants.  It takes all 21 independent stiffness tensor inputs, or only 9, depending on the
 * boolean input value given.  This can be extended or simplified to specify HCP, monoclinic,
 * cubic, etc as needed.
 */
class DymRupLinearElasticMaterial : public TensorMechanicsMaterial
{
public:
  DymRupLinearElasticMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpStrain();
  virtual void computeQpStress();
  virtual RankTwoTensor computeStressFreeStrain();

private:
  const VariableValue & _T;

  const Real _T0;
  Real _thermal_expansion_coeff;

  std::vector<Real> _applied_strain_vector;
  RankTwoTensor _applied_strain_tensor;
};

#endif //LINEARELASTICMATERIAL_H
