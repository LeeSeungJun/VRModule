#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapCircleGesture.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapCircleGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapCircleGesture();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Center;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Normal;

	UFUNCTION(BlueprintCallable, Category = "Leap Circle Gesture")
	class ULeapPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Progress;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Radius;

	void SetGesture(const class Leap::CircleGesture &Gesture);

private:
	class PrivateCircleGesture* Private;

	UPROPERTY()
	class ULeapPointable* PPointable = nullptr;
};