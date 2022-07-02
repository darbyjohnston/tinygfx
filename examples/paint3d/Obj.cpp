// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Obj.h"

#include "Mesh.h"

#include <tgCore/Error.h>
#include <tgCore/FileIO.h>
#include <tgCore/String.h>

#include <sstream>

namespace tg
{
    std::shared_ptr<Mesh> readObj(const std::string& fileName)
    {
        auto out = std::shared_ptr<Mesh>(new Mesh);

        auto io = file::FileIO::create();
        io->open(fileName, file::Mode::Read);

        while (!io->isEOF())
        {
            char buf[string::cBufferSize];
            file::readLine(io, buf);

            std::stringstream ss(buf);
            std::string type;
            ss >> type;
            if ("v" == type)
            {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                out->v.push_back(math::Vector3f(x, y, z));
            }
            else if ("vt" == type)
            {
                float u, v;
                ss >> u;
                ss >> v;
                out->t.push_back(math::Vector2f(u, v));
            }
            else if ("vn" == type)
            {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                out->n.push_back(math::Vector3f(x, y, z));
            }
            else if ("f" == type)
            {
                std::vector<size_t> vList;
                std::vector<size_t> tList;
                std::vector<size_t> nList;
                while (!ss.eof())
                {
                    std::string s;
                    ss >> s;
                    if ('#' == s[0])
                    {
                        break;
                    }
                    const auto split = string::split(s, '/', true);
                    size_t v = 0;
                    size_t t = 0;
                    size_t n = 0;
                    if (split.size() > 0 && !split[0].empty())
                    {
                        std::stringstream ss2(split[0]);
                        ss2 >> v;
                    }
                    if (split.size() > 1 && !split[1].empty())
                    {
                        std::stringstream ss2(split[1]);
                        ss2 >> t;
                    }
                    if (split.size() > 2 && !split[2].empty())
                    {
                        std::stringstream ss2(split[2]);
                        ss2 >> n;
                    }
                    vList.push_back(v);
                    tList.push_back(t);
                    nList.push_back(n);
                }
                if (vList.size() >= 3)
                {
                    for (size_t i = 1; i < vList.size() - 1; ++i)
                    {
                        Mesh::Triangle triangle;
                        triangle.v[0] = vList[0];
                        triangle.v[1] = vList[i];
                        triangle.v[2] = vList[i + 1];
                        triangle.t[0] = tList[0];
                        triangle.t[1] = tList[i];
                        triangle.t[2] = tList[i + 1];
                        triangle.n[0] = nList[0];
                        triangle.n[1] = nList[i];
                        triangle.n[2] = nList[i + 1];
                        out->triangles.push_back(triangle);
                    }
                }
            }
        }

        return out;
    }
}
