#pragma once
#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>
#include <trantor/net/EventLoop.h>

static drogon::WebSocketClientPtr ptr;
static drogon::HttpRequestPtr rptr;
static bool authenticated = false;

static int buy_threshold = 0;

static int sell_threshold = 0;
