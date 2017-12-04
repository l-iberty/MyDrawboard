#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <Windows.h>
#include "shape.h"

using namespace std;

#define PLUGIN_DIR ".\\plugins\\*"

class PluginLoader {
public:
	PluginLoader();
	~PluginLoader();
	vector<string> getPluginNames();
	QList<HMODULE> getDllModList();
private:
	vector<string> dll_paths; // DLL 文件的绝对路径
	vector<string> dll_names; // DLL 文件名, 不含路径
	vector<string> plugin_names; // 插件名
	QList<HMODULE> hModList; // DLL 模块句柄
	bool getDllFilePaths(char *path, vector<string> &paths);
};

#endif // PLUGINLOADER_H
