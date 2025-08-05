#ifndef SIZE_CONTROLLER_HPP
#define SIZE_CONTROLLER_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace softadastra::commerce::sizes
{
    void SizeController(crow::App<crow::CORSHandler> &app);
}

#endif