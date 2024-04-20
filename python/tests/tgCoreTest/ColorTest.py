# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

def members():
    c1 = tg.Color1F()
    assert c1[0] == 0
    c2 = tg.Color2F()
    assert c2[0] == 0
    assert c2[1] == 0
    c3 = tg.Color3F()
    assert c3[0] == 0
    assert c3[1] == 0
    assert c3[2] == 0
    c4 = tg.Color4F()
    assert c4[0] == 0
    assert c4[1] == 0
    assert c4[2] == 0
    assert c4[3] == 0
    
    c1 = tg.Color1F(1)
    assert c1.l == 1
    c2 = tg.Color2F(1, 1)
    assert c2.l == 1
    assert c2.a == 1
    c3 = tg.Color3F(1, 1, 1)
    assert c3.r == 1
    assert c3.g == 1
    assert c3.b == 1
    c4 = tg.Color4F(1, 1, 1, 1)
    assert c4.r == 1
    assert c4.g == 1
    assert c4.b == 1
    assert c4.a == 1

    c1 = tg.Color1F()
    c1[0] = 1
    assert c1[0] == 1
    c2 = tg.Color2F()
    c2[0] = 1
    assert c2[0] == 1
    c3 = tg.Color3F()
    c3[0] = 1
    assert c3[0] == 1
    c4 = tg.Color4F()
    c4[0] = 1
    assert c4[0] == 1

def operators():
    assert tg.Color1F(1) == tg.Color1F(1)
    assert tg.Color1F(1) != tg.Color1F(0)

def run():
    members()
    operators()