#ifndef PPMS_GLOBAL_H
#define PPMS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PPMS_LIBRARY)
#  define PPMS_EXPORT Q_DECL_EXPORT
#else
#  define PPMS_EXPORT Q_DECL_IMPORT
#endif

#endif // PPMS_GLOBAL_H
