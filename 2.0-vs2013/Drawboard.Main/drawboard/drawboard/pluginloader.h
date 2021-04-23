#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#define _CRT_SECURE_NO_WARINGS
#include "shape.h"
#include <Windows.h>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define PLUGIN_DIR ".\\plugins\\*"

typedef void (*PLUGIN_PROC_NAME)(char *);
typedef QIcon *(*PLUGIN_PROC_ICON)();

class PluginLoader {
public:
  PluginLoader();
  ~PluginLoader();
  vector<string> &getPluginNames();
  vector<QIcon *> &getPluginIcons();
  QList<HMODULE> &getDllModList();

private:
  bool getDllFilePaths(char *path, vector<string> &paths);

private:
  vector<string> m_LibPaths;     // DLL 文件的绝对路径
  vector<string> m_LibNames;     // DLL 文件名, 不含路径
  vector<string> m_PluginNames;  // 插件名
  vector<QIcon *> m_PluginIcons; // 插件图标
  QList<HMODULE> m_HModList;     // DLL 模块句柄
};

#endif // PLUGINLOADER_H
