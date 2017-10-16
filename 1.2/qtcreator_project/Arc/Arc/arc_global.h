#ifndef ARC_GLOBAL_H
#define ARC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ARC_LIBRARY)
#  define ARCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ARCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ARC_GLOBAL_H
