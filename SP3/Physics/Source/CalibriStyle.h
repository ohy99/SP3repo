#ifndef _CALIBRITEXT_H
#define _CALIBRITEXT_H

#include "FontType.h"
#include "LoadTextData.h"

class CalibriStyle : public FontType
{
public:
	CalibriStyle() {
		this->mesh = EntityBase::getInstance()->getEntity("CALIBRI");
		(this->textWidth) = LoadTextData("Image//Calibri Data.csv");
	}
	~CalibriStyle() {

	}
};

#endif
