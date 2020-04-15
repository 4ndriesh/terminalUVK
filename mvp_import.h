#ifndef MVP_IMPORT_H
#define MVP_IMPORT_H

//  SYB
#include "mvp_system.h"
#include "gtbuffers_udp_d2.h"
#include "modelgroupgorka.h"
#include "m_otceps.h"

class MVP_Import
{
public:
    MVP_Import();
    static MVP_Import* instance(){
           static MVP_Import one;
           return &one;

    }
    bool load(QString fn);
    ModelGroupGorka *gorka=nullptr;
};

#endif // MVP_IMPORT_H
