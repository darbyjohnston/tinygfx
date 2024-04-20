# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

def members():
    s2 = tg.Size2I()
    assert s2[0] == 0
    assert s2[1] == 0
    assert not s2.isValid()
    s3 = tg.Size3F()
    assert s3[0] == 0
    assert s3[1] == 0
    assert s3[2] == 0
    assert not s3.isValid()
    
    s2 = tg.Size2I(1, 2)
    assert s2.w == 1
    assert s2.h == 2
    s3 = tg.Size3F(1, 2, 3)
    assert s3.w == 1
    assert s3.h == 2
    assert s3.d == 3
    
    s2 = tg.Size2I()
    s2[0] = 1
    s2[1] = 2
    assert s2[0] == 1
    assert s2[1] == 2
    s3 = tg.Size3F()
    s3[0] = 1
    s3[1] = 2
    s3[2] = 3
    assert s3[0] == 1
    assert s3[1] == 2
    assert s3[2] == 3

def functions():
    s2 = tg.Size2I(2, 1)
    assert 2 == tg.aspectRatio(s2)
    s2 = tg.Size2F(2, 1)
    assert 2 == tg.aspectRatio(s2)
    
    s2 = tg.Size2F(1, 2)
    assert 2 == tg.area(s2)
    
    s3 = tg.Size3F(1, 2, 3)
    assert 6 == tg.volume(s3)

def operators():
    s2 = tg.Size2I(1, 2)
    s2a = s2 + 1
    s2b = s2 - 1
    assert tg.Size2I(2, 3) == s2a
    assert tg.Size2I(0, 1) == s2b

    assert tg.Size2I(1, 2) == tg.Size2I(1, 2)
    assert tg.Size2I(1, 2) != tg.Size2I(2, 1)

def run():
    members()
    functions()
    operators()
