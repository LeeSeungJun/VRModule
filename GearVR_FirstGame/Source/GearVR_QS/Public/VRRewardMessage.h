
#pragma once

#include "VRAnnouncer.h"
#include "VRRewardMessage.generated.h"

UCLASS(CustomConstructor, Abstract)
class UNREALTOURNAMENT_API UVRRewardMessage : public UVRLocalMessage
{
	GENERATED_UCLASS_BODY()

	UVRRewardMessage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		MessageArea = FName(TEXT("DeathMessage"));
		bIsSpecial = true;
		bIsUnique = true;
		bIsConsoleMessage = false;
		Lifetime = 3.0f;
		AnnouncementHS = FName(TEXT("RW_HolyShit"));
		bWantsBotReaction = true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Message)
	FText MessageText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Message)
	FName Announcement;

	/** Announcement on every other message. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Message)
		FName AnnouncementAlt;

	/** Announcement on fifth message. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Message)
		FName AnnouncementFive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Message)
		FName AnnouncementHS;

	virtual FLinearColor GetMessageColor_Implementation(int32 MessageIndex) const override
	{
		return FLinearColor::Red;
	}

	virtual float GetScaleInSize(int32 MessageIndex) const
	{
		return 3.f;
	}

	virtual bool ShouldPlayAnnouncement(const FClientReceiveData& ClientData) const
	{
		return true;
	}
	virtual FName GetAnnouncementName_Implementation(int32 Switch, const UObject* OptionalObject) const override
	{
		if (Switch == 100)
		{
			return AnnouncementHS;
		}
		if ((Switch > 0) && (Switch % 5 == 0) && (AnnouncementFive != NAME_None))
		{
			return AnnouncementFive;
		}
		if ((Switch % 2 == 1) && (AnnouncementAlt != NAME_None))
		{
			return AnnouncementAlt;
		}
		return Announcement;
	}
	virtual FText GetText(int32 Switch, bool bTargetsPlayerState1, class APlayerState* RelatedPlayerState_1, class APlayerState* RelatedPlayerState_2, class UObject* OptionalObject) const override
	{
		return MessageText;
	}
	virtual void PrecacheAnnouncements_Implementation(UVRAnnouncer* Announcer) const override
	{
		Announcer->PrecacheAnnouncement(Announcement);
		Announcer->PrecacheAnnouncement(AnnouncementAlt);
		Announcer->PrecacheAnnouncement(AnnouncementFive);
		Announcer->PrecacheAnnouncement(AnnouncementHS);
	}
};

