//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <string>

using namespace App1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void App1::MainPage::Monday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{	
	String^ text_to_show = "MONDAY";
	char arr[] = { 8,9,10,11,12,13,14,15,16,17,18,19,20 };
	
	for (int i = 0; i < 13; i++) {
		text_to_show += "\n FUCK YOU!";
	}
	ResultTextBlock->Text = text_to_show;
}

void App1::MainPage::Tuesday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ResultTextBlock->Text = "TUESDAY";
}

void App1::MainPage::Wednesday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ResultTextBlock->Text = "WEDNESDAY";
}

void App1::MainPage::Thursday_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ResultTextBlock->Text = "THURSDAY";
}
