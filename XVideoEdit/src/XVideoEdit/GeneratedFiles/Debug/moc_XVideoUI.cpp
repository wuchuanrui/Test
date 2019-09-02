/****************************************************************************
** Meta object code from reading C++ file 'XVideoUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XVideoUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XVideoUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_XVideoUI_t {
    QByteArrayData data[17];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XVideoUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XVideoUI_t qt_meta_stringdata_XVideoUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "XVideoUI"
QT_MOC_LITERAL(1, 9, 6), // "Export"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "Open"
QT_MOC_LITERAL(4, 22, 11), // "sliderPress"
QT_MOC_LITERAL(5, 34, 13), // "sliderRelease"
QT_MOC_LITERAL(6, 48, 6), // "setPos"
QT_MOC_LITERAL(7, 55, 3), // "set"
QT_MOC_LITERAL(8, 59, 9), // "exportEnd"
QT_MOC_LITERAL(9, 69, 5), // "Pause"
QT_MOC_LITERAL(10, 75, 4), // "Play"
QT_MOC_LITERAL(11, 80, 4), // "Mark"
QT_MOC_LITERAL(12, 85, 5), // "Blend"
QT_MOC_LITERAL(13, 91, 5), // "Merge"
QT_MOC_LITERAL(14, 97, 4), // "Left"
QT_MOC_LITERAL(15, 102, 3), // "pos"
QT_MOC_LITERAL(16, 106, 5) // "Right"

    },
    "XVideoUI\0Export\0\0Open\0sliderPress\0"
    "sliderRelease\0setPos\0set\0exportEnd\0"
    "Pause\0Play\0Mark\0Blend\0Merge\0Left\0pos\0"
    "Right"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XVideoUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    1,   88,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    0,   96,    2, 0x0a /* Public */,
      13,    0,   97,    2, 0x0a /* Public */,
      14,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void XVideoUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        XVideoUI *_t = static_cast<XVideoUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Export(); break;
        case 1: _t->Open(); break;
        case 2: _t->sliderPress(); break;
        case 3: _t->sliderRelease(); break;
        case 4: _t->setPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->set(); break;
        case 6: _t->exportEnd(); break;
        case 7: _t->Pause(); break;
        case 8: _t->Play(); break;
        case 9: _t->Mark(); break;
        case 10: _t->Blend(); break;
        case 11: _t->Merge(); break;
        case 12: _t->Left((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->Right((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject XVideoUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_XVideoUI.data,
      qt_meta_data_XVideoUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *XVideoUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XVideoUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_XVideoUI.stringdata0))
        return static_cast<void*>(const_cast< XVideoUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int XVideoUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
