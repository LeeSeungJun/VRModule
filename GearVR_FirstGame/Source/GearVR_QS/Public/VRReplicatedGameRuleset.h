
#pragma once

#include "AssetData.h"
#include "VRATypes.h"
#include "VRGameRuleset.h"
#include "VRReplicatedGameRuleset.generated.h"


UCLASS()
class UNREALTOURNAMENT_API AVRReplicatedGameRuleset : public AInfo
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Replicated, ReplicatedUsing = GotTag, BlueprintReadOnly, Category = Ruleset)
	FString UniqueTag;

	// Holds a list of Ruleset Categories this rule set should show up in.  This determines which tabs this rule is sorted in to
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	TArray<FName> Categories;

	// Holds the of this rule set.  It will be displayed over the badge
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	FString Title;

	// Holds the description for this Ruleset.  It will be displayed above the rules selection window.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	FString Tooltip;

	// Holds the description for this Ruleset.  It will be displayed above the rules selection window.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	FString Description;
	
	// Holds the maximum # of maps in this map list.  Set to 0 for unlimited.  Epic rulesets will have some of the 
	// the maps preset
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	int32 MaxMapsInList;

	// This is the list of maps that are available to this rule
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	TArray<AVRReplicatedMapInfo*> MapList;

	// The number of players needed to start.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	int32 MinPlayersToStart;

	// The number of players allowed in this match.  
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	int32 MaxPlayers;
	
	// The number of players that is optimal for this rule.  The game will not display maps who optimal player counts are less than this number.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	int32 OptimalPlayers;

	// Holds a string reference to the material to show for this rule's badge
	UPROPERTY(Replicated, ReplicatedUsing = BuildSlateBadge, BlueprintReadOnly, Category = Ruleset)
	FString DisplayTexture;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	uint32 bCustomRuleset:1;

	UPROPERTY()
	TArray<FString> RequiredPackages;

	UPROPERTY(Replicated)
	uint32 bTeamGame:1;

	// Not displayed, this wholes the game type that will be passed to the server via the URL.  
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Ruleset)
	FString GameMode;
	


	// -------------- These are server side only.

	// Hold the ?xxxx options that will be used to start the server.  NOTE: this set of options will be parsed for display.
	UPROPERTY(BlueprintReadOnly, Category = Ruleset)
	FString GameOptions;

	UPROPERTY(BlueprintReadOnly, Category = Ruleset)
	FString DefaultMap;

	UPROPERTY(BlueprintReadOnly, Category = Ruleset)
	TArray<FString> QuickPlayMaps;


	void SetRules(UVRGameRuleset* NewRules, const TArray<FAssetData>& MapAssets);

	UPROPERTY()
	VRexture2D*  BadgeTexture;

#if !UE_SERVER
	FSlateDynamicImageBrush* SlateBadge;
	const FSlateBrush* GetSlateBadge() const;
#endif

	// When the material reference arrives, build the slate texture
	UFUNCTION()
	virtual void BuildSlateBadge();

	UFUNCTION()
	virtual AVRGameMode* GetDefaultGameModeObject();

protected:

	UFUNCTION()
	virtual void GotTag();


	FString Fixup(FString OldText);
	int32 AddMapAssetToMapList(const FAssetData& Asset);
};



