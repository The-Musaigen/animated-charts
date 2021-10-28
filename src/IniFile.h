#ifndef INI_FILE_H_
#define INI_FILE_H_

class IniFile
{
	std::string mFilename;
public:
	IniFile(const std::string_view& aFilename) :
		mFilename(aFilename)
	{}

	int ReadInteger(const char* aSection, const char* aKey, const int aDefault)
	{
		return GetPrivateProfileInt(aSection, aKey, aDefault, mFilename.c_str());
	}

	float ReadFloat(const char* aSection, const char* aKey, const float aDefault)
	{
		char strResult[255]{ 0 };
		char strDefault[255]{ 0 };

		sprintf_s(strDefault, "%.f", aDefault);

		GetPrivateProfileString(aSection, aKey, strDefault, strResult,
			sizeof(strResult),
			mFilename.c_str());

		return std::strtof(strResult, NULL);
	}
};

#endif // !INI_FILE_H_
