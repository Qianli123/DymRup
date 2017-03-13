#include "DymrupApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// Action
#include "DymRupContactAction.h"
#include "ContactMaster.h"
#include "ContactPenetrationAuxAction.h"
#include "ContactPenetrationVarAction.h"
#include "ContactPressureAux.h"
#include "ContactPressureAuxAction.h"
#include "ContactPressureVarAction.h"
#include "NodalAreaAction.h"
#include "SlaveConstraint.h"
#include "OneDContactConstraint.h"
#include "MultiDContactConstraint.h"
#include "GluedContactConstraint.h"
#include "MechanicalContactConstraint.h"
#include "SparsityBasedContactConstraint.h"
#include "FrictionalContactProblem.h"
#include "ReferenceResidualProblem.h"
#include "NodalArea.h"
#include "NodalAreaAction.h"
#include "NodalAreaVarAction.h"
#include "ContactSlipDamper.h"
#include "ContactSplit.h"
// Material
#include "DymRupLinearElasticMaterial.h"



template<>
InputParameters validParams<DymrupApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

DymrupApp::DymrupApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  DymrupApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  DymrupApp::associateSyntax(_syntax, _action_factory);
}

DymrupApp::~DymrupApp()
{
}

// External entry point for dynamic application loading
extern "C" void DymrupApp__registerApps() { DymrupApp::registerApps(); }
void
DymrupApp::registerApps()
{
  registerApp(DymrupApp);
}

// External entry point for dynamic object registration
extern "C" void DymrupApp__registerObjects(Factory & factory) { DymrupApp::registerObjects(factory); }
void
DymrupApp::registerObjects(Factory & factory)
{
  registerMaterial(DymRupLinearElasticMaterial);

}

// External entry point for dynamic syntax association
extern "C" void DymrupApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { DymrupApp::associateSyntax(syntax, action_factory); }
void
DymrupApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  syntax.registerActionSyntax("DymRupContactAction", "DymRupContact/*");

  syntax.registerActionSyntax("ContactPenetrationAuxAction", "DymRupContact/*");
  syntax.registerActionSyntax("ContactPenetrationVarAction", "DymRupContact/*");

  syntax.registerActionSyntax("ContactPressureAuxAction", "DymRupContact/*");
  syntax.registerActionSyntax("ContactPressureVarAction", "DymRupContact/*");

  syntax.registerActionSyntax("NodalAreaAction", "DymRupContact/*");
  syntax.registerActionSyntax("NodalAreaVarAction", "DymRupContact/*");

  registerAction(DymRupContactAction, "add_aux_kernel");
  registerAction(DymRupContactAction, "add_aux_variable");
  registerAction(DymRupContactAction, "add_dirac_kernel");

// Don't know what to do Uncomment Error Already regestered 
  // registerTask("output_penetration_info_vars", false);
  // registerAction(DymRupContactAction, "output_penetration_info_vars");
  // syntax.addDependency("output_penetration_info_vars", "add_output");

  registerAction(ContactPenetrationAuxAction, "add_aux_kernel");
  registerAction(ContactPenetrationVarAction, "add_aux_variable");

  registerAction(ContactPressureAuxAction, "add_aux_kernel");
  registerAction(ContactPressureVarAction, "add_aux_variable");

  registerAction(NodalAreaAction, "add_user_object");
  registerAction(NodalAreaVarAction, "add_aux_variable");
}
