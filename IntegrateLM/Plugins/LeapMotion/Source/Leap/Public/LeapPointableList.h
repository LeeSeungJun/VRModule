#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointableList.generated.h"

UCLASS(BlueprintType)
class LEAPMOTION_API ULeapPointableList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapPointableList();
	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* Append(class ULeapPointableList *List);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "appendFingers", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* AppendFingers(class ULeapFingerList *List);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "appendTools", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* AppendTools(class ULeapToolList *List);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	int32 Count;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = "Leap Pointable List")
	ULeapPointableList *Extended();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Pointable List")
	class ULeapPointable *Frontmost();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	bool IsEmpty;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Pointable List")
	class ULeapPointable *Leftmost();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPointableByIndex", CompactNodeTitle = "[]", Keywords = "get pointable by index"), Category = "Leap Pointable List")
	class ULeapPointable *GetPointableByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Pointable List")
	class ULeapPointable *Rightmost();

	void SetPointableList(const class Leap::PointableList &Pointables);

private:
	class PrivatePointableList* Private;

	UPROPERTY()
	ULeapPointable* PLeftmost = nullptr;
	UPROPERTY()
	ULeapPointable* PRightmost = nullptr;
	UPROPERTY()
	ULeapPointable* PFrontmost = nullptr;
	UPROPERTY()
	ULeapPointable* PPointableByIndex = nullptr;
	UPROPERTY()
	ULeapPointableList* PAppendedList = nullptr;
	UPROPERTY()
	ULeapPointableList* PExtendedList = nullptr;
};