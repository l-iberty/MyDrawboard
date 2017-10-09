#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <Windows.h>
#include <QtGui\qevent.h>
#include "shape.h"

using namespace std;

#define PLUGIN_DIR ".\\plugins\\*"

class PluginLoader {
private:
	vector<string> dll_paths; // DLL �ļ��ľ���·��
	vector<string> dll_names; // DLL �ļ���, ����·��
	vector<string> plugin_names; // �����
	QList<HMODULE> hModList; // DLL ģ����
	
	// This routine is called only by constuctor.
	bool getDllFilePaths(char *path, vector<string> &paths);

public:
	PluginLoader();
	~PluginLoader();
	vector<string> getPluginNames();
	QList<HMODULE> getDllModList();
};

#endif // PLUGINLOADER_H