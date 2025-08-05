#ifndef COLOR_CONTROLLER_HPP
#define COLOR_CONTROLLER_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace softadastra::commerce::colors
{
    void ColorController(crow::App<crow::CORSHandler> &app);
}

#endif