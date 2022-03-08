// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Flying509Game/Flying509GameCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFlying509GameCharacter() {}
// Cross Module References
	FLYING509GAME_API UClass* Z_Construct_UClass_AFlying509GameCharacter_NoRegister();
	FLYING509GAME_API UClass* Z_Construct_UClass_AFlying509GameCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Flying509Game();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	FLYING509GAME_API UClass* Z_Construct_UClass_ABullet_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AFlying509GameCharacter::execOnTimelineFinished)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnTimelineFinished();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AFlying509GameCharacter::execDiveCatchTimelineFloatReturn)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DiveCatchTimelineFloatReturn(Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AFlying509GameCharacter::execDiveTimelineFloatReturn)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DiveTimelineFloatReturn(Z_Param_value);
		P_NATIVE_END;
	}
	void AFlying509GameCharacter::StaticRegisterNativesAFlying509GameCharacter()
	{
		UClass* Class = AFlying509GameCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DiveCatchTimelineFloatReturn", &AFlying509GameCharacter::execDiveCatchTimelineFloatReturn },
			{ "DiveTimelineFloatReturn", &AFlying509GameCharacter::execDiveTimelineFloatReturn },
			{ "OnTimelineFinished", &AFlying509GameCharacter::execOnTimelineFinished },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics
	{
		struct Flying509GameCharacter_eventDiveCatchTimelineFloatReturn_Parms
		{
			float value;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Flying509GameCharacter_eventDiveCatchTimelineFloatReturn_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFlying509GameCharacter, nullptr, "DiveCatchTimelineFloatReturn", nullptr, nullptr, sizeof(Flying509GameCharacter_eventDiveCatchTimelineFloatReturn_Parms), Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics
	{
		struct Flying509GameCharacter_eventDiveTimelineFloatReturn_Parms
		{
			float value;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Flying509GameCharacter_eventDiveTimelineFloatReturn_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFlying509GameCharacter, nullptr, "DiveTimelineFloatReturn", nullptr, nullptr, sizeof(Flying509GameCharacter_eventDiveTimelineFloatReturn_Parms), Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFlying509GameCharacter, nullptr, "OnTimelineFinished", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AFlying509GameCharacter_NoRegister()
	{
		return AFlying509GameCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AFlying509GameCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseTurnRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BaseTurnRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseLookUpRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BaseLookUpRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BulletBP_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_BulletBP;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxPitchLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxPitchLimit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinPitchLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinPitchLimit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxRollLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxRollLimit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinRollLimit_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinRollLimit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_YawTurnScale_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_YawTurnScale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BoostFlightSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BoostFlightSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NormalFlightSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_NormalFlightSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_diveCurve_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_diveCurve;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_catchCurve_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_catchCurve;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFlying509GameCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Flying509Game,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AFlying509GameCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AFlying509GameCharacter_DiveCatchTimelineFloatReturn, "DiveCatchTimelineFloatReturn" }, // 933224623
		{ &Z_Construct_UFunction_AFlying509GameCharacter_DiveTimelineFloatReturn, "DiveTimelineFloatReturn" }, // 3515680613
		{ &Z_Construct_UFunction_AFlying509GameCharacter_OnTimelineFinished, "OnTimelineFinished" }, // 265180464
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Flying509GameCharacter.h" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Follow camera */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
		{ "ToolTip", "Follow camera" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_FollowCamera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_FollowCamera_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseTurnRate_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
		{ "ToolTip", "Base turn rate, in deg/sec. Other scaling may affect final turn rate." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseTurnRate = { "BaseTurnRate", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, BaseTurnRate), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseTurnRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseTurnRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseLookUpRate_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
		{ "ToolTip", "Base look up/down rate, in deg/sec. Other scaling may affect final rate." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseLookUpRate = { "BaseLookUpRate", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, BaseLookUpRate), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseLookUpRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseLookUpRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BulletBP_MetaData[] = {
		{ "Category", "Shooting" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BulletBP = { "BulletBP", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, BulletBP), Z_Construct_UClass_ABullet_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BulletBP_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BulletBP_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxPitchLimit_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxPitchLimit = { "MaxPitchLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, MaxPitchLimit), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxPitchLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxPitchLimit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinPitchLimit_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinPitchLimit = { "MinPitchLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, MinPitchLimit), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinPitchLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinPitchLimit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxRollLimit_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxRollLimit = { "MaxRollLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, MaxRollLimit), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxRollLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxRollLimit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinRollLimit_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinRollLimit = { "MinRollLimit", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, MinRollLimit), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinRollLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinRollLimit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_YawTurnScale_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_YawTurnScale = { "YawTurnScale", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, YawTurnScale), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_YawTurnScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_YawTurnScale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BoostFlightSpeed_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BoostFlightSpeed = { "BoostFlightSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, BoostFlightSpeed), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BoostFlightSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BoostFlightSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_NormalFlightSpeed_MetaData[] = {
		{ "Category", "Flying" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_NormalFlightSpeed = { "NormalFlightSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, NormalFlightSpeed), METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_NormalFlightSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_NormalFlightSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_diveCurve_MetaData[] = {
		{ "Category", "Timeline" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_diveCurve = { "diveCurve", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, diveCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_diveCurve_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_diveCurve_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_catchCurve_MetaData[] = {
		{ "Category", "Timeline" },
		{ "ModuleRelativePath", "Flying509GameCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_catchCurve = { "catchCurve", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFlying509GameCharacter, catchCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_catchCurve_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_catchCurve_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFlying509GameCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_CameraBoom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_FollowCamera,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseTurnRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BaseLookUpRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BulletBP,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxPitchLimit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinPitchLimit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MaxRollLimit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_MinRollLimit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_YawTurnScale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_BoostFlightSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_NormalFlightSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_diveCurve,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFlying509GameCharacter_Statics::NewProp_catchCurve,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFlying509GameCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFlying509GameCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFlying509GameCharacter_Statics::ClassParams = {
		&AFlying509GameCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AFlying509GameCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFlying509GameCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFlying509GameCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFlying509GameCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFlying509GameCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFlying509GameCharacter, 638493616);
	template<> FLYING509GAME_API UClass* StaticClass<AFlying509GameCharacter>()
	{
		return AFlying509GameCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFlying509GameCharacter(Z_Construct_UClass_AFlying509GameCharacter, &AFlying509GameCharacter::StaticClass, TEXT("/Script/Flying509Game"), TEXT("AFlying509GameCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFlying509GameCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
