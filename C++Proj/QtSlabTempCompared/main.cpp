#include <QApplication>
#include "slabtempcomaredrender.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SlabTempComaredRender render;
    render.show();
    return QApplication::exec();
}
