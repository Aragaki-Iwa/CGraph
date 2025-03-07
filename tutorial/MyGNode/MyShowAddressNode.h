/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: MyShowAddressNode.h
@Time: 2021/10/31 12:50 上午
@Desc: 
***************************/

#ifndef CGRAPH_MYSHOWADDRESSNODE_H
#define CGRAPH_MYSHOWADDRESSNODE_H

#include "../../src/CGraph.h"
#include "../MyGParam/MyParam.h"

class MyShowAddressNode : public CGraph::GNode {

public:
    CSTATUS init() override {
        CSTATUS status = this->createGParam<MyParam>("param2");
        return status;
    }

    CSTATUS run () override {
        auto myParam = this->getGParam<MyParam>("param2");
        int cnt = 0;
        {
            CGraph::CGRAPH_PARAM_WRITE_CODE_BLOCK(myParam)
            cnt = ++myParam->iCount;
        }

        CGraph::CGRAPH_ECHO("singleton node run, name is [%s], this address is [0x%x], cnt is [%d].",
                            this->getName().c_str(), this, cnt);
        return STATUS_OK;
    }
};

#endif //CGRAPH_MYSHOWADDRESSNODE_H
