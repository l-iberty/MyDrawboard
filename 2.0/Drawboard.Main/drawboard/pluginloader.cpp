#include "pluginloader.h"

PluginLoader::PluginLoader() {
	bool bSuccess = false;
	
	if (getDllFilePaths(PLUGIN_DIR, m_LibPaths)) { // get DLL paths
		 // get DLL module handle
		for (int i = 0;i < m_LibPaths.size();i++) {
			HMODULE hMod = LoadLibraryA(m_LibPaths.at(i).c_str());
			if (hMod != NULL)
				m_HModList.push_back(hMod);
		}
		bSuccess = true;
	}
	if (!bSuccess)
		MessageBox(0, TEXT("Error loading plugins"), TEXT("ERROR"), MB_ICONERROR);
}

PluginLoader::~PluginLoader() {
	for (int i = 0;i < m_HModList.size();i++)
		FreeLibrary(m_HModList.at(i));
}

bool PluginLoader::getDllFilePaths(char *path, vector<string> &paths) {
	int hFile;
	struct _finddata_t fileinfo;

	if ((hFile = _findfirst(path, &fileinfo)) != -1) {
		do {
			// 不是文件夹
			if (!(fileinfo.attrib & _A_SUBDIR)) {
				string filespec = string(path);
				filespec = filespec.substr(0, filespec.length() - 1);
				filespec.append(fileinfo.name);
				paths.push_back(filespec);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		return true;
	}
	return false;
}

vector<string>& PluginLoader::getPluginNames() {
	char szName[MAX_PATH] = { 0 };

	for (int i = 0;i < m_HModList.size();i++) {
		HMODULE hLibMod = m_HModList.at(i);
		PLUGIN_PROC_NAME getPluginName = (PLUGIN_PROC_NAME)
			GetProcAddress(hLibMod, "getPluginName");
		if (getPluginName != NULL) {
			getPluginName(szName);
			m_PluginNames.push_back(szName);
		}
	}
	return m_PluginNames;
}

vector<QIcon*>& PluginLoader::getPluginIcons() {
	for (int i = 0;i < m_HModList.size();i++) {
		HMODULE hLibMod = m_HModList.at(i);
		PLUGIN_PROC_ICON getPluginIcon = (PLUGIN_PROC_ICON)
			GetProcAddress(hLibMod, "getPluginIcon");
		if (getPluginIcon != NULL)
			m_PluginIcons.push_back(getPluginIcon());
	}
	return m_PluginIcons;
}

QList<HMODULE>& PluginLoader::getDllModList() {
	return m_HModList;
}
