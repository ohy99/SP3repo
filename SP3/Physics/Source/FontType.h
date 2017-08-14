#ifndef _FONTTYPE_H
#define _FONTTYPE_H

#include "UIObj.h"

class FontType : public UIObj
{
public:
	virtual ~FontType() {
		if (textWidth != nullptr)
			delete textWidth;
		textWidth = nullptr;
	}
	float* textWidth;
protected:
	FontType() {
		textWidth = nullptr;
	}

};

#endif
