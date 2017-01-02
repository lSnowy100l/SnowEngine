#include "TextPanel.h"



TextPanel::TextPanel(const char* atlas_file_path, const char* atlas_font_data_file_path, const char* text) :
	_text(text),
	_texture_atlas(new TextureAtlas(atlas_font_data_file_path)),
	GUI(atlas_file_path)
{
	update();
}

void TextPanel::addChar(char character, GLfloat* data, GLfloat* texCoords, GLuint& vertices)
{
	CharacterData cd = _texture_atlas->getCharData(character);

	GLfloat
		pos_left_x = _char_pointer + cd.xoffset,
		pos_right_x = pos_left_x + cd.width,
		pos_top_y = cd.yoffset + cd.height,
		pos_bot_y = cd.yoffset;

	GLfloat
		tex_left_x = cd.x / 512.0f,
		tex_right_x = (cd.x + cd.width) / 512.0f,
		tex_top_y = cd.y / 512.0f,
		tex_bot_y = (cd.y + cd.height) / 512.0f;
	
	data[vertices] = pos_left_x;
	texCoords[vertices++] = tex_left_x;
	data[vertices] = pos_top_y;
	texCoords[vertices++] = tex_top_y;

	data[vertices] = pos_left_x;
	texCoords[vertices++] = tex_left_x;
	data[vertices] = pos_bot_y;
	texCoords[vertices++] = tex_bot_y;

	data[vertices] = pos_right_x;
	texCoords[vertices++] = tex_right_x;
	data[vertices] = pos_top_y;
	texCoords[vertices++] = tex_top_y;
	
	data[vertices] = pos_left_x;
	texCoords[vertices++] = tex_left_x;
	data[vertices] = pos_bot_y;
	texCoords[vertices++] = tex_bot_y;

	data[vertices] = pos_right_x;
	texCoords[vertices++] = tex_right_x;
	data[vertices] = pos_bot_y;
	texCoords[vertices++] = tex_bot_y;

	data[vertices] = pos_right_x;
	texCoords[vertices++] = tex_right_x;
	data[vertices] = pos_top_y;
	texCoords[vertices++] = tex_top_y;
	
	_char_pointer += cd.xadvance;
}

