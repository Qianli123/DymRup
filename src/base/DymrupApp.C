#include "DymrupApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

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
}

// External entry point for dynamic syntax association
extern "C" void DymrupApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { DymrupApp::associateSyntax(syntax, action_factory); }
void
DymrupApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
