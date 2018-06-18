#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#define _CRT_SECURE_NO_WARINGS
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <Windows.h>
#include "shape.h"

using namespace std;

#define PLUGIN_DIR ".\\plugins\\*"

typedef void (*PLUGIN_PROC_NAME)(char *);
typedef QIcon* (*PLUGIN_PROC_ICON)();

class PluginLoader {
public:
	PluginLoader();
	~PluginLoader();
	vector<string>& getPluginNames();
	vector<QIcon*>& getPluginIcons();
	QList<HMODULE>& getDllModList();
private:
	bool getDllFilePaths(char *path, vector<string> &paths);
private:
	vector<string> m_LibPaths; // DLL �ļ��ľ���·��
	vector<string> m_LibNames; // DLL �ļ���, ����·��
	vector<string> m_PluginNames; // �����
	vector<QIcon*> m_PluginIcons; // ���ͼ��
	QList<HMODULE> m_HModList; // DLL ģ����
};

#endif // PLUGINLOADER_H
