/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: T10-AspectParam.cpp
@Time: 2021/10/4 11:23 下午
@Desc: 本例主要演示，在切面流程中加入自定义参数的逻辑
***************************/

#include "MyGNode/MyNode1.h"
#include "MyGNode/MyNode2.h"
#include "MyGNode/MyWriteParamNode.h"
#include "MyGAspect/MyConnAspect.h"
#include "MyGParam/MyConnAspectParam.h"
#include "MyGAspect/MyTimerAspect.h"
#include "MyGAspect/MyPipeLineParamAspect.h"

using namespace CGraph;

void tutorial_aspect_param() {
    GPipelinePtr pipeline = GPipelineFactory::create();
    MyConnAspectParam paramA;
    paramA.ip = "127.0.0.1";
    paramA.port = 6666;

    MyConnAspectParam paramB;
    paramB.ip = "255.255.255.255";
    paramB.port = 9999;

    GElementPtr a, b, c = nullptr;

    pipeline->registerGElement<MyNode1>(&a, {}, "nodeA", 1);
    pipeline->registerGElement<MyNode2>(&b, {a}, "nodeB", 1);
    pipeline->registerGElement<MyWriteParamNode>(&c, {b}, "nodeC", 2);

    /** 给a节点添加 MyConnAspect 切面的逻辑，并且传入 paramA 相关参数 */
    a->addGAspect<MyConnAspect, MyConnAspectParam>(&paramA);

    /** 给b节点添加多个切面，有的传递参数，有的不传递 */
    b->addGAspect<MyConnAspect, MyConnAspectParam>(&paramB)->addGAspect<MyTimerAspect>();

    /** 在切面中，获取pipeline中的参数，并且进行对应处理 */
    c->addGAspect<MyPipeLineParamAspect>();

    pipeline->process();
    GPipelineFactory::clear();
}

int main() {
    tutorial_aspect_param();
    return 0;
}
