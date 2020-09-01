#ifndef CBVARIANT_H
#define CBVARIANT_H
#include <QVariant>
#include <QMap>
#include <QObject>
#include <QDebug>
/**
  * USING_MACROS_REG==1 使用宏名注册
  * USING_MACROS_REG==0 需要手动include头文件，反向依赖，进行注册
  **/
#define USING_MACROS_REG 1 //是否使用宏快速注册

#if USING_MACROS_REG
#define AL_DECLARE_VARIANT(Class) \
Q_DECLARE_METATYPE(Class)\
struct VariantRegisterHelper##Class \
{ \
    VariantRegisterHelper##Class() \
    { \
        Variant::registerClass<Class>(#Class); \
    } \
}; \
const VariantRegisterHelper##Class RegisterHelper##Class;//TODO:using const to register may waste memory

using Var_Type = QString;
extern QMap<int, Var_Type> m_userEnumMap;//metaID - className，可改为元组以兼容手动注册版本
class Variant
{
public:
    Variant(){}

    /**
     * @brief type: cover inline QVariant::type()const{}
     * if not Var_Type, will return Variant_InvalidUserType(1025);
     *
     */
    inline Var_Type getUserType() const{
        return (Var_Type)m_userEnumMap.value(m_data.userType(), "Variant_InvalidUserType");
    }

    template<typename T>
    inline void setValueR(const T &val)
    {
#ifdef ODEBUG
        int id = qMetaTypeId<T>();
        if(id >= QVariant::UserType){
            Q_ASSERT_X(id > QVariant::UserType, "Variant::setValueR()",
                       "This type does not resgiter as metaType,\
                       please register it in [void Variant::resgisterUserTypes()]");
                    Q_ASSERT(m_userEnumMap.contains(id));
            //qDebug()<<"Variant::setValueR, User type:"<<QMetaType::typeName(id);
        }else{
            //qDebug()<<"Variant::setValueR, Qt type:"<<QMetaType::typeName(id);
        }
#endif
        m_data.setValue(val);
    }

    template<typename T>
    inline T value() const
    {
        return m_data.value<T>();
    }

    inline bool isValid() const{
        return m_data.isValid();
    }

    inline void operator =(const Variant &var){
        m_data = var.m_data;
    }
    QVariant toQtVariant() const{return m_data;}
public:
    template<typename T>
    static void registerClass(QString className)
    {
        int typeID = qRegisterMetaType<T>();
        Q_ASSERT(typeID > QMetaType::User);
        Q_ASSERT(typeID == qMetaTypeId<T>());
//        Q_ASSERT(!m_userEnumMap.contains(typeID));
        if(!m_userEnumMap.contains(typeID))
            m_userEnumMap.insert(typeID, className);
        return ;
    }
private:
    QVariant m_data = QVariant();
};

#else //手动注册，比较麻烦
#define AL_DECLARE_VARIANT(Class) Q_DECLARE_METATYPE(Class)

struct tMeta_info_test{
    QString msg;
};
AL_DECLARE_VARIANT(tMeta_info_test)

extern QMap<int, int> m_userEnumMap;
class Variant
{
public:
    enum Var_Type {
        Variant_InvalidUserType = QVariant::UserType+1,
        meta_info_test,

    };

    Variant(){}

    /**
     * @brief type: cover inline QVariant::type()const{}
     * if not Var_Type, will return Variant_InvalidUserType(1025);
     *
     */
    inline Var_Type getUserType() const{
        return (Var_Type)m_userEnumMap.value(m_data.userType(), Variant_InvalidUserType);
    }

    template<typename T>
    inline void setValueR(const T &val);

    template<typename T>
    inline T value() const;

    inline bool isValid() const{
        return m_data.isValid();
    }

    inline void operator =(const Variant &var){
        m_data = var.m_data;
    }
    QVariant toQtVariant() const{return m_data;}
public:

    static void resgisterUserTypes();

    template<typename T>
    static bool registerUserType(Var_Type t);
private:
    QVariant m_data = QVariant();
};

template<typename T>
inline T Variant::value() const
{
    return m_data.value<T>();
}

template<typename T>
inline bool Variant::registerUserType(Variant::Var_Type t){
    int typeID = qRegisterMetaType<T>();
    Q_ASSERT(typeID > QMetaType::User);
    Q_ASSERT(typeID == qMetaTypeId<T>());
    Q_ASSERT(!m_userEnumMap.contains(typeID));
    m_userEnumMap.insert(typeID, t);
    return true;
}

template<typename T>
void Variant::setValueR(const T &val)
{
#ifdef ODEBUG
    int id = qMetaTypeId<T>();
    if(id >= QVariant::UserType){
        Q_ASSERT_X(id > QVariant::UserType, "Variant::setValueR()",
                   "This type does not resgiter as metaType,\
                     please register it in [void Variant::resgisterUserTypes()]");
        Q_ASSERT(m_userEnumMap.contains(id));
        //qDebug()<<"Variant::setValueR, User type:"<<QMetaType::typeName(id);
    }else{
        //qDebug()<<"Variant::setValueR, Qt type:"<<QMetaType::typeName(id);
    }
#endif
    m_data.setValue(val);
}
#endif //USING_MACROS_REG
#endif // CBVARIANT_H
