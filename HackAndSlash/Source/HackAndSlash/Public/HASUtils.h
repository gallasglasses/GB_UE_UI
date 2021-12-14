#pragma once

class HASUtils
{
public:
	template<typename T>
	static T* GetHASPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn)
		{
			return nullptr;
		}
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		
		return Cast<T>(Component);
	}
};