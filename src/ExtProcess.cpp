#include "ExtProcess.h"

namespace HideIt
{
	ExtProcess::ExtProcess()
	{
		m_hProcess = NULL;
		m_opacityPercentage = 100;
		m_hidden = false;
	}

	ExtProcess::ExtProcess(HWND hProcess)
	{
		m_hProcess = hProcess;
		m_opacityPercentage = 100;
		m_hidden = false;

		SetWindowLong(m_hProcess, GWL_EXSTYLE,
			GetWindowLong(m_hProcess, GWL_EXSTYLE) | WS_EX_LAYERED);
	}

	void ExtProcess::setOpacity(const unsigned int & opacityPercentage) // PRIVATE
	{
		m_opacityPercentage = opacityPercentage;

		SetLayeredWindowAttributes(m_hProcess, 0, (255 * m_opacityPercentage) / 100, LWA_ALPHA);
		UpdateWindow(m_hProcess);
	}

	unsigned int ExtProcess::getOpacity() const
	{
		return m_opacityPercentage;
	}

	void ExtProcess::increaseOpacity()
	{
		if (m_opacityPercentage >= 100)
			return;

		setOpacity(m_opacityPercentage + 10);
	}

	void ExtProcess::decreaseOpacity()
	{
		if (m_opacityPercentage == 0)
			return;

		setOpacity(m_opacityPercentage - 10);
	}

	void ExtProcess::resetOpacity()
	{
		setOpacity(100);
	}

	void ExtProcess::toggleHide()
	{
		if (m_hidden)
		{
			m_hidden = false;
			ShowWindow(m_hProcess, SW_SHOW);
		}
		else
		{
			m_hidden = true;
			ShowWindow(m_hProcess, SW_HIDE);
		}
	}

	bool ExtProcess::isHidden() const
	{
		return m_hidden;
	}

	ExtProcess::~ExtProcess()
	{
	}
}

