#include "shapefactory.h"

ShapeFactory::ShapeFactory() {
	PluginLoader* pluginLoader = new PluginLoader();
	hModList = pluginLoader->getDllModList();

	for (int i = 0;i < hModList.size();i++) {
		HMODULE hDllMod = hModList.at(i);
		if (hDllMod != NULL) {
			PPROC_INSTANCE proc_instance = (PPROC_INSTANCE)GetProcAddress(
				hDllMod, PROC_INSTANCE);
			PPROC_GETDULSHAPEINSTANCE proc_getDulShapeInstance = (PPROC_GETDULSHAPEINSTANCE)GetProcAddress(
				hDllMod, PROC_GETDULSHAPEINSTANCE);
			if (proc_instance && proc_getDulShapeInstance) {
				proc_instance_list.push_back(proc_instance);
				proc_getDulShapeInstance_list.push_back(proc_getDulShapeInstance);
			}
			else {
				MessageBoxA(0, "GetProcAddress Failed", "ERROR", MB_ICONERROR);
			}
		}
		else {
			MessageBoxA(0, "Cannot load library!", "ERROR", MB_ICONERROR);
		}
	}
}

ShapeFactory::~ShapeFactory() {

}

Shape* ShapeFactory::createShape(int type) {
	PPROC_INSTANCE proc_instance = proc_instance_list.at(type);
	Shape* shape = proc_instance();
	return shape;
}

Shape* ShapeFactory::createDulShape(int type, Shape& shape) {
	PPROC_GETDULSHAPEINSTANCE proc_getDulShapeInstance = proc_getDulShapeInstance_list.at(type);
	Shape* dulShape = proc_getDulShapeInstance(shape);
	return dulShape;
}

