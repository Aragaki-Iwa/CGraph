/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: MyParamCondition.h
@Time: 2021/6/19 11:58 下午
@Desc: 
***************************/

#ifndef CGRAPH_MYPARAMCONDITION_H
#define CGRAPH_MYPARAMCONDITION_H

#include "../../src/CGraph.h"
#include "../MyGParam/MyParam.h"

class MyParamCondition : public CGraph::GCondition {

public:
    /**
     * 在这里主要演示condition中可以通过获取上方参数的形式，
     * 来决定执行执行当前的第几个逻辑
     * @return
     */
    int choose () override {
        MyParam* myParam = this->getGParam<MyParam>("param1");
        if (nullptr == myParam) {
            return CGraph::GROUP_LAST_ELEMENT_INDEX;    // 如果没获取到，固定执行最后一个逻辑
        }

        int cnt = 0;
        {
            CGraph::CGRAPH_PARAM_READ_CODE_BLOCK(myParam)    // 如果当前算子，跟其他相关依赖算子不存在并行关系，则参数可以直接使用，不需要加锁
            cnt = myParam->iCount;
        }
        return (cnt % getRange());
    }
};

#endif //CGRAPH_MYPARAMCONDITION_H
