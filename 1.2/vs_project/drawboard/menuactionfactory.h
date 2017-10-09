#ifndef MENUACTIONFACTORY_H
#define MENUACTIONFACTORY_H

#include <QtWidgets\qaction.h>
#include "pluginloader.h"

class MenuActionFactory {
public:
	MenuActionFactory();
	~MenuActionFactory();
	QAction* createMenuAction(int type, QObject* parent);
	int getMenuActionNum();

private:
	vector<string> plugin_names;
};

#endif // MENUACTIONFACTORY_H
