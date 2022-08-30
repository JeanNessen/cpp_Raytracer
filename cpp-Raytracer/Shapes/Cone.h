#pragma once

#include "shape.h"

class cone final : public shape
{
public:
	cone();

	[[nodiscard]] vector local_normal_at(point pLocalPoint) const override;

	double minimum = -std::numeric_limits<double>::infinity();
	double maximum = std::numeric_limits<double>::infinity();

	bool closed = false;
private:

};

using cone_ptr = std::shared_ptr<cone>;