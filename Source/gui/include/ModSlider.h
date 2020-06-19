#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ModSlider : public Slider
{
public:


	ModSlider(Label* l) : label(l), isModifiable(false) {}
	~ModSlider() { label = nullptr; }

	void mouseDown(const MouseEvent& e) override
	{
		const ModifierKeys modifiers = ModifierKeys::getCurrentModifiersRealtime();
		if (isModifiable && modifiers.isPopupMenu())
		{
			if (isEnabled() && label->isEnabled())
			{
				setEnabled(false);
				label->setEnabled(false);
			}
			else
			{
				setEnabled(true);
				label->setEnabled(true);
			}
		}
		else
			Slider::mouseDown(e);
	}

	void setHasModifiers(bool mod)
	{
		isModifiable = mod;
	}

	bool hasModifier() const
	{
		return isModifiable;
	}


private:
	Label* label;
	bool isModifiable;
};