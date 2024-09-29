//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace App1
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void Monday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Tuesday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Wednesday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Thursday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
