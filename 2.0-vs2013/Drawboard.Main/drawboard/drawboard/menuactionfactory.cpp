#include "menuactionfactory.h"

MenuActionFactory::MenuActionFactory(PluginLoader &pluginLoader) {
	m_PluginNames = pluginLoader.getPluginNames();
	m_PluginIcons = pluginLoader.getPluginIcons();
}

MenuActionFactory::~MenuActionFactory() {

}

QAction* MenuActionFactory::createMenuAction(int type, QObject* parent) {
	QAction* action = new QAction(m_PluginNames.at(type).c_str(), parent);
	return action;
}

QIcon* MenuActionFactory::getMenuActionIcon(int type) {
	return m_PluginIcons.at(type);
}

int MenuActionFactory::getMenuActionNum() {
	return m_PluginNames.size();
}
