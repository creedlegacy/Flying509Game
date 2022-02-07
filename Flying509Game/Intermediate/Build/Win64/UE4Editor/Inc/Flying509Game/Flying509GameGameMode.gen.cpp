// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Flying509Game/Flying509GameGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFlying509GameGameMode() {}
// Cross Module References
	FLYING509GAME_API UClass* Z_Construct_UClass_AFlying509GameGameMode_NoRegister();
	FLYING509GAME_API UClass* Z_Construct_UClass_AFlying509GameGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Flying509Game();
// End Cross Module References
	void AFlying509GameGameMode::StaticRegisterNativesAFlying509GameGameMode()
	{
	}
	UClass* Z_Construct_UClass_AFlying509GameGameMode_NoRegister()
	{
		return AFlying509GameGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AFlying509GameGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFlying509GameGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Flying509Game,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Flying509GameGameMode.h" },
		{ "ModuleRelativePath", "Flying509GameGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFlying509GameGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFlying509GameGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFlying509GameGameMode_Statics::ClassParams = {
		&AFlying509GameGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFlying509GameGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFlying509GameGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFlying509GameGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFlying509GameGameMode, 367140014);
	template<> FLYING509GAME_API UClass* StaticClass<AFlying509GameGameMode>()
	{
		return AFlying509GameGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFlying509GameGameMode(Z_Construct_UClass_AFlying509GameGameMode, &AFlying509GameGameMode::StaticClass, TEXT("/Script/Flying509Game"), TEXT("AFlying509GameGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFlying509GameGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
