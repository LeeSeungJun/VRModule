
#pragma once 

#include "VRHUDWidget.h"
#include "VRScoreboard.generated.h"

USTRUCT()
struct FSelectionObject
{
	GENERATED_USTRUCT_BODY()

	// Holds a reference to PS that is under this score element
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scoreboard")
	TWeakObjectPtr<AVRPlayerState> ScoreOwner;

	// Holds the X1/Y1/X2/Y2 bounds of this score element.  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scoreboard")
	FVector4 ScoreBounds;

	FSelectionObject()
	{
		ScoreOwner.Reset();
		ScoreBounds = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	FSelectionObject(TWeakObjectPtr<AVRPlayerState> inScoreOwner, const FVector4& inScoreBounds)
	{
		ScoreOwner = inScoreOwner;
		ScoreBounds = inScoreBounds;
	}

};

USTRUCT()
struct FStatsFontInfo
{
	GENERATED_USTRUCT_BODY()

	FFontRenderInfo TextRenderInfo;
	float TextHeight;
	UFont* TextFont;
};

UCLASS()
class UNREALTOURNAMENT_API UVRScoreboard : public UVRHUDWidget
{
	GENERATED_UCLASS_BODY()

public:
	// The main drawing stub
	virtual void Draw_Implementation(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnHeaderPlayerX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnHeaderScoreX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnHeaderDeathsX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnHeaderPingX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnHeaderY;

	// The offset of text data within the cell
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnY;

	// The total Height of a given cell
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float CellHeight;

	// How much space in between each column
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float CenterBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float ColumnMedalX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float FooterPosY;

	// Where to draw the flags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	float FlagX;

	virtual void PreDraw(float DeltaTime, AVRHUD* InVRHUDOwner, UCanvas* InCanvas, FVector2D InCanvasCenter);

	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	virtual void AdvancePage(int32 Increment);
	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	virtual void SetPage(int32 NewPage);

	FTimerHandle OpenScoringPlaysHandle;

	/** no-params accessor for timers */
	UFUNCTION()
		virtual void OpenScoringPlaysPage();

	virtual void SetScoringPlaysTimer(bool bEnableTimer);

	/** Show current 2 pages of scoring stats breakdowns. */
	virtual void DrawScoringStats(float RenderDelta, float& YOffset);

	virtual void DrawStatsLeft(float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom);
	virtual void DrawStatsRight(float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom);

	virtual FLinearColor GetPlayerColorFor(AVRPlayerState* InPS) const;
	virtual FString GetPlayerNameFor(AVRPlayerState* InPS) const
	{
		return InPS ? InPS->PlayerName : "";
	};

	UPROPERTY()
		TArray<FText> StatsPageTitles;

	UPROPERTY()
		TArray<FText> StatsPageFooters;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Scoreboard")
	TArray<FVector2D> BadgeNumberUVs;

	UPROPERTY(BlueprintReadOnly, Category = "Scoreboard")
	TArray<FVector2D> BadgeUVs;

	/** number of 'pages' that can be flipped through on the scoreboard */
	UPROPERTY(BlueprintReadOnly, Category = "Scoreboard")
	int32 NumPages;

	UFUNCTION(BlueprintNativeEvent, Category = "Scoreboard")
	void PageChanged();

	UPROPERTY(BlueprintReadOnly, Category = "Scoreboard")
	int32 ActualPlayerCount;

	virtual AVRPlayerState* GetNextScoringPlayer(int32 dir, int32& PSIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	VRexture2D* TextureAtlas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	VRexture2D* FlagAtlas;

	virtual bool ShouldDraw_Implementation(bool bShowScores)
	{
		return bShowScores;
	}

	virtual void DrawGamePanel(float RenderDelta, float& YOffset);
	virtual void DrawGameOptions(float RenderDelta, float& YOffset);

	virtual void DrawTeamPanel(float RenderDelta, float& YOffset);

	virtual void DrawScorePanel(float RenderDelta, float& YOffset);
	virtual void DrawScoreHeaders(float RenderDelta, float& DrawY);
	virtual void DrawPlayerScores(float RenderDelta, float& DrawY);
	virtual void DrawPlayer(int32 Index, AVRPlayerState* PlayerState, float RenderDelta, float XOffset, float YOffset);
	virtual void DrawPlayerScore(AVRPlayerState* PlayerState, float XOffset, float YOffset, float Width, FLinearColor DrawColor);

	virtual void DrawServerPanel(float RenderDelta, float YOffset);

public:
	virtual bool IsInteractive() { return bIsInteractive; };

protected:

	// Will be true when the scoreboard is interactive.  This will cause the
	// scoreboard to track the SelectionStack and display selected items.
	bool bIsInteractive;

	// Holds a list of selectable objects on the scoreboard.  NOTE: this is regenerated every frame
	TArray<FSelectionObject> SelectionStack;

	int32 SelectionHitTest(FVector2D Position);

	FVector2D CursorPosition;

	TWeakObjectPtr<AVRPlayerState> SelectedPlayer;

	//-------------------------------------
	// Scoreboard stats breakdown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float ValueColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float ScoreColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float KillsColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float DeathsColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float ShotsColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
		float AccuracyColumn;

	UPROPERTY()
		bool bHighlightStatsLineTopValue;

	/** List of default weapons to display stats for. */
	UPROPERTY()
	TArray<AVRWeapon *> StatsWeapons;

	/** Index of current top weapon (in kills). */
	UPROPERTY()
		int32 BestWeaponIndex;

	/** Draw one line of scoring breakdown. */
	virtual void DrawStatsLine(FText StatsName, int32 StatValue, int32 ScoreValue, float DeltaTime, float XOffset, float& YPos, const FStatsFontInfo& StatsFontInfo, float ScoreWidth);

	/** Draw one line of scoring breakdown where values are string instead of int32. */
	virtual void DrawTextStatsLine(FText StatsName, FString StatValue, FString ScoreValue, float DeltaTime, float XOffset, float& YPos, const FStatsFontInfo& StatsFontInfo, float ScoreWidth, int32 HighlightIndex);

	virtual void DrawWeaponStatsLine(FText StatsName, int32 StatValue, int32 ScoreValue, int32 Shots, float Accuracy, float DeltaTime, float XOffset, float& YPos, const FStatsFontInfo& StatsFontInfo, float ScoreWidth, bool bIsBestWeapon = false);

	/** Draw individual weapon stats for player. */
	virtual void DrawWeaponStats(AVRPlayerState* PS, float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom, const FStatsFontInfo& StatsFontInfo);

	/** 5coring breakdown for an individual player. */
	virtual void DrawScoreBreakdown(float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom);

	/** Draw gametype specific stat lines for player score breakdown. */
	virtual void DrawPlayerStats(AVRPlayerState* PS, float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom, const FStatsFontInfo& StatsFontInfoL);

	/** Draw reward stat lines for player. */
	virtual void DrawRewardStats(AVRPlayerState* PS, float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom, const FStatsFontInfo& StatsFontInfoL);

	/** Draw movement stat lines for player. */
	virtual void DrawMovementStats(AVRPlayerState* PS, float DeltaTime, float& YPos, float XOffset, float ScoreWidth, float PageBottom, const FStatsFontInfo& StatsFontInfoL);

	//-------------------------------------

public:

	void BecomeInteractive();
	void BecomeNonInteractive();

	// Each time a mouse is moved, then 
	virtual void TrackMouseMovement(FVector2D NewMousePosition);

	// Attempts to select an item in the stack.  Returns true and flags the PS if it succeeds or false and clears all selections if fails.
	virtual bool AttemptSelection(FVector2D SelectionPosition);

	// Clears any selected PS
	virtual void ClearSelection();

	// Finds next selected PRI given an offset
	virtual void SelectNext(int32 Offset, bool bDoNoWrap=false);
	virtual void DefaultSelection(AVRGameState* GS, uint8 TeamIndex = 255);

	virtual void SelectionUp();
	virtual void SelectionDown();
	virtual void SelectionLeft();
	virtual void SelectionRight();
	virtual void SelectionClick();

	virtual float GetDrawScaleOverride();

};

