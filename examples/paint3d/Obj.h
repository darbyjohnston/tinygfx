// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Mesh.h>

#include <memory>
#include <string>

namespace tg
{
    class Mesh;

    //! Wavefront .obj reader.
    std::shared_ptr<geom::Mesh3D> readObj(const std::string&);
}
