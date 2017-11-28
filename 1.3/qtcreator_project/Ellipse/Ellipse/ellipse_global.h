#ifndef ELLIPSE_GLOBAL_H
#define ELLIPSE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ELLIPSE_LIBRARY)
#  define ELLIPSESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ELLIPSESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ELLIPSE_GLOBAL_H
