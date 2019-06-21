#pragma once
#include <Windows.h>

namespace HideIt
{
	class ExtProcess
	{
	private:
		HWND			m_hProcess;
		unsigned int		m_opacityPercentage;
		bool			m_hidden;

		void			setOpacity(const unsigned int &);
	public:
		ExtProcess();
		ExtProcess(HWND);

		void			toggleHide();
		void			increaseOpacity();
		void			decreaseOpacity();
		void			resetOpacity();
		bool			isHidden() const;
		unsigned int		getOpacity() const;

		~ExtProcess();
	};
}
