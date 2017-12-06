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

typedef void(*PLUGIN_PROC_NAME)(char *);

class PluginLoader {
public:
	PluginLoader();
	~PluginLoader();
	vector<string> getPluginNames();
	QList<HMODULE> getDllModList();
private:
	vector<string> m_LibPaths; // DLL 文件的绝对路径
	vector<string> m_LibNames; // DLL 文件名, 不含路径
	vector<string> m_PluginNames; // 插件名
	QList<HMODULE> m_HModList; // DLL 模块句柄
	bool getDllFilePaths(char *path, vector<string> &paths);
};

#endif // PLUGINLOADER_H
