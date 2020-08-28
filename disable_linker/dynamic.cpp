#include "dynamic.h"
#include "static.h"
Informer& globalGetter() {
    return g_s;
}
