#ifndef POLYGON_GLOBAL_H
#define POLYGON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POLYGON_LIBRARY)
#  define POLYGONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define POLYGONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // POLYGON_GLOBAL_H
