#pragma once

#include "Core.h"
#include "AnimBone.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API UAnimBone : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Position;


	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FRotator Orientation;


	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Scale;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Length;


	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Alpha;



	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector NextJoint;



	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector PrevJoint;


	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	bool Enabled();


	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetEnabled(bool Enable = true);


	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetFromTransform(const FTransform& Transform);


	UFUNCTION(BlueprintPure, Category = "Anim Bone")
	FTransform GetTransform();


	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void TranslateBone(FVector Shift);



	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void TransformBone(FTransform& ByTransform);
	
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);
};