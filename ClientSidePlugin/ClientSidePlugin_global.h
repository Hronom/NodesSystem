#ifndef CLIENTSIDEPLUGIN_GLOBAL_H
#define CLIENTSIDEPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CLIENTSIDEPLUGIN_LIBRARY)
#  define CLIENTSIDEPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLIENTSIDEPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLIENTSIDEPLUGIN_GLOBAL_H