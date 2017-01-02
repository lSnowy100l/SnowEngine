#pragma once
#include "GUI.h"

#define MAX_CHARACTERS 50

class TextureAtlas;

struct CharacterData
{
	CharacterData() {}
	CharacterData(unsigned x, unsigned y, unsigned width, unsigned height, unsigned xoffset, unsigned yoffset, unsigned xadvance) :
		x(x),
		y(y),
		width(width),
		height(height),
		xoffset(xoffset),
		yoffset(yoffset),
		xadvance(xadvance) {}
	unsigned char id;
	int x, y, width, height, xoffset, yoffset, xadvance;
};

class TextPanel :
	public GUI
{
private:
	bool _updated = false;
	unsigned _char_pointer = 0;
	const char* _text;
	TextureAtlas* _texture_atlas;
private:
	void addChar(char character, GLfloat* data, GLfloat* texCoords, GLuint& vertices);
public:
	TextPanel(const char* atlas_file_path, const char* atlas_font_data_file_path, const char* text);
	void update();
	void setText(const char* text);
	~TextPanel();
};

class TextureAtlas
{
private:
	CharacterData* _char_data;
public:
	TextureAtlas(const char* _file_path);
	CharacterData getCharData(char character);
};

