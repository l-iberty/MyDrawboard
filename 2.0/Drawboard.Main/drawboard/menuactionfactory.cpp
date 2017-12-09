#include "menuactionfactory.h"

MenuActionFactory::MenuActionFactory() {
	m_PluginLoader = new PluginLoader();
	m_PluginNames = m_PluginLoader->getPluginNames();
}

MenuActionFactory::~MenuActionFactory() {
	if (m_PluginLoader != NULL) { delete m_PluginLoader; }
}

QAction* MenuActionFactory::createMenuAction(int type, QObject* parent) {
	QAction* action = new QAction(m_PluginNames.at(type).c_str(), parent);
	return action;
}

int MenuActionFactory::getMenuActionNum() {
	return m_PluginNames.size();
}
