#ifndef COLORTABLE_H
#define COLORTABLE_H

// 140 �ֳ�����ɫ

enum ColorIndex 
{
	LightPink,
	Pink,
	Crimson,
	LavenderBlush,
	PaleVioletRed,
	HotPink,
	DeepPink,
	MediumVioletRed,
	Orchid,
	Thistle,
	Plum,
	Violet,
	Magenta,
	Fuchsia,
	DarkMagenta,
	Purple,
	MediumOrchid,
	DarkViolet,
	DarkOrchid,
	Indigo,
	BlueViolet,
	MediumPurple,
	MediumSlateBlue,
	SlateBlue,
	DarkSlateBlue,
	Lavender,
	GhostWhite,
	Blue,
	MediumBlue,
	MidnightBlue,
	DarkBlue,
	Navy,
	RoyalBlue,
	CornflowerBlue,
	LightSteelBlue,
	LightSlateGray,
	SlateGray,
	DodgerBlue,
	AliceBlue,
	SteelBlue,
	LightSkyBlue,
	SkyBlue,
	DeepSkyBlue,
	LightBlue,
	PowderBlue,
	CadetBlue,
	Azure,
	LightCyan,
	PaleTurquoise,
	Cyan,
	Aqua,
	DarkTurquoise,
	DarkSlateGray,
	DarkCyan,
	Teal,
	MediumTurquoise,
	LightSeaGreen,
	Turquoise,
	Aquamarine,
	MediumAquamarine,
	MediumSpringGreen,
	MintCream,
	SpringGreen,
	MediumSeaGreen,
	SeaGreen,
	Honeydew,
	LightGreen,
	PaleGreen,
	DarkSeaGreen,
	LimeGreen,
	Lime,
	ForestGreen,
	Green,
	DarkGreen,
	Chartreuse,
	LawnGreen,
	GreenYellow,
	DarkOliveGreen,
	YellowGreen,
	OliveDrab,
	Beige,
	LightGoldenrodYellow,
	Ivory,
	LightYellow,
	Yellow,
	Olive,
	DarkKhaki,
	LemonChiffon,
	PaleGoldenrod,
	Khaki,
	Gold,
	Cornsilk,
	Goldenrod,
	DarkGoldenrod,
	FloralWhite,
	OldLace,
	Wheat,
	Moccasin,
	Orange,
	PapayaWhip,
	BlanchedAlmond,
	NavajoWhite,
	AntiqueWhite,
	Tan,
	BurlyWood,
	Bisque,
	DarkOrange,
	Linen,
	Peru,
	PeachPuff,
	SandyBrown,
	Chocolate,
	SaddleBrown,
	Seashell,
	Sienna,
	LightSalmon,
	Coral,
	OrangeRed,
	DarkSalmon,
	Tomato,
	MistyRose,
	Salmon,
	Snow,
	LightCoral,
	RosyBrown,
	IndianRed,
	Red,
	Brown,
	FireBrick,
	DarkRed,
	Maroon,
	White,
	WhiteSmoke,
	Gainsboro,
	LightGrey,
	Silver,
	DarkGray,
	Gray,
	DimGray,
	Black
};

