# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

def members():
    b2 = tg.Box2I()
    assert b2.min == tg.V2I()
    assert b2.max == tg.V2I()
    b3 = tg.Box3F()
    assert b3.min == tg.V3F()
    assert b3.max == tg.V3F()
    
    min2 = tg.V2I(1, 2)
    max2 = tg.V2I(3, 4)
    b2 = tg.Box2I(min2, max2)
    assert b2.min == min2
    assert b2.max == max2
    assert 1 == b2.x()
    assert 2 == b2.y()
    assert 3 == b2.w()
    assert 3 == b2.h()
    min3 = tg.V3F(1, 2, 3)
    max3 = tg.V3F(4, 5, 6)
    b3 = tg.Box3F(min3, max3)
    assert b3.min == min3
    assert b3.max == max3
    assert 1 == b3.x()
    assert 2 == b3.y()
    assert 3 == b3.z()
    assert 3 == b3.w()
    assert 3 == b3.h()
    assert 3 == b3.d()
    
    size2 = tg.Size2I(3, 2)
    b2 = tg.Box2I(min2, size2)
    assert min2 == b2.min
    assert tg.V2I(3, 3) == b2.max
    assert size2 == b2.size()    
    min2 = tg.V2F(1, 2)
    size2 = tg.Size2F(3, 2)
    b2 = tg.Box2F(min2, size2)
    assert min2 == b2.min
    assert tg.V2F(4, 4) == b2.max
    assert size2 == b2.size()
    size3 = tg.Size3F(4, 5, 6)
    b3 = tg.Box3F(min3, size3)
    assert min3 == b3.min
    assert tg.V3F(5, 7, 9) == b3.max
    assert size3 == b3.size()

def functions():
    b3 = tg.Box3F(1, 2, 3, 4, 5, 6)
    c = tg.center(b3)
    assert tg.V3F(3, 4.5, 6) == c
    
    b2 = tg.Box2F(1, 2, 3, 4)
    a = tg.area(b2)
    assert 12 == a
    
    b3 = tg.Box3F(1, 2, 3, 4, 5, 6)
    v = tg.volume(b3)
    assert 120 == v
    
    b2 = tg.Box2I(0, 0, 3, 3)
    assert tg.contains(b2, tg.Box2I(0, 0, 1, 1))
    assert not tg.contains(b2, tg.Box2I(-1, -1, 1, 1))
    assert tg.contains(b2, tg.V2I(1, 1))
    assert not tg.contains(b2, tg.V2I(-1, -1))
    
    b2 = tg.Box2F(0, 0, 2, 2)
    assert tg.contains(b2, tg.Box2F(0, 0, 1, 1))
    assert not tg.contains(b2, tg.Box2F(-1, -1, 1, 1))
    assert tg.contains(b2, tg.V2F(1, 1))
    assert not tg.contains(b2, tg.V2F(-1, -1))
    
    b2 = tg.Box2I(0, 0, 3, 3)
    assert tg.intersects(b2, tg.Box2I(-1, -1, 2, 2))
    assert not tg.intersects(b2, tg.Box2I(-2, -2, 2, 2))
    b2a = tg.intersect(b2, tg.Box2I(-1, -1, 2, 2))
    assert tg.Box2I(0, 0, 1, 1) == b2a

    b2 = tg.Box2F(0, 0, 2, 2)
    assert tg.intersects(b2, tg.Box2F(-1, -1, 2, 2))
    assert not tg.intersects(b2, tg.Box2F(-2, -2, 1, 1))
    b2a = tg.intersect(b2, tg.Box2F(-1, -1, 2, 2))
    assert tg.Box2F(0, 0, 1, 1) == b2a
    
    b2 = tg.Box2I(1, 2, 3, 4)
    b2a = tg.expand(b2, tg.Box2I(1, 2, 4, 5))
    b2b = tg.expand(b2, tg.V2I(4, 5))
    assert tg.Box2I(1, 2, 4, 5) == b2a
    assert tg.Box2I(1, 2, 4, 4) == b2b
    
    b2 = tg.Box2I(1, 2, 3, 4)
    b2a = tg.margin(b2, tg.V2I(1, 2))
    b2b = tg.margin(b2, 1)
    b2c = tg.margin(b2, 1, 2, 3, 4)
    assert tg.Box2I(0, 0, 5, 8) == b2a
    assert tg.Box2I(0, 1, 5, 6) == b2b
    assert tg.Box2I(0, 0, 7, 10) == b2c

def operators():
    assert tg.Box2I(1, 2, 3, 4) == tg.Box2I(1, 2, 3, 4)
    assert tg.Box2I(1, 2, 3, 4) != tg.Box2I(4, 3, 2, 1)

def run():
    members()
    functions()
    operators()