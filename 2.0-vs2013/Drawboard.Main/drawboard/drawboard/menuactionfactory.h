#ifndef MENUACTIONFACTORY_H
#define MENUACTIONFACTORY_H

#include "pluginloader.h"
#include <QtWidgets/QAction>

class MenuActionFactory {
public:
  MenuActionFactory(PluginLoader &pluginLoader);
  ~MenuActionFactory();
  QAction *createMenuAction(int type, QObject *parent);
  QIcon *getMenuActionIcon(int type);
  int getMenuActionNum();

private:
  vector<string> m_PluginNames;
  vector<QIcon *> m_PluginIcons;
};

#endif // MENUACTIONFACTORY_H
