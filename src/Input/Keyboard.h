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
#ifndef KEYBOARD_H_
#define KEYBOARD_H_


#ifndef MINX_KEYBOARD_ALIAS
#define MINX_KEY_0   48
#define MINX_KEY_1   49
#define MINX_KEY_2   50
#define MINX_KEY_3   51
#define MINX_KEY_4   52
#define MINX_KEY_5   53
#define MINX_KEY_6   54
#define MINX_KEY_7   55
#define MINX_KEY_8   56
#define MINX_KEY_9   57
#define MINX_KEY_A   65
#define MINX_KEY_APOSTROPHE   39 /* ' */
#define MINX_KEY_B   66
#define MINX_KEY_BACKSLASH   92 /* \ */
#define MINX_KEY_BACKSPACE   259
#define MINX_KEY_C   67
#define MINX_KEY_CAPS_LOCK   280
#define MINX_KEY_COMMA   44 /* , */
#define MINX_KEY_D   68
#define MINX_KEY_DELETE   261
#define MINX_KEY_DOWN   264
#define MINX_KEY_E   69
#define MINX_KEY_END   269
#define MINX_KEY_ENTER   257
#define MINX_KEY_EQUAL   61 /* = */
#define MINX_KEY_ESCAPE   256
#define MINX_KEY_F   70
#define MINX_KEY_F1   290
#define MINX_KEY_F10   299
#define MINX_KEY_F11   300
#define MINX_KEY_F12   301
#define MINX_KEY_F13   302
#define MINX_KEY_F14   303
#define MINX_KEY_F15   304
#define MINX_KEY_F16   305
#define MINX_KEY_F17   306
#define MINX_KEY_F18   307
#define MINX_KEY_F19   308
#define MINX_KEY_F2   291
#define MINX_KEY_F20   309
#define MINX_KEY_F21   310
#define MINX_KEY_F22   311
#define MINX_KEY_F23   312
#define MINX_KEY_F24   313
#define MINX_KEY_F25   314
#define MINX_KEY_F3   292
#define MINX_KEY_F4   293
#define MINX_KEY_F5   294
#define MINX_KEY_F6   295
#define MINX_KEY_F7   296
#define MINX_KEY_F8   297
#define MINX_KEY_F9   298
#define MINX_KEY_G   71
#define MINX_KEY_GRAVE_ACCENT   96 /* ` */
#define MINX_KEY_H   72
#define MINX_KEY_HOME   268
#define MINX_KEY_I   73
#define MINX_KEY_INSERT   260
#define MINX_KEY_J   74
#define MINX_KEY_K   75
#define MINX_KEY_KP_0   320
#define MINX_KEY_KP_1   321
#define MINX_KEY_KP_2   322
#define MINX_KEY_KP_3   323
#define MINX_KEY_KP_4   324
#define MINX_KEY_KP_5   325
#define MINX_KEY_KP_6   326
#define MINX_KEY_KP_7   327
#define MINX_KEY_KP_8   328
#define MINX_KEY_KP_9   329
#define MINX_KEY_KP_ADD   334
#define MINX_KEY_KP_DECIMAL   330
#define MINX_KEY_KP_DIVIDE   331
#define MINX_KEY_KP_ENTER   335
#define MINX_KEY_KP_EQUAL   336
#define MINX_KEY_KP_MULTIPLY   332
#define MINX_KEY_KP_SUBTRACT   333
#define MINX_KEY_L   76
#define MINX_KEY_LAST   MINX_KEY_MENU
#define MINX_KEY_LEFT   263
#define MINX_KEY_LEFT_ALT   342
#define MINX_KEY_LEFT_BRACKET   91 /* [ */
#define MINX_KEY_LEFT_CONTROL   341
#define MINX_KEY_LEFT_SHIFT   340
#define MINX_KEY_LEFT_SUPER   343
#define MINX_KEY_M   77
#define MINX_KEY_MENU   348
#define MINX_KEY_MINUS   45 /* - */
#define MINX_KEY_N   78
#define MINX_KEY_NUM_LOCK   282
#define MINX_KEY_O   79
#define MINX_KEY_P   80
#define MINX_KEY_PAGE_DOWN   267
#define MINX_KEY_PAGE_UP   266
#define MINX_KEY_PAUSE   284
#define MINX_KEY_PERIOD   46 /* . */
#define MINX_KEY_PRINT_SCREEN   283
#define MINX_KEY_Q   81
#define MINX_KEY_R   82
#define MINX_KEY_RIGHT   262
#define MINX_KEY_RIGHT_ALT   346
#define MINX_KEY_RIGHT_BRACKET   93 /* ] */
#define MINX_KEY_RIGHT_CONTROL   345
#define MINX_KEY_RIGHT_SHIFT   344
#define MINX_KEY_RIGHT_SUPER   347
#define MINX_KEY_S   83
#define MINX_KEY_SCROLL_LOCK   281
#define MINX_KEY_SEMICOLON   59 /* ; */
#define MINX_KEY_SLASH   47 /* / */
#define MINX_KEY_SPACE   32
#define MINX_KEY_T   84
#define MINX_KEY_TAB   258
#define MINX_KEY_U   85
#define MINX_KEY_UNKNOWN   -1
#define MINX_KEY_UP   265
#define MINX_KEY_V   86
#define MINX_KEY_W   87
#define MINX_KEY_WORLD_1   161 /* non-US #1 */
#define MINX_KEY_WORLD_2   162 /* non-US #2 */
#define MINX_KEY_X   88
#define MINX_KEY_Y   89
#define MINX_KEY_Z   90
#define MINX_KEYBOARD_ALIAS
#endif

#include "IGenericHID.h"
#include "Button.h"
#include <map>
namespace MINX
{
	namespace Input
	{
		/** Represents a keyboard device.
		 */
		class Keyboard : public IGenericHID
		{
			public:
				/** Calls the IGenericHID constructor with game,512,0
				 */
				Keyboard(Game * game);
				/** Pulls data from the keyboardEvent queue in the Game object given to the constructor.
				 */
				void handleEvent();
				/** Gets a button for the state of 'key'
				*	@param key The Key to get the state of
				*/
				Button getKey(char key);
		};
	}
}
#endif
