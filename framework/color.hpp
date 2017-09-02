// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{

  Color():
	r(0.0f),g(0.0f),b(0.0f){}

  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  bool operator==(Color const& other)
  {
    if(r==other.r and b==other.b and g==other.g)
      {
        return true;
      }
    else
      return false;
  }
    bool operator!=(Color const& other)
  {
    if(r==other.r and b==other.b and g==other.g)
      {
        return false;
      }
    else
      return true;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }
  Color operator*(float fl)
  {
    return Color(r*fl,b*fl,b*fl);
  }
   Color operator-(float fl)
  {
    return Color(r-fl,b-fl,b-fl);
  }
     Color operator+(float fl)
  {
    return Color(r+fl,b+fl,b+fl);
  }
bool operator>=(Color const& other)
  {
    if(r>=other.r and b>=other.b and g>=other.g)
      {
        return true;
      }
    else
      return false;
  }
bool operator<=(Color const& other)
  {
    if(r<=other.r and b<=other.b and g<=other.g)
      {
        return true;
      }
    else
      return false;
  }
Color const final_color(){
	return Color{r/(r+1),g/(g+1),b/(b+1)};	
}

	
};

#endif //#define BUW_COLOR_HPP
