#ifndef DYMRUPAPP_H
#define DYMRUPAPP_H

#include "MooseApp.h"

class DymrupApp;

template<>
InputParameters validParams<DymrupApp>();

class DymrupApp : public MooseApp
{
public:
  DymrupApp(InputParameters parameters);
  virtual ~DymrupApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* DYMRUPAPP_H */
