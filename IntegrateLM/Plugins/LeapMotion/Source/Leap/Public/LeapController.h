#pragma once
#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapController.generated.h"

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class LEAPMOTION_API ULeapController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	~ULeapController();
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	UFUNCTION(BlueprintPure, meta = (Keywords = "is connected"), Category = "Leap Controller")
	bool IsConnected() const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Frame", Keywords = "get frame"), Category = "Leap Controller")
	class ULeapFrame* Frame(int32 History);

	
	UFUNCTION(BlueprintCallable, meta = (Keywords = "has Focus"), Category = "Leap Controller")
	bool HasFocus() const;


	UFUNCTION(BlueprintPure, meta = (Keywords = "is service connected"), Category = "Leap Controller")
	bool IsServiceConnected() const;


	UFUNCTION(BlueprintCallable, meta = (Keywords = "optimize hmd facing top set policy"), Category = "Leap Controller")
	void OptimizeForHMD(bool UseTopdown = false, bool AutoRotate = true, bool AutoShift = true);


	UFUNCTION(BlueprintCallable, meta = (Keywords = "use allow images set policy"), Category = "Leap Controller")
	void EnableImageSupport(bool AllowImages = true, bool EmitImageEvents = true, bool UseGammaCorrection = false);


	UFUNCTION(BlueprintCallable, meta = (Keywords = "enable background tracking"), Category = "Leap Controller")
	void EnableBackgroundTracking(bool TrackInBackground = false);


	UFUNCTION(BlueprintCallable, meta = (Keywords = "enable gesture"), Category = "Leap Controller")
	void EnableGesture(enum LeapGestureType GestureType, bool Enable = true);


	UFUNCTION(BlueprintCallable, Category = "Leap Controller")
	void SetLeapMountToHMDOffset(FVector Offset = FVector(8,0,0));	//default to the leap dk2 offset


	UFUNCTION(BlueprintCallable, meta = (Keywords = "set delegate self"), Category = "Leap Interface")
	void SetInterfaceDelegate(UObject* NewDelegate);

private:
	class LeapControllerPrivate* Private;
	
	UPROPERTY()
	class ULeapFrame* PFrame = nullptr;
};