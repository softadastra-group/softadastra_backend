#pragma once
// 🧠 Configuration pour ASIO standalone
#define ASIO_STANDALONE
#define ASIO_HAS_STD_STRING_VIEW
#define ASIO_DISABLE_CONCEPTS

// 🔁 Compatibilité Crow avec l'ancien io_service
#define io_service io_context

#include <asio.hpp>

#include "crow/query_string.h"
#include "crow/http_parser_merged.h"
#include "crow/ci_map.h"
#include "crow/TinySHA1.hpp"
#include "crow/settings.h"
#include "crow/socket_adaptors.h"
#include "crow/json.h"
#include "crow/mustache.h"
#include "crow/logging.h"
#include "crow/task_timer.h"
#include "crow/utility.h"
#include "crow/common.h"
#include "crow/http_request.h"
#include "crow/websocket.h"
#include "crow/parser.h"
#include "crow/http_response.h"
#include "crow/multipart.h"
#include "crow/multipart_view.h"
#include "crow/routing.h"
#include "crow/middleware.h"
#include "crow/middleware_context.h"
#include "crow/compression.h"
#include "crow/http_connection.h"
#include "crow/http_server.h"
#include "crow/app.h"
