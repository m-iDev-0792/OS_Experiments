/****************************************************************************
** Meta object code from reading C++ file 'scheduleview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scheduleview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scheduleview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScheduleView_t {
    QByteArrayData data[10];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScheduleView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScheduleView_t qt_meta_stringdata_ScheduleView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ScheduleView"
QT_MOC_LITERAL(1, 13, 10), // "paintEvent"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "QPaintEvent*"
QT_MOC_LITERAL(4, 38, 1), // "e"
QT_MOC_LITERAL(5, 40, 11), // "getDarwData"
QT_MOC_LITERAL(6, 52, 15), // "vector<QString>"
QT_MOC_LITERAL(7, 68, 9), // "taskNames"
QT_MOC_LITERAL(8, 78, 14), // "vector<RunMsg>"
QT_MOC_LITERAL(9, 93, 7) // "runMsgs"

    },
    "ScheduleView\0paintEvent\0\0QPaintEvent*\0"
    "e\0getDarwData\0vector<QString>\0taskNames\0"
    "vector<RunMsg>\0runMsgs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScheduleView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    2,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,

       0        // eod
};

void ScheduleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScheduleView *_t = static_cast<ScheduleView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 1: _t->getDarwData((*reinterpret_cast< vector<QString>(*)>(_a[1])),(*reinterpret_cast< vector<RunMsg>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ScheduleView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScheduleView.data,
      qt_meta_data_ScheduleView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScheduleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScheduleView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScheduleView.stringdata0))
        return static_cast<void*>(const_cast< ScheduleView*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScheduleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
