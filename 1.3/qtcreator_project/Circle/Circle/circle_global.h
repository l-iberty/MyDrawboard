#ifndef CIRCLE_GLOBAL_H
#define CIRCLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CIRCLE_LIBRARY)
#  define CIRCLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CIRCLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CIRCLE_GLOBAL_H
