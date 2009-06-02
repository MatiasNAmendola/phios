/*
 * Text.cpp
 *
 *  Created on: Jun 2, 2009
 *      Author: ghalex
 */

#include "Text.h"

namespace phi {
namespace kernel {
namespace drivers {
namespace video {

	Text::Text()
	{
		videoMemory = (unsigned short*) 0xB8000;

		cursorX = 0;
		cursorY = 0;

		attrib = 0x0F;
		blank  = 0x20 | (attrib << 8);
	}

	Text::~Text()
	{
	}

	void Text::clear()
	{
		int i, j;
		unsigned short* temp = videoMemory;

		for(i = 0; i < 25; i++)
		{
			for(j = 0 ; j < 80; j++)
			{
				temp  = videoMemory + (i * 80 + j);
				*temp = blank;
			}
		}

		cursorX = 0;
		cursorY = 0;

		moveCursor();
	}

	void Text::putc(char c)
	{
		unsigned short* where;

		if(c == '\b')
		{
			if(cursorX < 1)
			{
				cursorX = 79;
				cursorY--;

			} else
			{
				cursorX--;

				where  = videoMemory + (cursorY * 80 + cursorX);
				*where = blank;
			}
		} else if (c == '\t')
		{
		   cursorX = (cursorX + 8) & ~(8-1);
		}else if (c == '\n')
		{
			cursorX = 0;
			cursorY++;

		} else if(c >= ' ')
		{
			where  = videoMemory + (cursorY * 80 + cursorX);
			*where = c | attrib << 8;

			cursorX++;
		}

		moveCursor();
	}

	void Text::write(char* string)
	{
		int i =0;
		while(string[i])
			putc(string[i++]);
	}

	void Text::writeln(char* string)
	{
		write(string);

		cursorX = 0;
		cursorY++;

		moveCursor();
	}

	void Text::moveCursor()
	{
		/*
		unsigned short temp = cursorY * 80 + cursorX;

		outb(0x3D4, 14);
		outb(0x3D5, temp >> 8);
		outb(0x3D4, 15);
		outb(0x3D5, temp);
		*/
	}

}
}
}
}
