#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class Ctrl:public drogon::HttpSimpleController<Ctrl>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/analyze", Post);

    PATH_LIST_END
};
