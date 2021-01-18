#include "Ctrl.h"
void Ctrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    if (json) {
        std::cout << (*json)["tick"].asString() << std::endl;
        const Json::Value articles = (*json)["text"];
        for (int i = 0; i < articles.size(); ++i) {
            std::cout << articles[i].asString() << std::endl;
        }
        // TODO: Send articles to sen
    } else {
        std::cout << "NO JSON was received" << std::endl;
        Json::Value ret;
        ret["message"] = "Error: No JSON received.";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        // TODO: Find a way to send a status 400 or other code communicating bad request
        callback(resp);
    }

    // Perform Price derivative analysis
    

    Json::Value ret;
    ret["Did we do it?"] = "We did!";

    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
