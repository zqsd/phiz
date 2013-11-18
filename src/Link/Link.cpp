#include "Link.hpp"

namespace Phiz
{

Link::Link(Body* a, Body* b)
    : _a(a), _b(b)
{
}

Link::~Link()
{
}

}