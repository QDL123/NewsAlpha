#include "Ctrl.h"
void Ctrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    bool success = false;
    if (json) {
        std::cout << (*json)["tick"].asString() << std::endl;
        const Json::Value articles = (*json)["text"];
        for (int i = 0; i < articles.size(); ++i) {
            std::cout << articles[i].asString() << std::endl;
        }
        success = true;
    } else {
        std::cout << "FUCK WITH ME" << std::endl;
    }

    Json::Value ret;
    ret["result"] = "ok";
    if (success) {
        ret["clay"] = "fuck u";
    } else {
        ret["clay"] = "fuck u more bitch";
    }
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