unsigned int ColorTable[] = 
{
	(0xFFB6C1),	//ǳ�ۺ�
	(0xFFC0CB),	//�ۺ�
	(0xDC143C),	//�ɺ�(���)
	(0xFFF0F5),	//���Ϻ�
	(0xDB7093),	//����������
	(0xFF69B4),	//����ķۺ�
	(0xFF1493),	//��ۺ�
	(0xC71585),	//����������
	(0xDA70D6),	//������
	(0xD8BFD8),	//��
	(0xDDA0DD),	//������
	(0xEE82EE),	//������
	(0xFF00FF),	//���(Ʒ��õ���)
	(0xFF00FF),	//��������(�Ϻ�ɫ)
	(0x8B008B),	//�����
	(0x800080),	//��ɫ
	(0xBA55D3),	//��������
	(0x9400D3),	//��������
	(0x9932CC),	//��������
	(0x4B0082),	//����(����ɫ)
	(0x8A2BE2),	//��������
	(0x9370DB),	//����ɫ
	(0x7B68EE),	//�а�����
	(0x6A5ACD),	//������
	(0x483D8B),	//��������
	(0xE6E6FA),	//Ѭ�²ݵ���
	(0xF8F8FF),	//�����
	(0x0000FF),	//����
	(0x0000CD),	//����ɫ
	(0x191970),	//��ҹ��
	(0x00008B),	//����ɫ
	(0x000080),	//������
	(0x4169E1),	//�ʼ���(����)
	(0x6495ED),	//ʸ������
	(0xB0C4DE),	//������
	(0x778899),	//��ʯ���
	(0x708090),	//ʯ���
	(0x1E90FF),	//������
	(0xF0F8FF),	//����˿��
	(0x4682B4),	//����(����)
	(0x87CEFA),	//������ɫ
	(0x87CEEB),	//����ɫ
	(0x00BFFF),	//������
	(0xADD8E6),	//����
	(0xB0E0E6),	//��ҩ��
	(0x5F9EA0),	//������
	(0xF0FFFF),	//ε��ɫ
	(0xE0FFFF),	//����ɫ
	(0xAFEEEE),	//���̱�ʯ
	(0x00FFFF),	//��ɫ
	(0x00FFFF),	//ˮɫ
	(0x00CED1),	//���̱�ʯ
	(0x2F4F4F),	//��ʯ���
	(0x008B8B),	//����ɫ
	(0x008080),	//ˮѼɫ
	(0x48D1CC),	//���̱�ʯ
	(0x20B2AA),	//ǳ������
	(0x40E0D0),	//�̱�ʯ
	(0x7FFFD4),	//��ʯ����
	(0x66CDAA),	//�б�ʯ����
	(0x00FA9A),	//�д���ɫ
	(0xF5FFFA),	//��������
	(0x00FF7F),	//����ɫ
	(0x3CB371),	//�к�����
	(0x2E8B57),	//������
	(0xF0FFF0),	//�۹�ɫ
	(0x90EE90),	//����ɫ
	(0x98FB98),	//����ɫ
	(0x8FBC8F),	//��������
	(0x32CD32),	//��������
	(0x00FF00),	//������
	(0x228B22),	//ɭ����
	(0x008000),	//����
	(0x006400),	//����ɫ
	(0x7FFF00),	//���ؾ���(����ɫ)
	(0x7CFC00),	//��ƺ��
	(0xADFF2F),	//�̻�ɫ
	(0x556B2F),	//�������
	(0x9ACD32),	//����ɫ
	(0x6B8E23),	//��魺�ɫ
	(0xF5F5DC),	//��ɫ(����ɫ)
	(0xFAFAD2),	//���ջ�
	(0xFFFFF0),	//����
	(0xFFFFE0),	//ǳ��ɫ
	(0xFFFF00),	//����
	(0x808000),	//���
	(0xBDB76B),	//�ߴ��
	(0xFFFACD),	//���ʳ�
	(0xEEE8AA),	//�Ҿջ�
	(0xF0E68C),	//��ߴ��
	(0xFFD700),	//��ɫ
	(0xFFF8DC),	//����˿ɫ
	(0xDAA520),	//��ջ�
	(0xB8860B),	//����ջ�
	(0xFFFAF0),	//���İ�ɫ
	(0xFDF5E6),	//����˿
	(0xF5DEB3),	//С��ɫ
	(0xFFE4B5),	//¹Ƥѥ
	(0xFFA500),	//��ɫ
	(0xFFEFD5),	//��ľ��
	(0xFFEBCD),	//���׵�����ɫ
	(0xFFDEAD),	//������
	(0xFAEBD7),	//�Ŷ���
	(0xD2B48C),	//��ɫ
	(0xDEB887),	//Ӳľɫ
	(0xFFE4C4),	//������
	(0xFF8C00),	//���ɫ
	(0xFAF0E6),	//���鲼
	(0xCD853F),	//��³
	(0xFFDAB9),	//����ɫ
	(0xF4A460),	//ɳ��ɫ
	(0xD2691E),	//�ɿ���
	(0x8B4513),	//����ɫ
	(0xFFF5EE),	//������
	(0xA0522D),	//������ɫ
	(0xFFA07A),	//ǳ������ɫ
	(0xFF7F50),	//ɺ��
	(0xFF4500),	//�Ⱥ�ɫ
	(0xE9967A),	//������(����)ɫ
	(0xFF6347),	//���Ѻ�
	(0xFFE4E1),	//����õ��
	(0xFA8072),	//����(����)ɫ
	(0xFFFAFA),	//ѩ
	(0xF08080),	//��ɺ��ɫ
	(0xBC8F8F),	//õ����ɫ
	(0xCD5C5C),	//ӡ�Ⱥ�
	(0xFF0000),	//����
	(0xA52A2A),	//��ɫ
	(0xB22222),	//�ͻ�ש
	(0x8B0000),	//���ɫ
	(0x800000),	//��ɫ
	(0xFFFFFF),	//����
	(0xF5F5F5),	//����
	(0xDCDCDC),	//��˹���޻�ɫ
	(0xD3D3D3),	//ǳ��ɫ
	(0xC0C0C0),	//����ɫ
	(0xA9A9A9),	//���ɫ
	(0x808080),	//��ɫ
	(0x696969),	//�����Ļ�ɫ
	(0x000000),	//����
};

void getColorFromTable(ColorIndex idx, float vec[3])
{
	unsigned int rgb = ColorTable[idx];

	GLubyte  r = GLubyte ((rgb >> 16) & 0xFF);
	GLubyte  g = GLubyte ((rgb >> 8) & 0xFF);
	GLubyte  b = GLubyte (rgb & 0xFF);
	vec[0] = r / 255.0f;
	vec[1] = g / 255.0f;
	vec[2] = b / 255.0f;
}

#endif