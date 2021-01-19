#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>
#include <trantor/net/EventLoop.h>


#include "Ctrl.h"
#include "../params.h"

using namespace std::chrono_literals;

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

    auto wsPtr = WebSocketClient::newWebSocketClient("wss://paper-api.alpaca.markets");
    auto req2 = HttpRequest::newHttpRequest();
    bool continually = true;
    ptr = wsPtr;
    rptr = req2;
    req2->setPath("/stream");

    wsPtr->setMessageHandler([continually](const std::string &message,
                                           const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
        std::cout << "new message:" << message << std::endl;
        if (type == WebSocketMessageType::Pong)
        {
            std::cout << "recv a pong" << std::endl;
            if (!continually) {
                wsPtr->getLoop()->quit();
            } 
        } else {
            std::cout << message << std::endl;

            if (!authenticated) {
                const char* action_mess = "{ \"action\": \"listen\", \"data\": { \"streams\": [\"trade_updates\"] } }";
                wsPtr->getConnection()->send(action_mess);
                authenticated = true;
            }
        }
    });

    wsPtr->setConnectionClosedHandler([](const WebSocketClientPtr &wsPtr) {
        std::cout << "ws closed!" << std::endl;
    });
    wsPtr->connectToServer(req2,
                           [continually](ReqResult r,
                                         const HttpResponsePtr &resp,
                                         const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   std::cout << "ws connected!" << std::endl;
                                   wsPtr->getConnection()->setPingMessage("",
                                                                          2s);
                                   const char* listen_mess = "{ \"action\": \"authenticate\", \"data\": { \"key_id\": \"PK5PEMKJ664O67M3EX02\", \"secret_key\": \"zORKTwg211jUsxrRIVY51H75AzaEA81E28IqAExX\" } }";
                                   wsPtr->getConnection()->send(listen_mess);
                               }
                               else
                               {
                                   std::cout << "ws failed!" << std::endl;
                                //    if (!continually) {
                                    exit(1);
                                //    }
                               }
                           }); 

    // Perform Price derivative analysis
    int buy_sell_indicator;

    if(buy_sell_indicator > buy_threshold) {
        // Decide how much to buy
        // buy
        // continue streaming data until exit
    } else if(buy_sell_indicator < sell_threshold) {
        // Decide how much to sell
        // sell
    }

    Json::Value ret;
    ret["Did we do it?"] = "We did!";

    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
