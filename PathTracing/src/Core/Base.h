#pragma once

#define BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)
