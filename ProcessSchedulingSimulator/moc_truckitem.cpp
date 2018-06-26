/****************************************************************************
** Meta object code from reading C++ file 'truckitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "truckitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'truckitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TruckItem_t {
    QByteArrayData data[4];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TruckItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TruckItem_t qt_meta_stringdata_TruckItem = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TruckItem"
QT_MOC_LITERAL(1, 10, 8), // "rotation"
QT_MOC_LITERAL(2, 19, 3), // "pos"
QT_MOC_LITERAL(3, 23, 8) // "quantity"

    },
    "TruckItem\0rotation\0pos\0quantity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TruckItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QReal, 0x00095103,
       2, QMetaType::QPointF, 0x00095103,
       3, QMetaType::Float, 0x00095103,

       0        // eod
};

void TruckItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        TruckItem *_t = static_cast<TruckItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->rotation(); break;
        case 1: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->quantity(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        TruckItem *_t = static_cast<TruckItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRotation(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        case 2: _t->setQuantity(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TruckItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TruckItem.data,
      qt_meta_data_TruckItem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TruckItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TruckItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TruckItem.stringdata0))
        return static_cast<void*>(const_cast< TruckItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< TruckItem*>(this));
    return QObject::qt_metacast(_clname);
}

int TruckItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
