#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H
#include <QObject>
#include <QString>
#include <utils/variant.h>
struct t_VariantTest{
    QString str;
};
AL_DECLARE_VARIANT(t_VariantTest)

struct t_Error{
    QString str;
};

#endif // MYSTRUCTS_H
