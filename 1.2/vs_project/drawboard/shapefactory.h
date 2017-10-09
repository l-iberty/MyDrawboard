#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <iostream>
#include <Windows.h>
#include <QtGui\qevent.h>
#include "shape.h"
#include "pluginloader.h"

#define PROC_INSTANCE										"?instance@@YAPAVShape@@XZ"
#define PROC_GETDULSHAPEINSTANCE			"?getDulShapeInstance@@YAPAVShape@@AAV1@@Z"

typedef Shape *(*PPROC_INSTANCE)();
typedef Shape *(*PPROC_GETDULSHAPEINSTANCE)(Shape &);

class ShapeFactory {
public:
	ShapeFactory();
	~ShapeFactory();
	Shape* createShape(int type);
	Shape* createDulShape(int type, Shape& shape);

private:
	QList<HMODULE> hModList; // DLL Ä£¿é¾ä±ú
	QList<PPROC_INSTANCE> proc_instance_list;
	QList<PPROC_GETDULSHAPEINSTANCE> proc_getDulShapeInstance_list;
};

#endif // SHAPEFACTORY_H
