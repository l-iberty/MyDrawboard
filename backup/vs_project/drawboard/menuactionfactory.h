#ifndef MENUACTIONFACTORY_H
#define MENUACTIONFACTORY_H

#include <QtWidgets/QAction>
#include "pluginloader.h"

class MenuActionFactory {
public:
	MenuActionFactory();
	~MenuActionFactory();
	QAction* createMenuAction(int type, QObject* parent);
	int getMenuActionNum();
private:
	vector<string> m_PluginNames;
	PluginLoader* m_PluginLoader;
};

#endif // MENUACTIONFACTORY_H
