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
	vector<string> dll_paths; // DLL �ļ��ľ���·��
	vector<string> dll_names; // DLL �ļ���, ����·��
	vector<string> plugin_names; // �����
	QList<HMODULE> hModList; // DLL ģ����
	bool getDllFilePaths(char *path, vector<string> &paths);
};

#endif // PLUGINLOADER_H