void TextPanel::update()
{
	if (_updated) return;

	GLfloat* data = new GLfloat[MAX_CHARACTERS * 6 * 2];
	GLfloat* texCoords = new GLfloat[MAX_CHARACTERS * 6 * 2];
	GLuint vertCount = 0;
	_char_pointer = 0;

	unsigned i = 0;
	char c = _text[0];
	while (c != NULL && i < MAX_CHARACTERS) {
		addChar(c, data, texCoords, vertCount);
		i++;
		c = _text[i];
	}

	_vertexCount = vertCount / 2;

	glBindVertexArray(_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	delete[] data;
	delete[] texCoords;
	_updated = true;
}

void TextPanel::setText(const char * text)
{
	_text = text;
	_updated = false;
}


TextPanel::~TextPanel()
{
}

TextureAtlas::TextureAtlas(const char * _file_path)
{
	_char_data = new CharacterData[256];
	_char_data[10] = CharacterData(0, 0, 0, 0, 0, 0, 0);
	_char_data[32] = CharacterData(0, 0, 0, 0, -3, 76, 30);
	_char_data[33] = CharacterData(405, 344, 17, 64, 3, 18, 31);
	_char_data[34] = CharacterData(487, 344, 23, 28, 2, 19, 35);
	_char_data[35] = CharacterData(332, 215, 52, 65, -1, 18, 58);
	_char_data[36] = CharacterData(324, 0, 47, 76, 0, 12, 58);
	_char_data[37] = CharacterData(271, 215, 61, 65, 0, 18, 69);
	_char_data[38] = CharacterData(250, 149, 57, 66, 1, 17, 66);
	_char_data[39] = CharacterData(498, 215, 11, 28, 2, 19, 23);
	_char_data[40] = CharacterData(53, 0, 23, 79, 1, 17, 33);
	_char_data[41] = CharacterData(76, 0, 23, 79, 1, 17, 33);
	_char_data[42] = CharacterData(214, 460, 44, 41, 3, 18, 58);
	_char_data[43] = CharacterData(168, 460, 46, 48, 2, 26, 58);
	_char_data[44] = CharacterData(303, 460, 16, 27, 2, 66, 29);
	_char_data[45] = CharacterData(455, 460, 25, 12, -2, 51, 29);
	_char_data[46] = CharacterData(440, 460, 15, 16, 3, 66, 29);
	_char_data[47] = CharacterData(161, 0, 48, 79, -8, 17, 47);
	_char_data[48] = CharacterData(200, 149, 50, 66, 1, 17, 59);
	_char_data[49] = CharacterData(84, 215, 46, 65, 5, 17, 58);
	_char_data[50] = CharacterData(130, 215, 47, 65, 1, 17, 58);
	_char_data[51] = CharacterData(413, 79, 51, 66, -1, 17, 59);
	_char_data[52] = CharacterData(0, 149, 51, 66, 0, 16, 59);
	_char_data[53] = CharacterData(177, 215, 49, 65, 0, 18, 59);
	_char_data[54] = CharacterData(51, 149, 49, 66, 1, 17, 58);
	_char_data[55] = CharacterData(360, 344, 45, 64, 3, 18, 59);
	_char_data[56] = CharacterData(100, 149, 51, 66, 0, 17, 58);
	_char_data[57] = CharacterData(151, 149, 49, 66, 1, 17, 59);
	_char_data[58] = CharacterData(488, 408, 15, 49, 3, 33, 29);
	_char_data[59] = CharacterData(471, 344, 16, 60, 2, 33, 29);
	_char_data[60] = CharacterData(80, 460, 44, 48, 3, 26, 59);
	_char_data[61] = CharacterData(319, 460, 46, 26, 2, 36, 58);
	_char_data[62] = CharacterData(124, 460, 44, 48, 4, 26, 58);
	_char_data[63] = CharacterData(226, 215, 45, 65, -2, 17, 51);
	_char_data[64] = CharacterData(111, 79, 63, 67, 0, 16, 71);
	_char_data[65] = CharacterData(384, 215, 52, 64, -3, 18, 54);
	_char_data[66] = CharacterData(436, 215, 48, 64, 4, 18, 60);
	_char_data[67] = CharacterData(174, 79, 50, 66, 1, 17, 58);
	_char_data[68] = CharacterData(0, 280, 51, 64, 4, 18, 64);
	_char_data[69] = CharacterData(51, 280, 43, 64, 4, 18, 55);
	_char_data[70] = CharacterData(94, 280, 41, 64, 4, 19, 51);
	_char_data[71] = CharacterData(224, 79, 52, 66, 1, 17, 64);
	_char_data[72] = CharacterData(464, 79, 47, 65, 4, 17, 63);
	_char_data[73] = CharacterData(484, 215, 14, 64, 4, 18, 29);
	_char_data[74] = CharacterData(307, 149, 33, 65, -3, 18, 41);
	_char_data[75] = CharacterData(135, 280, 52, 64, 4, 18, 62);
	_char_data[76] = CharacterData(187, 280, 40, 64, 4, 18, 50);
	_char_data[77] = CharacterData(227, 280, 62, 64, 4, 18, 77);
	_char_data[78] = CharacterData(289, 280, 48, 64, 4, 18, 64);
	_char_data[79] = CharacterData(276, 79, 53, 66, 1, 17, 63);
	_char_data[80] = CharacterData(337, 280, 45, 64, 4, 19, 56);
	_char_data[81] = CharacterData(0, 0, 53, 79, 1, 17, 63);
	_char_data[82] = CharacterData(382, 280, 48, 64, 4, 18, 61);
	_char_data[83] = CharacterData(329, 79, 51, 66, -2, 17, 57);
	_char_data[84] = CharacterData(430, 280, 46, 64, -2, 18, 50);
	_char_data[85] = CharacterData(340, 149, 46, 65, 3, 18, 60);
	_char_data[86] = CharacterData(0, 344, 52, 64, -3, 18, 54);
	_char_data[87] = CharacterData(52, 344, 74, 64, -2, 18, 78);
	_char_data[88] = CharacterData(126, 344, 51, 64, -3, 18, 53);
	_char_data[89] = CharacterData(177, 344, 53, 64, -5, 18, 52);
	_char_data[90] = CharacterData(230, 344, 46, 64, -1, 18, 52);
	_char_data[91] = CharacterData(282, 0, 21, 78, 4, 18, 34);
	_char_data[92] = CharacterData(209, 0, 48, 79, -1, 17, 47);
	_char_data[93] = CharacterData(303, 0, 21, 78, 1, 18, 34);
	_char_data[94] = CharacterData(258, 460, 45, 33, -1, 17, 51);
	_char_data[95] = CharacterData(0, 509, 49, 12, -3, 82, 51);
	_char_data[96] = CharacterData(365, 460, 27, 20, 4, 13, 51);
	_char_data[97] = CharacterData(0, 408, 43, 52, 0, 31, 54);
	_char_data[98] = CharacterData(386, 149, 43, 65, 4, 18, 55);
	_char_data[99] = CharacterData(87, 408, 41, 51, 0, 32, 48);
	_char_data[100] = CharacterData(429, 149, 43, 65, 0, 18, 55);
	_char_data[101] = CharacterData(43, 408, 44, 52, 0, 31, 52);
	_char_data[102] = CharacterData(380, 79, 33, 66, -2, 16, 35);
	_char_data[103] = CharacterData(371, 0, 47, 72, -1, 26, 50);
	_char_data[104] = CharacterData(472, 149, 39, 65, 4, 18, 55);
	_char_data[105] = CharacterData(476, 280, 14, 64, 3, 18, 28);
	_char_data[106] = CharacterData(257, 0, 25, 78, -8, 19, 27);
	_char_data[107] = CharacterData(276, 344, 42, 64, 4, 18, 52);
	_char_data[108] = CharacterData(490, 280, 13, 64, 4, 18, 29);
	_char_data[109] = CharacterData(215, 408, 63, 50, 4, 32, 79);
	_char_data[110] = CharacterData(278, 408, 39, 50, 4, 32, 55);
	_char_data[111] = CharacterData(128, 408, 44, 51, 0, 32, 52);
	_char_data[112] = CharacterData(0, 215, 42, 65, 4, 31, 54);
	_char_data[113] = CharacterData(42, 215, 42, 65, 0, 32, 54);
	_char_data[114] = CharacterData(317, 408, 27, 50, 4, 32, 37);
	_char_data[115] = CharacterData(172, 408, 43, 51, -2, 32, 49);
	_char_data[116] = CharacterData(439, 344, 32, 62, -3, 21, 35);
	_char_data[117] = CharacterData(344, 408, 40, 50, 4, 33, 56);
	_char_data[118] = CharacterData(384, 408, 43, 49, -2, 33, 47);
	_char_data[119] = CharacterData(427, 408, 61, 49, -2, 33, 65);
	_char_data[120] = CharacterData(0, 460, 43, 49, -3, 33, 44);
	_char_data[121] = CharacterData(318, 344, 42, 64, -3, 33, 44);
	_char_data[122] = CharacterData(43, 460, 37, 49, 0, 33, 44);
	_char_data[123] = CharacterData(99, 0, 25, 79, 2, 17, 33);
	_char_data[124] = CharacterData(149, 0, 12, 79, 15, 17, 50);
	_char_data[125] = CharacterData(124, 0, 25, 79, -1, 17, 33);
	_char_data[126] = CharacterData(392, 460, 48, 20, 1, 40, 58);
	_char_data[161] = CharacterData(422, 344, 17, 63, 3, 33, 31);
	_char_data[225] = CharacterData(418, 0, 43, 71, 0, 12, 54);
	_char_data[233] = CharacterData(461, 0, 44, 71, 0, 12, 52);
	_char_data[237] = CharacterData(84, 79, 27, 69, 2, 13, 29);
	_char_data[243] = CharacterData(0, 79, 44, 70, 0, 13, 52);
	_char_data[250] = CharacterData(44, 79, 40, 70, 4, 13, 56);
}

CharacterData TextureAtlas::getCharData(char character)
{
	return _char_data[character];
}
