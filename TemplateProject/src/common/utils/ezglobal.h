/**
  *	@brief
  *	@author	adam
  *	@date	2016/6/22
  */


#ifndef EZGLOBAL_H
#define EZGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore/qsharedpointer.h>

/*!
 *  Q_DECLARE_PRIVATE and d_ptr
 *
*/
#define EZ_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    QSharedPointer<Class##Private> d_ptr;

#define EZINSTANCE_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    Class##Private *d_ptr;

/*!
 *  Q_DECLARE_PUBLIC and q_ptr
 *
*/
#define EZ_DECLARE_PUBLIC(Class) \
    private: \
    Q_DECLARE_PUBLIC(Class) \
    Class* q_ptr;

#ifdef EZTest
#define EZ_UNIT_TEST(Class)\
    private: \
    friend class Class##Test;
#else
#define EZ_UNIT_TEST(Class)
#endif

#define EZ_SAFE_DELETE(p) do { if(p) { delete (p); (p) = 0; } } while(0)

#define TopicMaxLen 120

#endif // EZGLOBAL_H
