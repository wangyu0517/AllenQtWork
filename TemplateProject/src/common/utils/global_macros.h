#ifndef _GLOBAL_MACROS_H_
#define _GLOBAL_MACROS_H_

#include <QtCore/qglobal.h>
#include <QtCore/qsharedpointer.h>

/*!
 *  NONEQOBJECT_DECLARE_PRIVATE and d_ptr
 * use this macro NONE_QOBJECT_DECLARE_PRIVATE when your class don't inherit from QObject,
 * using QSharedPointer to free private class
*/
#define AL_NONEQOBJECT_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    QSharedPointer<Class##Private> d_ptr;

/*!
 *  QOBJECT_DECLARE_PRIVATE
 * use this macro "QOBJECT_DECLARE_PRIVATE" when your private class inherit from QObject.
 * QObject while help you free the private class,
 * or free the private class by yourself
*/
#define AL_QOBJECT_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    Class##Private *d_ptr;

/*!
 *  Q_DECLARE_PUBLIC and q_ptr
 *
*/
#define AL_DECLARE_PUBLIC(Class) \
    private: \
    Q_DECLARE_PUBLIC(Class) \
    Class* q_ptr;

#ifdef AL_UNIT_TEST
#define AL_DECLARE_TEST(Class)\
    private: \
    friend class Class##Test;
#else
#define AL_DECLARE_TEST(Class)
#endif

#define SAFE_DELETE(p) do { if(p) { delete (p); (p) = 0; } } while(0)


#endif //_GLOBAL_MACROS_H_

