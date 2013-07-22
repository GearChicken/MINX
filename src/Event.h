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
#ifndef EVENT_H_
#define EVENT_H_
namespace MINX
{
	enum Event
	{
		FOCUS_STATE_CHANGE,
		KEY_STATE_CHANGE,
		MOUSE_MOVEMENT,
		MOUSE_BUTTON_STATE_CHANGE,
		JOY_AXIS_MOVEMENT,
		JOY_BALL_MOVEMENT,
		JOY_BUTTON_STATE_CHANGE,
		APP_QUIT_REQUEST,
		APP_SYSTEM_WM_EVENT,
		APP_VIDEO_REDRAW,
		USER_CUSTOM_EVENT,
		USER_CUSTOM_EVENT2,
		USER_CUSTOM_EVENT3,
		USER_CUSTOM_EVENT4,
		USER_CUSTOM_EVENT5,
		USER_CUSTOM_EVENT6,
		USER_CUSTOM_EVENT7,
		USER_CUSTOM_EVENT8
	};
}
#endif
