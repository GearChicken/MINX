/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#include "Matrix4x4.h"
using namespace MINX;

Matrix4x4::Matrix4x4(float ma11,float ma12,float ma13,float ma14,float ma21,float ma22,float ma23,float ma24,float ma31,float ma32,float ma33,float ma34,float ma41, float ma42,float ma43,float ma44)
{
	m11=ma11;
	m12=ma12;
	m13=ma13;
	m14=ma14;
	m21=ma21;
	m22=ma22;
	m23=ma23;
	m24=ma24;
	m31=ma31;
	m32=ma32;
	m33=ma33;
	m34=ma34;
	m41=ma41;
	m42=ma42;
	m43=ma43;
	m44=ma44;
}
