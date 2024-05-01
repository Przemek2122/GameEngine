#include "CoreEngine.h"
#include "Assets/IniReader/IniObject.h"

#include "Assets/Assets/IniAsset.h"
#include "Assets/IniReader/IniManager.h"
#include "Misc/StringHelpers.h"

FIniField::FIniField(std::string InName, std::string InValue)
	: Name(std::move(InName))
	, Value(std::move(InValue))
{
}

std::string FIniField::GetName() const
{
	return Name;
}

std::string FIniField::GetValueAsString() const
{
	return Value;
}

int FIniField::GetValueAsInt() const
{
	return SDL_atoi(Value.c_str());
}

bool FIniField::GetValueAsBool() const
{
	static std::string BoolTrueStringValue = "true";

	bool bIsTrue = false;

	if (FStringHelpers::CompareStringCaseInsensitive(Value, BoolTrueStringValue))
	{
		bIsTrue = true;
	}

	return bIsTrue;
}

FIniObject::FIniObject(FIniManager* InIniManager, std::string InIniPath, std::string InIniName)
	: IniManager(InIniManager)
	, IniPath(std::move(InIniPath))
	, IniName(std::move(InIniName))
{
}

FIniObject::~FIniObject()
{
	FieldsMap.Clear();
}

void FIniObject::Initialize()
{
	FAssetsManager* AssetsManager = IniManager->GetAssetsManager();
	IniAssetSharedPtr = AssetsManager->CreateAssetFromRelativePath<FIniAsset>(IniName, IniPath);
}

bool FIniObject::DoesIniExist() const
{
	return IniAssetSharedPtr->DoesFileExist();
}

void FIniObject::LoadIni()
{
	
}

void FIniObject::SaveIni()
{
}

bool FIniObject::ContainsFieldByName(const std::string& FieldName) const
{
	return FieldsMap.ContainsKey(FieldName);
}

bool FIniObject::ContainsFieldByValue(const std::string& FieldValue) const
{
	const FFunctorLambda<bool, std::string, std::shared_ptr<FIniField>> SearchFunction = [&](std::string Key, std::shared_ptr<FIniField> Field)
	{
		if (FieldValue == Field->GetValueAsString())
		{
			return true;
		}

		return false;
	};

	const bool bHasValue = FieldsMap.ContainsByPredicate(SearchFunction);

	return bHasValue;
}

std::shared_ptr<FIniField> FIniObject::FindFieldByName(const std::string& FieldName)
{
	std::shared_ptr<FIniField> Value;

	if (ContainsFieldByName(FieldName))
	{
		Value = FieldsMap.FindValueByKey(FieldName);
	}

	return Value;
}

std::shared_ptr<FIniField> FIniObject::FindFieldByValue(const std::string& FieldValue)
{
	std::shared_ptr<FIniField> Value;

	if (ContainsFieldByValue(FieldValue))
	{
		Value = FieldsMap.FindValueByKey(FieldValue);
	}

	return Value;
}

void FIniObject::AddOrUpdateField(const FIniField& IniField)
{
	const std::string FieldName = IniField.GetName();
	if (!FieldName.empty())
	{
		if (ContainsFieldByName(FieldName))
		{
			FieldsMap[FieldName] = std::make_shared<FIniField>(IniField);
		}
		else
		{
			FieldsMap.Emplace(FieldName, std::make_shared<FIniField>(IniField));
		}
	}
}
