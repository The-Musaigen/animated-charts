#include "main.h"

std::unique_ptr<injector::Hook> gHookDrawHealthBar;
std::unique_ptr<injector::Hook> gHookDrawArmorBar;

Chart gHealthChart;
Chart gArmorChart;

IniFile gIniFile(".\\AnimatedCharts.ini");

void OnDrawHealthBar(float aX, float aY, std::uint16_t aWidth, std::uint8_t aHeight,
	float aProgress, char aProgressAdd, std::uint8_t aDrawPercentage,
	std::uint8_t aDrawBlackBorder, std::uint8_t* aColor, std::uint8_t* aAddColor)
{
	gHealthChart.Update();

	if (gHealthChart.GetEndProgress() != aProgress)
		gHealthChart.Start(aProgress);

	return gHookDrawHealthBar->Call(aX, aY, aWidth, aHeight, gHealthChart.GetProgress(), aProgressAdd,
		aDrawPercentage, aDrawBlackBorder, aColor, aAddColor);
}

void OnDrawArmorBar(float aX, float aY, std::uint16_t aWidth, std::uint8_t aHeight,
	float aProgress, char aProgressAdd, std::uint8_t aDrawPercentage,
	std::uint8_t aDrawBlackBorder, std::uint8_t* aColor, std::uint8_t* aAddColor)
{
	gArmorChart.Update();

	if (gArmorChart.GetEndProgress() != aProgress)
		gArmorChart.Start(aProgress);

	return gHookDrawArmorBar->Call(aX, aY, aWidth, aHeight, gArmorChart.GetProgress(), aProgressAdd,
		aDrawPercentage, aDrawBlackBorder, aColor, aAddColor);
}

BOOL APIENTRY DllMain(_In_ HMODULE aModule, _In_ DWORD aReasonForCall, _In_ LPVOID aReserved)
{
	if (aReasonForCall == DLL_PROCESS_ATTACH)
	{
		namespace c = std::chrono;

		int healthDuration = gIniFile.ReadInteger("Duration", "Health", 500);
		int armorDuration = gIniFile.ReadInteger("Duration", "Armor", 500);

		float healthSpeed = gIniFile.ReadFloat("Speed", "Health", 1.f);
		float armorSpeed = gIniFile.ReadFloat("Speed", "Armor", 1.f);

		gHealthChart.SetDuration(c::milliseconds(healthDuration));
		gArmorChart.SetDuration(c::milliseconds(armorDuration));

		gHealthChart.SetSpeed(healthSpeed);
		gArmorChart.SetSpeed(armorSpeed);

		gHookDrawHealthBar = std::make_unique<injector::Hook>(0x589395, OnDrawHealthBar);
		gHookDrawHealthBar->Install();

		gHookDrawArmorBar = std::make_unique<injector::Hook>(0x58917A, OnDrawArmorBar);
		gHookDrawArmorBar->Install();
	}

	return TRUE;
}
