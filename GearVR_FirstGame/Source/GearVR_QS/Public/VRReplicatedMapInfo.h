
#pragma once

#include "VRATypes.h"
#include "VRPlayerState.h"
#include "VRReplicatedMapInfo.generated.h"

UCLASS()
class UNREALTOURNAMENT_API AVRReplicatedMapInfo : public AInfo
{
	GENERATED_UCLASS_BODY()

	virtual void PreInitializeComponents() override;

	// The weapon
	UPROPERTY(Replicated)
	FString MapPackageName;

	UPROPERTY(Replicated)
	FString MapAssetName;

	UPROPERTY(Replicated)
	FString Title;

	UPROPERTY(Replicated)
	FString AVRhor;

	UPROPERTY(Replicated)
	FString Description;

	UPROPERTY(Replicated)
	int32 OptimalPlayerCount;

	UPROPERTY(Replicated)
	int32 OptimalTeamPlayerCount;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MapScreenshotReference)
	FString MapScreenshotReference;

	UPROPERTY(Replicated)
	FPackageRedirectReference Redirect;

	// What rounds are this weapon available in
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_VoteCount)
	int32 VoteCount;

	bool bNeedsUpdate;

#if !UE_SERVER
	FSlateDynamicImageBrush* MapBrush;
#endif

	UPROPERTY()
	VRexture2D* MapScreenshot;

public:
	void RegisterVoter(AVRPlayerState* Voter);
	void UnregisterVoter(AVRPlayerState* Voter);

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:
	TArray<AVRPlayerState*> VoterRegistry;

	UFUNCTION()
	virtual void OnRep_VoteCount();

	UFUNCTION()
	virtual void OnRep_MapScreenshotReference();

	virtual void PreLoadScreenshot();
	void MapTextureLoadComplete(const FName& InPackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
};



