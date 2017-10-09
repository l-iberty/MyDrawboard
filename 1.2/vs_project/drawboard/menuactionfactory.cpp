#include "menuactionfactory.h"

MenuActionFactory::MenuActionFactory() {
	PluginLoader* pluginLoader = new PluginLoader();
	plugin_names = pluginLoader->getPluginNames();
}

MenuActionFactory::~MenuActionFactory() {

}

QAction* MenuActionFactory::createMenuAction(int type, QObject* parent) {
	QAction* action = new QAction(plugin_names.at(type).c_str(), parent);
	return action;
}

int MenuActionFactory::getMenuActionNum() {
	return plugin_names.size();
}

