#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapKeyTapGesture.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapKeyTapGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapKeyTapGesture();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap  Gesture")
	TEnumAsByte<LeapBasicDirection> BasicDirection;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	FVector Direction;


	UFUNCTION(BlueprintCallable, Category = "Leap Key Tap Gesture")
	class ULeapPointable* Pointable();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	FVector Position;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	float Progress;

	void SetGesture(const class Leap::KeyTapGesture &Gesture);

private:
	class PrivateKeyTapGesture* Private;

	UPROPERTY()
	ULeapPointable* PPointable = nullptr;
};