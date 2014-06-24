/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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
#include <thread>
#ifndef THREAD_H_
#define THREAD_H_
namespace MINX
{
	/** An object-oriented replacement for std::thread. Similar to Java(tm)'s Thread class.
	 * This class is used by programmers creating subclasses of it and implementing the virtual run() method.
	 */
	class Thread
	{
		public:
			/** Constructs a Thread
			 */
			Thread();
			/** Begins the execution of this Thread
			 */
			void Start();
			/** Forces this Thread to exit
			 */
			void Kill();
			/** Causes the Thread to run concurrent to its calling thread
			 */
			void Detach();
			/** Waits for the Thread to finish before continuing execution of its calling thread
			 */
			void Join();
			/** The method to be executed in this Thread
			 * This method must be overloaded by a subclass of Thread in order to be used
			 */
			virtual void Run();
			/** Forces this Thread to exit and deconstructs it
			 */
			~Thread();
		private:
			/** The less object oriented thread used on the inside of the thread class
			 */
			std::thread * internalThread;
	};
}
#endif
