#include "variant.h"
#include <QDebug>

#if USING_MACROS_REG
QMap<int, Var_Type> m_userEnumMap;
#else
QMap<int, int> m_userEnumMap;
void Variant::resgisterUserTypes()
{
    registerUserType<tMeta_info_test>(meta_info_test);

}
#endif

