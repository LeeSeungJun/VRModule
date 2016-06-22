#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGestureList.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapGestureList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapGestureList();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	bool IsEmpty;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	int32 Count;
	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getIndex", CompactNodeTitle = "[]", Keywords = "get index"), Category = "Leap Gesture List")
	class ULeapGesture *GetIndex(int32 Index);

	ULeapGesture* operator[](int Index);

	void SetGestureList(const class Leap::GestureList &Gesturelist);

private:
	class PrivateGestureList* Private;

	UPROPERTY()
	ULeapGesture* PGesture = nullptr;
};